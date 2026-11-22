

#include "fcoolwin.hh"



inline DWORD fwh_printA( const HANDLE console, UINT CP, const void* text, DWORD write ) noexcept
{
    SetConsoleOutputCP( CP );
    DWORD r = 0;
    WriteConsoleA(
        console,
        text, write,
        &r,NULL
    );
    return r;
}
inline DWORD fwh_printW( const HANDLE console, const void* text, DWORD write ) noexcept
{
    DWORD r = 0;
    WriteConsoleW(
        console,
        text, write,
        &r, NULL
    );
    return r;
}




