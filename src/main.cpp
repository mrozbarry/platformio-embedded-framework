#include <Platform.hpp>
#include <Application.hpp>
#include <Root.hpp>
#include <pages/Scrollable.hpp>
#include <pages/Boot.hpp>
#include <Navigator.hpp>

#ifdef NATIVE_BUILD
#include <ctime>
#endif

void setup()
{
  Application *root = Application::set(new Root());

  root->init(millis());

  root->queue(
    new Navigator::ShowPage(
      // new Pages::Boot(2000)
      new Pages::Scrollable()
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
  srand(time(NULL));
  setup();
  while (true) {
    loop();
    delay(1);
  }
  return 0;
}
#endif
