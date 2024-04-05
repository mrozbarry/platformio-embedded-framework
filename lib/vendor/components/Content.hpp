#include <components/Base.hpp>


#pragma once

namespace Components {
  class Content : public Base {
    public:
      Content(Base *child)
        : Base()
        , child(child)
      {
      }

      ~Content()
      {
        if (!child) {
          return;
        }
        delete child;
      }

      void render(OutputBuffer &buffer) override
      {
        child->render(buffer);
      }

    protected:
      Base  *child;
  };
};
