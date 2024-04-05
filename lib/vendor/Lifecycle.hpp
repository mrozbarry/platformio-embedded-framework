#include <Platform.hpp>
#include <Message.hpp>

#pragma once

class Application;

class Lifecycle
{
  public:
    Lifecycle();
    virtual ~Lifecycle();

    Application *app();

    virtual void init(unsigned long ms);
    virtual void tick(unsigned long ms);
    virtual void message(Message *message);
};
