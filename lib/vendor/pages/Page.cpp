#include <pages/Page.hpp>
#include <outputs/Output.hpp>
#include <Application.hpp>

namespace Pages {
  Page::Page()
    : Lifecycle()
    , isMounted(false)
    , isDirty(true)
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
    render->group = new MessageGroup(new Outputs::Output::Clear());
    return render;
  }

  Page::Render *Page::Render::update()
  {
    Page::Render *render = new Page::Render();
    render->group = new MessageGroup(new Outputs::Output::Move(0, 0));
    return render;
  }

  Page::Render *Page::Render::move(uint8_t x, uint8_t y)
  {
    group->add(new Outputs::Output::Move(x, y));
    return this;
  }

  Page::Render *Page::Render::write(const char *text)
  {
    group->add(new Outputs::Output::Write(text));
    return this;
  }

  Page::Render *Page::Render::write(const char character)
  {
    const char str[2] = {character, 0};
    return write((const char *)&str[0]);
  }

  void Page::show()
  {
    isMounted = true;
  }

  void Page::hide()
  {
    isMounted = false;
  }

  Page::Render *Page::render()
  {
    return Page::Render::nothing();
  }

  void Page::tick(unsigned long ms)
  {
    if (willUpdate(ms)) {
      Page::Render *rendered = render();
      if (rendered) {
        Application::get()->queue(rendered->group);
        isDirty = false;
      }
    }
  }

  bool Page::willUpdate(unsigned long ms)
  {
    return isDirty;
  }
};
