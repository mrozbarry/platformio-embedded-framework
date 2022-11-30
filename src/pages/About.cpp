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
      ->move(3, 1)
      ->write("Starting app")
      ->move(7, 2)
      ->write("v1.0.0");
  }
}
