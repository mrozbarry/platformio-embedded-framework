#include <Navigator.hpp>
#include <pages/Page.hpp>

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

Navigator::ShowPage::ShowPage(Pages::Page *page, unsigned long when)
  : Message(Message::Type::NAVIGATE_SHOW_PAGE, when)
  , page(page)
{}

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

void Navigator::message(Message *message)
{
  if (!message->is(Message::Type::NAVIGATE_SHOW_PAGE)) {
    if (page) {
      page->message(message);
    }
    return;
  }
  message->stopBubbling();

  onShowPage((Navigator::ShowPage *)message);
}

void Navigator::onShowPage(Navigator::ShowPage *showPageMessage)
{
  if (page != NULL) {
    page->hide();
    delete page;
    page = NULL;
  }

  if (showPageMessage->page == NULL) {
    return;
  }

  page = (Pages::Page *)showPageMessage->page;
  page->init(now);
  page->show();
}
