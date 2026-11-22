

#include "opwin.hh"

#define FCOOLMACRO_HEXA 0
#define FCOOLMACRO_FLOAT16 0
#define FCOOLMACRO_FLOAT32 0
#define FCOOLMACRO_FLOAT32X 0
#define FCOOLMACRO_FLOAT64 0
#define FCOOLMACRO_FLOAT64X 0
#define FCOOLMACRO_FLOAT128 0

#include <Fcool/_data.hh>


#pragma once

#if FCOOLMACRO_MEMEXCEPT
void Fcool::_cpu::mem_except( ) {
    MessageBoxA(
        NULL,
        "Fcool -> Memory allocation error!",
        "FCOOL internal Error",
        MB_OK | MB_ICONERROR
    );
    ExitProcess( 1 );
}
#endif


