#include <pages/About.hpp>
#include <outputs/Output.hpp>

#include <Root.hpp>

namespace Pages
{
  About::About()
    : Page()
  {}

  void About::render()
  {
    root.publish(new Outputs::Output::Clear());
    root.publish(new Outputs::Output::MoveCursor(3, 1));
    root.publish(new Outputs::Output::Write("Starting App", 12));
    root.publish(new Outputs::Output::MoveCursor(7, 2));
    root.publish(new Outputs::Output::Write("v1.0.0", 6));
  }
}
