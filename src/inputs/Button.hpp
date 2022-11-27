#include <Lifecycle.hpp>

#pragma once

namespace Inputs
{
  class Button : public Lifecycle {
    public:
      enum class Type {
        SELECT,
        UP,
        RIGHT,
        DOWN,
        LEFT,
      };

      class ButtonEvent : public Message {
        public:
          ButtonEvent(Button::Type which, Message::Type type);

          bool is(Button::Type which);

          const Button::Type  which;
      };

      class Press : public ButtonEvent {
        public:
          Press(Button::Type type);
      };

      class LongPress : public ButtonEvent {
        public:
          LongPress(Button::Type type);
      };

      Button(Type type, unsigned long minMsLongPress = 300);
      ~Button();

      void init(unsigned long ms);
      void tick(unsigned long ms);

      void press(unsigned long ms);
      void release(unsigned long ms);

    protected:
      void shortPress();
      void longPress();

      const Type    type;
      unsigned long pressedAt;
      bool          isPressed;
      unsigned long minMsLongPress;
  };
};
