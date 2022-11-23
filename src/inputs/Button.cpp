#include <inputs/Button.hpp>
#include <Message.hpp>
#include <Root.hpp>

namespace Inputs {
  Button::Button(unsigned long minMsLongPress)
    : Lifecycle()
    , pressedAt(0)
    , isPressed(false)
    , minMsLongPress(minMsLongPress)
  {
  }

  Button::~Button()
  {}

  void Button::init(unsigned long ms)
  {}

  void Button::tick(unsigned long ms)
  {}

  void Button::press(unsigned long ms)
  {
    isPressed = true;
    pressedAt = ms;
  }

  void Button::release(unsigned long ms)
  {
    isPressed = false;
    unsigned long duration = ms - pressedAt;
    pressedAt = 0;

    if (duration >= minMsLongPress) {
      root.publish(new Message(Message::Type::BUTTON_LONGPRESS));
    } else {
      root.publish(new Message(Message::Type::BUTTON_PRESS));
    }
  }
}
