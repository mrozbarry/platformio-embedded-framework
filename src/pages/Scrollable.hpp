#include <pages/Page.hpp>
#include <inputs/Button.hpp>

#pragma once

#ifndef SCROLLABLE_ITEMS_COUNT
#define SCROLLABLE_ITEMS_COUNT  8
#endif

namespace Pages {
  class Scrollable : public Page {
    public:
      Scrollable(uint8_t rows = 4);
      ~Scrollable();

      void show();
      Page::Render *render();

      void tick(unsigned long ms);
      void message(Message *message);
      
      void onButtonPress(Inputs::Button::Press *pressMessage);

      void cursorUp();
      void cursorDown();
    
    protected:
      const uint8_t rows;
      uint8_t       offset;
      uint8_t       cursor;
      char          items[SCROLLABLE_ITEMS_COUNT][9] = {
        "1s Item ",
        "Second  ",
        "10 chars",
        "is not  ",
        "much    ",
        "At least",
        "it will ",
        "looks ok"
      };
      bool          dirty;
  };
};
