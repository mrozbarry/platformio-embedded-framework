#include <Message.hpp>

Message::Message(Message::Type type, unsigned long when, bool willBubble)
  : type(type)
  , when(when)
  , isBubbling(willBubble)
{}

bool Message::ready(unsigned long ms)
{
  return ms >= when;
}

bool Message::is(Type type)
{
  return this->type == type;
}

void Message::stopBubbling()
{
  isBubbling = false;
}
