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
      void moveCursor(uint8_t x, uint8_t y);
      void write(const char *string, uint8_t length);

    protected:
      void drawBar();

      char  **buffer;
      bool  dirty;
  };
};
