
#if !__has_include(<windows.h>)
#error "windows.h is required but was not found"
#endif

#include <windows.h>

#pragma once


// Use the default Windows heap for memory allocation and deallocation.
inline void* operator new( SIZE_T size ) noexcept {
    void* ptr = HeapAlloc( GetProcessHeap( ), HEAP_ZERO_MEMORY, size );
    if ( !ptr ) {
        return nullptr;
    }
    return ptr;
}

inline void operator delete( void* ptr ) noexcept {
    if ( ptr ) {
        HeapFree( GetProcessHeap( ), 0, ptr );
    }
}

inline void operator delete( void* ptr, SIZE_T ) noexcept {
    if ( ptr ) {
        HeapFree( GetProcessHeap( ), 0, ptr );
    }
}

inline void* operator new[]( SIZE_T size ) noexcept {
    void* ptr = HeapAlloc( GetProcessHeap( ), HEAP_ZERO_MEMORY, size );
    if ( !ptr ) {
        return nullptr;
    }
    return ptr;
}

inline void operator delete[]( void* ptr ) noexcept {
    if ( ptr ) {
        HeapFree( GetProcessHeap( ), 0, ptr );
    }
}

inline void operator delete[]( void* ptr, SIZE_T ) noexcept {
    if ( ptr ) {
        HeapFree( GetProcessHeap( ), 0, ptr );
    }
}

inline void* operator new( SIZE_T size, std::align_val_t alignment ) noexcept {
    void* ptr = _aligned_malloc( size, static_cast<SIZE_T>( alignment ) );
    if ( !ptr ) {
        return nullptr;
    }
    return ptr;
}

inline void operator delete( void* ptr, std::align_val_t ) noexcept {
    if ( ptr ) {
        _aligned_free( ptr );
    }
}

inline void* operator new[]( SIZE_T size, std::align_val_t alignment ) noexcept {
    void* ptr = _aligned_malloc( size, static_cast<SIZE_T>( alignment ) );
    if ( !ptr ) {
        return nullptr;
    }
    return ptr;
}

inline void operator delete[]( void* ptr, std::align_val_t ) noexcept {
    if ( ptr ) {
        _aligned_free( ptr );
    }
}

inline void* operator new( SIZE_T, void* ptr ) noexcept {
    return ptr;
}

inline void operator delete( void*, void* ) noexcept {
    // No operation needed for placement delete.
}

