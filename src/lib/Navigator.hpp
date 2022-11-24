#include <lib/Lifecycle.hpp>
#include <Message.hpp>
#include <pages/Page.hpp>

#pragma once

class Navigator : public Lifecycle
{
  public:
    class ShowPage : public Message {
      public:
        ShowPage(Pages::Page *page, unsigned long when = 0);
        const Pages::Page *page;
    };

    Navigator();
    ~Navigator();

    void showPage(Pages::Page *page);

    void init(unsigned long ms);
    void tick(unsigned long ms);
    void message(Message *message);

    void onShowPage(ShowPage *showPageMessage);

  private:
    Pages::Page          *page;
    unsigned long now;
};
