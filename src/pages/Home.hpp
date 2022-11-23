#include <pages/Page.hpp>
#include <lib/Lifecycle.hpp>
#include <inputs/TempSensor.hpp>
#include <Message.hpp>

#pragma once

namespace Pages {
  class Home : public Page
  {
    public:
      Home();

      void init(unsigned long ms);
      void message(Message *message);
      void onTempSensorResult(Inputs::TempSensor::Result *resultMessage);

      void render();

    protected:
  };
};
