#include <lib/Lifecycle.hpp>
#include <Message.hpp>
#include <pages/Page.hpp>

#pragma once

namespace Pages {
  class Navigator : public Lifecycle
  {
    public:
      class ShowPage : public Message {
        public:
          ShowPage(Page *page, unsigned long when = 0);
          const Page *page;
      };

      Navigator();
      ~Navigator();

      void showPage(Page *page);

      void init(unsigned long ms);
      void tick(unsigned long ms);
      void render();
      void message(Message *message);

    private:
      Page          *page;
      unsigned long now;
  };
};
