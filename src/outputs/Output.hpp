#include <lib/Lifecycle.hpp>
#include <Message.hpp>
#include <Platform.hpp>

#pragma once

#ifndef OUTPUT_WIDTH
#define OUTPUT_WIDTH  20
#endif

#ifndef OUTPUT_HEIGHT
#define OUTPUT_HEIGHT 4
#endif

namespace Outputs {
  class Output : public Lifecycle
  {
    public:
      class Clear : public Message
      {
        public:
          Clear();
      };

      class Write : public Message
      {
        public:
          Write(const char *string, uint8_t length);

          const char *string;
          const uint8_t length;
      };

      class MoveCursor : public Message
      {
        public:
          MoveCursor(uint8_t x, uint8_t y);

          const uint8_t x;
          const uint8_t y;
      };

      Output(uint8_t width = OUTPUT_WIDTH, uint8_t height = OUTPUT_HEIGHT);
      ~Output();

      void init(unsigned long);
      void message(Message *message);

      void onMoveCursor(MoveCursor *moveCursorMessage);
      void onWrite(Write *writeMessage);

      virtual void on();
      virtual void off();
      virtual void clear();
      virtual void moveCursor(uint8_t x, uint8_t y);
      virtual void write(const char *string, uint8_t length);

    protected:
      const uint8_t   width;
      const uint8_t   height;
      uint8_t         cursorX;
      uint8_t         cursorY;
      bool            cursorShow;

  };
};
