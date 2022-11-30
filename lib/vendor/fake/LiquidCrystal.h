#pragma once

class LiquidCrystal
{
  public:
    LiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    {}

    ~LiquidCrystal()
    {}

    void begin(uint8_t cols, uint8_t rows) {}
    void display() {}
    void noDisplay() {}
    void cursor() {}
    void noCursor() {}
    void blink() {}
    void noBlink() {}
    void clear() {}
    void home() {}
    void setCursor(uint8_t col, uint8_t row) {}
    void print(const char *text) {}
};
