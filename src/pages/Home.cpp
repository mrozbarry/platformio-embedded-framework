#include <pages/Home.hpp>
#include <outputs/Output.hpp>
#include <Application.hpp>

namespace Pages {

  Home::Home()
    : Page()
  {}

  Page::Render *Home::render()
  {
    return Page::Render::output()
      ->cursor(0, 0)
      ->write("12:00p Mon 24-11-2022", 20)
      ->cursor(0, 1)
      ->write("Set: 00.0", 9)
      ->cursor(0, 2)
      ->write("In:  20.0  0%", 14)
      ->cursor(0, 3)
      ->write("Out: 20.0  0%", 14);
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
    if (resultMessage->which == Inputs::TempSensor::Type::INDOOR) {
      // root.publishNow(new Outputs::Output::MoveCursor(5, 2));
    } else {
      // root.publishNow(new Outputs::Output::MoveCursor(5, 3));
    }

    // char line[14];
    // snprintf(&line[0], 14, "% 2.1f % 2.0f%%", resultMessage->temp, resultMessage->humidity); 
    // root.publishNow(new Outputs::Output::Write(line, 13));
  }
};
