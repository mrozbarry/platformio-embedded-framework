#include <Platform.hpp>

#pragma once

class Message
{
  public:
    // Add your custom message types here
    enum class Type {
      NOOP = 0,

      BUTTON_PRESS,
      BUTTON_LONGPRESS,

      NAVIGATE_SHOW_PAGE,

      OUTPUT_CLEAR,
      OUTPUT_MOVE_CURSOR,
      OUTPUT_WRITE,

      TEMP_SENSOR_READ,
      TEMP_SENSOR_RESULT,

      END_OF_TYPES,
    };

    Message(Type type, unsigned long when = 0, bool willBubble = true);

    bool ready(unsigned long ms);

    bool is(Type type);

    void stopBubbling();

    const Message::Type type;
    const unsigned long when;

  private:
    bool  isBubbling;
};
