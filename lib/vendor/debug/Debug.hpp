#pragma once

#if NATIVE_BUILD && DEBUG

#include <iostream>
#ifndef debug
#define debug(val) std::cout << val << std::endl
#endif

#else

#ifndef debug
#define debug(val)
#endif

#endif
