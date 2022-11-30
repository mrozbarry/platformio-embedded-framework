#include <Lifecycle.hpp>
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
      class Backlight : public Message
      {
        public:
          Backlight(bool toggle);

          const bool  toggle;
      };

      class Cursor : public Message
      {
        public:
          Cursor(bool toggle);

          const bool  toggle;
      };

      class Blink : public Message
      {
        public:
          Blink(bool toggle);

          const bool  toggle;
      };

      class Clear : public Message
      {
        public:
          Clear();
      };

      class Write : public Message
      {
        public:
          Write(const char *string);

          const char *string;
      };

      class Move : public Message
      {
        public:
          Move(uint8_t x, uint8_t y);

          const uint8_t x;
          const uint8_t y;
      };

      Output(uint8_t width = OUTPUT_WIDTH, uint8_t height = OUTPUT_HEIGHT);
      ~Output();

      void init(unsigned long);
      void message(Message *message);

    private:
      void onBacklight(Backlight *backlightMessage);
      void onCursor(Cursor *cursorMessage);
      void onBlink(Blink *blinkMessage);
      void onMove(Move *moveMessage);
      void onWrite(Write *writeMessage);

    public:
      virtual void backlight(bool toggle);
      virtual void cursor(bool toggle);
      virtual void blink(bool toggle);
      virtual void clear();
      virtual void move(uint8_t x, uint8_t y);
      virtual void write(const char *string);

      const uint8_t   width;
      const uint8_t   height;
  };
};
