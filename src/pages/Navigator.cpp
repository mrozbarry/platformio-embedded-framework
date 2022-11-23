#include <pages/Navigator.hpp>
#include <pages/Page.hpp>
#include <lib/Debug.hpp>
#include <Root.hpp>

namespace Pages {
  Navigator::Navigator()
    : Lifecycle()
    , page(NULL)
    , now(0)
  {}

  Navigator::~Navigator()
  {
    if (page != NULL) {
      delete page;
    }
  }

  Navigator::ShowPage::ShowPage(Page *page, unsigned long when)
    : Message(Message::Type::NAVIGATE_PAGE, when)
    , page(page)
  {}

  void Navigator::showPage(Page *page)
  {
    root.publish(new Navigator::ShowPage(page));
  }

  void Navigator::init(unsigned long ms)
  {
    now = ms;
  }

  void Navigator::tick(unsigned long ms)
  {
    now = ms;
    if (page == NULL) return;
    page->tick(ms);
  }

  void Navigator::render()
  {
    if (page == NULL) return;
    page->render();
  }

  void Navigator::message(Message *message)
  {
    if (!message->is(Message::Type::NAVIGATE_PAGE)) {
      if (page) {
        page->message(message);
      }
      return;
    }
    message->stopBubbling();

    const Navigator::ShowPage *msg = (const Navigator::ShowPage*)message;

    if (page != NULL) {
      page->hide();
      delete page;
      page = NULL;
    }

    if (msg->page == NULL) {
      return;
    }

    page = (Page *)msg->page;
    page->init(now);
    page->show();
  }
};
