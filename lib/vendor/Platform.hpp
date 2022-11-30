#pragma once

#ifdef NATIVE_BUILD
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <string>
#include <chrono>
#include <thread>

#ifndef String
#define String std::string
#endif

#ifndef delay
#define delay(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms)) 
#endif

#ifndef millis
unsigned long millis();
#endif

#ifndef NATIVE_OR_EMBEDDED
#define NATIVE_OR_EMBEDDED(native, embedded)  native
#endif

#else /* NATIVE_BUILD */

#include <Arduino.h>

#ifndef NATIVE_OR_EMBEDDED
#define NATIVE_OR_EMBEDDED(native, embedded)  embedded
#endif

#endif /* NATIVE_BUILD */

