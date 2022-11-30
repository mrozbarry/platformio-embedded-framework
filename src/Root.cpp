#include <Root.hpp>
#include <Navigator.hpp>
#include <outputs/Console.hpp>
#include <inputs/TempSensor.hpp>
#include <inputs/ButtonGroup.hpp>
#include <inputs/ButtonDevice.hpp>

Root::Root()
  : Application()
{
  eachItem([this](Lifecycle *item, unsigned int i) {
      this->items[i] = NULL;
  });

  this->items[0] = new Navigator();
#ifdef NATIVE_BUILD
  this->items[1] = new Outputs::Console();
#else
  this->items[1] = new Outputs::Lcd();
#endif
  this->items[2] = new Inputs::TempSensor(Inputs::TempSensor::Type::INDOOR, 2000);
  this->items[3] = new Inputs::TempSensor(Inputs::TempSensor::Type::OUTDOOR, 2000);
#ifdef NATIVE_BUILD
  this->items[4] = new Inputs::ButtonGroup(
    new Inputs::ButtonDevice(Inputs::Button::Type::UP, "./dev/btn-up/press"),
    new Inputs::ButtonDevice(Inputs::Button::Type::DOWN, "./dev/btn-down/press"),
    new Inputs::ButtonDevice(Inputs::Button::Type::LEFT, "./dev/btn-left/press"),
    new Inputs::ButtonDevice(Inputs::Button::Type::RIGHT, "./dev/btn-right/press"),
    new Inputs::ButtonDevice(Inputs::Button::Type::SELECT, "./dev/btn-select/press")
  );
#else
#endif
}

Root::~Root()
{
  eachItem([](Lifecycle *item, unsigned int i) {
    delete item;
  });
}

void Root::init(unsigned long ms)
{
  eachItem([&ms](Lifecycle *item, unsigned int i) {
    item->init(ms);
  });
}

void Root::tick(unsigned long ms)
{
  eachItem([&ms](Lifecycle *item, unsigned int i) {
    item->tick(ms);
  });
}

void Root::publish(Message *message)
{
  if (message == NULL) return;

  eachItem([message](Lifecycle *item, unsigned int i) {
    item->message(message);
  });
}
