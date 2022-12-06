#include <Platform.hpp>

#pragma once

class OutputBuffer {
  public:
    OutputBuffer(uint8_t width, uint8_t height);
    OutputBuffer(OutputBuffer &other, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

    ~OutputBuffer();

    void clear();
    uint8_t print(uint8_t x, uint8_t y, const char *text);

    char *offset(uint8_t x, uint8_t y);

    void debug();

    const uint8_t width;
    const uint8_t height;

  protected:
    bool    isValid;
    char    **buffer;
    bool    ownsBuffer;
};
