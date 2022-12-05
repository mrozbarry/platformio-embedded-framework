#include <pages/Page.hpp>
#include <pages/Carousel.hpp>
#include <inputs/TempSensor.hpp>
#include <Navigator.hpp>
#include <Application.hpp>

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
        Application::get()->queue(new Navigator::ShowPage(new Carousel(), ms + milliseconds));
      }

    private:
      unsigned long milliseconds;
  };
};
