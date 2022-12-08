#include <outputs/Console.hpp>

#ifdef NATIVE_BUILD
#include <iostream>

namespace Outputs {
  Console::Console(uint8_t width, uint8_t height)
    : Output(width, height)
    , buffer(width, height)
    , dirty(false)
    , cursorX(0)
    , cursorY(0)
    , blinkAt(0)
    , cursorBlinkShow(false)
  {
    buffer.clear();
  }

  Console::~Console()
  {
  }

  void Console::init(unsigned long ms)
  {
    blinkAt = ms + 200;
  }

  void Console::tick(unsigned long ms)
  {
#ifndef DEBUG
    if (ms > blinkAt) {
      cursorBlinkShow = !cursorBlinkShow;
      dirty = true;

      blinkAt = ms + 200;
    }
#endif
    if (!dirty) return;

    // posix/terminal escape for clear/return cursor to top
    // https://stackoverflow.com/a/6487534
#ifndef DEBUG
    std::cout << "\x1B[2J" << "\x1B[H";
#endif

    buffer.debug();

    dirty = false;
  }

  void Console::render(Components::Base &layout)
  {
  }

  void Console::clear()
  {
    buffer.clear();
    dirty = true;
  }
  
  void Console::move(uint8_t x, uint8_t y)
  {
    cursorX = x >= width ? width - 1 : x;
    cursorY = y >= height ? height - 1 : y;
  }
  
  void Console::write(const char *string)
  {
    uint8_t len = buffer.print(cursorX, cursorY, string);
    cursorX += len;
  }
};

#endif
