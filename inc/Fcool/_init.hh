/**
 * @headerfile Fcool/_init.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.2
 * @copyright (C) Matias Viitanen 2026
 * This file is part of the Fcool library
 */


#ifndef FCOOL_HEAD__INIT
#define FCOOL_HEAD__INIT 0.1


#include "__fcool.hh"


namespace Fcool::_init
{
    /// @brief success result enumeter
    enum _value : tiny_t {
        /// @brief #### module is already loaded
        ready = zero,
        /// @brief #### module was successfully loaded and cannot be unloaded by third party
        success_stable = +dual,
        /// @brief #### module was successfully loaded but can be unloaded by third party
        success_unstable = +unit,
        /// @brief #### module failed due to being unsupported by the platform
        fail_stable = -dual,
        /// @brief #### module failed due to an issue
        fail_unstable = -unit
    };
    /// @brief success result
    struct type
    {
        /// @brief the success result value
        _value val;
        constexpr type( _value v ) noexcept
        : val( v ) { }
        constexpr type( ) noexcept
        : val( ready ) { }
        constexpr bool stable( ) const noexcept {
            return val == fail_stable || val == success_stable || val == ready;
        }
        constexpr explicit operator bool( ) const noexcept {
            return ( val >= ready );
        }
    };
    /// @brief get a failed success result
    /// @param stable 
    /// @return 
    constexpr type get_fail( bool stable ) {
        return stable ? fail_stable : fail_unstable;
    }
    /// @brief get a succeeded success result
    /// @param stable 
    /// @return 
    constexpr type get_success( bool stable ) {
        return stable ? success_stable : success_unstable;
    }
    /// @brief getter property
    /// @tparam T_Tp result type
    template < typename T_Tp >
    struct property_get
    {
        using getter_t = bool ( * )( T_Tp& ) noexcept;
        /// @brief getter function
        getter_t getter;
        constexpr property_get( getter_t _getter ) noexcept
        : getter( _getter ) { }
        constexpr property_get& operator=( const property_get& ) const noexcept = delete;
        constexpr property_get& operator=( property_get&& ) const noexcept = delete;
        constexpr property_get* operator&( ) const noexcept = delete;
        /// @brief 
        /// @param out the property output value
        /// @return weather the property was successfully read
        constexpr bool get( T_Tp& out ) const noexcept {
            return getter( out );
        }
        /// @brief read the property as its value type, enabling operators supported by T_Tp
        constexpr operator T_Tp( ) const {
            T_Tp in{};
            get( in );
            return in;
        }
        template < typename T_Arg >
        constexpr auto operator+( T_Arg val ) const -> decltype( T_Tp{} + val ) {
            T_Tp in;
            get( in );
            return ( in + val );
        }
        template < typename T_Arg >
        constexpr auto operator-( T_Arg val ) const -> decltype( T_Tp{} - val ) {
            T_Tp in;
            get( in );
            return ( in - val );
        }
        template < typename T_Arg >
        constexpr auto operator*( T_Arg val ) const -> decltype( T_Tp{} * val ) {
            T_Tp in;
            get( in );
            return ( in * val );
        }
        template < typename T_Arg >
        constexpr auto operator/( T_Arg val ) const -> decltype( T_Tp{} / val ) {
            T_Tp in;
            get( in );
            return ( in / val );
        }
        template < typename T_Arg >
        constexpr auto operator%( T_Arg val ) const -> decltype( T_Tp{} % val ) {
            T_Tp in;
            get( in );
            return ( in % val );
        }
        template < typename T_Arg >
        constexpr auto operator==( T_Arg val ) const -> decltype( T_Tp{} == val ) {
            T_Tp in;
            get( in );
            return ( in == val );
        }
        template < typename T_Arg >
        constexpr auto operator!=( T_Arg val ) const -> decltype( T_Tp{} != val ) {
            T_Tp in;
            get( in );
            return ( in != val );
        }
        template < typename T_Arg >
        constexpr auto operator>( T_Arg val ) const -> decltype( T_Tp{} > val ) {
            T_Tp in;
            get( in );
            return ( in > val );
        }
        template < typename T_Arg >
        constexpr auto operator<( T_Arg val ) const -> decltype( T_Tp{} < val ) {
            T_Tp in;
            get( in );
            return ( in < val );
        }
        template < typename T_Arg >
        constexpr auto operator>=( T_Arg val ) const -> decltype( T_Tp{} >= val ) {
            T_Tp in;
            get( in );
            return ( in >= val );
        }
        template < typename T_Arg >
        constexpr auto operator<=( T_Arg val ) const -> decltype( T_Tp{} <= val ) {
            T_Tp in;
            get( in );
            return ( in <= val );
        }
        template < typename T_Arg >
        constexpr auto operator<=>( T_Arg val ) const -> decltype( T_Tp{} <=> val ) {
            T_Tp in;
            get( in );
            return ( in <=> val );
        }
        template < typename T_Arg >
        constexpr auto operator&&( T_Arg val ) const -> decltype( T_Tp{} && val ) {
            T_Tp in;
            get( in );
            return ( in && val );
        }
        template < typename T_Arg >
        constexpr auto operator||( T_Arg val ) const -> decltype( T_Tp{} || val ) {
            T_Tp in;
            get( in );
            return ( in || val );
        }
        template < typename T_Arg >
        constexpr auto operator&( T_Arg val ) const -> decltype( T_Tp{} & val ) {
            T_Tp in;
            get( in );
            return ( in != val );
        }
        template < typename T_Arg >
        constexpr auto operator|( T_Arg val ) const -> decltype( T_Tp{} | val ) {
            T_Tp in;
            get( in );
            return ( in | val );
        }
        template < typename T_Arg >
        constexpr auto operator^( T_Arg val ) const -> decltype( T_Tp{} ^ val ) {
            T_Tp in;
            get( in );
            return ( in ^ val );
        }
        template < typename T_Arg >
        constexpr auto operator<<( T_Arg val ) const -> decltype( T_Tp{} << val ) {
            T_Tp in;
            get( in );
            return ( in << val );
        }
        template < typename T_Arg >
        constexpr auto operator>>( T_Arg val ) const -> decltype( T_Tp{} >> val ) {
            T_Tp in;
            get( in );
            return ( in >> val );
        }
        template < typename T_Arg >
        constexpr auto operator[]( T_Arg val ) const -> decltype( T_Tp{}[val] ) {
            T_Tp in;
            get( in );
            return ( in[val] );
        }
        template < typename T_Arg >
        constexpr auto operator->*( T_Arg val ) const -> decltype( T_Tp{}->*val ) {
            T_Tp in;
            get( in );
            return ( in->*val );
        }
        template < typename... T_Args >
        constexpr auto operator!=( T_Args&&... vals ) const -> decltype( T_Tp{}( vals... ) ) {
            T_Tp in;
            get( in );
            return ( in( vals... ) );
        }
        template < typename T_Arg >
        constexpr auto operator,( T_Arg val ) const -> decltype( T_Tp{}, val ) {
            T_Tp in;
            get( in );
            return ( in, val );
        }
    };
    /// @brief setter property
    /// @tparam T_Tp assign type
    template < typename T_Tp >
    struct property_set
    {
        using setter_t = bool ( * )( T_Tp&& ) noexcept;
        /// @brief setter function
        setter_t setter;
        constexpr property_set( setter_t _getter ) noexcept
        : setter( _getter ) { }
        constexpr property_set& operator=( const property_set& ) const noexcept = delete;
        constexpr property_set& operator=( property_set&& ) const noexcept = delete;
        constexpr property_set* operator&( ) const noexcept = delete;
        /// @brief 
        /// @param in the property input value
        /// @return weather the property check passed
        constexpr bool set( T_Tp&& in ) const noexcept {
            return setter( _type::forward<T_Tp>( in ) );
        }
        /// @brief 
        /// @param in the property input value
        /// @return weather the property check passed
        constexpr bool set( T_Tp& in ) const noexcept {
            return setter( _type::forward<T_Tp>( in ) );
        }
        //
        constexpr bool operator=( T_Tp&& in ) const {
            return setter( _type::forward<T_Tp>( in ) );
        }
        constexpr bool operator=( T_Tp& in ) const {
            return setter( _type::forward<T_Tp>( in ) );
        }
    };
    /// @brief getter + setter property
    /// @tparam T_TpGet result type
    /// @tparam T_TpSet assign type
    template < typename T_TpGet, typename T_TpSet = T_TpGet >
    struct property : public property_get<T_TpGet>, public property_set<T_TpSet>
    {
        using property_get<T_TpGet>::getter_t;
        using property_set<T_TpSet>::setter_t;
        using property_get<T_TpGet>::getter;
        using property_set<T_TpSet>::setter;
        using property_get<T_TpGet>::get;
        using property_set<T_TpSet>::set;
        using property_set<T_TpSet>::operator=;
        constexpr property(
            typename property_get<T_TpGet>::getter_t _getter,
            typename property_set<T_TpSet>::setter_t _setter
        ) noexcept
        : property_get<T_TpGet>( _getter ), property_set<T_TpSet>( _setter ) { }
        constexpr property& operator=( const property& ) noexcept = delete;
        constexpr property& operator=( property&& ) noexcept = delete;
        constexpr property* operator&( ) const noexcept = delete;
    };
    //
}


#endif


