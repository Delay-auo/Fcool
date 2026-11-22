/**
 * @headerfile Fcool/sync.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.2
 * @copyright (C) Matias Viitanen 2026
 * This file is part of the Fcool library
 */


#ifndef FCOOL_HEAD_SYNC
#define FCOOL_HEAD_SYNC 0.1


#include "Fcool/_time.hh"
#include "Fcool/_init.hh"


namespace Fcool::sync
{
    //
    bool is_loaded( ) noexcept;
    bool hard_reload( bool& stable ) noexcept;
    bool soft_reload( bool& stable ) noexcept;
    bool unload( ) noexcept;
    //
    inline bool hard_reload( ) noexcept { bool stable; return hard_reload( stable ); }
    inline bool soft_reload( ) noexcept { bool stable; return soft_reload( stable ); }
    /// @brief initialize the module
    /// @return result
    inline const _init::type init( ) noexcept {
        if ( !is_loaded( ) ) {
            bool stable;
            if ( !hard_reload( stable ) )
                return _init::get_fail( stable );
            else
                return _init::get_success( stable );
        }
        return { };
    }
    /// @brief safely reinitialize the module
    /// @return result
    inline const _init::type reinit( ) noexcept {
        if ( !is_loaded( ) ) {
            bool stable;
            if ( soft_reload( stable ) )
                return _init::get_success( stable );
            else
                return _init::get_fail( stable );
        }
        return { };
    }
    /// @brief uninitialize the module
    /// @return result
    inline const _init::type uninit( ) noexcept {
        if ( is_loaded( ) ) {
            if ( unload( ) )
                return _init::get_success( fail );
            else
                return _init::get_fail( fail );
        }
        return { };
    }
    /// @brief get everything the implementation can and cannot do
    namespace capability
    {
        using _cap_t = _cpu::nat_unit;
        enum _cap : _cap_t
        {
            None            = zero,
            MultiThreading  = unit << 0,
            MutexLocks      = unit << 1,
            Sleeping        = unit << 2,
            Waiting         = unit << 3,
            Unix            = unit << 4,
            Local           = unit << 5
        };
        _cap_t get_all( ) noexcept;
    }
    /// @brief ### async function runner
    struct Thread
    {
        /// @brief ### thread function type
        using Func = void ( * )( );
        /// @brief ### argumented thread function argument type
        using Arg = addr_t;
        /// @brief ### argumented thread function type
        using ArgFunc = void ( * )( Arg );
        ~Thread( ) noexcept;
        Thread( Func ) noexcept;
        Thread( ArgFunc ) noexcept;
        constexpr Thread( const Thread& ) noexcept = delete;
        constexpr Thread( Thread&& ) noexcept = delete;
        constexpr Thread& operator=( const Thread& ) noexcept = delete;
        constexpr Thread& operator=( Thread&& ) noexcept = delete;
        /// @brief sleep on the current thread
        /// @param sleep duration 
        /// @return weather waited the full time 
        static bool sleep( _time::duration_fast );
        /// @brief critical section
        struct Lock
        {
            Lock( ) noexcept;
            ~Lock( ) noexcept;
            constexpr Lock( const Lock& ) noexcept = delete;
            constexpr Lock( Lock&& ) noexcept = delete;
            constexpr Lock& operator=( const Lock& ) noexcept = delete;
            constexpr Lock& operator=( Lock&& ) noexcept = delete;
            void lock( );
            bool try_lock( );
            void unlock( );
        private:
            _mem::handle impl;
        };
        /// @brief automatic lock
        class AutoLock
        {
            Lock& lock;
        public:
            AutoLock( Lock& s)
                : lock(s) { lock.lock(); }
            ~AutoLock()
                { lock.unlock(); }
        };
    private:
        _mem::handle impl;
        friend bool wait_for( Thread ) noexcept;
    };
    /// @brief wait for a thread to finish
    /// @param thread 
    /// @return weather the tread is done
    bool wait_for( Thread ) noexcept;
    /// @brief wait for a duration
    /// @param wait_duration 
    /// @return weather waited the full time 
    bool wait_for( _time::duration_fast ) noexcept;
    /// @brief wait for a duration from 00:00:00 UTC
    /// @param wait_duration 
    /// @return weather waited to the point succesfully
    bool clock_wait_unix( _time::duration_prec ) noexcept;
    /// @brief wait for a duration from local epoch
    /// @param wait_duration 
    /// @return weather waited to the point succesfully
    bool clock_wait_local( _time::duration_prec ) noexcept;
    /// @brief get duration passed since 00:00:00 UTC
    /// @return duration from unix epoch ( **exceptions return zero time unit duration** )
    _time::duration_prec clock_now_unix( ) noexcept;
    /// @brief get duration passed since local epoch started
    /// @return duration from local epoch ( **exceptions return zero time unit duration** )
    _time::duration_prec clock_now_local( ) noexcept;
    //
    #if defined(FCOOLMACRO_NO_IMPL) && FCOOLMACRO_NO_IMPL
        //
        inline bool is_loaded( ) noexcept { return false; }
        inline bool hard_reload( bool& stable ) noexcept { stable = false; return false; }
        inline bool soft_reload( bool& stable ) noexcept { stable = false; return false; }
        inline bool unload( ) noexcept { return false; }
        //
        inline capability::_cap_t capability::get_all( ) noexcept { return capability::None; }
        //
        inline Thread::~Thread( ) noexcept { }
        inline Thread::Thread( Func ) noexcept { }
        inline Thread::Thread( ArgFunc ) noexcept { }
        inline bool Thread::sleep( _time::duration_fast ) { return false; }
        //
        inline Thread::Lock::Lock( ) noexcept { }
        inline Thread::Lock::~Lock( ) noexcept { }
        inline Thread::Lock::Lock( const Lock& ) noexcept { }
        inline Thread::Lock& Thread::Lock::operator=( const Lock& ) noexcept { return *this; }
        inline void Thread::Lock::lock( ) { }
        inline bool Thread::Lock::try_lock( ) { return false; }
        inline void Thread::Lock::open( ) { }
        //
        inline bool wait_for( Thread ) noexcept { return false; }
        inline bool wait_for( _time::duration_fast ) noexcept { return false; }
        inline bool clock_wait_unix( _time::duration_prec ) noexcept { return false; }
        inline bool clock_wait_local( _time::duration_prec ) noexcept { return false; }
        inline _time::duration_prec clock_now_unix( ) noexcept { return { }; }
        inline _time::duration_prec clock_now_local( ) noexcept { return { }; }
        //
    #endif
    //
}


#endif




