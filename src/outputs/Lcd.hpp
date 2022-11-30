#include <outputs/Output.hpp>

#ifndef NATIVE_BUILD
#include <LiquidCrystal.h>
#else
#include <fake/LiquidCrystal.h>
#endif

#pragma once

#ifndef LCD_COLS
#define LCD_COLS  16
#endif

#ifndef LCD_ROWS
#define LCD_ROWS  2
#endif

#ifndef LCD_PIN_RS
#define LCD_PIN_RS  0
#endif

#ifndef LCD_PIN_ENABLE
#define LCD_PIN_ENABLE  0
#endif

#ifndef LCD_PIN_D4
#define LCD_PIN_D4  0
#endif

#ifndef LCD_PIN_D5
#define LCD_PIN_D5  0
#endif

#ifndef LCD_PIN_D6
#define LCD_PIN_D6  0
#endif

#ifndef LCD_PIN_D7
#define LCD_PIN_D7  0
#endif

namespace Outputs {
  class Lcd : public Output
  {
    public:
      Lcd();
      ~Lcd();

      void backlight(bool toggle) override;
      void cursor(bool toggle) override;
      void blink(bool toggle) override;
      void clear() override;
      void move(uint8_t x, uint8_t y) override;
      void write(const char *string) override;

    private:
      LiquidCrystal   _lcd;
  };
};
