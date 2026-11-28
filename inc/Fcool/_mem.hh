/**
 * @headerfile Fcool/_mem.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.2
 * @copyright (C) Matias Viitanen 2026
 * This file is part of the Fcool library
 */



#ifndef FCOOL_HEAD__MEM
#define FCOOL_HEAD__MEM 0.1

#include "__fcool.hh"
#include "_type.hh"
#include "_cpu.hh"


#ifndef FCOOLMACRO_MEMEXCEPT
#   ifdef _DEBUG
#       define FCOOLMACRO_MEMEXCEPT _DEBUG
#   else
#       define FCOOLMACRO_MEMEXCEPT 0
#   endif
#endif


namespace Fcool::_mem
{

#pragma region // base classes

/// @brief #### lightweight general pointer wrapper
template < typename T_Tp >
struct _raw_ptr
{
    constexpr _raw_ptr( ) noexcept = default;
    constexpr _raw_ptr( decltype(nullptr) that ) noexcept
    : mem( that ) { }
    constexpr _raw_ptr( T_Tp* const that ) noexcept
    : mem( that ) { }
    constexpr _raw_ptr( addr_t that ) noexcept
    : mem( reinterpret_cast<T_Tp*>(that) ) { }
    constexpr _raw_ptr( _ptr_t that ) noexcept
    : mem( reinterpret_cast<T_Tp*>(that) ) { }
    //
    constexpr _raw_ptr( const _raw_ptr& that ) noexcept
    : mem( that ) { }
    constexpr _raw_ptr( const _raw_ptr<_type::_Clear_c<T_Tp>>& that ) noexcept
    requires(_type::_Check_c<T_Tp>) : mem( that ) { }
    constexpr _raw_ptr( const _raw_ptr<_type::_Clear_v<T_Tp>>& that ) noexcept
    requires(_type::_Check_v<T_Tp>) : mem( that ) { }
    template < typename T_As >
    constexpr _raw_ptr( const _raw_ptr<T_As>& that ) noexcept
    requires requires( T_As* _ptr ) { static_cast<T_Tp*>( _ptr ); }
    : mem( static_cast<T_Tp*>( static_cast<T_As*>( that ) ) ) { }
    //
    constexpr _raw_ptr( _raw_ptr&& that ) noexcept
    : _raw_ptr( that ) { }
    constexpr _raw_ptr( _raw_ptr<_type::_Clear_c<T_Tp>>&& that ) noexcept
    requires(_type::_Check_c<T_Tp>) : _raw_ptr( that ) { }
    constexpr _raw_ptr( _raw_ptr<_type::_Clear_v<T_Tp>>&& that ) noexcept
    requires(_type::_Check_v<T_Tp>) : _raw_ptr( that ) { }
    template < typename T_As >
    constexpr _raw_ptr( _raw_ptr<T_As>&& that ) noexcept
    requires requires( T_As* _ptr ) { static_cast<T_Tp*>( _ptr ); }
    : mem( static_cast<T_Tp*>( static_cast<T_As*>( that ) ) ) { }
    //
    constexpr explicit operator T_Tp*( ) const noexcept {
        return mem;
    }
    constexpr explicit operator addr_t( ) const noexcept {
        return reinterpret_cast<addr_t>( mem );
    }
    constexpr explicit operator _ptr_t( ) const noexcept {
        return reinterpret_cast<_ptr_t>( mem );
    }
    constexpr _raw_ptr& operator=( decltype(nullptr) that ) noexcept {
        mem = that;
        return *this;
    }
    constexpr _raw_ptr& operator=( const _raw_ptr& that ) noexcept {
        mem = that.mem;
        return *this;
    }
    constexpr _raw_ptr& operator=( _raw_ptr&& that ) noexcept {
        mem = that.mem;
        return *this;
    }
    constexpr _raw_ptr& operator=( T_Tp* that ) noexcept {
        mem = that;
        return *this;
    }
    constexpr _raw_ptr& operator=( addr_t that ) noexcept {
        mem = reinterpret_cast<T_Tp*>(that);
        return *this;
    }
    constexpr _raw_ptr& operator=( _ptr_t that ) noexcept {
        mem = reinterpret_cast<T_Tp*>(that);
        return *this;
    }
    //
    /// @brief multi purpose pointer casting helper
    /// @tparam T_As 
    template < typename T_As >
    constexpr _raw_ptr<T_As> cast( ) const {
        if constexpr (
            _type::is_same< T_Tp, T_As > ||
            _type::is_same<_type::copy_cv<T_Tp,void>,T_As> )
            return mem;
        else if constexpr (
            _type::is_same< T_Tp, _type::_Clear_c<T_As> > ||
            _type::is_same< T_Tp, _type::_Clear_v<T_As> > ||
            _type::is_same< T_Tp, _type::_Clear_cv<T_As> > )
            return static_cast<T_As*>( mem );
        else if constexpr ( _type::is_same_cv<T_Tp,T_As> )
            return const_cast<T_As*>( mem );
        else if constexpr ( _type::cv_matches< T_Tp, T_As > )
            return reinterpret_cast<T_As*>( mem );
        else
            return reinterpret_cast<T_As*>(
                const_cast<_type::copy_cv<T_As,T_Tp>*>( mem )
            );
    }
    explicit constexpr operator bool( ) const noexcept {
        return mem != nullptr;
    }
    constexpr bool operator!=( decltype(nullptr) that ) const noexcept {
        return mem != that;
    }
    constexpr bool operator!=( _raw_ptr that ) const noexcept {
        return mem != that.mem;
    }
    constexpr bool operator!=( T_Tp* that ) const noexcept {
        return mem != that;
    }
    constexpr bool operator!=( addr_t that ) const noexcept {
        return mem != reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator!=( _ptr_t that ) const noexcept {
        return mem != reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator!( ) const noexcept {
        return mem == nullptr;
    }
    constexpr bool operator==( decltype(nullptr) that ) const noexcept {
        return mem == that;
    }
    constexpr bool operator==( _raw_ptr that ) const noexcept {
        return mem == that.mem;
    }
    constexpr bool operator==( T_Tp* that ) const noexcept {
        return mem == that;
    }
    constexpr bool operator==( addr_t that ) const noexcept {
        return mem == reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator==( _ptr_t that ) const noexcept {
        return mem == reinterpret_cast<T_Tp*>(that);
    }
    //
    constexpr bool operator<( decltype(nullptr) that ) const noexcept {
        return mem < that;
    }
    constexpr bool operator<=( decltype(nullptr) that ) const noexcept {
        return mem <= that;
    }
    constexpr bool operator>( decltype(nullptr) that ) const noexcept {
        return mem > that;
    }
    constexpr bool operator>=( decltype(nullptr) that ) const noexcept {
        return mem >= that;
    }
    constexpr bool operator<( _raw_ptr that ) const noexcept {
        return mem < that.mem;
    }
    constexpr bool operator<=( _raw_ptr that ) const noexcept {
        return mem <= that.mem;
    }
    constexpr bool operator>( _raw_ptr that ) const noexcept {
        return mem > that.mem;
    }
    constexpr bool operator>=( _raw_ptr that ) const noexcept {
        return mem >= that.mem;
    }
    constexpr bool operator<( T_Tp* that ) const noexcept {
        return mem < that;
    }
    constexpr bool operator<=( T_Tp* that ) const noexcept {
        return mem <= that;
    }
    constexpr bool operator>( T_Tp* that ) const noexcept {
        return mem > that;
    }
    constexpr bool operator>=( T_Tp* that ) const noexcept {
        return mem >= that;
    }
    constexpr bool operator<( addr_t that ) const noexcept {
        return mem < reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator<=( addr_t that ) const noexcept {
        return mem <= reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator>( addr_t that ) const noexcept {
        return mem > reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator>=( addr_t that ) const noexcept {
        return mem >= reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator<( _ptr_t that ) const noexcept {
        return mem < reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator<=( _ptr_t that ) const noexcept {
        return mem <= reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator>( _ptr_t that ) const noexcept {
        return mem > reinterpret_cast<T_Tp*>(that);
    }
    constexpr bool operator>=( _ptr_t that ) const noexcept {
        return mem >= reinterpret_cast<T_Tp*>(that);
    }
    //
protected:
    using ref_t = _type::_cond<
        _type::is_void<T_Tp>,
        _type::copy_cv<T_Tp,byte_t>,
        T_Tp
    >&;
    T_Tp* mem;
    //
};
/// @brief #### lightweight general object wrapper
template < typename T_Tp >
struct _raw_obj : public _raw_ptr<T_Tp>
{
    using _raw_ptr<T_Tp>::mem;
    using _raw_ptr<T_Tp>::_raw_ptr;
    using _raw_ptr<T_Tp>::operator=;
    constexpr _raw_obj( const _raw_ptr<T_Tp>& that ) noexcept
    : _raw_ptr<T_Tp>( that ) { }
    constexpr _raw_obj( _raw_ptr<T_Tp>&& that ) noexcept
    : _raw_ptr<T_Tp>( that ) { }
    //
    constexpr _raw_ptr<T_Tp>::ref_t operator*( ) const noexcept
    requires( !_type::is_void<T_Tp> ) {
        return *mem;
    }
    /// @brief multi purpose object casting helper
    /// @tparam T_As 
    template < typename T_As >
    constexpr _raw_obj<T_As> cast( ) const {
        return _raw_obj<T_As>( _raw_ptr<T_Tp>::template cast<T_As>() );
    }
    constexpr T_Tp* operator->( ) const noexcept {
        return mem;
    }
};
/// @brief #### lightweight general array wrapper
template < typename T_Tp >
struct _raw_arr : public _raw_ptr<T_Tp>
{
    using _raw_ptr<T_Tp>::mem;
    using _raw_ptr<T_Tp>::_raw_ptr;
    using _raw_ptr<T_Tp>::operator=;
    constexpr _raw_arr( const _raw_ptr<T_Tp>& that ) noexcept
    : _raw_ptr<T_Tp>( that ) { }
    constexpr _raw_arr( _raw_ptr<T_Tp>&& that ) noexcept
    : _raw_ptr<T_Tp>( that ) { }
    //
    /// @brief multi purpose array casting helper
    /// @tparam T_As 
    template < typename T_As >
    constexpr _raw_arr<T_As> cast( ) const {
        return _raw_arr<T_As>( _raw_ptr<T_Tp>::template cast<T_As>() );
    }
    constexpr _raw_ptr<T_Tp>::ref_t operator[]( addr_t addr ) const noexcept
    requires( !_type::is_void<T_Tp> ) {
        return mem[addr];
    }
};

/// @brief #### lightweight general object wrapper with arithetic operations
/// @tparam T_Tp 
template < typename T_Tp >
struct obj : public _raw_obj<T_Tp>
{
    static_assert( !_type::is_void<T_Tp>, "void memory objects not allowed" );
    using _raw_obj<T_Tp>::mem;
    using _raw_obj<T_Tp>::_raw_obj;
    using _raw_obj<T_Tp>::operator=;
    constexpr obj operator+( addr_t that ) const noexcept {
        return ( mem + that );
    }
    constexpr obj operator-( addr_t that ) const noexcept {
        return ( mem - that );
    }
    constexpr obj operator++( int ) noexcept {
        return mem++;
    }
    constexpr obj operator--( int ) noexcept {
        return mem--;
    }
    constexpr obj& operator+=( addr_t that ) noexcept {
        mem += that;
        return *this;
    }
    constexpr obj& operator-=( addr_t that ) noexcept {
        mem -= that;
        return *this;
    }
    constexpr obj& operator++( ) noexcept {
        ++mem;
        return *this;
    }
    constexpr obj& operator--( ) noexcept {
        --mem;
        return *this;
    }
};
template < typename T_Tp >
/// @brief #### lightweight general array wrapper with arithetic operations
/// @tparam T_Tp 
struct arr : public _raw_arr<T_Tp>
{
    static_assert( !_type::is_void<T_Tp>, "void memory arrays not allowed" );
    using _raw_arr<T_Tp>::mem;
    using _raw_arr<T_Tp>::_raw_arr;
    using _raw_arr<T_Tp>::operator=;
    constexpr obj<T_Tp> operator+( addr_t that ) const noexcept {
        return ( mem + that );
    }
    constexpr obj<T_Tp> operator-( addr_t that ) const noexcept {
        return ( mem - that );
    }
    constexpr arr operator++( int ) noexcept {
        return mem++;
    }
    constexpr arr operator--( int ) noexcept {
        return mem--;
    }
    constexpr arr& operator+=( addr_t that ) noexcept {
        mem += that;
        return *this;
    }
    constexpr arr& operator-=( addr_t that ) noexcept {
        mem -= that;
        return *this;
    }
    constexpr arr& operator++( ) noexcept {
        ++mem;
        return *this;
    }
    constexpr arr& operator--( ) noexcept {
        --mem;
        return *this;
    }
};
template < typename T_Tp >
/// @brief #### lightweight general pointer wrapper with arithetic operations
/// @tparam T_Tp 
struct ptr : public _raw_ptr<T_Tp>
{
    static_assert( !_type::is_void<T_Tp>, "void memory pointers not allowed" );
    using _raw_ptr<T_Tp>::mem;
    using _raw_ptr<T_Tp>::_raw_ptr;
    using _raw_ptr<T_Tp>::operator=;
    constexpr ptr operator+( addr_t that ) const noexcept {
        return ( mem + that );
    }
    constexpr ptr operator-( addr_t that ) const noexcept {
        return ( mem - that );
    }
    constexpr ptr& operator+=( addr_t that ) noexcept {
        mem += that;
        return *this;
    }
    constexpr ptr& operator-=( addr_t that ) noexcept {
        mem -= that;
        return *this;
    }
};
/// @brief ### general handle pointer type
using handle_m = _raw_obj<void>;
/// @brief ### general buffer pointer type
using buffer_m = _raw_arr<void>;
/// @brief ### constant handle pointer type
using handle_c = _raw_obj<const void>;
/// @brief ### constant buffer pointer type
using buffer_c = _raw_arr<const void>;
/// @brief ### volatile handle pointer type
using handle_v = _raw_obj<volatile void>;
/// @brief ### volatile buffer pointer type
using buffer_v = _raw_arr<volatile void>;
/// @brief ### qualified handle pointer type
using handle_cv = _raw_obj<const volatile void>;
/// @brief ### qualified buffer pointer type
using buffer_cv = _raw_arr<const volatile void>;

/// @brief forwarard iterator
/// @tparam T_Tp 
template < typename T_Tp >
using  iterator_forward = obj<T_Tp>;
/// @brief reverse iterator
/// @tparam T_Tp 
template < typename T_Tp >
struct iterator_reverse : public _raw_obj<T_Tp>
{
    using _raw_obj<T_Tp>::mem;
    using _raw_obj<T_Tp>::_raw_obj;
    using _raw_obj<T_Tp>::operator=;
    constexpr iterator_reverse operator+( addr_t that ) const noexcept {
        return ( mem - that );
    }
    constexpr iterator_reverse operator-( addr_t that ) const noexcept {
        return ( mem + that );
    }
    constexpr iterator_reverse operator++( int ) noexcept {
        return mem--;
    }
    constexpr iterator_reverse operator--( int ) noexcept {
        return mem++;
    }
    constexpr iterator_reverse& operator+=( addr_t that ) noexcept {
        mem -= that;
        return *this;
    }
    constexpr iterator_reverse& operator-=( addr_t that ) noexcept {
        mem += that;
        return *this;
    }
    constexpr iterator_reverse& operator++( ) noexcept {
        --mem;
        return *this;
    }
    constexpr iterator_reverse& operator--( ) noexcept {
        ++mem;
        return *this;
    }
};

/// @brief sized array type
/// @tparam T_Tp 
template < typename T_Tp >
struct arr_view : public _raw_arr<T_Tp>
{
    using _raw_arr<T_Tp>::mem;
    /// @brief the array span
    const addr_t span;
    //
    constexpr arr_view( ) noexcept = default;
    constexpr arr_view( decltype(nullptr) that, addr_t spex ) noexcept
    : _raw_arr<T_Tp>( that ), span( spex ) { }
    constexpr arr_view( T_Tp* const that, addr_t spex ) noexcept
    : _raw_arr<T_Tp>( that ), span( spex ) { }
    constexpr arr_view( addr_t that, addr_t spex ) noexcept
    : _raw_arr<T_Tp>( reinterpret_cast<T_Tp*>(that) ), span(spex) { }
    //
    constexpr arr_view( const _raw_ptr<T_Tp>& that, addr_t spex ) noexcept
    : _raw_arr<T_Tp>( that ), span( spex ) { }
    constexpr arr_view( _raw_ptr<T_Tp>&& that, addr_t spex ) noexcept
    : _raw_arr<T_Tp>( that ), span( spex ) { }
    //
    constexpr arr_view( const arr_view& that ) noexcept
    : _raw_arr<T_Tp>( that ), span( that.span ) {}
    constexpr arr_view( arr_view&& that ) noexcept
    : _raw_arr<T_Tp>( that ), span( that.span ) {}
    //
    constexpr arr_view& operator=( const arr_view& that ) noexcept = delete;
    constexpr arr_view& operator=( arr_view&& that ) noexcept = delete;
    //
    /// @brief get the first element
    constexpr T_Tp& front( ) const noexcept {
        return *begin( );
    }
    /// @brief get the last element
    constexpr T_Tp& back( ) const noexcept {
        return *rbegin( );
    }
    /// @brief view span begin
    /// @return forward iterator
    constexpr iterator_forward<T_Tp> begin( ) noexcept {
        return mem;
    }
    /// @brief view span end
    /// @return forward iterator
    constexpr iterator_forward<T_Tp> end( ) noexcept {
        return mem + span;
    }
    /// @brief view span begin
    /// @return reverse iterator
    constexpr iterator_reverse<T_Tp> rbegin( ) noexcept {
        return mem + span - unit;
    }
    /// @brief view span end
    /// @return reverse iterator
    constexpr iterator_reverse<T_Tp> rend( ) noexcept {
        return mem - unit;
    }
    /// @brief view span begin
    /// @return forward iterator
    constexpr const iterator_forward<T_Tp> begin( ) const noexcept {
        return mem;
    }
    /// @brief view span end
    /// @return forward iterator
    constexpr const iterator_forward<T_Tp> end( ) const noexcept {
        return mem + span;
    }
    /// @brief view span begin
    /// @return reverse iterator
    constexpr const iterator_reverse<T_Tp> rbegin( ) const noexcept {
        return mem + span - unit;
    }
    /// @brief view span end
    /// @return reverse iterator
    constexpr const iterator_reverse<T_Tp> rend( ) const noexcept {
        return mem - unit;
    }
    /// @brief constant view span begin
    /// @return forward iterator
    constexpr const iterator_forward<const T_Tp> cbegin( ) const noexcept {
        return mem;
    }
    /// @brief constant view span end
    /// @return forward iterator
    constexpr const iterator_forward<const T_Tp> cend( ) const noexcept {
        return mem + span;
    }
    /// @brief constant view span begin
    /// @return reverse iterator
    constexpr const iterator_reverse<const T_Tp> crbegin( ) const noexcept {
        return mem + span - unit;
    }
    /// @brief constant view span end
    /// @return reverse iterator
    constexpr const iterator_reverse<const T_Tp> crend( ) const noexcept {
        return mem - unit;
    }
    //
};

#pragma endregion

#pragma region // copying and casting

/// @brief #### lightweight general pointer casting
/// @tparam T_As 
/// @tparam T_Tp 
/// @param mem 
/// @return casted type
template < typename T_As, typename T_Tp >
constexpr _raw_ptr<T_As> cast( const _raw_ptr<T_Tp>& mem ) {
    return mem.template cast<T_As>( );
}
/// @brief #### lightweight general object casting
/// @tparam T_As 
/// @tparam T_Tp 
/// @param mem 
/// @return casted type
template < typename T_As, typename T_Tp >
constexpr _raw_obj<T_As> cast( const _raw_obj<T_Tp>& mem ) {
    return static_cast<_raw_obj<T_As>>(
        mem.template cast<T_As>( )
    );
}
/// @brief #### lightweight general array casting
/// @tparam T_As 
/// @tparam T_Tp 
/// @param mem 
/// @return casted type
template < typename T_As, typename T_Tp >
constexpr _raw_arr<T_As> cast( const _raw_arr<T_Tp>& mem ) {
    return static_cast<_raw_arr<T_As>>(
        mem.template cast<T_As>( )
    );
}
/// @brief #### lightweight general handle casting
/// @tparam T_Tp 
/// @param mem 
/// @return a general handle
template < typename T_Tp >
constexpr handle_m cast_handle_m( const _raw_obj<T_Tp>& mem ) {
    return cast<void>( mem );
}
/// @brief #### lightweight general buffer casting
/// @tparam T_Tp 
/// @param mem 
/// @return a general buffer
template < typename T_Tp >
constexpr buffer_m cast_buffer_m( const _raw_arr<T_Tp>& mem ) {
    return cast<void>( mem );
}
/// @brief #### lightweight constant handle casting
/// @tparam T_Tp 
/// @param mem 
/// @return a constant handle
template < typename T_Tp >
constexpr handle_c cast_handle_c( const _raw_obj<T_Tp>& mem ) {
    return cast<const void>( mem );
}
/// @brief #### lightweight constant buffer casting
/// @tparam T_Tp 
/// @param mem 
/// @return a constant buffer
template < typename T_Tp >
constexpr buffer_c cast_buffer_c( const _raw_arr<T_Tp>& mem ) {
    return cast<const void>( mem );
}
/// @brief #### lightweight volatile handle casting
/// @tparam T_Tp 
/// @param mem 
/// @return a volatile handle
template < typename T_Tp >
constexpr handle_v cast_handle_v( const _raw_obj<T_Tp>& mem ) {
    return cast<volatile void>( mem );
}
/// @brief #### lightweight volatile buffer casting
/// @tparam T_Tp 
/// @param mem 
/// @return a volatile buffer
template < typename T_Tp >
constexpr buffer_v cast_buffer_v( const _raw_arr<T_Tp>& mem ) {
    return cast<volatile void>( mem );
}
/// @brief #### lightweight qualified handle casting
/// @tparam T_Tp 
/// @param mem 
/// @return a qualified handle
template < typename T_Tp >
constexpr handle_cv cast_handle_v( const _raw_obj<T_Tp>& mem ) {
    return cast<const volatile void>( mem );
}
/// @brief #### lightweight qualified buffer casting
/// @tparam T_Tp 
/// @param mem 
/// @return a qualified buffer
template < typename T_Tp >
constexpr buffer_cv cast_buffer_v( const _raw_arr<T_Tp>& mem ) {
    return cast<const volatile void>( mem );
}
/// @brief basic copy assignment from object
/// @tparam T_Tp 
/// @tparam T_Out 
/// @param in 
/// @param out 
template < typename T_Tp, typename T_Out = T_Tp >
constexpr void assign_copy( _raw_obj<T_Tp> in, _raw_obj<T_Out> out ) noexcept {
    *out = *in;
}
/// @brief basic copy assignment from array
/// @tparam T_Tp 
/// @tparam T_Out 
/// @param in 
/// @param out 
/// @param span 
template < typename T_Tp, typename T_Out = T_Tp >
constexpr void assign_copy( _raw_arr<T_Tp> in, _raw_arr<T_Out> out, addr_t span ) noexcept {
    for ( addr_t i = 0; i < span; ++i )
        out[i] = in[i];
}
/// @brief basic move assignment from object
/// @tparam T_Tp 
/// @tparam T_Out 
/// @param in 
/// @param out 
template < typename T_Tp, typename T_Out = T_Tp >
constexpr void assign_move( _raw_obj<T_Tp> in, _raw_obj<T_Out> out ) noexcept {
    *out = _type::move( *in );
}
/// @brief basic move assignment from array
/// @tparam T_Tp 
/// @tparam T_Out 
/// @param in 
/// @param out 
/// @param span 
template < typename T_Tp, typename T_Out = T_Tp >
constexpr void assign_move( _raw_arr<T_Tp> in, _raw_arr<T_Out> out, addr_t span ) noexcept {
    if ( in == out )
        return;
    if ( out < in )
        for ( addr_t i = 0; i < span; ++i )
            out[i] = in[i];
    else
        for ( addr_t i = span - 1; i < _cpu::val_max_size; --i )
            out[i] = in[i];
}
/// @brief basic copy from object
/// @tparam T_Tp 
/// @param in 
/// @param out 
template < typename T_Tp >
constexpr void copy( _raw_obj<_type::_Place_c<T_Tp>> in, _raw_obj<_type::_Clear_c<T_Tp>> out ) noexcept {
    using nfs_t = _cpu::_nat_from_size<sizeof(T_Tp)>;
    assign_copy<nfs_t>(
        _raw_arr<nfs_t>{cast<nfs_t>( in )},
        _raw_arr<nfs_t>{cast<nfs_t>( out )},
        _cpu::_from_size_count<sizeof(T_Tp)>
    );
}
/// @brief basic copy from array
/// @tparam T_Tp 
/// @param in 
/// @param out 
/// @param span 
template < typename T_Tp >
constexpr void copy( _raw_arr<_type::_Place_c<T_Tp>> in, _raw_arr<_type::_Clear_c<T_Tp>> out, addr_t span ) noexcept {
    using nfs_t = _cpu::_nat_from_size<sizeof(T_Tp)>;
    assign_copy<nfs_t>(
        cast<nfs_t>( in ),
        cast<nfs_t>( out ),
        _cpu::_from_size_count<sizeof(T_Tp)> * span
    );
}
/// @brief basic move from object
/// @tparam T_Tp 
/// @param in 
/// @param out 
template < typename T_Tp >
constexpr void move( _raw_obj<_type::_Place_c<T_Tp>> in, _raw_obj<_type::_Clear_c<T_Tp>> out ) noexcept {
    using nfs_t = _cpu::_nat_from_size<sizeof(T_Tp)>;
    assign_move<nfs_t>(
        _raw_arr<nfs_t>{cast<nfs_t>( in )},
        _raw_arr<nfs_t>{cast<nfs_t>( out )},
        _cpu::_from_size_count<sizeof(T_Tp)>
    );
}
/// @brief basic move from array
/// @tparam T_Tp 
/// @param in 
/// @param out 
/// @param span 
template < typename T_Tp >
constexpr void move( _raw_arr<_type::_Place_c<T_Tp>> in, _raw_arr<_type::_Clear_c<T_Tp>> out, addr_t span ) noexcept {
    using nfs_t = _cpu::_nat_from_size<sizeof(T_Tp)>;
    assign_move<nfs_t>(
        cast<nfs_t>( in ),
        cast<nfs_t>( out ),
        _cpu::_from_size_count<sizeof(T_Tp)> * span
    );
}

#pragma endregion

#pragma region // allocation

#if FCOOLMACRO_MEMEXCEPT
/// @brief #### triggers a exeption
/// @warning ### this function is only declared and not defined
[[noreturn]]
void except( );
#endif

/// @brief ### constructs a new object
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param mem 
/// @param ...args 
template < typename T_Tp, typename... TS_Args >
constexpr void place_obj( _raw_obj<T_Tp> mem, TS_Args&&... args ) {
    ::new ( static_cast<void*>( cast<void>( mem ) ) ) T_Tp( _type::forward<TS_Args>( args )... );
}
/// @brief ### deconstructs object
/// @tparam T_Tp 
/// @param mem 
template < typename T_Tp >
constexpr void flush_obj( _raw_obj<T_Tp> mem ) {
    return mem->~T_Tp( );
}
/// @brief ### allocates a new handle
/// @warning #### must be deallocated using delete_handle
/// @param size 
/// @return 
inline handle_m create_handle( addr_t size ) {
    #if FCOOLMACRO_MEMEXCEPT
        handle_m mem(::operator new( size ));
        if ( !mem )
            except( );
        return mem;
    #else
        return ::operator new( size );
    #endif
}
/// @brief ### allocates aligned a new handle
/// @warning #### must be deallocated using delete_handle
/// @param size 
/// @param align 
/// @return 
inline handle_m create_handle( addr_t size, _ali_t align ) {
    #if FCOOLMACRO_MEMEXCEPT
        handle_m mem(::operator new( size, std::align_val_t{ align } ));
        if ( !mem )
            except( );
        return mem;
    #else
        return ::operator new( size, std::align_val_t{ align } );
    #endif
}
/// @brief ### allocates and constructs a new object
/// @warning #### must be deallocated and deconstructed using delete_obj or flush_obj and delete_handle
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param ...args 
/// @return 
template < typename T_Tp, typename... TS_Args >
constexpr _raw_obj<T_Tp> create_obj( TS_Args&&... args ) {
    obj<T_Tp> mem = create_handle( sizeof(T_Tp), alignof(T_Tp) );
    obj_place<T_Tp,TS_Args...>( mem, _type::forward<TS_Args>( args )... );
    return mem;
}
/// @brief ### creates a new object
/// @warning #### must be deleted using free_obj
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param ...args 
/// @return 
template < typename T_Tp, typename... TS_Args >
constexpr _raw_obj<T_Tp> make_obj( TS_Args&&... args ) {
    #if FCOOLMACRO_MEMEXCEPT
        handle_m mem( new T_Tp( _type::forward<TS_Args>( args )... ) );
        if ( !mem )
            except( );
        return mem;
    #else
        return new T_Tp( _type::forward<TS_Args>( args )... );
    #endif
}
/// @brief ### frees allocated handle
/// @param mem 
inline void delete_handle( handle_c mem ) noexcept {
    return ::operator delete( const_cast<void*>( static_cast<const void*>( mem ) ) );
}
/// @brief ### frees aligned allocated handle
/// @param mem 
/// @param align 
inline void delete_handle( handle_c mem, _ali_t align ) noexcept {
    return ::operator delete( const_cast<void*>( static_cast<const void*>( mem ) ), std::align_val_t{ align } );
}
/// @brief ### frees and deconstructs allocated object
/// @warning ### doesn't work on objects created with make_obj( ... )
/// @tparam T_Tp 
/// @param mem 
template < typename T_Tp >
constexpr void delete_obj( _raw_obj<T_Tp> mem ) {
    flush_obj<T_Tp>( mem );
    delete_handle( mem, alignof(T_Tp) );
}
/// @brief ### deletes created object
/// @warning ### only works on objects created with make_obj( ... )
/// @tparam T_Tp 
/// @param mem 
template < typename T_Tp >
constexpr void free_obj( _raw_obj<T_Tp> mem ) {
    delete static_cast<T_Tp*>( mem );
}

/// @brief ### constructs a new array
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param mem 
/// @param span 
/// @param ...args one argument = one object ( amount crossing span is undefined behavior )
template < typename T_Tp, typename... TS_Args >
constexpr void place_arr( _raw_arr<T_Tp> mem, addr_t span, TS_Args&&... args ) {
    addr_t i = 0;
    arr<T_Tp> _arr = mem;
    ( place_obj( _arr + ( i++ ), _type::forward<TS_Args>( args ) ), ... );
    while ( i < span )
        place_obj( _arr + ( i++ ) );
}
/// @brief ### deconstructs array
/// @tparam T_Tp 
/// @param mem 
/// @param span 
template < typename T_Tp >
constexpr void flush_arr( _raw_arr<T_Tp> mem, addr_t span ) {
    for ( addr_t i = span-1; i < span; --i )
        mem[i].~T_Tp( );
}
/// @brief ### allocates a new buffer
/// @warning #### must be deallocated using delete_buffer
/// @param size 
/// @return 
inline buffer_m create_buffer( addr_t size ) {
    #if FCOOLMACRO_MEMEXCEPT
        buffer_m mem(::operator new[]( size ));
        if ( !mem )
            except( );
        return mem;
    #else
        return ::operator new[]( size );
    #endif
}
/// @brief ### allocates aligned bytes for a new buffer
/// @warning #### must be deallocated using delete_buffer
/// @param size 
/// @param align 
/// @return 
inline buffer_m create_buffer( addr_t size, _ali_t align ) {
    #if FCOOLMACRO_MEMEXCEPT
        buffer_m mem(::operator new[]( size, std::align_val_t{ align } ));
        if ( !mem )
            except( );
        return mem;
    #else
        return ::operator new[]( size, std::align_val_t{ align } );
    #endif
}
/// @brief ### allocates and constructs a new array
/// @warning #### must be deallocated and deconstructed using delete_arr or flush_arr and delete_buffer
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param span 
/// @param ...args one argument = one object ( amount crossing span is undefined behavior )
/// @return 
template < typename T_Tp, typename... TS_Args >
constexpr _raw_arr<T_Tp> create_arr( addr_t span, TS_Args&&... args ) {
    arr<T_Tp> mem = create_buffer( sizeof(T_Tp) * span, alignof(T_Tp) );
    place_arr<T_Tp,TS_Args...>( mem, span, _type::forward<TS_Args>( args )... );
    return mem;
}
/// @brief ### creates a new array
/// @warning #### must be deleted using free_arr
/// @tparam T_Tp 
/// @tparam ...TS_Args 
/// @param span 
/// @param ...args one argument = one object ( amount crossing span is undefined behavior )
/// @return 
template < typename T_Tp, typename... TS_Args >
constexpr _raw_arr<T_Tp> make_arr( addr_t span, TS_Args&&... args ) {
    #if FCOOLMACRO_MEMEXCEPT
        buffer_c mem( new T_Tp[span]( _type::forward<TS_Args>( args )... ) );
        if ( !mem )
            except( );
        return mem;
    #else
        return new T_Tp[span]( _type::forward<TS_Args>( args )... );
    #endif
}
/// @brief ### frees allocated buffer
/// @param mem 
inline void delete_buffer( buffer_c mem ) noexcept {
    return ::operator delete[]( const_cast<void*>( static_cast<const void*>( mem ) ) );
}
/// @brief ### frees aligned allocated buffer
/// @param mem 
/// @param align 
inline void delete_buffer( buffer_c mem, _ali_t align ) noexcept {
    return ::operator delete[]( const_cast<void*>( static_cast<const void*>( mem ) ), std::align_val_t{ align } );
}
/// @brief ### frees and deconstructs allocated array
/// @warning ### doesn't work on arrays created with make_arr( ... )
/// @tparam T_Tp 
/// @param mem 
/// @param span 
template < typename T_Tp >
constexpr void delete_arr( _raw_arr<T_Tp> mem, addr_t span ) {
    flush_arr<T_Tp>( mem, span );
    delete_buffer( mem, alignof(T_Tp) );
}
/// @brief ### deletes a created array
/// @warning ### only works on arrays created with make_arr( ... )
/// @tparam T_Tp 
/// @param mem 
template < typename T_Tp >
constexpr void free_arr( _raw_arr<T_Tp> mem ) {
    delete[] static_cast<T_Tp*>( mem );
}

#pragma endregion

#pragma region // smartptr

/// @brief allocated handle that will automatically be freed on cleanup
struct smart_handle : public handle_c
{
    inline smart_handle( addr_t size )
    : handle_c( create_handle( size ) ) { }
    constexpr smart_handle( const smart_handle& ) noexcept = delete;
    constexpr smart_handle( smart_handle&& that ) noexcept
    : handle_c( that ) { }
    inline ~smart_handle( ) {
        delete_handle( *this );
    }
};
/// @brief allocated buffer that will automatically be freed on cleanup
struct smart_buffer : public buffer_c
{
    inline smart_buffer( addr_t size )
    : buffer_c( create_buffer( size ) ) { }
    constexpr smart_buffer( const smart_buffer& ) noexcept = delete;
    constexpr smart_buffer( smart_buffer&& that ) noexcept
    : buffer_c( that ) { }
    inline ~smart_buffer( ) {
        delete_buffer( *this );
    }
};
/// @brief allocated handle that will automatically be freed on cleanup
struct smart_aligned_handle : public handle_c
{
    inline smart_aligned_handle( addr_t size, _ali_t align )
    : handle_c( create_handle( size, align ) ), ali(align) { }
    constexpr smart_aligned_handle( const smart_aligned_handle& ) noexcept = delete;
    constexpr smart_aligned_handle( smart_aligned_handle&& that ) noexcept
    : handle_c( that ), ali( that.ali ) { }
    inline ~smart_aligned_handle( ) {
        delete_handle( *this, ali );
    }
    constexpr _ali_t alignment( ) const noexcept { return ali; }
protected:
    const _ali_t ali;
};
/// @brief allocated buffer that will automatically be freed on cleanup
struct smart_aligned_buffer : public buffer_c
{
    inline smart_aligned_buffer( addr_t size, _ali_t align )
    : buffer_c( create_buffer( size, align ) ), ali(align) { }
    constexpr smart_aligned_buffer( const smart_aligned_buffer& ) noexcept = delete;
    constexpr smart_aligned_buffer( smart_aligned_buffer&& that ) noexcept
    : buffer_c( that ), ali( that.ali ) { }
    inline ~smart_aligned_buffer( ) {
        delete_buffer( *this, ali );
    }
    constexpr _ali_t alignment( ) const noexcept { return ali; }
protected:
    const _ali_t ali;
};

/// @brief allocated object that will automatically be freed on cleanup
/// @brief *will not construct or deconstruct*
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_raw_obj : public _raw_obj<T_Tp>
{
    inline smart_raw_obj( )
    : _raw_obj<T_Tp>( create_handle( sizeof(T_Tp), alignof(T_Tp) ) ) { }
    constexpr smart_raw_obj( const smart_raw_obj& ) noexcept = delete;
    constexpr smart_raw_obj( smart_raw_obj&& that ) noexcept
    : _raw_obj<T_Tp>( that ) { }
    inline ~smart_raw_obj( ) {
        delete_handle( *this, alignof(T_Tp) );
    }
};
/// @brief allocated array that will automatically be freed on cleanup
/// @brief *will not construct or deconstruct*
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_raw_arr : public _raw_arr<T_Tp>
{
    inline smart_raw_arr( addr_t span )
    : _raw_arr<T_Tp>( create_buffer( sizeof(T_Tp) * span, alignof(T_Tp) ) ) { }
    constexpr smart_raw_arr( const smart_raw_arr& ) noexcept = delete;
    constexpr smart_raw_arr( smart_raw_arr&& that ) noexcept
    : _raw_arr<T_Tp>( that ) { }
    inline ~smart_raw_arr( ) {
        delete_buffer( *this, alignof(T_Tp) );
    }
};

/// @brief allocated and constructed object that will automatically be freed and deconstructed on cleanup
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_obj : public _raw_obj<T_Tp>
{
    template < typename... TS_Args >
    constexpr smart_obj( TS_Args&&... args )
    : _raw_obj<T_Tp>( obj_make_buff<T_Tp>( _type::forward<TS_Args>( args )... ) ) { }
    constexpr smart_obj( const smart_obj& ) noexcept = delete;
    constexpr smart_obj( smart_obj&& that ) noexcept
    : _raw_obj<T_Tp>( that ) { }
    constexpr ~smart_obj( ) {
        obj_free_buff<T_Tp>( *this );
    }
};
/// @brief allocated and constructed array that will automatically be freed and deconstructed on cleanup
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_arr : public arr_view<T_Tp>
{
    using arr_view<T_Tp>::span;
    template < typename... TS_Args >
    constexpr smart_arr( addr_t spex, TS_Args&&... args )
    : arr_view<T_Tp>( create_arr<T_Tp>( spex, _type::forward<TS_Args>( args )... ), spex ) { }
    constexpr smart_arr( const smart_arr& ) noexcept = delete;
    constexpr smart_arr( smart_arr&& that ) noexcept
    : arr_view<T_Tp>( that ) { }
    constexpr ~smart_arr( ) {
        delete_arr<T_Tp>( *this, span );
    }
};

/// @brief new object that will automatically be deleted on cleanup
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_new_obj : public _raw_obj<T_Tp>
{
    template < typename... TS_Args >
    constexpr smart_new_obj( TS_Args&&... args )
    : _raw_obj<T_Tp>( obj_make_hold<T_Tp>( _type::forward<TS_Args>( args )... ) ) { }
    constexpr smart_new_obj( const smart_new_obj& ) noexcept = delete;
    constexpr smart_new_obj( smart_new_obj&& that ) noexcept
    : _raw_obj<T_Tp>( that ) { }
    constexpr ~smart_new_obj( ) {
        obj_free_hold<T_Tp>( *this );
    }
};
/// @brief new array that will automatically be deleted on cleanup
/// @tparam T_Tp 
template < typename T_Tp >
struct smart_new_arr : public _raw_arr<T_Tp>
{
    template < typename... TS_Args >
    constexpr smart_new_arr( addr_t span, TS_Args&&... args )
    : _raw_arr<T_Tp>( make_arr<T_Tp>( span, _type::forward<TS_Args>( args )... ) ) { }
    constexpr smart_new_arr( const smart_new_arr& ) noexcept = delete;
    constexpr smart_new_arr( smart_new_arr&& that ) noexcept
    : _raw_arr<T_Tp>( that ) { }
    constexpr ~smart_new_arr( ) {
        free_arr<T_Tp>( *this );
    }
};

#pragma endregion

}


#endif




