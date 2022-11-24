#include <pages/Scrollable.hpp>
#include <outputs/Output.hpp>
#include <Root.hpp>

namespace Pages {
  Scrollable::Scrollable(uint8_t rows)
    : Page()
    , rows(rows)
    , offset(0)
    , cursor(0)
    , dirty(true)
  {
  }

  Scrollable::~Scrollable()
  {}

  void Scrollable::show()
  {
  }

  void Scrollable::render()
  {
    root.publishNow(new Outputs::Output::Clear());

    for (unsigned int i = 0; i < 4; i++) {
      unsigned int index = offset + i;
      if (index >= SCROLLABLE_ITEMS_COUNT) break;

      root.publish(new Outputs::Output::MoveCursor(0, i));
      root.publish(new Outputs::Output::Write(cursor == i ? ">" : " ", 1));
      root.publish(new Outputs::Output::Write(items[index], 9));
    }
  }

  void Scrollable::tick(unsigned long ms)
  {
    if (dirty) {
      render();
      dirty = false;
    }
  }

  void Scrollable::message(Message *message)
  {
    switch (message->type) {
      case Message::Type::BUTTON_PRESS:
        return onButtonPress((Inputs::Button::Press *)message);

      default:
        break;
    }
  }

  void Scrollable::onButtonPress(Inputs::Button::Press *pressMessage)
  {
    switch (pressMessage->which) {
      case Inputs::Button::Type::UP:
        return cursorUp();

      case Inputs::Button::Type::DOWN:
        return cursorDown();

      default:
        break;
    }
  }

  void Scrollable::cursorUp()
  {
    dirty = true;
    if (cursor == 0) {
      offset = offset == 0
        ? offset
        : offset - 1;

      return;
    }

    cursor--;
  }

  void Scrollable::cursorDown()
  {
    dirty = true;
    if (cursor == (rows - 1)) {
      offset = offset == SCROLLABLE_ITEMS_COUNT - rows - 1
        ? offset
        : offset + 1;

      return;
    }

    cursor++;
  }
};
