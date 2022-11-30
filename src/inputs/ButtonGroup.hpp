#include <Lifecycle.hpp>
#include <inputs/Button.hpp>

#pragma once

namespace Inputs {
  class ButtonGroup : public Lifecycle
  {
    public:
      ButtonGroup(Button *up = NULL, Button *down = NULL, Button *left = NULL, Button *right = NULL, Button *select = NULL);
      ~ButtonGroup();

      void init(unsigned long ms) override;
      void tick(unsigned long ms) override;
      void message(Message *message) override;

    protected:
      Button  *up;
      Button  *down;
      Button  *left;
      Button  *right;
      Button  *select;
  };
};
