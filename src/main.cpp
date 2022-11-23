#include <Platform.hpp>
#include <Root.hpp>
#include <pages/Boot.hpp>

void setup()
{
  root.init(millis());

  root.publishNow(
    new Pages::Navigator::ShowPage(
      new Pages::Boot(2000)
    )
  );
}

void loop()
{
  root.tick(millis());
}

#ifdef NATIVE_BUILD
int main()
{
  setup();
  while (true) {
    loop();
  }
  return 0;
}
#endif
