#include <MessageGroup.hpp>

MessageGroup::MessageItem::MessageItem(Message *message) 
    : message(message)
    , next(NULL)
{}

MessageGroup::MessageItem::~MessageItem()
{
    delete message;
}

MessageGroup::MessageGroup(Message *firstMessage)
    : Message(Message::Type::MESSAGE_GROUP)
    , first(firstMessage)
{}

MessageGroup::~MessageGroup()
{}

MessageGroup *MessageGroup::add(Message *message)
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

