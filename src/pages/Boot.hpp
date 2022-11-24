#include <pages/Page.hpp>
#include <pages/Home.hpp>
#include <pages/About.hpp>
#include <Navigator.hpp>
#include <inputs/TempSensor.hpp>
#include <Application.hpp>

#pragma once

namespace Pages {
  class Boot : public Page {
    public:
      Boot(unsigned long milliseconds)
        : Page()
        , indoor(false)
        , outdoor(false)
        , now(0)
        , milliseconds(milliseconds)
      {}

      ~Boot()
      {}

      void init(unsigned long ms)
      {
        now = ms;
      }

      void tick(unsigned long ms)
      {
        now = ms;

        if (!indoor) {
          return Application::get()->queue(
            new Inputs::TempSensor::Read(Inputs::TempSensor::Type::INDOOR)
          );
        }

        if (!outdoor) {
          return Application::get()->queue(
            new Inputs::TempSensor::Read(Inputs::TempSensor::Type::OUTDOOR)
          );
        }
      }

      void message(Message *message)
      {
        switch (message->type)
        {
          case Message::Type::TEMP_SENSOR_RESULT:
            return onTempSensorResult((Inputs::TempSensor::Result *)message);

          default:
            break;
        }
      }

      void onTempSensorResult(Inputs::TempSensor::Result *resultMsg)
      {
        if (indoor && outdoor) return;

        if (resultMsg->which == Inputs::TempSensor::Type::INDOOR) {
          // root.publishNow(new Outputs::Output::MoveCursor(2, 2));
          // root.publishNow(new Outputs::Output::Write("X", 1));
          indoor = true;
        } else {
          // root.publishNow(new Outputs::Output::MoveCursor(2, 3));
          // root.publishNow(new Outputs::Output::Write("X", 1));
          outdoor = true;
        }

        if (indoor && outdoor) {
          Application::get()->queue(new Navigator::ShowPage(new Pages::About(), now + milliseconds));
          Application::get()->queue(new Navigator::ShowPage(new Pages::Home(), now + milliseconds + 5000));
          return;
        }
      }

      void render()
      {
        // root.publish(new Outputs::Output::MoveCursor(5, 0));
        // root.publish(new Outputs::Output::Write("Booting...", 10));
        // root.publish(new Outputs::Output::MoveCursor(1, 2));
        // root.publish(new Outputs::Output::Write(indoor ? "[X] " : "[ ] ", 4));
        // root.publish(new Outputs::Output::Write("Indoor sensor", 13));
        // root.publish(new Outputs::Output::MoveCursor(1, 3));
        // root.publish(new Outputs::Output::Write(outdoor ? "[X] " : "[ ] ", 4));
        // root.publish(new Outputs::Output::Write("Outdoor sensor", 14));
      }

    private:
      bool          indoor;
      bool          outdoor;
      unsigned long now;
      unsigned long milliseconds;
  };
};
