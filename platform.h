#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef OS_MAC
#include "include_macos/fdf.h"
#else
#include "include/fdf.h"
#endif

#endif
