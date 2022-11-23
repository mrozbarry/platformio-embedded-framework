#include <Root.hpp>
#include <outputs/Console.hpp>
#include <lib/Debug.hpp>

Root::Root()
  : Lifecycle()
  , navigator()
  , output(NULL)
  , indoor(Inputs::TempSensor::Type::INDOOR, 0, 2000)
  , outdoor(Inputs::TempSensor::Type::OUTDOOR, 0, 2000)
{
  for (uint8_t i = 0; i < ROOT_QUEUE_SIZE; i++) {
    queue[i] = NULL;
  }
  output = (Outputs::Output *)new Outputs::Console();
}

Root::~Root()
{
  for (uint8_t i = 0; i < ROOT_QUEUE_SIZE; i++) {
    if (queue[i] == NULL) continue;
    delete queue[i];
  }
  delete output;
}

void Root::init(unsigned long ms)
{
  navigator.init(ms);
  output->init(ms);
  indoor.init(ms);
  outdoor.init(ms);
}

void Root::tick(unsigned long ms)
{
  handleMessages(ms);

  navigator.tick(ms);
  if (output) output->tick(ms);
  indoor.tick(ms);
  outdoor.tick(ms);
}

void Root::publish(Message *message)
{
  if (message == NULL) return;

  for (uint8_t i = 0; i < ROOT_QUEUE_SIZE; i++) {
    if (queue[i] != NULL) continue;
    queue[i] = message;
    return;
  }

  debug("Unable to queue message!");
}

void Root::publishNow(Message *message)
{
  if (message == NULL) return;

  navigator.message(message);
  if (output) output->message(message);
  indoor.message(message);
  outdoor.message(message);

  delete message;
}

void Root::handleMessages(unsigned long ms)
{
  for(uint8_t i = 0; i < ROOT_QUEUE_SIZE; i++) {
    if (queue[i] == NULL) continue;
    if (!queue[i]->ready(ms)) continue;

    publishNow(queue[i]);

    queue[i] = NULL;
  }

  for(uint8_t i = 0; i < ROOT_QUEUE_SIZE; i++) {
    if (queue[i] != NULL) continue;
    for(uint8_t j = i + 1; j < ROOT_QUEUE_SIZE; j++) {
      if (queue[j] == NULL) continue;
      queue[i] = queue[j];
      queue[j] = NULL;
      break;
    }
  }
}

Root root = Root();
