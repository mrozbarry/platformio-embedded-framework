#include <pages/Page.hpp>
#include <Lifecycle.hpp>
#include <inputs/TempSensor.hpp>
#include <Message.hpp>

#pragma once

namespace Pages {
  class Home : public Page
  {
    public:
      Home();

      void message(Message *message);
      void onTempSensorResult(Inputs::TempSensor::Result *resultMessage);

      Page::Render *render();

    protected:
  };
};
