#include <components/Base.hpp>
#include <Platform.hpp>

#pragma once

namespace Components {
  class Text : public Base {
    public:
      enum class Align {
        LEFT = 0,
        CENTER,
        RIGHT
      };

      Text(const char *text, Align align = Align::LEFT)
        : Base()
        , text(text)
        , length(strlen(text))
        , align(align)
      {}

      virtual ~Text()
      {}

      void render(OutputBuffer &buffer) override
      {
        uint8_t x, y;
        switch (align) {
          case Align::LEFT:
            buffer.print(0, 0, text);
            break;

          case Align::CENTER:
            buffer.print((int8_t)(buffer.width / 2) - (int8_t)(length / 2), 0, text);
            break;

          case Align::RIGHT:
            buffer.print((int8_t)buffer.width - (int8_t)length, 0, text);
            break;
        }
      }

    protected:
      const char    *text;
      const uint8_t length;
      const Align   align;
  };
};
