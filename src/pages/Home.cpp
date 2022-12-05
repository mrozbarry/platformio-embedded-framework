#include <pages/Home.hpp>
#include <outputs/Output.hpp>
#include <Application.hpp>

namespace Pages {

  Home::Home()
    : Page()
  {}

  void Home::init(unsigned long ms)
  {
    Application::get()->queue(new Inputs::TempSensor::Read(Inputs::TempSensor::Type::ANY, false));
  }

  Page::Render *Home::render()
  {
    return Page::Render::output()
      ->move(0, 0)
      ->write("12:00p    24-11-2022")
      ->move(0, 1)
      ->write("Set: 00.0C")
      ->move(0, 2)
      ->write("In: ")
      ->write(&indoor[0])
      ->move(0, 3)
      ->write("Out:")
      ->write(&outdoor[0]);
  }

  void Home::message(Message *message) {
    switch (message->type) {
      case Message::Type::TEMP_SENSOR_RESULT:
        return onTempSensorResult((Inputs::TempSensor::Result *)message);

      default:
        break;
    }
  }

  void Home::onTempSensorResult(Inputs::TempSensor::Result *resultMessage)
  {
    switch (resultMessage->which)
    {
      case Inputs::TempSensor::Type::INDOOR:
        updateState([this, &resultMessage]() {
          this->setReading(&this->indoor[0], resultMessage->temp, resultMessage->humidity);
        });
        break;

      case Inputs::TempSensor::Type::OUTDOOR:
        updateState([this, &resultMessage]() {
          this->setReading(&this->outdoor[0], resultMessage->temp, resultMessage->humidity);
        });

      default:
        break;
    }

  }

  int Home::setReading(char *str, float temp, float humidity)
  {
#ifdef NATIVE_BUILD
    int length = snprintf(str, HOME_SEGMENT_LENGTH, "%3.2fC %2.0f%%", temp, humidity);
#else
    char tempStr[6];
    char humStr[4];
    dtostrf(temp, 2, 1, &tempStr[0]);
    dtostrf(humidity, 2, 0, &humStr[0]);
    int length = snprintf(str, HOME_SEGMENT_LENGTH, "%sC %s%%", tempStr, humStr);
#endif
    if (str[0] == '+') {
      str[0] = ' ';
    }
    return length;
  }
};
