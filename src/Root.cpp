#include <Root.hpp>
#include <outputs/Console.hpp>

Root::Root()
  : Application()
{
  this->items[0] = new Navigator();
  this->items[1] = new Outputs::Console();
  this->items[2] = new Inputs::TempSensor(Inputs::TempSensor::Type::INDOOR, 2000);
  this->items[3] = new Inputs::TempSensor(Inputs::TempSensor::Type::OUTDOOR, 2000);
  this->items[4] = new Inputs::ButtonDevice(Inputs::Button::Type::UP, "./dev/btn-up/press");
  this->items[5] = new Inputs::ButtonDevice(Inputs::Button::Type::DOWN, "./dev/btn-down/press");
  this->items[6] = new Inputs::ButtonDevice(Inputs::Button::Type::LEFT, "./dev/btn-left/press");
  this->items[7] = new Inputs::ButtonDevice(Inputs::Button::Type::RIGHT, "./dev/btn-right/press");
  this->items[8] = new Inputs::ButtonDevice(Inputs::Button::Type::SELECT, "./dev/btn-select/press");
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
