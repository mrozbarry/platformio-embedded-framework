#include <Platform.hpp>

#ifdef NATIVE_BUILD
unsigned long millis()
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
#endif
