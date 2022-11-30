#include <inputs/TempSensor.hpp>
#include <Application.hpp>

#ifdef NATIVE_BUILD
#include <cstdlib>
#include <algorithm>
#endif

namespace Inputs {
  TempSensor::TempSensor(TempSensor::Type type, unsigned long readThrottle = 2000)
    : Lifecycle()
    , type(type)
    , now(0)
    , readThrottle(readThrottle)
    , nextReadAt(0)
    , temp(16.0f)
    , humidity(20.0f)
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

  bool TempSensor::read()
  {
    if (!canRead()) {
      return false;
    }

#ifdef NATIVE_BUILD
    float tempIncrement = ((((float)(rand() % 10)) / 10.0f) - 0.5f) / 2.0f;
    float humidityIncrement = ((((float)(rand() % 10)) / 10.0f) - 0.5f) / 2.0f;
#else
    float tempIncrement = 0.01f;
    float humidityIncrement = 0.002f;
#endif

    temp = std::min(
      std::max(
        temp + tempIncrement,
        -30.0f
      ),
      40.0f
    );
    humidity = std::min(
      std::max(
        humidity + humidityIncrement,
        10.0f
      ),
      90.0f
    );
    nextReadAt = now + readThrottle;
    return true;
  }

  void TempSensor::init(unsigned long ms)
  {
    now = ms;
    nextReadAt = now + readThrottle;
  }

  void TempSensor::tick(unsigned long ms)
  {
    now = ms;

    if (read())
    {
      Application::get()->queue(
        new TempSensor::Result(type, temp, humidity)
      );
    }
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

    read();

    Application::get()->queue(new TempSensor::Result(type, temp, humidity));
  }
};
