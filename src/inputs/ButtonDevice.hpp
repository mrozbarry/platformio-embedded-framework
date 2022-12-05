#include <inputs/Button.hpp>

#ifdef NATIVE_BUILD
#include <sys/stat.h>
#include <cerrno>
#endif

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
#ifdef NATIVE_BUILD
      struct stat   deviceStat;
      time_t        lastModifiedAt;
#endif
  };
};
