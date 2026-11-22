

#pragma once

using OUT = long;
using IN = long;

extern "C" OUT syscall(IN number, ...);


constexpr IN IN_exit  = 60;

#include <placement.hh>
