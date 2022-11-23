#include <Platform.hpp>
#include <Message.hpp>

#pragma once

class Lifecycle
{
  public:
    Lifecycle();
    ~Lifecycle();

    virtual void init(unsigned long ms);
    virtual void tick(unsigned long ms);
    virtual void message(Message *message);
};
