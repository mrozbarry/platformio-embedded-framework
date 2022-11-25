#include <Platform.hpp>
#include <Application.hpp>
#include <Root.hpp>
#include <pages/Boot.hpp>
#include <Navigator.hpp>

void setup()
{
  Application *root = Application::set(new Root());

  root->init(millis());

  root->queue(
    new Navigator::ShowPage(
      new Pages::Boot(2000)
    )
  );
}

void loop()
{
  Application *root = Application::get();
  root->handleMessages(millis());
  root->tick(millis());
}

#ifdef NATIVE_BUILD
int main()
{
  setup();
  while (true) {
    loop();
    delay(100);
  }
  return 0;
}
#endif
