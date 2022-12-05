#include <inputs/ButtonDevice.hpp>

#ifdef NATIVE_BUILD
#include <sys/stat.h>
#include <cerrno>
#include <iostream>

namespace Inputs
{
  ButtonDevice::ButtonDevice(Button::Type type, const char *device, bool willShortPress)
    : Button(type)
    , device(device)
    , willShortPress(willShortPress)
    , lastModifiedAt(0)
  {}

  ButtonDevice::~ButtonDevice()
  {
  }

  void ButtonDevice::init(unsigned long ms)
  {
    updateLastModifiedAt();
  }

  void ButtonDevice::tick(unsigned long ms)
  {
    time_t  previous = lastModifiedAt;

    updateLastModifiedAt();

    if (previous == lastModifiedAt) return;

    if (willShortPress) {
      shortPress();
    } else {
      longPress();
    }
  }

  void ButtonDevice::updateLastModifiedAt()
  {
    if (stat(device, &deviceStat)) {
      std::cerr << "Unable to stat device" << std::endl << device << std::endl << std::strerror(errno) << std::endl;
    } else {
      lastModifiedAt = deviceStat.st_ctime;
    }
  }
};
#endif
