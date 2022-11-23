#include <lib/Lifecycle.hpp>

#pragma once

namespace Inputs
{
  class Button : public Lifecycle {
    public:
      Button(unsigned long minMsLongPress = 300);
      ~Button();

      void init(unsigned long ms);
      void tick(unsigned long ms);

      void press(unsigned long ms);
      void release(unsigned long ms);

    protected:
      unsigned long pressedAt;
      bool isPressed;
      unsigned long minMsLongPress;
  };
};
