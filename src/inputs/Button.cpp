#include <inputs/Button.hpp>
#include <Message.hpp>
#include <Application.hpp>

namespace Inputs {
  Button::Button(Button::Type type, unsigned long minMsLongPress)
    : Lifecycle()
    , type(type)
    , pressedAt(0)
    , isPressed(false)
    , minMsLongPress(minMsLongPress)
  {
  }

  Button::~Button()
  {}

  Button::ButtonEvent::ButtonEvent(Button::Type which, Message::Type type)
    : Message(type)
    , which(which)
  {}

  bool Button::ButtonEvent::is(Button::Type which)
  {
    return this->which == which;
  }

  Button::Press::Press(Button::Type which)
    : ButtonEvent(which, Message::Type::BUTTON_PRESS)
  {}

  Button::LongPress::LongPress(Button::Type which)
    : ButtonEvent(which, Message::Type::BUTTON_LONGPRESS)
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
    pressedAt = 0;

    return ((ms - pressedAt) >= minMsLongPress)
      ? longPress()
      : shortPress();
  }

  void Button::shortPress()
  {
    Application::get()->queue(new Press(type));
  }

  void Button::longPress()
  {
    Application::get()->queue(new LongPress(type));
  }
}
