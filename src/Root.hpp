#include <Application.hpp>
#include <Message.hpp>
#include <Navigator.hpp>
#include <outputs/Output.hpp>
#include <inputs/TempSensor.hpp>
#include <inputs/ButtonDevice.hpp>

#pragma once

#ifndef ROOT_ITEM_COUNT
#define ROOT_ITEM_COUNT 9
#endif

class Root : public Application
{
  public:
    Root();
    ~Root();

    void init(unsigned long ms) override;
    void tick(unsigned long ms) override;

  protected:
    void publish(Message *message) override;

    template<typename Functor>
    void eachItem(Functor func, bool skipNull = true)
    {
      for(unsigned int i = 0; i < ROOT_ITEM_COUNT; i++) {
        if (skipNull && items[i] == NULL) continue;
        func(items[i], i);
      }
    }

    Lifecycle             *items[ROOT_ITEM_COUNT];
};
