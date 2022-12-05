#include <pages/Page.hpp>
#include <inputs/Button.hpp>

#pragma once

#ifndef PAGES_CAROUSEL_COUNT
#define PAGES_CAROUSEL_COUNT  3
#endif

namespace Pages {
  class Carousel : public Page
  {
    public:
      Carousel();
      ~Carousel();

      void init(unsigned long ms) override;
      void tick(unsigned long ms) override;
      void message(Message *msg) override;
      bool willUpdate(unsigned long ms) override;

      void next();
      void prev();
      void toggleCanRotate(bool toggle);

      void onButtonPress(Inputs::Button::Press *buttonPressMessage);

    protected:
      int  pageIndex;
      Page *pages[PAGES_CAROUSEL_COUNT];
      bool canRotate;
  };
};
