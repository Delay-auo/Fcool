/**
 * @headerfile Fcool/_data.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.1
 * @copyright (C) Matias Viitanen 2025 - 2026
 * This file is part of the Fcool library
 */


#ifndef FCOOL_HEAD__DATA
#define FCOOL_HEAD__DATA 0.0


#include "__fcool.hh"
#include "_cpu.hh"
#include "_mem.hh"


namespace Fcool::_data
{
    /// @brief #### pair containing two values
    /// @tparam T_first 
    /// @tparam T_second 
    template < typename T_first, typename T_second = T_first >
    struct pair
    {
        T_first first;
        T_second second;
    };
    //
    template < typename T_Tp >
    struct arr_area
    {
        _mem::_raw_arr<T_Tp> arr;
        addr_t span;
        addr_t capacity = zero;
        constexpr arr_area( ) noexcept = default;
        constexpr arr_area( decltype(nullptr) that, addr_t spex, addr_t cap ) noexcept
        : arr( that ), span( spex ), capacity( cap ) { }
        constexpr arr_area( T_Tp* const that, addr_t spex, addr_t cap ) noexcept
        : arr( that ), span( spex ), capacity( cap ) { }
        constexpr arr_area( addr_t that, addr_t spex, addr_t cap ) noexcept
        : arr( reinterpret_cast<T_Tp*>(that) ), span(spex) { }
        //
        constexpr arr_area( const _mem::_raw_ptr<T_Tp>& that, addr_t spex, addr_t cap ) noexcept
        : arr( that ), span( spex ), capacity( cap ) { }
        constexpr arr_area( _mem::_raw_ptr<T_Tp>&& that, addr_t spex, addr_t cap ) noexcept
        : arr( that ), span( spex ), capacity( cap ) { }
        //
        constexpr arr_area( const _mem::arr_view<T_Tp>& that, addr_t cap ) noexcept
        : arr( that ), span( that.span ), capacity( cap ) { }
        constexpr arr_area( _mem::arr_view<T_Tp>&& that, addr_t cap ) noexcept
        : arr( that ), span( that.span ), capacity( cap ) { }
        //
        constexpr arr_area( const arr_area& that ) noexcept
        : arr( that ), span( that.span ), capacity( that.capacity ) {}
        constexpr arr_area( arr_area&& that ) noexcept
        : arr( that ), span( that.span ), capacity( that.capacity ) {}
    };
    /// @brief #### vector
    /// @tparam T_Tp 
    template < typename T_Tp >
    class vect
    {
        //
        _mem::arr<T_Tp> arr = nullptr;
        addr_t n;
        addr_t c = zero;
        constexpr void __free( ) const {
            if ( arr )
                _mem::delete_buffer( arr, alignof(T_Tp) );
        }
        constexpr void __swap( _mem::_raw_arr<T_Tp> new_arr, addr_t new_c ) noexcept {
            arr = new_arr;
            if ( arr )
                c = new_c;
            else
                c = zero;
        }
        constexpr void __drop( ) noexcept {
            arr = nullptr;
            c = zero;
            n = c;
        }
        constexpr bool __reserve_internal( addr_t at, addr_t span ) noexcept {
            if ( span <= c )
                return pass;
            const addr_t max_span = _cpu::val_max_addr / sizeof(T_Tp);
            if ( span >= max_span )
                return fail;
            _mem::arr<T_Tp> new_arr = _mem::create_buffer( sizeof(T_Tp) * span, alignof(T_Tp) );
            if ( !new_arr )
                return fail;
            if ( arr && n ) {
                if ( at > n )
                    at = n;
                if ( at )
                    _mem::copy<T_Tp>( arr, new_arr, at );
                if ( at < n )
                    _mem::copy<T_Tp>( arr + at, new_arr + at + unit, n - at );
            }
            _mem::arr<T_Tp> old_arr = arr;
            __swap( new_arr, span );
            if ( old_arr )
                _mem::delete_buffer( old_arr, alignof(T_Tp) );
            return pass;
        }
        constexpr bool __grow( addr_t at, addr_t span ) noexcept {
            if ( span <= c )
                return pass;
            const addr_t max_span = _cpu::val_max_addr / sizeof(T_Tp);
            if ( span >= max_span )
                return fail;
            addr_t new_c = ( c == zero ? signed{unit} : c );
            while ( new_c < span ) {
                if ( new_c > max_span / 2 ) {
                    new_c = span;
                    break;
                }
                new_c *= 2;
            }
            return __reserve_internal( at, new_c );
        }
        //
        using C_Tp = _type::_Place_c<T_Tp>;
        template < typename T_U >
        friend constexpr vect<T_Tp> __raw_vect( _mem::_raw_arr<T_Tp>, addr_t, addr_t ) noexcept;
        template < typename T_U >
        friend constexpr vect<T_Tp> __raw_vect( _mem::_raw_arr<T_Tp>, addr_t ) noexcept;
        constexpr vect( arr_area<T_Tp> that ) noexcept
        : arr( that.arr ), n( that.span ), c( that.capacity ) { }
        //
    public:
        //
        static_assert( !_type::is_void<T_Tp> );
        //
        constexpr vect( ) {
            n = c;
        }
        template < typename... TS_Args >
        constexpr vect( addr_t span, TS_Args&&... args ) {
            if ( span < _cpu::val_max_addr/sizeof(T_Tp) )
                __swap( _mem::create_buffer( sizeof(T_Tp) * span, alignof(T_Tp) ), span );
            n = c;
            __place_every( _type::forward<TS_Args>( args )... );
        }
        constexpr ~vect( ) {
            __flush_every( );
            __free( );
        }
        //
        /// @brief 
        /// @return the vector as array pointer
        constexpr _mem::_raw_arr<T_Tp> _get( ) const noexcept {
            return arr;
        }
        /// @brief 
        /// @return the vector as array view
        constexpr _mem::arr_view<T_Tp> view( ) const noexcept {
            return { arr, n };
        }
        /// @brief 
        /// @return whether the container is empty
        constexpr bool empty( ) const noexcept {
            return ( n == zero );
        }
        /// @brief 
        /// @return the index of the last element
        constexpr addr_t back_index( ) const noexcept {
            return (empty( ) ? signed{zero} : (n - unit));
        }
        /// @brief 
        /// @return the number of elements
        constexpr addr_t span( ) const noexcept {
            return n;
        }
        /// @brief 
        /// @return the number of elements that can be held in currently allocated storage
        constexpr addr_t capacity( ) const noexcept {
            return c;
        }
        /// @brief reduces memory usage by freeing unused memory
        /// @return 
        constexpr bool compress( ) noexcept {
            if ( empty( ) ) {
                __free( );
                __drop( );
                return pass;
            }
            _mem::arr<T_Tp> new_arr = _mem::create_buffer( sizeof(T_Tp) * n, alignof(T_Tp) );
            if ( new_arr ) {
                _mem::copy<T_Tp>( arr, new_arr, n );
                __swap( new_arr, n );
                return pass;
            } else
                return fail;
        }
        /// @brief clears the contents
        constexpr void clear( ) noexcept {
            __flush_every( );
            __clear( );
        }
        /// @brief wipes the whole data
        constexpr void wipe( ) noexcept {
            __flush_every( );
            __wipe( );
        }
        //
        /// @brief clears the contents **without deconstruction**
        constexpr void __clear( ) noexcept {
            n = zero;
        }
        /// @brief wipes the whole data **without deconstruction**
        constexpr void __wipe( ) noexcept {
            __free( );
            __drop( );
        }
        /// @brief 
        /// @param at index
        /// @return element from a specified index
        constexpr _mem::obj<T_Tp> __obj_at( addr_t at ) const noexcept {
            if ( at >= n )
                return nullptr;
            return ( arr + at );
        }
        /// @brief 
        /// @return the first element
        constexpr _mem::obj<T_Tp> __obj_front( ) const noexcept {
            if ( empty( ) )
                return nullptr;
            return ( arr );
        }
        /// @brief 
        /// @return the last element
        constexpr _mem::obj<T_Tp> __obj_back( ) const noexcept {
            return __obj_at( back_index( ) );
        }
        /// @brief constructs a new element to a specified index
        /// @warning #### doesn't deconstruct
        /// @tparam ...TS_Args 
        /// @param at index
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void __place_at( addr_t at, TS_Args&&... args ) const {
            _mem::obj<T_Tp> obj = __obj_at( at );
            if ( obj )
                _mem::place_obj<T_Tp>( obj, _type::forward<TS_Args>( args )... );
        }
        /// @brief constructs a new first element
        /// @warning #### doesn't deconstruct
        /// @tparam ...TS_Args 
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void __place_front( TS_Args&&... args ) const {
            _mem::obj<T_Tp> obj = __obj_front( );
            if ( obj )
                _mem::place_obj<T_Tp>( obj, _type::forward<TS_Args>( args )... );
        }
        /// @brief constructs a new last element
        /// @warning #### doesn't deconstruct
        /// @tparam ...TS_Args 
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void __place_back( TS_Args&&... args ) const {
            _mem::obj<T_Tp> obj = __obj_back( );
            if ( obj )
                _mem::place_obj<T_Tp>( obj, _type::forward<TS_Args>( args )... );
        }
        /// @brief constructs every element in the vector
        /// @tparam ...TS_Args 
        /// @param ...args one argument = one object ( amount crossing capacity is undefined behavior )
        template < typename... TS_Args >
        constexpr void __place_every( TS_Args&&... args ) const {
            if ( empty( ) )
                return;
            _mem::place_arr( arr, n, _type::forward<TS_Args>( args )... );
        }
        /// @brief deconstructs object from a specified index
        /// @warning using deconstructed object results in undefined behavior
        /// @param at index
        constexpr void __flush_at( addr_t at ) const {
            _mem::obj<T_Tp> obj = __obj_at( at );
            if ( obj )
                _mem::flush_obj<T_Tp>( obj );
        }
        /// @brief deconstructs the first object
        /// @warning using deconstructed object results in undefined behavior
        constexpr void __flush_front( ) const {
            _mem::obj<T_Tp> obj = __obj_front( );
            if ( obj )
                _mem::flush_obj<T_Tp>( obj );
        }
        /// @brief deconstructs the last object
        /// @warning using deconstructed object results in undefined behavior
        constexpr void __flush_back( ) const {
            _mem::obj<T_Tp> obj = __obj_back( );
            if ( obj )
                _mem::flush_obj<T_Tp>( obj );
        }
        /// @brief deconstructs every element in the vector
        constexpr void __flush_every( ) const {
            if ( arr )
                _mem::flush_arr<T_Tp>( arr, n );
        }
        /// @brief reserve a block of storage
        /// @param at the index where to reserve the block
        /// @param span amount of elements to reserve
        /// @return weather reserving was successful
        constexpr bool __reserve_at( addr_t at, addr_t span = unit ) noexcept {
            addr_t new_n = n + span;
            if ( __grow( at, new_n ) ) {
                n = new_n;
                return pass;
            } else
                return fail;
        }
        /// @brief reserve a block of storage in the begin of the vector
        /// @param span amount of elements to reserve
        /// @return weather reserving was successful
        constexpr bool __reserve_front( addr_t span = unit ) noexcept {
            return __reserve_at( zero, span );
        }
        /// @brief reserve a block of storage in the back of the vector
        /// @param span amount of elements to reserve
        /// @return weather reserving was successful
        constexpr bool __reserve_back( addr_t span = unit ) noexcept {
            return __reserve_at( n, span );
        }
        /// @brief raw copy a memory block
        /// @param at the index where to copy the block
        /// @param src source
        constexpr void __source_at( addr_t at, _mem::_raw_obj<C_Tp> src ) noexcept {
            _mem::obj<T_Tp> obj = __obj_at( at );
            if ( obj )
                _mem::move<T_Tp>( src, obj );
        }
        /// @brief raw copy a memory block
        /// @param at the index where to copy the block
        /// @param src source
        /// @param span amount of elements to reserve
        constexpr void __source_at( addr_t at, _mem::_raw_arr<C_Tp> src, addr_t span ) noexcept {
            _mem::obj<T_Tp> obj = __obj_at( at );
            if ( obj )
                _mem::move<T_Tp>( src, obj, span );
        }
        /// @brief raw copy a memory block in the begin of the vector
        /// @param src source
        constexpr void __source_front( _mem::_raw_obj<C_Tp> src ) noexcept {
            _mem::obj<T_Tp> obj = __obj_front( );
            if ( obj )
                _mem::move<T_Tp>( src, __obj_front( ) );
        }
        /// @brief raw copy a memory block in the begin of the vector
        /// @param src source
        /// @param span amount of elements to reserve
        constexpr void __source_front( _mem::_raw_arr<C_Tp> src, addr_t span ) noexcept {
            if ( span > c )
                span = c;
            _mem::obj<T_Tp> obj = __obj_front( );
            _mem::move<T_Tp>( src, obj, span );
        }
        /// @brief raw copy a memory block in the back of the vector
        /// @param src source
        constexpr void __source_back( _mem::_raw_obj<C_Tp> src ) noexcept {
            _mem::move<T_Tp>( src, __obj_back( ) );
        }
        /// @brief raw copy a memory block in the back of the vector
        /// @param src source
        /// @param span amount of elements to reserve
        constexpr void __source_back( _mem::_raw_arr<C_Tp> src, addr_t span ) noexcept {
            addr_t src_off = zero;
            if ( span > n ) {
                src_off = span - n;
                span = n;
            }
            _mem::move<T_Tp>( _mem::arr<C_Tp>{src} + src_off, __obj_at( n - span ), span );
        }
        //
        /// @brief access specified element with bounds checking
        /// @tparam at index
        /// @return a reference
        constexpr T_Tp& get_at( addr_t at ) const noexcept {
            return *__obj_at( at );
        }
        /// @brief access the first element
        /// @return a reference
        constexpr T_Tp& get_front( ) const noexcept {
            return *__obj_front( );
        }
        /// @brief access the last element
        /// @return a reference
        constexpr T_Tp& get_back( ) const noexcept {
            return *__obj_back( );
        }
        //
        /// @brief deconstructs and reconstructs a element
        /// @tparam ...TS_Args 
        /// @param at index
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void swap_at( addr_t at, TS_Args&&... args ) {
            __flush_at( at );
            __place_at( at, _type::forward<TS_Args>( args )... );
        }
        /// @brief deconstructs and reconstructs the first element
        /// @tparam ...TS_Args 
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void swap_front( TS_Args&&... args ) {
            __flush_front( );
            __place_front( _type::forward<TS_Args>( args )... );
        }
        /// @brief deconstructs and reconstructs the last element
        /// @tparam ...TS_Args 
        /// @param ...args 
        template < typename... TS_Args >
        constexpr void swap_back( TS_Args&&... args ) {
            __flush_back( );
            __place_back( _type::forward<TS_Args>( args )... );
        }
        //
        /// @brief inserts element
        /// @tparam ...TS_Args 
        /// @param at index
        /// @param ...args 
        /// @return 
        template < typename... TS_Args >
        constexpr bool add_at( addr_t at, TS_Args&&... args ) {
            bool r = __reserve_at( at );
            if ( r )
                __place_at( at, _type::forward<TS_Args>( args )... );
            return r;
        }
        /// @brief inserts element to the front
        /// @tparam ...TS_Args 
        /// @param ...args 
        /// @return 
        template < typename... TS_Args >
        constexpr bool add_front( TS_Args&&... args ) {
            bool r = __reserve_front( );
            if ( r )
                __place_front( _type::forward<TS_Args>( args )... );
            return r;
        }
        /// @brief inserts element to the back
        /// @tparam ...TS_Args 
        /// @param ...args 
        /// @return 
        template < typename... TS_Args >
        constexpr bool add_back( TS_Args&&... args ) {
            bool r = __reserve_front( );
            if ( r )
                __place_back( _type::forward<TS_Args>( args )... );
            return r;
        }
        //
        /// @brief removes element
        /// @param at index
        constexpr void pop_at( addr_t at ) noexcept {
            if ( at >= n )
                return;
            __flush_at( at );
            const addr_t trailing = back_index( ) - at;
            if ( trailing != zero )
                _mem::move<T_Tp>( __obj_at( at + unit ), __obj_at( at ), trailing );
            n--;
        }
        /// @brief removes multiple elements
        /// @param at index
        /// @param span amount
        constexpr void pop_at( addr_t at, addr_t span ) noexcept {
            if ( at >= n || span == zero )
                return;
            if ( span > n - at )
                span = n - at;
            _mem::flush_arr<T_Tp>( __obj_at( at ), span );
            const addr_t trailing = n - at - span;
            if ( trailing != zero )
                _mem::move<T_Tp>( __obj_at( at + span ), __obj_at( at ), trailing );
            n -= span;
        }
        /// @brief removes the first element
        constexpr void pop_front( ) noexcept {
            pop_at( zero );
        }
        /// @brief removes multiple elements from the begin
        /// @param span amount
        constexpr void pop_front( addr_t span ) noexcept {
            pop_at( zero, span );
        }
        /// @brief removes the last element
        constexpr void pop_back( ) noexcept {
            __flush_back( );
            n--;
        }
        /// @brief removes multiple elements from the end
        /// @param span amount
        constexpr void pop_back( addr_t span ) noexcept {
            for ( ;span > zero; --span ) {
                __flush_back( );
                --n;
            }
        }
        //
        constexpr explicit operator bool( ) const noexcept {
            return static_cast<bool>(arr);
        }
        constexpr bool operator!( ) const noexcept {
            return !arr;
        }
        constexpr T_Tp& operator[]( addr_t at ) const noexcept {
            return arr[ at ];
        }
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
        constexpr _mem::iterator_forward<T_Tp> begin( ) noexcept {
            return arr;
        }
        /// @brief view span end
        /// @return forward iterator
        constexpr _mem::iterator_forward<T_Tp> end( ) noexcept {
            return arr + span;
        }
        /// @brief view span begin
        /// @return reverse iterator
        constexpr _mem::iterator_reverse<T_Tp> rbegin( ) noexcept {
            return arr + span - unit;
        }
        /// @brief view span end
        /// @return reverse iterator
        constexpr _mem::iterator_reverse<T_Tp> rend( ) noexcept {
            return arr - unit;
        }
        /// @brief view span begin
        /// @return forward iterator
        constexpr const _mem::iterator_forward<T_Tp> begin( ) const noexcept {
            return arr;
        }
        /// @brief view span end
        /// @return forward iterator
        constexpr const _mem::iterator_forward<T_Tp> end( ) const noexcept {
            return arr + span;
        }
        /// @brief view span begin
        /// @return reverse iterator
        constexpr const _mem::iterator_reverse<T_Tp> rbegin( ) const noexcept {
            return arr + span - unit;
        }
        /// @brief view span end
        /// @return reverse iterator
        constexpr const _mem::iterator_reverse<T_Tp> rend( ) const noexcept {
            return arr - unit;
        }
        /// @brief constant view span begin
        /// @return forward iterator
        constexpr const _mem::iterator_forward<const T_Tp> cbegin( ) const noexcept {
            return arr;
        }
        /// @brief constant view span end
        /// @return forward iterator
        constexpr const _mem::iterator_forward<const T_Tp> cend( ) const noexcept {
            return arr + span;
        }
        /// @brief constant view span begin
        /// @return reverse iterator
        constexpr const _mem::iterator_reverse<const T_Tp> crbegin( ) const noexcept {
            return arr + span - unit;
        }
        /// @brief constant view span end
        /// @return reverse iterator
        constexpr const _mem::iterator_reverse<const T_Tp> crend( ) const noexcept {
            return arr - unit;
        }
        //
    };
    //
    template < typename T_Tp >
    constexpr vect<T_Tp> __raw_vect( _mem::_raw_arr<T_Tp> arr, addr_t span, addr_t capacity ) noexcept {
        return { arr_area<T_Tp>( arr, span, capacity ) };
    }
    template < typename T_Tp >
    constexpr vect<T_Tp> __raw_vect( _mem::_raw_arr<T_Tp> arr, addr_t span ) noexcept {
        return { arr_area<T_Tp>( arr, span, span ) };
    }
    /// @brief get the vector pointer, size and capacity as arr_area
    /// @tparam T_Tp 
    /// @param vec 
    /// @return arr_area that contains the allocated vector data
    template < typename T_Tp >
    constexpr arr_area<T_Tp> __vect_get_area( vect<T_Tp> vec ) noexcept {
        return { vec.view( ), vec.capacity( ) };
    }
    /// @brief get the vector pointer, size and capacity as arr_area
    /// @warning clears the vector
    /// @tparam T_Tp 
    /// @param vec 
    /// @return arr_area that contains the allocated vector data
    template < typename T_Tp >
    constexpr arr_area<T_Tp> __vect_get_area_and_clear( vect<T_Tp> vec ) noexcept {
        arr_area<T_Tp> r = __vect_get_area( vec );
        vec.__drop( );
        return r;
    }
    //
}


#endif




