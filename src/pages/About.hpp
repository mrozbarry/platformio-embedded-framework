#include <pages/Page.hpp>

#pragma once

namespace Pages
{
  class About : public Page
  {
    public:
      About();

      Page::Render *render();
  };
};
