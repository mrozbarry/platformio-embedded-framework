#include <Root.hpp>
#include <outputs/Console.hpp>
#include <debug/Debug.hpp>

Root::Root()
  : Application()
  , navigator()
  , output(NULL)
  , indoor(Inputs::TempSensor::Type::INDOOR, 2000)
  , outdoor(Inputs::TempSensor::Type::OUTDOOR, 2000)
{
  output = (Outputs::Output *)new Outputs::Console();
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
}

void Root::tick(unsigned long ms)
{
  navigator.tick(ms);
  if (output) output->tick(ms);
  indoor.tick(ms);
  outdoor.tick(ms);
}

void Root::publish(Message *message)
{
  if (message == NULL) return;

  navigator.message(message);
  if (output) output->message(message);
  indoor.message(message);
  outdoor.message(message);
}
