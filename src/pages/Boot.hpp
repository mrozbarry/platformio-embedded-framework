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
        Page::tick(ms);

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
          updateState([this]() {
            this->indoor = true;
          });
        } else {
          updateState([this]() {
            this->outdoor = true;
          });
        }

        if (indoor && outdoor) {
          Application::get()->queue(new Navigator::ShowPage(new Pages::About(), now + milliseconds));
          Application::get()->queue(new Navigator::ShowPage(new Pages::Home(), now + milliseconds + 5000));
          return;
        }
      }

      Page::Render *render()
      {
        return Page::Render::output()
          ->cursor(5, 0)
          ->write("Booting...", 10)
          ->cursor(1, 2)
          ->write(indoor ? "[X] " : "[ ] ", 4)
          ->write("Indoor sensor", 13)
          ->cursor(1, 3)
          ->write(outdoor ? "[X] " : "[ ] ", 4)
          ->write("Outdoor sensor", 14);
      }

    private:
      bool          indoor;
      bool          outdoor;
      unsigned long now;
      unsigned long milliseconds;
  };
};
