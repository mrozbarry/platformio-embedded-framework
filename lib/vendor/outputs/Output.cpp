#include <outputs/Output.hpp>

namespace Outputs {

  Output::Output(uint8_t width, uint8_t height)
    : Lifecycle()
    , width(width)
    , height(height)
  {}

  Output::~Output()
  {}

  Output::Backlight::Backlight(bool toggle)
    : Message(Message::Type::OUTPUT_BACKLIGHT)
    , toggle(toggle)
  {}

  Output::Cursor::Cursor(bool toggle)
    : Message(Message::Type::OUTPUT_CURSOR)
    , toggle(toggle)
  {}

  Output::Blink::Blink(bool toggle)
    : Message(Message::Type::OUTPUT_BLINK)
    , toggle(toggle)
  {}

  Output::Clear::Clear()
    : Message(Message::Type::OUTPUT_CLEAR)
  {}

  Output::Write::Write(const char *string)
    : Message(Message::Type::OUTPUT_WRITE)
    , string(string)
  {}

  Output::Move::Move(uint8_t x, uint8_t y)
    : Message(Message::Type::OUTPUT_MOVE)
    , x(x)
    , y(y)
  {}

  void Output::init(unsigned long ms)
  {
    backlight(true);
  }

  void Output::message(Message *message)
  {
    switch (message->type)
    {
      case Message::Type::OUTPUT_BACKLIGHT:
        return onBacklight((Output::Backlight *)message);

      case Message::Type::OUTPUT_CURSOR:
        return onCursor((Output::Cursor *)message);

      case Message::Type::OUTPUT_BLINK:
        return onBlink((Output::Blink *)message);

      case Message::Type::OUTPUT_CLEAR:
        return clear();

      case Message::Type::OUTPUT_WRITE:
        return onWrite((Output::Write *)message);

      case Message::Type::OUTPUT_MOVE:
        return onMove((Output::Move *)message);

      default:
        return;
    }
  }

  void Output::render(Components::Base &layout)
  {}

  void Output::onBacklight(Backlight *backlightMessage)
  {
    backlight(backlightMessage->toggle);
  }

  void Output::onCursor(Cursor *cursorMessage)
  {
    cursor(cursorMessage->toggle);
  }

  void Output::onBlink(Blink *blinkMessage)
  {
    blink(blinkMessage->toggle);
  }

  void Output::onMove(Move *moveMessage)
  {
    move(moveMessage->x, moveMessage->y);
  }

  void Output::onWrite(Write *writeMessage)
  {
    write(writeMessage->string);
  }

  void Output::backlight(bool toggle)
  {}

  void Output::cursor(bool toggle)
  {}

  void Output::blink(bool toggle)
  {}

  void Output::clear()
  {}

  void Output::write(const char *string)
  {}

  void Output::move(uint8_t x, uint8_t y)
  {}
};
