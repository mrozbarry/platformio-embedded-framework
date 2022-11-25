#include <Lifecycle.hpp>
#include <MessageGroup.hpp>

#pragma once

namespace Pages {
  class Page : public Lifecycle
  {
    public:
      class Render
      {
        public:
          Render();
          ~Render();

          static Render *nothing();
          static Render *output();
          static Render *update();

          Render *cursor(uint8_t x, uint8_t y);
          Render *write(const char *text, unsigned length);

          MessageGroup  *group;
      };

      Page();
      virtual ~Page();

      virtual void show();
      virtual void hide();
      virtual Render *render();

      void tick(unsigned long ms) override;

      virtual bool willUpdate(unsigned long ms);

      template<typename Functor>
      void updateState(Functor updateFn)
      {
        updateFn();
        isDirty = true;
      }

    protected:
      bool    isMounted;
      bool    isDirty;
  };
};
