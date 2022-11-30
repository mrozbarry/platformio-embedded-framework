#include <outputs/Lcd.hpp>

namespace Outputs {
  Lcd::Lcd()
    : Output(LCD_COLS, LCD_ROWS)
    , _lcd(LCD_PIN_RS, LCD_PIN_ENABLE, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7)
  {
    _lcd.begin(width, height);
    backlight(true);
    cursor(false);
    blink(false);
    clear();
  }

  Lcd::~Lcd()
  {
  }

  void Lcd::backlight(bool toggle)
  {
    if (toggle) {
      _lcd.display();
    } else {
      _lcd.noDisplay();
    }
  }

  void Lcd::cursor(bool toggle)
  {
    if (toggle) {
      _lcd.cursor();
    } else {
      _lcd.noCursor();
    }
  }

  void Lcd::blink(bool toggle)
  {
    if (toggle) {
      _lcd.blink();
    } else {
      _lcd.noBlink();
    }
  }

  void Lcd::clear()
  {
    _lcd.clear();
    _lcd.home();
  }
  
  void Lcd::move(uint8_t x, uint8_t y)
  {
    _lcd.setCursor(x, y);
  }
  
  void Lcd::write(const char *string)
  {
    _lcd.print(string);
  }
};
