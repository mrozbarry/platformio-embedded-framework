#include <pages/Page.hpp>
#include <pages/Home.hpp>
#include <pages/Navigator.hpp>
#include <inputs/TempSensor.hpp>
#include <Root.hpp>

#pragma once

namespace Pages {
  class Splash : public About {
    public:
      Splash(unsigned long milliseconds)
        : About()
        , milliseconds(milliseconds)
      {}

      ~Splash()
      {}

      void init(unsigned long ms)
      {
        root.publish(new Navigator::ShowPage(new Home(), ms + milliseconds));
      }

    private:
      unsigned long milliseconds;
  };
};
