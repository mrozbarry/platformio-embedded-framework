#include <pages/Page.hpp>
#include <pages/Home.hpp>
#include <pages/Splash.hpp>
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
          return app()->queue(
            new Inputs::TempSensor::Read(Inputs::TempSensor::Type::INDOOR)
          );
        }

        if (!outdoor) {
          return app()->queue(
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

        updateState([this, resultMsg]() {
          if (resultMsg->which == Inputs::TempSensor::Type::INDOOR) {
            this->indoor = true;
          } else {
            this->outdoor = true;
          }
        });

        if (indoor && outdoor) {
          app()->queue(new Navigator::ShowPage(new Pages::Splash(5000), now + milliseconds));
          return;
        }
      }

      Page::Render *render()
      {
        return Page::Render::output()
          ->move(5, 0)
          ->write("Booting...")
          ->move(1, 2)
          ->write(indoor ? "[X] " : "[ ] ")
          ->write("Indoor sensor")
          ->move(1, 3)
          ->write(outdoor ? "[X] " : "[ ] ")
          ->write("Outdoor sensor");
      }

    private:
      bool          indoor;
      bool          outdoor;
      unsigned long now;
      unsigned long milliseconds;
  };
};
