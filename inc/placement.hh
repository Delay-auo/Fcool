
#pragma once

#include <Fcool/__fcool.hh>

inline void* operator new(Fcool::size_t, void* p) noexcept {
    return p;
}

inline void operator delete(void*, void*) noexcept {}




