#include <Lifecycle.hpp>
#include <Message.hpp>
#include <outputs/Output.hpp>

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

    virtual const Outputs::Output *getOutput();

  protected:
    virtual void publish(Message *message);

    static Application  *app;
    Message             *messageQueue[APPLICATION_MESSAGE_QUEUE_SIZE];

};
