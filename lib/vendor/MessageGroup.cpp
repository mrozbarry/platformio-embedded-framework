#include <MessageGroup.hpp>

MessageGroup::MessageItem::MessageItem(Message *message) 
    : message(message)
    , next(NULL)
{}

MessageGroup::MessageItem::~MessageItem()
{
    delete message;
    delete next;
}

MessageGroup::MessageItem *MessageGroup::MessageItem::add(Message *message)
{
  next = new MessageItem(message);
  return next;
}

MessageGroup::MessageGroup(Message *firstMessage)
    : Message(Message::Type::MESSAGE_GROUP)
    , first(firstMessage)
{}

MessageGroup::~MessageGroup()
{}

MessageGroup::MessageItem *MessageGroup::add(Message *message)
{
    MessageItem *i = iter();
    while (i->next)
    {
        i = i->next;
    }
    i->next = new MessageItem(message);
    return i->next;
}

MessageGroup::MessageItem *MessageGroup::iter() 
{
    return &first;
}

