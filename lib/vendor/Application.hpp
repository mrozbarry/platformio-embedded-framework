#include <Lifecycle.hpp>
#include <Message.hpp>

#pragma once

#ifndef APPLICATION_MESSAGE_QUEUE_SIZE
#define APPLICATION_MESSAGE_QUEUE_SIZE 10
#endif

class Application : public Lifecycle
{
  public:
    static Application *get();
    static Application *set(Application *newApplication);

    Application();
    ~Application();

    void queue(Message *message);
    void handleMessages(unsigned long ms);

  protected:
    static Application  *app;

    virtual void publish(Message *message);

    Message             *messageQueue[APPLICATION_MESSAGE_QUEUE_SIZE];

};

