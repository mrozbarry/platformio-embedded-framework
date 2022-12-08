#include <outputs/Output.hpp>
#include <OutputBuffer.hpp>

#pragma once

namespace Outputs {
  class Console : public Output
  {
    public:
      Console(uint8_t width = OUTPUT_WIDTH, uint8_t height = OUTPUT_HEIGHT);
      virtual ~Console();

      void init(unsigned long ms) override;
      void tick(unsigned long ms) override;
      void render(Components::Base &layout) override;

      void clear() override;
      void move(uint8_t x, uint8_t y) override;
      void write(const char *string) override;

    protected:
      OutputBuffer  buffer;
      bool          dirty;

      uint8_t       cursorX;
      uint8_t       cursorY;
      char          cursorOver;
      unsigned long blinkAt;
      bool          cursorBlinkShow;
  };
};
