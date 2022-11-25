#include <pages/Page.hpp>
#include <Lifecycle.hpp>
#include <inputs/TempSensor.hpp>
#include <Message.hpp>

#pragma once

#ifndef HOME_SEGMENT_LENGTH
#define HOME_SEGMENT_LENGTH 11
#endif

namespace Pages {
  class Home : public Page
  {
    public:
      Home();

      void init(unsigned long ms) override;

      Page::Render *render() override;

      void message(Message *message) override;
      void onTempSensorResult(Inputs::TempSensor::Result *resultMessage);

    protected:
      int setReading(char *str, float temp, float humidity);

      char indoor[HOME_SEGMENT_LENGTH];
      char outdoor[HOME_SEGMENT_LENGTH];
  };
};
