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

#else /* NATIVE_BUILD */

#include <Arduino.h>

#endif /* NATIVE_BUILD */
