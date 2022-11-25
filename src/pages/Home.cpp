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
      ->cursor(0, 0)
      ->write("12:00p    24-11-2022", 20)
      ->cursor(0, 1)
      ->write("Set: 00.0C", 10)
      ->cursor(0, 2)
      ->write("In: ", 4)
      ->write(&indoor[0], 13)
      ->cursor(0, 3)
      ->write("Out:", 4)
      ->write(&outdoor[0], 13);
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
    int length = snprintf(str, HOME_SEGMENT_LENGTH, "%+4.1fC %2.0f%%", temp, humidity);
    if (str[0] == '+') {
      str[0] = ' ';
    }
    return length;
  }
};
