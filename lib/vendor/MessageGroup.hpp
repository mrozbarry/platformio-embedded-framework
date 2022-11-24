#include <Message.hpp>

#pragma once

class MessageGroup : public Message
{
  public:
    class MessageItem {
      public:
        MessageItem(Message *message, MessageItem *prev);
        ~MessageItem();

        MessageItem *next;

        const Message *message;
    }

    MessageGroup(Message *firstMessage);
    ~MessageGroup();

    MessageGroup *add(Message *message);
    MessageItem *iter();

  protected:
    MessageItem   first;
}
