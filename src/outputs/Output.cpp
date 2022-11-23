#include <outputs/Output.hpp>

namespace Outputs {

  Output::Output(uint8_t width, uint8_t height)
    : Lifecycle()
    , width(width)
    , height(height)
  {}

  Output::~Output()
  {}

  Output::Clear::Clear()
    : Message(Message::Type::OUTPUT_CLEAR)
  {}

  Output::Write::Write(const char *string, uint8_t length)
    : Message(Message::Type::OUTPUT_WRITE)
    , string(string)
    , length(length)
  {}

  Output::MoveCursor::MoveCursor(uint8_t x, uint8_t y)
    : Message(Message::Type::OUTPUT_MOVE_CURSOR)
    , x(x)
    , y(y)
  {}

  void Output::init(unsigned long ms)
  {
    on();
  }

  void Output::message(Message *message)
  {
    switch (message->type)
    {
      case Message::Type::OUTPUT_CLEAR:
        return clear();

      case Message::Type::OUTPUT_WRITE:
        return onWrite((Output::Write *)message);

      case Message::Type::OUTPUT_MOVE_CURSOR:
        return onMoveCursor((Output::MoveCursor *)message);

      default:
        return;
    }
  }

  void Output::onMoveCursor(MoveCursor *moveCursorMessage)
  {
    return moveCursor(moveCursorMessage->x, moveCursorMessage->y);
  }

  void Output::onWrite(Write *writeMessage)
  {
    return write(writeMessage->string, writeMessage->length);
  }

  void Output::on()
  {}

  void Output::off()
  {}

  void Output::clear()
  {}

  void Output::write(const char *string, uint8_t length)
  {}

  void Output::moveCursor(uint8_t x, uint8_t y)
  {}
};
