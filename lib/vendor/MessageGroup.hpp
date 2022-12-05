#include <Message.hpp>

#pragma once

class MessageGroup : public Message
{
  public:
    class MessageItem {
      public:
        MessageItem(Message *message);
        ~MessageItem();

        MessageItem *add(Message *message);

        const Message *message;

        MessageItem *next;
    };

    MessageGroup(Message *firstMessage);
    ~MessageGroup();

    MessageItem *add(Message *message);
    MessageItem *iter();

  protected:
    MessageItem   first;
};
