#include <components/Base.hpp>

#pragma once

namespace Components {
  class Rows : public Base {
    public:
      Rows(Base *a, Base *b)
        : Base()
        , count(2)
        , children(new Base*[2])
      {
        children[0] = a;
        children[1] = b;
      }

      Rows(Base *a, Base *b, Base *c)
        : Base()
        , count(3)
        , children(new Base*[3])
      {
        children[0] = a;
        children[1] = b;
        children[2] = c;
      }

      Rows(Base *a, Base *b, Base *c, Base *d)
        : Base()
        , count(4)
        , children(new Base*[4])
      {
        children[0] = a;
        children[1] = b;
        children[2] = c;
        children[3] = d;
      }

      ~Rows()
      {
        eachChild([](Base *child, unsigned int i) {
          delete child;
        });
        delete[] children;
      }

      template<typename Func>
      void eachChild(Func func)
      {
        for(unsigned int i = 0; i < count; i++) {
          func(children[i], i);
        }
      }

      void render(OutputBuffer &buffer) override
      {
        eachChild([this, &buffer](Base *child, unsigned int i) {
          if (i >= buffer.height) return;

          OutputBuffer subBuffer = OutputBuffer(buffer, 0, i, buffer.width, 1);
          child->render(subBuffer);
        });
      }

    protected:
      unsigned int  count;
      Base          **children;
  };
};
