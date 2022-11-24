#include <pages/Page.hpp>
#include <outputs/Output.hpp>

namespace Pages {
  Page::Page()
    : Lifecycle()
    , isMounted(false)
  {}

  Page::~Page()
  {}

  Page::Render::Render()
    : group(NULL)
  {}

  Page::Render::~Render()
  {
    if (group) delete group;
  }

  Page::Render *Page::Render::nothing()
  {
    return NULL;
  }

  Page::Render *Page::Render::output()
  {
    Page::Render *render = new Page::Render();
    group = new MessageGroup(new Outputs::Output::Clear());
    return render;
  }
  Page::Render *Page::Render::cursor(uint8_t x, uint8_t y)
  {
    group->add(new Outputs::Output::Cursor(x, y));
    return this;
  }

  Page::Render *Page::Render::write(const char *text, unsigned int length)
  {
    group->add(new Outputs::Output::Write(text, length));
    return this;
  }

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

  void Page::tick(unsigned long ms)
  {
    if (willUpdate(ms)) {
      Page::Render *rendered = render();
      if (rendered) {
        Application::get()->queue(rendered->group);
      }
    }
  }

  bool Page::willUpdate(unsigned long ms)
  {
    return true;
  }
};
