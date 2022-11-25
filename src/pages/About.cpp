#include <pages/About.hpp>
#include <outputs/Output.hpp>

#include <Application.hpp>

namespace Pages
{
  About::About()
    : Page()
  {}

  Page::Render *About::render()
  {
    return Page::Render::output()
      ->cursor(3, 1)
      ->write("Starting app", 12)
      ->cursor(7, 2)
      ->write("v1.0.0", 6);
  }
}
