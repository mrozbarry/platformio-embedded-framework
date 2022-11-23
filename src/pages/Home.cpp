#include <pages/Home.hpp>
#include <outputs/Output.hpp>
#include <Root.hpp>
#include <lib/Debug.hpp>

namespace Pages {

  Home::Home()
    : Page()
  {}

  void Home::render()
  {
    root.publish(new Outputs::Output::MoveCursor(0, 0));
    root.publish(new Outputs::Output::Write("0X:XXp Tue 00-XXX-22", 20));
    root.publish(new Outputs::Output::MoveCursor(0, 1));
    root.publish(new Outputs::Output::Write("Set: 19.0", 9));
    root.publish(new Outputs::Output::MoveCursor(0, 2));
    root.publish(new Outputs::Output::Write("In:  20.0  0%", 14));
    root.publish(new Outputs::Output::MoveCursor(0, 3));
    root.publish(new Outputs::Output::Write("Out: -4.0  0%", 14));
  }

  void Home::init(unsigned long ms)
  {
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
      root.publishNow(new Outputs::Output::MoveCursor(5, 2));
    } else {
      root.publishNow(new Outputs::Output::MoveCursor(5, 3));
    }

    char line[14];
    snprintf(&line[0], 14, "% 2.1f % 2.0f%%", resultMessage->temp, resultMessage->humidity); 
    root.publishNow(new Outputs::Output::Write(line, 13));
  }
};
