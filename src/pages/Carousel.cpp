#include <pages/Carousel.hpp>

#include <pages/Home.hpp>
#include <pages/Scrollable.hpp>
#include <pages/About.hpp>

namespace Pages {
  Carousel::Carousel()
    : Page()
    , pageIndex(0)
    , canRotate(true)
  {
    pages[0] = new Home();
    pages[1] = new Scrollable();
    pages[2] = new About();
  }

  Carousel::~Carousel()
  {
    for (unsigned int i = 0; i < PAGES_CAROUSEL_COUNT; i++) {
      if (pages[i] == NULL) continue;
      delete pages[i];
    }
  }
  
  void Carousel::init(unsigned long ms)
  {
    if (pages[pageIndex]) {
      pages[pageIndex]->show();
    }
  }

  void Carousel::tick(unsigned long ms)
  {
    if (pages[pageIndex]) {
      pages[pageIndex]->tick(ms);
    }
    Page::tick(ms);
  }

  void Carousel::message(Message *msg)
  {
    switch (msg->type)
    {
      case Message::Type::BUTTON_PRESS:
        onButtonPress((Inputs::Button::Press *)msg);
        break;

      default:
        break;
    }
    if (pages[pageIndex]) {
      pages[pageIndex]->message(msg);
    }
  }

  bool Carousel::willUpdate(unsigned long ms)
  {
    return (pages[pageIndex] != NULL ? pages[pageIndex]->willUpdate(ms) : false) || Page::willUpdate(ms);
  }

  void Carousel::next()
  {
    if (!canRotate) return;

    if (pages[pageIndex]) {
      pages[pageIndex]->hide();
    }
    updateState([this]() {
      this->pageIndex = (this->pageIndex + 1) % PAGES_CAROUSEL_COUNT;
    });
    if (pages[pageIndex]) {
      pages[pageIndex]->show();
    }
  }

  void Carousel::prev()
  {
    if (!canRotate) return;

    if (pages[pageIndex]) {
      pages[pageIndex]->hide();
    }
    updateState([this]() {
      this->pageIndex = (((this->pageIndex * -1) - 1) % PAGES_CAROUSEL_COUNT) * -1;
    });
    if (pages[pageIndex]) {
      pages[pageIndex]->show();
    }
  }

  void Carousel::toggleCanRotate(bool toggle)
  {
    canRotate = toggle;
  }

  void Carousel::onButtonPress(Inputs::Button::Press *msg)
  {
    switch (msg->which)
    {
      case Inputs::Button::Type::LEFT:
        prev();
        break;

      case Inputs::Button::Type::RIGHT:
        next();
        break;

      default:
        break;
    }
  }
};
