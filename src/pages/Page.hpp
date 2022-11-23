#include <lib/Lifecycle.hpp>

#pragma once

namespace Pages {
  class Page : public Lifecycle
  {
    public:
      Page();
      virtual ~Page();

      virtual void show();
      virtual void hide();
      virtual void render();

    protected:
      bool    isMounted;
  };
};
