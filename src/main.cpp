#include <Platform.hpp>
#include <Application.hpp>
#include <Root.hpp>
#include <pages/Scrollable.hpp>
#include <pages/Boot.hpp>
#include <Navigator.hpp>

#include <OutputBuffer.hpp>
#include <components/Columns.hpp>
#include <components/Rows.hpp>
#include <components/Text.hpp>

#ifdef NATIVE_BUILD
#include <ctime>
#endif

void setup()
{
  Application *root = Application::set(new Root());

  root->init(millis());

  root->queue(
    new Navigator::ShowPage(
      new Pages::Boot(2000)
      // new Pages::Scrollable()
    )
  );
}

void loop()
{
  Application *root = Application::get();

  root->handleMessages(millis());
  root->tick(millis());

  delay(100);
}

#ifdef NATIVE_BUILD
int main()
{
  //OutputBuffer buffer = OutputBuffer(20, 4);
  //Components::Rows layout = Components::Rows(
  //    new Components::Columns(
  //      new Components::Text("Lft", Components::Text::Align::LEFT),
  //      new Components::Text("Mid", Components::Text::Align::CENTER),
  //      new Components::Text("Rgt", Components::Text::Align::RIGHT)
  //    ),
  //    new Components::Text("Long and centered", Components::Text::Align::CENTER)
  //);
  //layout.render(buffer);
  //buffer.debug();
  //return 0;

  srand(time(NULL));
  setup();
  while (true) {
    loop();
    delay(1);
  }
  return 0;
}
#endif
