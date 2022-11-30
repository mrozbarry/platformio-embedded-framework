#include <outputs/Output.hpp>

#pragma once

namespace Outputs {
  class Console : public Output
  {
    public:
      Console(uint8_t width = OUTPUT_WIDTH, uint8_t height = OUTPUT_HEIGHT);
      ~Console();

      void tick(unsigned long ms);

      void clear();
      void move(uint8_t x, uint8_t y);
      void write(const char *string);

    protected:
      void drawBar();

      char    **buffer;
      bool    dirty;

      uint8_t cursorX;
      uint8_t cursorY;
  };
};
