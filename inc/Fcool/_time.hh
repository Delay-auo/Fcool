/**
 * @headerfile Fcool/_data.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.2
 * @copyright (C) Matias Viitanen 2026
 * This file is part of the Fcool library
 */



#ifndef FCOOL_HEAD__TIME
#define FCOOL_HEAD__TIME 0.1


#include "__fcool.hh"
#include "_cpu.hh"


namespace Fcool::_time
{
    //
    /// @brief the fast duration tick type
    using __fast_t = _cpu::nat_quad;
    /// @brief the precise duration tick type
    using __prec_t = _cpu::nat_octa;
    /// @brief the fast duration tick max value
    constexpr __fast_t __max_fast = _cpu::val_max_nat<__fast_t>;
    /// @brief the precise duration tick max value
    constexpr __prec_t __max_prec = _cpu::val_max_nat<__prec_t>;
    //
    constexpr __prec_t _mul_high( __prec_t left, __prec_t right ) noexcept {
        constexpr __prec_t mask = __prec_t{0xFFFFFFFF};
        const __prec_t left_lo = left & mask;
        const __prec_t left_hi = left >> 32;
        const __prec_t right_lo = right & mask;
        const __prec_t right_hi = right >> 32;
        const __prec_t low_product = left_lo * right_lo;
        const __prec_t cross_left = left_lo * right_hi;
        const __prec_t cross_right = left_hi * right_lo;
        const __prec_t middle = (low_product >> 32) +
            (cross_left & mask) + (cross_right & mask);
        return left_hi * right_hi + (cross_left >> 32) +
            (cross_right >> 32) + (middle >> 32);
    }
    /// @brief seconds in a minute
    constexpr __fast_t _DIFF_SEC_IN_MIN = 60U;
    /// @brief minutes in a hour
    constexpr __fast_t _DIFF_MIN_IN_HOUR = 60U;
    /// @brief hours in a day
    constexpr __prec_t _DIFF_HOUR_IN_DAY = 24U;
    /// @brief seconds in a hour
    constexpr __fast_t _DIFF_SEC_IN_HOUR = _DIFF_SEC_IN_MIN * _DIFF_MIN_IN_HOUR;
    /// @brief minutes in a day
    constexpr __prec_t _DIFF_MIN_IN_DAY = _DIFF_HOUR_IN_DAY * _DIFF_MIN_IN_HOUR;
    /// @brief seconds in a day
    constexpr __prec_t _DIFF_SEC_IN_DAY = _DIFF_SEC_IN_HOUR * _DIFF_HOUR_IN_DAY;
    /// @brief milliseconds in a second
    constexpr __fast_t _DIFF_MILLISEC_IN_SEC = 1000U;
    /// @brief microseconds in a millisecond
    constexpr __fast_t _DIFF_MICROSEC_IN_MILLISEC = 1000U;
    /// @brief nanoseconds in a microsecond
    constexpr __fast_t _DIFF_NANOSEC_IN_MICROSEC = 1000U;
    /// @brief microseconds in a second
    constexpr __fast_t _DIFF_MICROSEC_IN_SEC = _DIFF_MILLISEC_IN_SEC * _DIFF_MICROSEC_IN_MILLISEC;
    /// @brief nanoseconds in a second
    constexpr __fast_t _DIFF_NANOSEC_IN_SEC = _DIFF_MICROSEC_IN_SEC * _DIFF_NANOSEC_IN_MICROSEC;
    /// @brief fast ticks in a second
    constexpr __prec_t _DIFF_FAST_TICK_IN_SEC = __prec_t{__max_fast} + unit;
    static_assert( _DIFF_FAST_TICK_IN_SEC > __max_fast );
    /// @brief milliseconds in a day
    constexpr __prec_t _DIFF_MILLISEC_IN_DAY = _DIFF_SEC_IN_DAY * _DIFF_MILLISEC_IN_SEC;
    /// @brief microseconds in a day
    constexpr __prec_t _DIFF_MICROSEC_IN_DAY = _DIFF_SEC_IN_DAY * _DIFF_MICROSEC_IN_SEC;
    /// @brief nanoseconds in a day
    constexpr __prec_t _DIFF_NANOSEC_IN_DAY = _DIFF_SEC_IN_DAY * _DIFF_NANOSEC_IN_SEC;
    /// @brief fast ticks in a day
    constexpr __prec_t _DIFF_FAST_TICK_IN_DAY = _DIFF_SEC_IN_DAY * _DIFF_FAST_TICK_IN_SEC;
    #if FCOOLMACRO_HEXA
        /// @brief larger than precise duration tick type
        /// @warning ### declared only if *FCOOLMACRO_HEXA*
        /// @warning #### not portable across compilers
        using __mega_t = _cpu::nat_hexa;
        /// @brief precise ticks in a day
        /// @warning ### declared only if *FCOOLMACRO_HEXA*
        /// @warning #### not portable across compilers
        constexpr __mega_t _DIFF_PREC_TICK_IN_DAY = __mega_t{__max_prec} + unit;
        static_assert( _DIFF_PREC_TICK_IN_DAY > __max_prec );
    #endif
    //
    constexpr static __fast_t _fast_frac_get( __fast_t part, __fast_t range ) noexcept {
        return static_cast<__fast_t>(
            (
                static_cast<__prec_t>(part % range) *
                static_cast<__prec_t>(_DIFF_FAST_TICK_IN_SEC) +
                static_cast<__prec_t>(range) - __prec_t{1}
            ) /
            static_cast<__fast_t>( range )
        );
    }
    constexpr static __prec_t _prec_frac_get( __prec_t part, __prec_t range ) noexcept {
        #if FCOOLMACRO_HEXA
            return static_cast<__prec_t>(
                (
                    static_cast<__mega_t>(part % range) *
                    static_cast<__mega_t>(_DIFF_PREC_TICK_IN_DAY) +
                    static_cast<__mega_t>(range) - __mega_t{1}
                ) /
                static_cast<__prec_t>(range)
            );
        #else
            __prec_t remainder = part % range;
            __prec_t ticks = zero;
            for ( unsigned int bit = 0; bit < 64; ++bit ) {
                ticks <<= 1;
                if ( remainder >= range - remainder ) {
                    remainder -= range - remainder;
                    ticks |= unit;
                } else {
                    remainder += remainder;
                }
            }
            return ticks + static_cast<__prec_t>(remainder != zero);
        #endif
    }
    /// @brief #### precise duration
    class duration_prec;
    /// @brief #### fast duration
    class duration_fast
    {
        __fast_t secs;
        __fast_t frac;
        //
        constexpr duration_fast( __prec_t _fast_ticks ) noexcept
        : secs(static_cast<__fast_t>(_fast_ticks/_DIFF_FAST_TICK_IN_SEC)), frac(_fast_ticks%_DIFF_FAST_TICK_IN_SEC) { }
        constexpr duration_fast( __fast_t _secs, __fast_t _frac ) noexcept
        : secs(_secs), frac(_frac) { }
        //
        friend constexpr duration_fast secs( __fast_t ) noexcept;
        friend constexpr duration_fast millisecs( __fast_t ) noexcept;
        friend constexpr duration_fast microsecs( __fast_t ) noexcept;
        friend constexpr duration_fast nanosecs( __fast_t ) noexcept;
        friend constexpr duration_fast fast_ticks( __prec_t ) noexcept;
        //
        constexpr __fast_t get_sec_fraction( __fast_t range ) const noexcept {
            return static_cast<__fast_t>(
                static_cast<__prec_t>(frac) *
                static_cast<__prec_t>(range) /
                _DIFF_FAST_TICK_IN_SEC
            );
        }
        //
    public:
        //
        constexpr duration_fast( ) noexcept
        : secs(zero), frac(zero) { }
        constexpr duration_fast( const duration_prec& ) noexcept;
        constexpr duration_fast( duration_prec&& that ) noexcept
        : duration_fast(that) { }
        /// @brief 
        /// @return the total seconds in the duration
        constexpr __fast_t get_secs( ) const noexcept {
            return secs;
        }
        /// @brief 
        /// @return the amount of ticks to the next second
        constexpr __fast_t get_ticks_( ) const noexcept {
            return frac;
        }
        /// @brief 
        /// @return the total days in the duration
        constexpr __fast_t get_days( ) const noexcept {
            return secs / _DIFF_SEC_IN_DAY;
        }
        /// @brief 
        /// @return the total hours in the duration
        constexpr __fast_t get_hours( ) const noexcept {
            return secs / _DIFF_SEC_IN_HOUR;
        }
        /// @brief 
        /// @return the amount of hours to the next day
        constexpr __fast_t get_hours_( ) const noexcept {
            return get_hours( ) % _DIFF_HOUR_IN_DAY;
        }
        /// @brief 
        /// @return the total minutes in the duration
        constexpr __fast_t get_mins( ) const noexcept {
            return secs / _DIFF_SEC_IN_MIN;
        }
        /// @brief 
        /// @return the amount of minutes to the next hour
        constexpr __fast_t get_mins_( ) const noexcept {
            return get_mins( ) % _DIFF_MIN_IN_HOUR;
        }
        /// @brief 
        /// @return the amount of seconds to the next minute
        constexpr __fast_t get_secs_( ) const noexcept {
            return secs % _DIFF_SEC_IN_MIN;
        }
        /// @brief 
        /// @return the total milliseconds in the duration
        constexpr __prec_t get_millisecs( ) const noexcept {
            return static_cast<__prec_t>( secs ) * _DIFF_MILLISEC_IN_SEC + get_sec_fraction( _DIFF_MILLISEC_IN_SEC );
        }
        /// @brief 
        /// @return the amount of milliseconds to the next second
        constexpr __fast_t get_millisecs_( ) const noexcept {
            return get_sec_fraction( _DIFF_MILLISEC_IN_SEC ) % _DIFF_MILLISEC_IN_SEC;
        }
        /// @brief 
        /// @return the total microseconds in the duration
        constexpr __prec_t get_microsecs( ) const noexcept {
            return static_cast<__prec_t>(secs) * _DIFF_MICROSEC_IN_SEC + get_sec_fraction( _DIFF_MICROSEC_IN_SEC );
        }
        /// @brief 
        /// @return the amount of microseconds to the next millisecond
        constexpr __fast_t get_microsecs_( ) const noexcept {
            return get_sec_fraction( _DIFF_MICROSEC_IN_SEC ) % _DIFF_MICROSEC_IN_MILLISEC;
        }
        /// @brief 
        /// @return the total nanoseconds in the duration
        constexpr __prec_t get_nanosecs( ) const noexcept {
            return static_cast<__prec_t>(secs) * _DIFF_NANOSEC_IN_SEC + get_sec_fraction( _DIFF_NANOSEC_IN_SEC );
        }
        /// @brief 
        /// @return the amount of nanosecond to the next microsecond
        constexpr __fast_t get_nanosecs_( ) const noexcept {
            return get_sec_fraction( _DIFF_NANOSEC_IN_SEC ) % _DIFF_NANOSEC_IN_MICROSEC;
        }
        /// @brief 
        /// @return the total tick count in the duration
        constexpr __prec_t get_ticks( ) const noexcept {
            return static_cast<__prec_t>(secs) * _DIFF_FAST_TICK_IN_SEC + frac;
        }
        //
        constexpr bool operator<( duration_fast that ) const noexcept {
            return ( secs == that.secs ) ? frac < that.frac : secs < that.secs;
        }
        constexpr bool operator<=( duration_fast that ) const noexcept {
            return ( secs == that.secs ) ? frac <= that.frac : secs < that.secs;
        }
        constexpr bool operator>( duration_fast that ) const noexcept {
            return ( secs == that.secs ) ? frac > that.frac : secs > that.secs;
        }
        constexpr bool operator>=( duration_fast that ) const noexcept {
            return ( secs == that.secs ) ? frac >= that.frac : secs > that.secs;
        }
        constexpr bool operator==( duration_fast that ) const noexcept {
            return ( secs == that.secs ) && ( frac == that.frac );
        }
        //
        constexpr duration_fast operator+( duration_fast that ) const noexcept {
            return { get_ticks( ) + that.get_ticks( ) };
        }
        constexpr duration_fast operator-( duration_fast that ) const noexcept {
            if ( operator<( that ) )
                return { zero, zero };
            return { get_ticks( ) - that.get_ticks( ) };
        }
        constexpr duration_fast operator%( duration_fast that ) const noexcept {
            if ( that.secs == zero && that.frac == zero )
                return { zero, zero };
            return { get_ticks( ) % that.get_ticks( ) };
        }
        constexpr duration_fast operator*( __fast_t that ) const noexcept {
            return { get_ticks( ) * that };
        }
        constexpr duration_fast operator/( __fast_t that ) const noexcept {
            if ( that == zero )
                return { zero, zero };
            return { get_ticks( ) / that };
        }
        //
        constexpr duration_fast& operator+=( duration_fast that ) noexcept {
            *this = *this + that;
            return *this;
        }
        constexpr duration_fast& operator-=( duration_fast that ) noexcept {
            *this = *this - that;
            return *this;
        }
        constexpr duration_fast& operator%=( duration_fast that ) noexcept {
            *this = *this % that;
            return *this;
        }
        constexpr duration_fast& operator*=( __fast_t that ) noexcept {
            *this = *this * that;
            return *this;
        }
        constexpr duration_fast& operator/=( __fast_t that ) noexcept {
            *this = *this / that;
            return *this;
        }
        //
    };
    /// @brief 
    /// @param s seconds
    /// @return fast duration in seconds
    constexpr duration_fast secs( __fast_t s ) noexcept {
        return { s, zero };
    }
    /// @brief 
    /// @param ms milliseconds
    /// @return fast duration in milliseconds
    constexpr duration_fast millisecs( __fast_t ms ) noexcept {
        return { ms/_DIFF_MILLISEC_IN_SEC, _fast_frac_get(ms,_DIFF_MILLISEC_IN_SEC) };
    }
    /// @brief 
    /// @param mcs microseconds
    /// @return fast duration in microseconds
    constexpr duration_fast microsecs( __fast_t mcs ) noexcept {
        return { mcs/_DIFF_MICROSEC_IN_SEC, _fast_frac_get(mcs,_DIFF_MICROSEC_IN_SEC) };
    }
    /// @brief 
    /// @param ns nanosecond
    /// @return fast duration in nanosecond
    constexpr duration_fast nanosecs( __fast_t ns ) noexcept {
        return { ns/_DIFF_NANOSEC_IN_SEC, _fast_frac_get(ns,_DIFF_NANOSEC_IN_SEC) };
    }
    /// @brief 
    /// @param fast_ticks total tick count
    /// @return fast duration in ticks
    constexpr duration_fast fast_ticks( __prec_t fast_ticks ) noexcept {
        return { fast_ticks };
    }
    /// @brief longest possible time held in fast duration
    constexpr duration_fast fast_longest = fast_ticks( __max_prec );
    //
    class duration_prec
    {
        __prec_t days;
        __prec_t frac;
        //
        #if FCOOLMACRO_HEXA
            constexpr duration_prec( __mega_t _prec_ticks ) noexcept
            : days(static_cast<__prec_t>(_prec_ticks/_DIFF_PREC_TICK_IN_DAY)), frac(static_cast<__prec_t>(_prec_ticks%_DIFF_PREC_TICK_IN_DAY)) { }
        #else
            constexpr duration_prec( __prec_t _prec_ticks ) noexcept
            : days(zero), frac( _prec_ticks ) { }
        #endif
        constexpr duration_prec( __prec_t _days, __prec_t _frac ) noexcept
        : days(_days), frac(_frac) { }
        //
        friend constexpr duration_prec days_prec( __prec_t ) noexcept;
        friend constexpr duration_prec hours_prec( __prec_t ) noexcept;
        friend constexpr duration_prec mins_prec( __prec_t ) noexcept;
        friend constexpr duration_prec secs_prec( __prec_t ) noexcept;
        friend constexpr duration_prec millisecs_prec( __prec_t ) noexcept;
        friend constexpr duration_prec microsecs_prec( __prec_t ) noexcept;
        friend constexpr duration_prec nanosecs_prec( __prec_t ) noexcept;
        friend constexpr duration_prec fast_ticks_prec( __prec_t ) noexcept;
        friend constexpr duration_prec prec_ticks(
        #if FCOOLMACRO_HEXA
            __mega_t
        #else
            __prec_t
        #endif
        ) noexcept;
        //
        constexpr __prec_t get_day_fraction( __prec_t range ) const noexcept {
            #if FCOOLMACRO_HEXA
                return static_cast<__prec_t>(
                    static_cast<__mega_t>(frac) *
                    static_cast<__mega_t>(range) /
                    _DIFF_PREC_TICK_IN_DAY
                );
            #else
                return _mul_high(frac, range);
            #endif
        }
        //
    public:
        //
        constexpr duration_prec( ) noexcept
        : days(zero), frac(zero) { }
        constexpr duration_prec( const duration_fast& that ) noexcept
        : days(that.get_days( )), frac(
            _prec_frac_get(that.get_ticks( ), _DIFF_FAST_TICK_IN_DAY)
        ) { }
        constexpr duration_prec( duration_fast&& that ) noexcept
        : duration_prec(that) { }
        /// @brief 
        /// @return the total days in the duration
        constexpr __prec_t get_days( ) const noexcept {
            return days;
        }
        /// @brief 
        /// @return the amount of ticks to the next day
        constexpr __prec_t get_prec_ticks_( ) const noexcept {
            return frac;
        }
        //
        #if FCOOLMACRO_HEXA
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total hours in the duration
            constexpr __mega_t get_hours( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_HOUR_IN_DAY + get_day_fraction( _DIFF_HOUR_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total minutes in the duration
            constexpr __mega_t get_mins( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_MIN_IN_DAY + get_day_fraction( _DIFF_MIN_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total seconds in the duration
            constexpr __mega_t get_secs( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_SEC_IN_DAY + get_day_fraction( _DIFF_SEC_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total milliseconds in the duration
            constexpr __mega_t get_millisecs( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_MILLISEC_IN_DAY + get_day_fraction( _DIFF_MILLISEC_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total microseconds in the duration
            constexpr __mega_t get_microsecs( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_MICROSEC_IN_DAY + get_day_fraction( _DIFF_MICROSEC_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total nanoseconds in the duration
            constexpr __mega_t get_nanosecs( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_NANOSEC_IN_DAY + get_day_fraction( _DIFF_NANOSEC_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total fast ticks in the duration
            constexpr __mega_t get_fast_ticks( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_FAST_TICK_IN_DAY + get_day_fraction( _DIFF_FAST_TICK_IN_DAY );
            }
            /// @brief 
            /// @warning ### declared only if *FCOOLMACRO_HEXA*
            /// @warning #### not portable across compilers
            /// @return the total tick count in the duration
            constexpr __mega_t get_prec_ticks( ) const noexcept {
                return static_cast<__mega_t>(days) * _DIFF_PREC_TICK_IN_DAY + frac;
            }
        #endif
        /// @brief 
        /// @return the amount of hours to the next day
        constexpr __prec_t get_hours_( ) const noexcept {
            return get_day_fraction( _DIFF_HOUR_IN_DAY ) % _DIFF_HOUR_IN_DAY;
        }
        /// @brief 
        /// @return the amount of minutes to the next hour
        constexpr __prec_t get_mins_( ) const noexcept {
            return get_day_fraction( _DIFF_MIN_IN_DAY ) % _DIFF_MIN_IN_HOUR;
        }
        /// @brief 
        /// @return the amount of seconds to the next minutes
        constexpr __prec_t get_secs_( ) const noexcept {
            return get_day_fraction( _DIFF_SEC_IN_DAY ) % _DIFF_SEC_IN_MIN;
        }
        /// @brief 
        /// @return the amount of milliseconds to the next second
        constexpr __prec_t get_millisecs_( ) const noexcept {
            return get_day_fraction( _DIFF_MILLISEC_IN_DAY ) % _DIFF_MILLISEC_IN_SEC;
        }
        /// @brief 
        /// @return the amount of microseconds to the next millisecond
        constexpr __prec_t get_microsecs_( ) const noexcept {
            return get_day_fraction( _DIFF_MICROSEC_IN_DAY ) % _DIFF_MICROSEC_IN_MILLISEC;
        }
        /// @brief 
        /// @return the amount of nanoseconds to the next microsecond
        constexpr __prec_t get_nanosecs_( ) const noexcept {
            return get_day_fraction( _DIFF_NANOSEC_IN_DAY ) % _DIFF_NANOSEC_IN_MICROSEC;
        }
        /// @brief 
        /// @return the amount of fast ticks to the next second
        constexpr __fast_t get_fast_ticks_( ) const noexcept {
            return static_cast<__fast_t>( get_day_fraction( _DIFF_FAST_TICK_IN_DAY ) % _DIFF_FAST_TICK_IN_SEC );
        }
        //
        constexpr bool operator<( duration_prec that ) const noexcept {
            return ( days == that.days ) ? frac < that.frac : days < that.days;
        }
        constexpr bool operator<=( duration_prec that ) const noexcept {
            return ( days == that.days ) ? frac <= that.frac : days < that.days;
        }
        constexpr bool operator>( duration_prec that ) const noexcept {
            return ( days == that.days ) ? frac > that.frac : days > that.days;
        }
        constexpr bool operator>=( duration_prec that ) const noexcept {
            return ( days == that.days ) ? frac >= that.frac : days > that.days;
        }
        constexpr bool operator==( duration_prec that ) const noexcept {
            return ( days == that.days ) && ( frac == that.frac );
        }
        constexpr bool operator!=( duration_prec that ) const noexcept {
            return ( days != that.days ) || ( frac != that.frac );
        }
        //
        constexpr duration_prec operator+( duration_prec that ) const noexcept {
            #if FCOOLMACRO_HEXA
                return { get_prec_ticks( ) + that.get_prec_ticks( ) };
            #else
                __prec_t _days = days + that.days;
                __prec_t _frac = frac + that.frac;
                if ( __max_prec - frac < that.frac )
                    ++_days;
                return { _days, _frac };
            #endif
        }
        constexpr duration_prec operator-( duration_prec that ) const noexcept {
            if ( operator<(that) )
                return { zero, zero };
            #if FCOOLMACRO_HEXA
                return { get_prec_ticks( ) - that.get_prec_ticks( ) };
            #else
                __prec_t _days = days - that.days;
                __prec_t _frac = frac - that.frac;
                if ( that.frac > frac )
                    --_days;
                return { _days, _frac };
            #endif
        }
        constexpr duration_prec operator%( duration_prec that ) const noexcept {
            if ( that.days == zero && that.frac == zero )
                return { zero, zero };
            #if FCOOLMACRO_HEXA
                return { get_prec_ticks( ) % that.get_prec_ticks( ) };
            #else
                __prec_t _remainder_days = zero;
                __prec_t _remainder_frac = zero;
                for ( unsigned int bit = 128; bit > 0; --bit ) {
                    const bool _carry = (_remainder_days >> 63) != zero;
                    _remainder_days = (_remainder_days << 1) | (_remainder_frac >> 63);
                    _remainder_frac <<= 1;
                    if ( bit > 64 )
                        _remainder_days |= (days >> (bit - 65)) & unit;
                    else
                        _remainder_frac |= (frac >> (bit - 1)) & unit;
                    if ( _carry || _remainder_days > that.days ||
                        (_remainder_days == that.days && _remainder_frac >= that.frac) ) {
                        const bool _borrow = _remainder_frac < that.frac;
                        _remainder_frac -= that.frac;
                        _remainder_days -= that.days + static_cast<__prec_t>(_borrow);
                    }
                }
                return { _remainder_days, _remainder_frac };
            #endif
        }
        constexpr duration_prec operator*( __prec_t that ) const noexcept {
            #if FCOOLMACRO_HEXA
                return { get_prec_ticks( ) * that };
            #else
                const __prec_t _frac = frac * that;
                return { days * that + _mul_high(frac, that), _frac };
            #endif
        }
        constexpr duration_prec operator/( __prec_t that ) const noexcept {
            if ( that == zero )
                return { zero, zero };
            #if FCOOLMACRO_HEXA
                return { get_prec_ticks( ) / that };
            #else
                const __prec_t _days = days / that; 
                __prec_t _remainder = days % that;
                __prec_t _frac = zero;
                for ( unsigned int bit = 64; bit > 0; --bit ) {
                    bool _quotient_bit = false;
                    if ( _remainder >= that - _remainder ) {
                        _remainder -= that - _remainder;
                        _quotient_bit = true;
                    } else {
                        _remainder += _remainder;
                    }
                    if ( ((frac >> (bit - 1)) & unit) != zero ) {
                        if ( _remainder == that - unit ) {
                            _remainder = zero;
                            _quotient_bit = true;
                        } else {
                            ++_remainder;
                        }
                    }
                    _frac = (_frac << 1) | static_cast<__prec_t>(_quotient_bit);
                }
                return { _days, _frac };
            #endif
        }
        //
        constexpr duration_prec& operator+=( duration_prec that ) noexcept {
            *this = *this + that;
            return *this;
        }
        constexpr duration_prec& operator-=( duration_prec that ) noexcept {
            *this = *this - that;
            return *this;
        }
        constexpr duration_prec& operator%=( duration_prec that ) noexcept {
            *this = *this % that;
            return *this;
        }
        constexpr duration_prec& operator*=( __prec_t that ) noexcept {
            *this = *this * that;
            return *this;
        }
        constexpr duration_prec& operator/=( __prec_t that ) noexcept {
            *this = *this / that;
            return *this;
        }
        //
    };
    //
    /// @brief 
    /// @param d days
    /// @return precise duration in days
    constexpr duration_prec days_prec( __prec_t d ) noexcept {
        return { d, zero };
    }
    /// @brief 
    /// @param h hours
    /// @return precise duration in hours
    constexpr duration_prec hours_prec( __prec_t h ) noexcept {
        return { h/_DIFF_HOUR_IN_DAY, _prec_frac_get(h,_DIFF_HOUR_IN_DAY) };
    }
    /// @brief 
    /// @param min minutes
    /// @return precise duration in minutes
    constexpr duration_prec mins_prec( __prec_t min ) noexcept {
        return { min/_DIFF_MIN_IN_DAY, _prec_frac_get(min,_DIFF_MIN_IN_DAY) };
    }
    /// @brief 
    /// @param s seconds
    /// @return precise duration in seconds
    constexpr duration_prec secs_prec( __prec_t s ) noexcept {
        return { s/_DIFF_SEC_IN_DAY, _prec_frac_get(s,_DIFF_SEC_IN_DAY) };
    }
    /// @brief 
    /// @param ms milliseconds
    /// @return precise duration in milliseconds
    constexpr duration_prec millisecs_prec( __prec_t ms ) noexcept {
        return { ms/_DIFF_MILLISEC_IN_DAY, _prec_frac_get(ms,_DIFF_MILLISEC_IN_DAY) };
    }
    /// @brief 
    /// @param mcs microseconds
    /// @return precise duration in microseconds
    constexpr duration_prec microsecs_prec( __prec_t mcs ) noexcept {
        return { mcs/_DIFF_MICROSEC_IN_DAY, _prec_frac_get(mcs,_DIFF_MICROSEC_IN_DAY) };
    }
    /// @brief 
    /// @param ns nanoseconds
    /// @return precise duration in nanoseconds
    constexpr duration_prec nanosecs_prec( __prec_t ns ) noexcept {
        return { ns/_DIFF_NANOSEC_IN_DAY, _prec_frac_get(ns,_DIFF_NANOSEC_IN_DAY) };
    }
    /// @brief 
    /// @param fast_ticks fast ticks
    /// @return precise duration in fast ticks
    constexpr duration_prec fast_ticks_prec( __prec_t fast_ticks ) noexcept {
        return { fast_ticks/_DIFF_FAST_TICK_IN_DAY, _prec_frac_get(fast_ticks,_DIFF_FAST_TICK_IN_DAY) };
    }
    #if FCOOLMACRO_HEXA
        /// @brief 
        /// @param prec_ticks 
        /// @return precise duration in precise ticks
        constexpr duration_prec prec_ticks( __mega_t prec_ticks ) noexcept {
            return { prec_ticks };
        }
        /// @brief longest possible time held in fast duration
        constexpr duration_prec prec_longest = prec_ticks( _cpu::val_max_nat<__mega_t> );
    #else
        /// @brief 
        /// @param prec_ticks 
        /// @return precise duration in precise ticks
        constexpr duration_prec prec_ticks( __prec_t prec_ticks ) noexcept {
            return { prec_ticks };
        }
        /// @brief longest possible time held in fast duration
        constexpr duration_prec prec_longest = prec_ticks( __max_prec ) + days_prec( __max_prec );
    #endif
    constexpr duration_fast::duration_fast( const duration_prec& that ) noexcept
    {
        #if FCOOLMACRO_HEXA
            const __mega_t fractional_seconds =
                static_cast<__mega_t>(that.get_prec_ticks_()) * _DIFF_SEC_IN_DAY;
            const __mega_t total_seconds =
                static_cast<__mega_t>(that.get_days()) * _DIFF_SEC_IN_DAY +
                fractional_seconds / _DIFF_PREC_TICK_IN_DAY;
            const __mega_t fractional_fast_ticks =
                (fractional_seconds % _DIFF_PREC_TICK_IN_DAY) *
                _DIFF_FAST_TICK_IN_SEC / _DIFF_PREC_TICK_IN_DAY;
            secs = static_cast<__fast_t>( total_seconds );
            frac = static_cast<__fast_t>( fractional_fast_ticks );
        #else
            const __prec_t total_fast_ticks =
                that.get_days() * _DIFF_FAST_TICK_IN_DAY +
                _mul_high(that.get_prec_ticks_(), _DIFF_FAST_TICK_IN_DAY);
            secs = static_cast<__fast_t>( total_fast_ticks / _DIFF_FAST_TICK_IN_SEC );
            frac = static_cast<__fast_t>( total_fast_ticks % _DIFF_FAST_TICK_IN_SEC );
        #endif
    }
    //
}


#endif
