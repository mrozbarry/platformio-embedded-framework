#include <Lifecycle.hpp>
#include <Message.hpp>

#pragma once

namespace Inputs {
  class TempSensor : public Lifecycle
  {
    public:
      enum class Type {
        INDOOR,
        OUTDOOR,
        ANY,
      };

      class Read : public Message
      {
        public:
          Read(TempSensor::Type which, bool onlyPublishNew = false);

          const TempSensor::Type  which;
          const bool onlyPublishNew;

          bool isFor(TempSensor *sensor);
      };

      class Result : public Message
      {
        public:
          Result(TempSensor::Type which, float temp, float humidity);

          const TempSensor::Type  which;
          const float temp;
          const float humidity;
      };

      TempSensor(TempSensor::Type type, uint8_t pin, unsigned long readThrottle);
      ~TempSensor();

      bool canRead();
      void read(bool onlyPublishNew);

      void init(unsigned long ms);
      void tick(unsigned long ms);
      void message(Message *message);

      void onRead(Read *readMessage);

    protected:
      Type          type;
      uint8_t       pin;
      unsigned long now;
      unsigned long readThrottle;
      unsigned long nextReadAt;
      float         temp;
      float         humidity;
      bool          hasBeenReadAtLeastOnce;
  };
};
