

#include <win/fcoolwin.hh>
#include <Fcool/sync.hh>


namespace Fcool::sync
{
    struct fwh_thread_data
    {
        Thread::Func func;
        Thread::ArgFunc argfunc;
        Thread::Arg arg;
    };
    inline DWORD WINAPI fwh_thread_func( LPVOID parameter ) noexcept
    {
        fwh_thread_data* data = static_cast<fwh_thread_data*>( parameter );
        if ( data == nullptr )
            return 0;
        if ( data->func != nullptr )
            data->func( );
        delete data;
        return 0;
    }
    inline DWORD WINAPI fwh_thread_argfunc( LPVOID parameter ) noexcept
    {
        fwh_thread_data* data = static_cast<fwh_thread_data*>( parameter );
        if ( data == nullptr )
            return 0;
        if ( data->argfunc != nullptr )
            data->argfunc( data->arg );
        delete data;
        return 0;
    }
    //
    bool is_loaded( ) noexcept { return pass; }
    bool hard_reload( bool& stable ) noexcept { stable = pass; return pass; }
    bool soft_reload( bool& stable ) noexcept { stable = pass; return pass; }
    bool unload( ) noexcept { return pass; }
    //
    capability::_cap_t capability::get_all( ) noexcept
    {
        return
            _cap::MultiThreading |
            _cap::MutexLocks |
            _cap::Sleeping |
            _cap::Waiting |
            _cap::Unix |
            _cap::Local;
    }
    //
    Thread::~Thread( ) noexcept
    {
        HANDLE handle = static_cast<HANDLE>( static_cast<void*>( impl ) );
        if ( handle != nullptr && handle != INVALID_HANDLE_VALUE )
            CloseHandle( handle );
        impl = nullptr;
    }
    //
    Thread::Thread( Func func ) noexcept
    : impl(nullptr)
    {
        if ( func == nullptr )
            return;
        fwh_thread_data* data = new fwh_thread_data{
            func,
            nullptr,
            zero
        };
        if ( data == nullptr )
            return;
        HANDLE handle = CreateThread(
            nullptr,
            zero,
            fwh_thread_func,
            data,
            zero,
            nullptr
        );
        if ( handle == nullptr || handle == INVALID_HANDLE_VALUE ) {
            delete data;
            return;
        }
        impl = reinterpret_cast<void*>( handle );
    }
    //
    Thread::Thread( ArgFunc func ) noexcept
    : impl(nullptr)
    {
        if ( func == nullptr )
            return;
        fwh_thread_data* data = new fwh_thread_data{
            nullptr,
            func,
            zero
        };
        if ( data == nullptr )
            return;
        HANDLE handle = CreateThread(
            nullptr,
            zero,
            fwh_thread_argfunc,
            data,
            zero,
            nullptr
        );
        if ( handle == nullptr || handle == INVALID_HANDLE_VALUE ) {
            delete data;
            return;
        }
        impl = reinterpret_cast<void*>( handle );
    }
    //
    bool Thread::sleep( _time::duration_fast duration ) {
        _time::__prec_t ms = duration.get_millisecs( );
        constexpr DWORD max_sleep_time = INFINITE - unit;
        while ( ms > max_sleep_time ) {
            Sleep( max_sleep_time );
            ms -= max_sleep_time;
        }
        Sleep( static_cast<DWORD>(ms) );
        return pass;
    }
    //
    Thread::Lock::Lock( ) noexcept
    : impl( new CRITICAL_SECTION ) {
        InitializeCriticalSection(
            static_cast<LPCRITICAL_SECTION>(
                _mem::cast<CRITICAL_SECTION>( impl )
            )
        );
    }
    Thread::Lock::~Lock( ) noexcept {
        DeleteCriticalSection(
            static_cast<LPCRITICAL_SECTION>(
                _mem::cast<CRITICAL_SECTION>( impl )
            )
        );
    }
    void Thread::Lock::lock( ) {
        EnterCriticalSection(
            static_cast<LPCRITICAL_SECTION>(
                _mem::cast<CRITICAL_SECTION>( impl )
            )
        );
    }
    bool Thread::Lock::try_lock( ) {
        return TryEnterCriticalSection(
            static_cast<LPCRITICAL_SECTION>(
                _mem::cast<CRITICAL_SECTION>( impl )
            )
        );
    }
    void Thread::Lock::unlock( ) {
        LeaveCriticalSection(
            static_cast<LPCRITICAL_SECTION>(
                _mem::cast<CRITICAL_SECTION>( impl )
            )
        );
    }
    //
    bool wait_for( Thread thread ) noexcept {
        HANDLE original = static_cast<HANDLE>( static_cast<void*>( thread.impl ) );
        if ( original == nullptr || original == INVALID_HANDLE_VALUE )
            return fail;
        HANDLE duplicate = nullptr;
        if (
            DuplicateHandle(
                GetCurrentProcess( ),
                original,
                GetCurrentProcess( ),
                &duplicate,
                zero,
                FALSE,
                DUPLICATE_SAME_ACCESS
            ) == 0
        )
            return fail;

        thread.impl = reinterpret_cast<void*>( duplicate );
        return WaitForSingleObject( duplicate, INFINITE ) == WAIT_OBJECT_0;
    }
    //
    bool wait_for( _time::duration_fast duration ) noexcept {
        HANDLE timer = CreateWaitableTimer( NULL, TRUE, NULL );
        if ( timer == NULL )
            return fail;
        LARGE_INTEGER time;
        time.QuadPart = -static_cast<LONGLONG>( duration.get_nanosecs( ) / 100ULL );
        if ( SetWaitableTimer( timer, &time, zero, NULL, NULL, FALSE ) ) {
            _time::__prec_t ms = duration.get_millisecs( );
            return (
                WaitForSingleObject( timer, ms > INFINITE ? INFINITE : static_cast<DWORD>(ms) )
                != WAIT_FAILED
            ) && CloseHandle( timer );
        } else {
            CloseHandle( timer );
            return fail;
        }
    }
    //
    inline ULONGLONG fwh_get_ticks( ) noexcept {
        FILETIME filetime;
        GetSystemTimePreciseAsFileTime( &filetime );
        ULARGE_INTEGER ticks;
        ticks.LowPart = filetime.dwLowDateTime;
        ticks.HighPart = filetime.dwHighDateTime;
        return ticks.QuadPart;
    }
    constexpr ULONGLONG fwh_unix_epoch = 116444736000000000ULL;
    //
    bool clock_wait_unix( _time::duration_prec target ) noexcept {
        constexpr _time::duration_fast max_chunk = _time::secs( 4294967U );
        for ( ;; ) {
            const _time::duration_prec now = clock_now_unix( );
            if ( now >= target )
                return pass;
            const _time::duration_prec remaining = target - now;
            const _time::duration_fast remaining_fast( remaining );
            if ( !Thread::sleep(
                remaining_fast > max_chunk ? max_chunk : remaining_fast
            ) )
                return fail;
        }
    }
    //
    bool clock_wait_local( _time::duration_prec target ) noexcept {
        for ( ;; ) {
            const _time::duration_prec now = clock_now_local( );
            if ( now >= target )
                return pass;
            const _time::duration_prec remaining = target - now;
            const _time::duration_fast remaining_fast( remaining );
            if ( !wait_for( remaining_fast ) )
                return fail;
        }
    }
    //
    _time::duration_prec clock_now_unix( ) noexcept {
        ULONGLONG ticks = fwh_get_ticks( );
        if ( ticks < fwh_unix_epoch )
            return _time::duration_prec{ };
        const ULONGLONG elapsed = ticks - fwh_unix_epoch;
        return (
            _time::secs_prec( elapsed / 10000000ULL ) +
            _time::nanosecs_prec( ( elapsed % 10000000ULL ) * 100ULL )
        );
    }
    //
    _time::duration_prec clock_now_local( ) noexcept {
        LARGE_INTEGER counter;
        LARGE_INTEGER frequency;
        if (
            QueryPerformanceFrequency( &frequency ) == 0 ||
            frequency.QuadPart <= zero ||
            QueryPerformanceCounter( &counter ) == 0 ||
            counter.QuadPart < zero
        )
            return _time::duration_prec{ };
        const _time::__prec_t ticks =
            static_cast<_time::__prec_t>( counter.QuadPart );
        const _time::__prec_t freq =
            static_cast<_time::__prec_t>( frequency.QuadPart );
        const _time::__prec_t secs = ticks / freq;
        const _time::__prec_t remainder = ticks % freq;
        const _time::__prec_t nanosecs =
            ( remainder * 1000000000ULL ) / freq;
        return
            _time::secs_prec( secs ) +
            _time::nanosecs_prec( nanosecs );
    }
    //
}