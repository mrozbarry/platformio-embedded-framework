#include <components/Base.hpp>


#pragma once

namespace Components {
  class Columns : public Base {
    public:
      Columns(Base *a, Base *b)
        : Base()
        , count(2)
        , children(new Base*[2])
      {
        children[0] = a;
        children[1] = b;
      }

      Columns(Base *a, Base *b, Base *c)
        : Base()
        , count(3)
        , children(new Base*[3])
      {
        children[0] = a;
        children[1] = b;
        children[2] = c;
      }
      Columns(Base *a, Base *b, Base *c, Base *d)
        : Base()
        , count(4)
        , children(new Base*[4])
      {
        children[0] = a;
        children[1] = b;
        children[2] = c;
        children[3] = d;
      }

      ~Columns()
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
        unsigned int width = buffer.width / count;
        unsigned int remainder = buffer.width - (width * count);
        unsigned int offset = 0;
        eachChild([this, &buffer, &width, &remainder, &offset](Base *child, unsigned int i) {
          unsigned int w = width;
          if (remainder > 0) {
            w += 1;
            remainder -= 1;
          }
          OutputBuffer subBuffer = OutputBuffer(buffer, offset, 0, w, buffer.height);
          child->render(subBuffer);
          offset += w;
        });
      }

    protected:
      unsigned int  count;
      Base          **children;
  };
};
