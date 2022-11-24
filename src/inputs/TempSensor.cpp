#include <inputs/TempSensor.hpp>
#include <Application.hpp>

namespace Inputs {
  TempSensor::TempSensor(TempSensor::Type type, uint8_t pin, unsigned long readThrottle = 2000)
    : Lifecycle()
    , type(type)
    , pin(pin)
    , now(0)
    , readThrottle(readThrottle)
    , nextReadAt(0)
    , temp(0.0f)
    , humidity(0.0f)
    , hasBeenReadAtLeastOnce(false)
  {}

  TempSensor::~TempSensor()
  {}

  TempSensor::Read::Read(TempSensor::Type which, bool onlyPublishNew)
    : Message(Message::Type::TEMP_SENSOR_READ)
    , which(which)
    , onlyPublishNew(onlyPublishNew)
  {}

  bool TempSensor::Read::isFor(TempSensor *sensor)
  {
    return which == TempSensor::Type::ANY || which == sensor->type;
  }

  TempSensor::Result::Result(TempSensor::Type which, float temp, float humidity)
    : Message(Message::Type::TEMP_SENSOR_RESULT)
    , which(which)
    , temp(temp)
    , humidity(humidity)
  {}

  bool TempSensor::canRead()
  {
    return now >= nextReadAt;
  }

  void TempSensor::read(bool onlyPublishNew)
  {
    if (!canRead() && onlyPublishNew) return;

    if (canRead()) {
      temp += 0.01f;
      humidity = 40.0f;
      nextReadAt = now + readThrottle;
      hasBeenReadAtLeastOnce = true;
    }

    if (!hasBeenReadAtLeastOnce) return;

    Application::get()->queue(new TempSensor::Result(type, temp, humidity));
  }

  void TempSensor::init(unsigned long ms)
  {
    now = ms;
    nextReadAt = now + readThrottle;
  }

  void TempSensor::tick(unsigned long ms)
  {
    now = ms;

    if (!canRead()) return;

    read(true);
  }

  void TempSensor::message(Message *message)
  {
    switch (message->type)
    {
      case Message::Type::TEMP_SENSOR_READ:
        return onRead((TempSensor::Read *)message);

      default:
        break;
    }
  }

  void TempSensor::onRead(TempSensor::Read *readMessage)
  {
    if (!readMessage->isFor(this)) return;

    read(readMessage->onlyPublishNew);
  }
};
