#include <pages/Scrollable.hpp>
#include <outputs/Output.hpp>
#include <Application.hpp>

namespace Pages {
  Scrollable::Scrollable(uint8_t rows)
    : Page()
    , rows(rows)
    , offset(0)
    , selected(0)
  {
  }

  Scrollable::~Scrollable()
  {}

  void Scrollable::show()
  {
  }

  Page::Render *Scrollable::render()
  {
    Page::Render *render = Render::output();

    for (unsigned int i = 0; i < 4; i++) {
      unsigned int index = offset + i;
      if (index >= SCROLLABLE_ITEMS_COUNT) break;

      render 
        ->move(0, i)
        ->write(i == selected ? ">" : " ")
        ->write(items[index]);
    }

    return render;
  }

  void Scrollable::tick(unsigned long ms)
  {
    Page::tick(ms);
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
    updateState([this]() {
      if (selected == 0) {
        this->offset = this->offset == 0
          ? this->offset
          : this->offset - 1;

        return;
      }

      this->selected--;
    });

  }

  void Scrollable::cursorDown()
  {
    updateState([this]() {
      if (this->selected == (this->rows - 1)) {
        this->offset = this->offset == SCROLLABLE_ITEMS_COUNT - this->rows
          ? this->offset
          : this->offset + 1;

        return;
      }

      this->selected++;
    });
  }
};
