#include <pages/Page.hpp>
#include <outputs/Output.hpp>
#include <lib/Debug.hpp>
#include <Root.hpp>

namespace Pages {
  Page::Page()
    : Lifecycle()
    , isMounted(false)
  {}

  Page::~Page()
  {}

  void Page::show()
  {
    isMounted = true;
  }

  void Page::hide()
  {
    isMounted = false;
  }

  void Page::render()
  {}
};
