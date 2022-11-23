#include <iostream>

#include <outputs/Console.hpp>

namespace Outputs {
  Console::Console(uint8_t width, uint8_t height)
    : Output(width, height)
    , buffer(NULL)
    , dirty(false)
  {
    buffer = new char*[height];
    for (uint8_t y = 0; y < height; y++) {
      buffer[y] = new char[width];
    }
    clear();
  }

  Console::~Console()
  {
    if (buffer == NULL) return;

    for(uint8_t row = 0; row < height; row++) {
      if (buffer[row] == NULL) continue;
      delete[] buffer[row];
      buffer[row] = NULL;
    }
    delete[] buffer;
  }

  void Console::tick(unsigned long ms)
  {
    if (!dirty) return;

    // posix/terminal escape for clear/return cursor to top
    // https://stackoverflow.com/a/6487534
    std::cout << "\x1B[2J\x1B[H";

    drawBar();
    for (uint8_t r = 0; r < height; r++) {
      std::cout << '|';
      for (uint8_t c = 0; c < width; c++) {
        std::cout << buffer[r][c];
      }
      std::cout << '|' << std::endl;
    }
    drawBar();

    dirty = false;
  }

  void Console::clear()
  {
    for(uint8_t row = 0; row < height; row++) {
      buffer[row][width] = 0;
      for(uint8_t col = 0; col < width; col++) {
        buffer[row][col] = ' ';
      }
    }
    dirty = true;
  }
  
  void Console::moveCursor(uint8_t x, uint8_t y)
  {
    cursorX = x >= width ? width - 1 : x;
    cursorY = y >= height ? height - 1 : y;
  }
  
  void Console::write(const char *string, uint8_t length)
  {
    uint8_t startX = cursorX;
    for (uint8_t i = 0; i < length; i++) {
      uint8_t c = startX + i;
      if (c >= width) {
        cursorY += 1;
        cursorX = 0;
      }
      if (cursorY >= height) {
        cursorY = 0;
      }
      if (string[i] == 0) break;

      cursorX = c;
      if (buffer[cursorY][cursorX] == string[i]) continue;

      buffer[cursorY][cursorX] = string[i];
      dirty = true;
    }
  }

  void Console::drawBar()
  {
    std::cout << '+';
    for (uint8_t x = 0; x < width; x++) {
      std::cout << '-';
    }
    std::cout << '+' << std::endl;
  }
};
