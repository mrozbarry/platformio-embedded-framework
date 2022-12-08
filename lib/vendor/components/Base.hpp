#include <OutputBuffer.hpp>

#pragma once

namespace Components {
  class Base {
    public:
      Base()
      {}

      virtual ~Base()
      {}

      virtual void render(OutputBuffer &buffer)
      {}
  };
};
