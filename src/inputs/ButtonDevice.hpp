#include <inputs/Button.hpp>
#include <sys/stat.h>
#include <cerrno>

#pragma once

namespace Inputs
{
  class ButtonDevice : public Button {
    public:
      ButtonDevice(Button::Type type, const char *device, bool willShortPress = true);
      ~ButtonDevice();

      void init(unsigned long ms);
      void tick(unsigned long ms);

    protected:
      void updateLastModifiedAt();

      const char    *device;
      bool          willShortPress;
      struct stat   deviceStat;
      time_t        lastModifiedAt;
  };
};
