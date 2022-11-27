#include <Root.hpp>
#include <outputs/Console.hpp>

Root::Root()
  : Application()
  , navigator()
  , output(new Outputs::Console())
  , indoor(Inputs::TempSensor::Type::INDOOR, 2000)
  , outdoor(Inputs::TempSensor::Type::OUTDOOR, 2000)
  , down(Inputs::Button::Type::DOWN, "./dev/btn-down/press")
{
}

Root::~Root()
{
  delete output;
}

void Root::init(unsigned long ms)
{
  navigator.init(ms);
  if (output) output->init(ms);
  indoor.init(ms);
  outdoor.init(ms);
  down.init(ms);
}

void Root::tick(unsigned long ms)
{
  navigator.tick(ms);
  if (output) output->tick(ms);
  indoor.tick(ms);
  outdoor.tick(ms);
  down.tick(ms);
}

void Root::publish(Message *message)
{
  if (message == NULL) return;

  navigator.message(message);
  if (output) output->message(message);
  indoor.message(message);
  outdoor.message(message);
  down.message(message);
}
