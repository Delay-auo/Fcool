/**
 * @headerfile Fcool/_text.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.1
 * @copyright (C) Matias Viitanen 2025 - 2026
 * This file is part of the Fcool library
 */



#ifndef FCOOL_HEAD__TEXT
#define FCOOL_HEAD__TEXT 0.1


#include "__fcool.hh"
#include "_cpu.hh"
#include "_mem.hh"
#include "_data.hh"


namespace Fcool::_text
{
    //
    /// @brief a pointer string type
    /// @tparam T_Chr character format
    template < _cpu::check_any_chr T_Chr >
    using _ptr = _mem::arr< T_Chr >;
    /// @brief base range pointer string type
    using ptr_base = _ptr<_cpu::chr_base>;
    /// @brief wide range pointer string type
    using ptr_wide = _ptr<_cpu::chr_wide>;
    /// @brief UTF-8 pointer string type
    using ptr__unit = _ptr<_cpu::chr__unit>;
    /// @brief UTF-16 pointer string type
    using ptr__dual = _ptr<_cpu::chr__dual>;
    /// @brief UTF-32 pointer string type
    using ptr__quad = _ptr<_cpu::chr__quad>;
    /// @brief Primary Unicode pointer string type
    using uniptr = _ptr< _cpu::unicode_t >;
    /// @brief a string pointer type
    /// @tparam T_Chr character format
    template < _cpu::check_any_chr T_Chr >
    using _str = _mem::arr< const T_Chr >;
    /// @brief base range string pointer type
    using str_base = _str<_cpu::chr_base>;
    /// @brief wide range string pointer type
    using str_wide = _str<_cpu::chr_wide>;
    /// @brief UTF-8 string pointer type
    using str__unit = _str<_cpu::chr__unit>;
    /// @brief UTF-16 string pointer type
    using str__dual = _str<_cpu::chr__dual>;
    /// @brief UTF-32 string pointer type
    using str__quad = _str<_cpu::chr__quad>;
    /// @brief primary Unicode pointer string type
    using unistr = _ptr< _cpu::unicode_t >;
    //
    /// @brief string length
    using len_t = addr_t;
    /// @brief string length max value
    constexpr len_t max_len = _cpu::val_max_nat< len_t >;
    static_assert( max_len > zero );
    /// @brief 
    /// @tparam T_Chr character format
    /// @param s string
    /// @return the length of a null terminated string
    template < _cpu::check_any_chr T_Chr >
    constexpr len_t nt_len( _str<T_Chr> s ) noexcept {
        len_t l = zero;
        while ( s[ l ] != zero ) {
            ++l;
        }
        return l;
    }
    /// @brief 
    /// @tparam T_Chr character format
    /// @param s 
    /// @return the length of a null terminated string
    template < _cpu::check_any_chr T_Chr >
    constexpr len_t nt_len( const T_Chr* const s ) noexcept {
        return nt_len( _str<T_Chr>( s ) );
    }
    template < _cpu::check_any_chr T_Chr >
    constexpr len_t nt_get( _str<T_Chr> str, len_t str_l, _ptr<T_Chr> ptr ) noexcept {
        len_t copied = zero;
        for ( len_t i = zero; i < str_l; ++i ) {
            if ( str[ i ] != zero ) {
                ptr[ copied ] = str[ i ];
                ++copied;
            }
        }
        ptr[ copied ] = T_Chr{ zero };
        return copied;
    }
    /// @brief allocates a new pointer string
    /// @warning #### must be deallocated using free_ptr
    /// @tparam T_Chr character format
    /// @param l length of the new string
    /// @return pointer string
    template < _cpu::check_any_chr T_Chr >
    inline _ptr<T_Chr> _make_ptr( len_t l ) noexcept {
        return _mem::create_buffer( l * sizeof( T_Chr ) );
    }
    /// @brief allocates a new pointer string filled with empty characters
    /// @warning #### must be deallocated using free_ptr
    /// @tparam T_Chr character format
    /// @param l length of the new string
    /// @return pointer string
    template < _cpu::check_any_chr T_Chr >
    inline _ptr<T_Chr> _make_ptr_empty( len_t l ) noexcept {
        return _mem::create_arr< T_Chr >( l );
    }
    /// @brief frees allocated pointer string
    /// @tparam T_Chr character format
    /// @param s pointer string
    template < _cpu::check_any_chr T_Chr >
    inline void _free_str( _str<T_Chr> s ) noexcept {
        _mem::delete_buffer( _mem::cast_buffer( s ) );
    }
    /// @brief allocates a new base-range pointer string
    /// @warning must be deallocated using free_ptr_base
    /// @param l length of the new string
    /// @return base-range pointer string
    inline ptr_base make_ptr_base( len_t l ) noexcept {
        return _make_ptr<_cpu::chr_base>( l );
    }
    /// @brief allocates a new wide-range pointer string
    /// @warning must be deallocated using free_ptr_wide
    /// @param l length of the new string
    /// @return wide-range pointer string
    inline ptr_wide make_ptr_wide( len_t l ) noexcept {
        return _make_ptr<_cpu::chr_wide>( l );
    }
    /// @brief allocates a new UTF-8 pointer string
    /// @warning must be deallocated using free_ptr__unit
    /// @param l length of the new string
    /// @return UTF-8 pointer string
    inline ptr__unit make_ptr__unit( len_t l ) noexcept {
        return _make_ptr<_cpu::chr__unit>( l );
    }
    /// @brief allocates a new UTF-16 pointer string
    /// @warning must be deallocated using free_ptr__dual
    /// @param l length of the new string
    /// @return UTF-16 pointer string
    inline ptr__dual make_ptr__dual( len_t l ) noexcept {
        return _make_ptr<_cpu::chr__dual>( l );
    }
    /// @brief allocates a new UTF-32 pointer string
    /// @warning must be deallocated using free_ptr__quad
    /// @param l length of the new string
    /// @return UTF-32 pointer string
    inline ptr__quad make_ptr__quad( len_t l ) noexcept {
        return _make_ptr<_cpu::chr__quad>( l );
    }
    /// @brief allocates a new primary Unicode pointer string
    /// @warning must be deallocated using free_uniptr
    /// @param l length of the new string
    /// @return primary Unicode pointer string
    inline uniptr make_uniptr( len_t l ) noexcept {
        return _make_ptr<_cpu::unicode_t>( l );
    }
    /// @brief allocates a new base-range pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr_base
    /// @param l length of the new string
    /// @return base-range pointer string
    inline ptr_base make_ptr_empty_base( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::chr_base>( l );
    }
    /// @brief allocates a new wide-range pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr_wide
    /// @param l length of the new string
    /// @return wide-range pointer string
    inline ptr_wide make_ptr_empty_wide( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::chr_wide>( l );
    }
    /// @brief allocates a new UTF-8 pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr__unit
    /// @param l length of the new string
    /// @return UTF-8 pointer string
    inline ptr__unit make_ptr_empty__unit( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::chr__unit>( l );
    }
    /// @brief allocates a new UTF-16 pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr__dual
    /// @param l length of the new string
    /// @return UTF-16 pointer string
    inline ptr__dual make_ptr_empty__dual( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::chr__dual>( l );
    }
    /// @brief allocates a new UTF-32 pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr__quad
    /// @param l length of the new string
    /// @return UTF-32 pointer string
    inline ptr__quad make_ptr_empty__quad( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::chr__quad>( l );
    }
    /// @brief allocates a new primary Unicode pointer string filled with empty characters
    /// @warning must be deallocated using free_ptr__quad
    /// @param l length of the new string
    /// @return primary Unicode pointer string
    inline uniptr make_uniptr_empty( len_t l ) noexcept {
        return _make_ptr_empty<_cpu::unicode_t>( l );
    }
    /// @brief frees an allocated base-range pointer string
    /// @param s base-range pointer string
    inline void free_str_base( str_base s ) noexcept {
        _free_str<_cpu::chr_base>( s );
    }
    /// @brief frees an allocated wide-range pointer string
    /// @param s wide-range pointer string
    inline void free_str_wide( str_wide s ) noexcept {
        _free_str<_cpu::chr_wide>( s );
    }
    /// @brief frees an allocated UTF-8 pointer string
    /// @param s UTF-8 pointer string
    inline void free_str__unit( str__unit s ) noexcept {
        _free_str<_cpu::chr__unit>( s );
    }
    /// @brief frees an allocated UTF-16 pointer string
    /// @param s UTF-16 pointer string
    inline void free_str__dual( str__dual s ) noexcept {
        _free_str<_cpu::chr__dual>( s );
    }
    /// @brief frees an allocated UTF-32 pointer string
    /// @param s UTF-32 pointer string
    inline void free_str__quad( str__quad s ) noexcept {
        _free_str<_cpu::chr__quad>( s );
    }
    /// @brief frees an allocated primary Unicode pointer string
    /// @param s primary Unicode pointer string
    inline void free_unistr( unistr s ) noexcept {
        _free_str<_cpu::unicode_t>( s );
    }
    //
    #pragma region // conversion logic
    //
    template < _cpu::check_any_chr T_Chr, _cpu::check_any_chr T_Out = T_Chr >
    constexpr len_t convert( _str<T_Chr> str, _ptr<T_Out> ptr, len_t len ) {
        if constexpr ( _type::is_same<T_Chr,T_Out> ) {
           _mem::copy( str, ptr, len );
            return len;
        } else {
            static_assert( !_type::is_same<T_Chr,_cpu::chr__quad> );
            static_assert( !_type::is_same<T_Out,_cpu::chr__quad> );
            _mem::smart_new_arr<_cpu::chr__quad> buffer( len );
            if ( buffer ) {
                len_t common_len = convert<T_Chr,_cpu::chr__quad>( str, buffer, len );
                return convert<_cpu::chr__quad,T_Out>(
                    buffer,
                    ptr,
                    common_len
                );
            } else
                return zero;
        }
    }
    //
    template < > constexpr len_t convert( str__quad utf32, ptr__unit utf_8, len_t len ) {
        len_t out = 0;
        for (len_t i = 0; i < len; ++i) {
            _cpu::chr__quad cp = static_cast<_cpu::chr__quad>(utf32[i]);
            if (cp <= 0x7F) {
                utf_8[out++] = static_cast<_cpu::chr__unit>(cp);
            }
            else if (cp <= 0x7FF) {
                utf_8[out++] = static_cast<_cpu::chr__unit>(0xC0 | (cp >> 6));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | (cp & 0x3F));
            }
            else if (cp <= 0xFFFF) {
                if (cp >= 0xD800 && cp <= 0xDFFF)
                    cp = 0xFFFD;

                utf_8[out++] = static_cast<_cpu::chr__unit>(0xE0 | (cp >> 12));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | ((cp >> 6) & 0x3F));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | (cp & 0x3F));
            }
            else if (cp <= 0x10FFFF) {
                utf_8[out++] = static_cast<_cpu::chr__unit>(0xF0 | (cp >> 18));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | ((cp >> 12) & 0x3F));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | ((cp >> 6) & 0x3F));
                utf_8[out++] = static_cast<_cpu::chr__unit>(0x80 | (cp & 0x3F));
            }
            else {
                utf_8[out++] = static_cast<_cpu::chr__unit>(0xEF);
                utf_8[out++] = static_cast<_cpu::chr__unit>(0xBF);
                utf_8[out++] = static_cast<_cpu::chr__unit>(0xBD);
            }
        }
        return out;
    }
    template < > constexpr len_t convert( str__quad utf32, ptr__dual utf16, len_t len ) {
        len_t out = 0;
        for (unsigned i = 0; i < len; ++i) {
            _cpu::chr__quad cp = static_cast<_cpu::chr__quad>(utf32[i]);
            if (cp <= 0xFFFF) {
                if (cp >= 0xD800 && cp <= 0xDFFF)
                    cp = 0xFFFD;
                utf16[out++] = static_cast<_cpu::chr__dual>(cp);
            }
            else if (cp <= 0x10FFFF) {
                cp -= 0x10000;
                utf16[out++] = static_cast<_cpu::chr__dual>(0xD800 + (cp >> 10));
                utf16[out++] = static_cast<_cpu::chr__dual>(0xDC00 + (cp & 0x3FF));
            }
            else {
                utf16[out++] = static_cast<_cpu::chr__dual>(0xFFFD);
            }
        }
        return out;
    }
    template < > constexpr len_t convert( str__unit utf_8, ptr__quad utf32, len_t len ) {
        len_t in = 0;
        len_t out = 0;
        while (in < len) {
            _cpu::chr__quad cp;
            _cpu::chr__unit b0 = static_cast<_cpu::chr__unit>(utf_8[in++]);
            if (b0 < 0x80) {
                cp = b0;
            }
            else if ((b0 & 0xE0) == 0xC0 && in < len) {
                _cpu::chr__unit b1 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                cp = ((b0 & 0x1F) << 6)
                | (b1 & 0x3F);
                if (cp < 0x80)
                    cp = 0xFFFD;
            }
            else if ((b0 & 0xF0) == 0xE0 && in + unit < len) {
                _cpu::chr__unit b1 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                _cpu::chr__unit b2 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                cp = ((b0 & 0x0F) << 12)
                | ((b1 & 0x3F) << 6)
                | (b2 & 0x3F);
                if (cp < 0x800 || (cp >= 0xD800 && cp <= 0xDFFF))
                    cp = 0xFFFD;
            }
            else if ((b0 & 0xF8) == 0xF0 && in + dual < len) {
                _cpu::chr__unit b1 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                _cpu::chr__unit b2 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                _cpu::chr__unit b3 = static_cast<_cpu::chr__unit>(utf_8[in++]);
                cp = ((b0 & 0x07) << 18)
                | ((b1 & 0x3F) << 12)
                | ((b2 & 0x3F) << 6)
                | (b3 & 0x3F);
                if (cp < 0x10000 || cp > 0x10FFFF)
                    cp = 0xFFFD;
            }
            else {
                cp = 0xFFFD;
            }
            utf32[out++] = static_cast<_cpu::chr__quad>(cp);
        }
        return out;
    }
    template < > constexpr len_t convert( str__dual utf16, ptr__quad utf32, len_t len ) {
        len_t in = 0;
        len_t out = 0;
        while (in < len) {
            _cpu::chr__quad w1 = static_cast<_cpu::chr__dual>(utf16[in++]);
            if (w1 >= 0xD800 && w1 <= 0xDBFF) {
                if (in < len) {
                    _cpu::chr__quad w2 = static_cast<_cpu::chr__dual>(utf16[in]);
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF) {
                        ++in;
                        utf32[out++] = static_cast<_cpu::chr__quad>(
                            0x10000 +
                            (((w1 - 0xD800) << 10) |
                            (w2 - 0xDC00))
                        );
                        continue;
                    }
                }
                utf32[out++] = static_cast<_cpu::chr__quad>(0xFFFD);
            }
            else if (w1 >= 0xDC00 && w1 <= 0xDFFF) {
                utf32[out++] = static_cast<_cpu::chr__quad>(0xFFFD);
            }
            else {
                utf32[out++] = static_cast<_cpu::chr__quad>(w1);
            }
        }
        return out;
    }
    //
    template < > constexpr len_t convert( str__quad utf32, ptr_base b_str, len_t len ) {
        return convert( utf32, ptr__unit(_mem::cast<_cpu::chr__unit>( b_str )), len );
    }
    template < > constexpr len_t convert( str__quad utf32, ptr_wide w_str, len_t len ) {
        return convert( utf32, _ptr<_cpu::__wide_match_t>(_mem::cast<_cpu::__wide_match_t>( w_str )), len );
    }
    template < > constexpr len_t convert( str_base b_str, ptr__quad utf32, len_t len ) {
        return convert( str__unit(_mem::cast<const _cpu::chr__unit>( b_str )), utf32, len );
    }
    template < > constexpr len_t convert( str_wide w_str, ptr__quad utf32, len_t len ) {
        return convert( _str<_cpu::__wide_match_t>(_mem::cast<const _cpu::__wide_match_t>( w_str )), utf32, len );
    }
    //
    template < _cpu::check_any_chr T_Chr, _cpu::check_any_chr T_Out = T_Chr >
    constexpr len_t convert( const T_Chr* str, T_Out* ptr, len_t len ) {
        return convert( _str<T_Chr>(str), _ptr<T_Out>(ptr), len );
    }
    template < _cpu::check_any_chr T_Chr, _cpu::check_any_chr T_Out = T_Chr >
    constexpr len_t convert( _str<T_Chr> str, T_Out* ptr, len_t len ) {
        return convert( str, _ptr<T_Out>(ptr), len );
    }
    template < _cpu::check_any_chr T_Chr, _cpu::check_any_chr T_Out = T_Chr >
    constexpr len_t convert( const T_Chr* str, _ptr<T_Out> ptr, len_t len ) {
        return convert( _str<T_Chr>(str), ptr, len );
    }
    //
    template < _cpu::check_any_chr T_Chr, _cpu::check_any_chr T_Out >
    constexpr len_t conversion_comparison = sizeof(T_Chr) <= sizeof(T_Out) ? signed{unit} : (sizeof(T_Chr) / sizeof(T_Out) );
    //
    #pragma endregion
    //
    /// @brief sized pointer type
    /// @tparam T_Chr character format
    template < _cpu::check_any_chr T_Chr >
    class _view_ptr
    {
        _ptr<T_Chr> ptr;
        len_t len;
    public:
        template < len_t T_len >
        constexpr _view_ptr( const T_Chr(&that)[T_len] ) noexcept
        : ptr( that ), len( T_len ) { }
        constexpr _view_ptr( _ptr<T_Chr> that, len_t length ) noexcept
        : ptr( that ), len( length ) { }
        constexpr _view_ptr( _ptr<T_Chr> that ) noexcept
        : _view_ptr( that, nt_len( that ) ) { }
        constexpr _view_ptr( _mem::arr_view<T_Chr> that ) noexcept
        : _view_ptr( that, that.span ) { }
        /// @brief 
        /// @return the pointer string
        _ptr<T_Chr> view( ) const noexcept { return ptr; }
        /// @brief 
        /// @param p 
        /// @return 
        T_Chr view( addr_t p ) const noexcept { return ptr[p]; }
        void view( addr_t p, T_Chr val ) const noexcept { ptr[p] = val; }
        len_t length( ) const noexcept { return len; }
    };
    /// @brief sized string type
    /// @tparam T_Chr character format
    template < _cpu::check_any_chr T_Chr >
    class _view_str
    {
        _str<T_Chr> str;
        len_t len;
    public:
        template < len_t T_len >
        constexpr _view_str( const T_Chr(&that)[T_len] ) noexcept
        : str( that ), len( T_len ) { }
        constexpr _view_str( _view_ptr<T_Chr> that ) noexcept
        : str( that.view( ) ), len( that.length( ) ) { }
        constexpr _view_str( _str<T_Chr> that, len_t length ) noexcept
        : str( that ), len( length ) { }
        constexpr _view_str( _str<T_Chr> that ) noexcept
        : _view_str( that, nt_len( that ) ) { }
        constexpr _view_str( _mem::arr_view<const T_Chr> that ) noexcept
        : _view_str( that, that.span ) { }
        //
        _str<T_Chr> view( ) const noexcept { return str; }
        const T_Chr view( addr_t p ) const noexcept { return str[p]; }
        len_t length( ) const noexcept { return len; }
    };
    /// @brief base range sized pointer type
    using view_base_ptr = _view_ptr<_cpu::chr_base>;
    /// @brief wide range sized pointer type
    using view_wide_ptr = _view_ptr<_cpu::chr_wide>;
    /// @brief UTF-8 sized pointer type
    using view__unit_ptr = _view_ptr<_cpu::chr__unit>;
    /// @brief UTF-16 sized pointer type
    using view__dual_ptr = _view_ptr<_cpu::chr__dual>;
    /// @brief UTF-32 sized pointer type
    using view__quad_ptr = _view_ptr<_cpu::chr__quad>;
    /// @brief primary Unicode sized pointer type
    using view_uniptr = _view_ptr<_cpu::unicode_t>;
    /// @brief base range sized string type
    using view_base_str = _view_str<_cpu::chr_base>;
    /// @brief wide range sized string type
    using view_wide_str = _view_str<_cpu::chr_wide>;
    /// @brief UTF-8 sized string type
    using view__unit_str = _view_str<_cpu::chr__unit>;
    /// @brief UTF-16 sized string type
    using view__dual_str = _view_str<_cpu::chr__dual>;
    /// @brief UTF-32 sized string type
    using view__quad_str = _view_str<_cpu::chr__quad>;
    /// @brief primary Unicode sized string type
    using view_unistr = _view_str<_cpu::unicode_t>;
    //
    static constexpr size_t __flt_default_prec( size_t fraction, size_t radix ) {
        const size_t scale = radix == dual ? num(unit)
            : radix == octa ? num(octa)
            : radix == hexa ? num(hexa)
            : deci;
        return fraction / scale + ( fraction % scale != zero );
    }
    //
    constexpr view_base_str pass_str = { "true", unit + unit + unit + unit };
    constexpr view_base_str fail_str = { "false", unit + unit + unit + unit + unit };
    //
    template < _cpu::check_any_chr T_Chr >
    class _edit
    {
        _data::vect<T_Chr> data;
        //
        static constexpr T_Chr dec_start = T_Chr{'0'};
        static constexpr T_Chr dec_end = T_Chr{'9'};
        static constexpr T_Chr ext_upper = T_Chr{'A'};
        static constexpr T_Chr ext_lower = T_Chr{'a'};
        static constexpr T_Chr sign_neg = T_Chr{'-'};
        static constexpr T_Chr sign_pos = T_Chr{'+'};
        static constexpr T_Chr separator = T_Chr{'.'};
        static constexpr T_Chr nptr[quad+dual+unit] = { T_Chr{'n'}, T_Chr{'u'}, T_Chr{'l'}, T_Chr{'l'}, T_Chr{'p'}, T_Chr{'t'}, T_Chr{'r'} };
        static constexpr T_Chr inf_pos_upper[quad] = { sign_pos, T_Chr{'I'}, T_Chr{'N'}, T_Chr{'F'} };
        static constexpr T_Chr inf_neg_upper[quad] = { sign_neg, T_Chr{'I'}, T_Chr{'N'}, T_Chr{'F'} };
        static constexpr T_Chr inf_pos_lower[quad] = { sign_pos, T_Chr{'i'}, T_Chr{'n'}, T_Chr{'f'} };
        static constexpr T_Chr inf_neg_lower[quad] = { sign_neg, T_Chr{'i'}, T_Chr{'n'}, T_Chr{'f'} };
        static constexpr T_Chr nan_upper[dual + unit] = { T_Chr{'N'}, T_Chr{'A'}, T_Chr{'N'} };
        static constexpr T_Chr nan_lower[dual + unit] = { T_Chr{'N'}, T_Chr{'a'}, T_Chr{'N'} };
        static constexpr T_Chr exponent_lower[dual + unit] = { T_Chr{'e'}, sign_neg, sign_pos };
        static constexpr T_Chr exponent_upper[dual + unit] = { T_Chr{'E'}, sign_neg, sign_pos };
        static constexpr T_Chr zero_pos[dual] = { sign_pos, dec_start };
        static constexpr T_Chr zero_neg[dual] = { sign_neg, dec_start };
        static constexpr T_Chr ptr_sign = T_Chr{'x'};
        //
        static constexpr T_Chr digit( size_t value, bool upper ) {
            return value < deci
                ? static_cast<T_Chr>( dec_start + value )
                : static_cast<T_Chr>( ( upper ? ext_upper : ext_lower ) + value - deci );
        }
        template < _cpu::check_any_nat T_Nat >
        static constexpr _view_str<T_Chr> _integer_buf( T_Nat value, size_t min_w, size_t radix, bool upper ) {
            const size_t bit_count = sizeof(T_Nat) * octa;
            const size_t width = bit_count > min_w ? bit_count : min_w;
            if ( width >= max_len / sizeof(T_Chr) )
                return { nullptr, zero };
            _mem::_raw_arr<T_Chr> arr = _mem::create_buffer( sizeof(T_Chr) * ( width + unit ), alignof(T_Chr) );
            if ( !arr )
                return { nullptr, zero };
            size_t len = zero;
            do {
                arr[len++] = digit( static_cast<size_t>( value % radix ), upper );
                value = static_cast<T_Nat>( value / radix );
            } while ( value != zero );
            while ( len < min_w )
                arr[len++] = dec_start;
            for ( size_t i = zero; i < len / dual; ++i ) {
                const T_Chr temp = arr[i];
                arr[i] = arr[len - unit - i];
                arr[len - unit - i] = temp;
            }
            return { arr, len };
        }
        template < _cpu::check_any_int T_Int >
        static constexpr _view_str<T_Chr> _signed_integer_buf( T_Int value, size_t min_w, size_t radix, bool upper ) {
#if FCOOLMACRO_HEXA
            using T_Nat = _type::_cond<
                sizeof(T_Int) == sizeof(_cpu::nat_hexa),
                _cpu::nat_hexa,
                _cpu::_nat_from_size<sizeof(T_Int)>
            >;
#else
            using T_Nat = _cpu::_nat_from_size<sizeof(T_Int)>;
#endif
            const bool is_negative = value < zero;
            T_Nat magnitude = is_negative
                ? static_cast<T_Nat>( -(value + unit) )
                : static_cast<T_Nat>( value );
            if ( is_negative )
                ++magnitude;
            _view_str<T_Chr> digits = _integer_buf<T_Nat>( magnitude, min_w, radix, upper );
            if ( !digits.view( ) )
                return digits;
            if ( is_negative ) {
                _mem::_raw_arr<T_Chr> arr = _mem::create_buffer( sizeof(T_Chr) * ( digits.length( ) + unit ), alignof(T_Chr) );
                if ( !arr ) {
                    _mem::delete_buffer( _mem::cast<void>( digits.view( ) ), alignof(T_Chr) );
                    return { nullptr, zero };
                }
                arr[0] = sign_neg;
                _ptr<T_Chr> out = arr;
                out += static_cast<addr_t>( unit );
               _mem::copy( digits.view( ), out, digits.length( ) );
                _mem::delete_buffer( _mem::cast<void>( digits.view( ) ), alignof(T_Chr) );
                return { arr, digits.length( ) + unit };
            }
            return digits;
        }
        static constexpr _view_str<T_Chr> _literal_buf( const char* text, size_t len ) {
            _mem::_raw_arr<T_Chr> arr = _mem::create_buffer( sizeof(T_Chr) * len, alignof(T_Chr) );
            if ( !arr )
                return { nullptr, zero };
            for ( size_t i = zero; i < len; ++i )
                arr[i] = static_cast<T_Chr>( text[i] );
            return { arr, len };
        }
        template < _cpu::check_any_flt T_Flt >
        static constexpr _view_str<T_Chr> _float_buf( T_Flt value, size_t prec, size_t radix, bool upper ) {
            if ( value != value )
                return _literal_buf( upper ? nan_upper : nan_lower, dual + unit );
            const bool is_negative = value < signed{zero};
            T_Flt magnitude = is_negative ? -value : value;
            bool is_zero = magnitude == signed{zero};
            if ( ( magnitude / T_Flt(dual) == magnitude || magnitude * T_Flt(dual) == magnitude ) && !is_zero ) {
                if ( is_negative )
                    return _literal_buf( upper ? inf_neg_upper : inf_neg_lower, quad );
                return _literal_buf( upper ? inf_pos_upper : inf_pos_lower, quad );
            }
            const size_t int_max = _cpu::val_flt_exp_bias<T_Flt> + unit;
            const size_t prefix = is_negative ? num(unit) : zero;
            if ( int_max > max_len - quad - prefix ||
                 prec > max_len - int_max - quad - prefix )
                return { nullptr, zero };
            const size_t capacity = int_max + prec + quad + prefix;
            if ( capacity > max_len / sizeof(T_Chr) )
                return { nullptr, zero };
            _mem::_raw_arr<T_Chr> arr = _mem::create_buffer( sizeof(T_Chr) * capacity, alignof(T_Chr) );
            if ( !arr )
                return { nullptr, zero };
            size_t len = zero;
            if ( is_negative )
                arr[len++] = sign_neg;
            else if ( is_zero )
                arr[len++] = sign_pos;
            T_Flt place = T_Flt(unit);
            while ( place <= magnitude / T_Flt(radix) )
                place *= T_Flt(radix);
            do {
                size_t value_digit = zero;
                while ( magnitude >= place && value_digit < radix ) {
                    magnitude -= place;
                    ++value_digit;
                }
                arr[len++] = digit( value_digit, upper );
                place /= T_Flt(radix);
            } while ( place >= T_Flt(unit) );
            if ( prec != zero ) {
                arr[len++] = separator;
                for ( size_t i = zero; i < prec; ++i ) {
                    magnitude *= T_Flt(radix);
                    size_t value_digit = zero;
                    while ( magnitude >= T_Flt(unit) && value_digit < radix ) {
                        magnitude -= T_Flt(unit);
                        ++value_digit;
                    }
                    arr[len++] = digit( value_digit, upper );
                }
            }
            magnitude *= T_Flt(radix);
            size_t next_digit = zero;
            while ( magnitude >= T_Flt(unit) && next_digit < radix ) {
                magnitude -= T_Flt(unit);
                ++next_digit;
            }
            if ( next_digit * dual >= radix ) {
                size_t pos = len;
                bool carry = pass;
                while ( pos > prefix && carry ) {
                    --pos;
                    if ( arr[pos] == separator )
                        continue;
                    size_t current = zero;
                    while ( current < radix && arr[pos] != digit( current, upper ) )
                        ++current;
                    if ( current + unit < radix ) {
                        arr[pos] = digit( current + unit, upper );
                        carry = fail;
                    } else {
                        arr[pos] = dec_start;
                    }
                }
                if ( carry ) {
                    for ( size_t i = len; i > prefix; --i )
                        arr[i] = arr[i - unit];
                    arr[prefix] = digit( unit, upper );
                    ++len;
                }
            }
            return { arr, len };
        }
        //
        template < _cpu::check_any_nat T_Nat >
        static constexpr _view_str<T_Chr> hex_buff( T_Nat v, len_t min_w, bool upper ) {
            return _integer_buf( v, min_w, hexa, upper );
        }
        template < _cpu::check_any_int T_Int >
        static constexpr _view_str<T_Chr> hex_buff( T_Int v, len_t min_w, bool upper ) {
            return _signed_integer_buf( v, min_w, hexa, upper );
        }
        template < _cpu::check_any_flt T_Flt >
        static constexpr _view_str<T_Chr> hex_buff( T_Flt v, size_t prec, bool upper ) {
            return _float_buf( v, prec, hexa, upper );
        }
        //
        template < _cpu::check_any_nat T_Nat >
        static constexpr _view_str<T_Chr> dec_buf( T_Nat v, len_t min_w ) {
            return _integer_buf( v, min_w, deci, fail );
        }
        template < _cpu::check_any_int T_Int >
        static constexpr _view_str<T_Chr> dec_buf( T_Int v, len_t min_w ) {
            return _signed_integer_buf( v, min_w, deci, fail );
        }
        template < _cpu::check_any_flt T_Flt >
        static constexpr _view_str<T_Chr> _dec_buf( T_Flt v, size_t prec ) {
            return _float_buf( v, prec, deci, fail );
        }
        //
        template < _cpu::check_any_nat T_Nat >
        static constexpr _view_str<T_Chr> oct_buf( T_Nat v, len_t min_w ) {
            return _integer_buf( v, min_w, octa, pass );
        }
        template < _cpu::check_any_int T_Int >
        static constexpr _view_str<T_Chr> oct_buf( T_Int v, len_t min_w ) {
            return _signed_integer_buf( v, min_w, octa, pass );
        }
        template < _cpu::check_any_flt T_Flt >
        static constexpr _view_str<T_Chr> oct_buf( T_Flt v, size_t prec ) {
            return _float_buf( v, prec, octa, pass );
        }
        //
        template < _cpu::check_any_nat T_Nat >
        static constexpr _view_str<T_Chr> bin_buf( T_Nat v, len_t min_w ) {
            return _integer_buf( v, min_w, dual, pass );
        }
        template < _cpu::check_any_int T_Int >
        static constexpr _view_str<T_Chr> bin_buf( T_Int v, len_t min_w ) {
            return _signed_integer_buf( v, min_w, dual, pass );
        }
        template < _cpu::check_any_flt T_Flt >
        static constexpr _view_str<T_Chr> bin_buf( T_Flt v, size_t prec ) {
            return _float_buf( v, prec, dual, fail );
        }
        //
    public:
        constexpr _edit( ) = default;
        constexpr _edit( T_Chr v )
        : data( unit, v ) { }
        constexpr _edit( T_Chr v, len_t l )
        : data( l ) { set_front( v, l ); }
        constexpr _edit( _str<T_Chr> s, len_t len )
        : data( len ) {
            if ( data )
                data.__source_front( s, len );
        }
        constexpr _edit( _str<T_Chr> s )
        : _edit( s, nt_len( s ) ) { }
        constexpr _edit( const _mem::smart_arr<T_Chr>& arr )
        : _edit( arr, arr.span( ) ) { }
        constexpr _edit( const _mem::smart_arr<T_Chr>&& arr )
        : _edit( arr ) { }
        template < size_t T_len >
        constexpr _edit( const T_Chr(&s)[T_len] )
        : _edit( s, T_len ) { }
        constexpr _edit( const T_Chr* const& s )
        : _edit( s, nt_len( s ) ) { }
        constexpr _edit( const T_Chr* const&& s )
        : _edit( s ) { }
        constexpr _edit( _view_str<T_Chr> s )
        : _edit( s.view( ), s.length( ) ) { }
        template < _cpu::check_any_nat T_Nat >
        constexpr _edit( T_Nat v, len_t min_w = unit ) {
            add_back( dec_buf<T_Nat>( v, min_w ) );
        }
        template < _cpu::check_any_int T_Int >
        constexpr _edit( T_Int v, len_t min_w = unit ) {
            add_back( dec_buf<T_Int>( v, min_w ) );
        }
        template < _cpu::check_any_flt T_Flt >
        constexpr _edit( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            add_back( _dec_buf<T_Flt>( v, prec ) );
        }
        constexpr explicit _edit( bool& v ) {
            add_back( v );
        }
        constexpr explicit _edit( bool&& v ) {
            add_back( v );
        }
        constexpr explicit _edit( decltype(nullptr) ) {
            add_back( nptr, quad+dual+unit );
        }
        constexpr _edit( _mem::_raw_ptr<void> ptr ) {
            if ( ptr ) {
                add_back( dec_start );
                add_back( ptr_sign );
                add_back( hex_buff<addr_t>( static_cast<addr_t>( ptr ), sizeof(addr_t) * dual, pass ) );
            } else
                add_back( nptr, quad+dual+unit );
        }
        //
        constexpr T_Chr& operator[]( addr_t p ) {
            return data[p];
        }
        constexpr _view_ptr<T_Chr> view( ) {
            return data.view( );
        }
        constexpr operator _view_str<T_Chr>( ) {
            return view( );
        }
        //
        /// @brief reduces memory usage by freeing unused memory
        /// @return 
        constexpr bool compress( ) noexcept {
            return data.compress( );
        }
        /// @brief access specified character with bounds checking
        /// @param p point
        /// @return a character
        constexpr T_Chr& get_at( addr_t p ) noexcept {
            return data.get_at( p );
        }
        /// @brief assign a specified character with bounds checking
        /// @param p point
        /// @param v value
        constexpr void  set_at( addr_t p, T_Chr v ) {
            data.__source_at( p, &v );
        }
        /// @brief assign multiple specified characters with bounds checking
        /// @param p point
        /// @param v value
        /// @param l block length
        constexpr void  set_at( addr_t p, T_Chr v, len_t l ) {
            for ( len_t i = zero; i < l; ++i )
                set_at( p + i, v );
        }
        /// @brief copy a block of characters from another string
        /// @param p point
        /// @param s string
        /// @param l block length
        constexpr void  set_at( addr_t p, _str<T_Chr> s, len_t l ) {
            data.__source_at( p, s, l );
        }
        /// @brief copy a block of characters from null terminated string
        /// @param p point
        /// @param s string
        constexpr void  set_at( addr_t p, _str<T_Chr> s ) {
            set_at( p, s, nt_len( s ) );
        }
        /// @brief copy a block of characters from sized string
        /// @param p point
        /// @param s string
        constexpr void  set_at( addr_t p, _view_str<T_Chr> s ) {
            set_at( p, s.view( ), s.length( ) );
        }
        /// @brief access the first character
        /// @return a character
        constexpr T_Chr& get_front( ) noexcept {
            return data.get_front( );
        }
        /// @brief assign the first character
        /// @param v value
        constexpr void  set_front( T_Chr v ) {
            data.__source_front( &v );
        }
        /// @brief assign multiple character from the begin
        /// @param v value
        /// @param l block length
        constexpr void  set_front( T_Chr v, len_t l ) {
            for ( len_t i = zero; i < l; ++i )
                set_at( i, v );
        }
        /// @brief copy a block of characters from another string
        /// @param s string
        /// @param l block length
        constexpr void  set_front( _str<T_Chr> s, len_t l ) {
            data.__source_front( s, l );
        }
        /// @brief copy a block of characters from null terminated string
        /// @param s string
        constexpr void  set_front( _str<T_Chr> s ) {
            set_front( s, nt_len( s ) );
        }
        /// @brief copy a block of characters from sized string
        /// @param s string
        constexpr void  set_front( _view_str<T_Chr> s ) {
            set_front( s.view( ), s.length( ) );
        }
        /// @brief access the last character
        /// @return a character
        constexpr T_Chr& get_back( ) noexcept {
            return data.get_back( );
        }
        /// @brief assign the last character
        /// @param v value
        constexpr void  set_back( T_Chr v ) {
            data.__source_back( &v );
        }
        /// @brief assign multiple character from the end
        /// @param v value
        /// @param l block length
        constexpr void  set_back( T_Chr v, len_t l ) {
            for ( len_t i = unit; i <= l; ++i )
                set_at( data.n - i, v );
        }
        /// @brief copy a block of characters from another string
        /// @param s string
        /// @param l block length
        constexpr void  set_back( _str<T_Chr> s, len_t l ) {
            data.__source_back( _mem::cast<T_Chr>(s), l );
        }
        /// @brief copy a block of characters from null terminated string
        /// @param s string
        constexpr void  set_back( _str<T_Chr> s ) {
            set_back( s, nt_len( s ) );
        }
        /// @brief copy a block of characters from sized string
        /// @param s string
        constexpr void  set_back( _view_str<T_Chr> s ) {
            set_back( s.view( ), s.length( ) );
        }
        //
        /// @brief reserve space and insert characters at a specified position
        /// @param p insertion position
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_at_l( addr_t p, len_t l = unit ) {
            const len_t old_len = data.span( );
            if ( l == zero )
                return pass;
            if ( p > old_len || l > max_len - old_len )
                return fail;
            return data.__reserve_at( p, l );
        }
        /// @brief insert a character at a specified position
        /// @param p insertion position
        /// @param v character value
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, T_Chr v ) {
            return data.add_at( p, v );
        }
        /// @brief insert repeated characters at a specified position
        /// @param p insertion position
        /// @param v character value
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, T_Chr v, len_t l ) {
            bool r = add_at( p, l );
            if ( r )
                set_at( p, v, l );
            return r;
        }
        /// @brief insert a block of characters at a specified position
        /// @param p insertion position
        /// @param s source string
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, _str<T_Chr> s, len_t l ) {
            bool r = add_at( p, l );
            if ( r )
                set_at( p, s, l );
            return r;
        }
        /// @brief insert a null-terminated string at a specified position
        /// @param p insertion position
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, _str<T_Chr> s ) {
            return add_at( p, s, nt_len( s ) );
        }
        /// @brief insert an array at a specified position
        /// @param p insertion position
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, const _mem::smart_arr<T_Chr>& arr ) {
            return add_at( p, arr, arr.span( ) );
        }
        /// @brief insert an array at a specified position
        /// @param p insertion position
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, const _mem::smart_arr<T_Chr>&& arr ) {
            return add_at( p, arr );
        }
        /// @brief insert a character array at a specified position
        /// @param p insertion position
        /// @param s source array
        /// @return whether the insertion succeeded
        template < size_t T_len >
        constexpr bool add_at( addr_t p, const T_Chr(&s)[T_len] ) {
            return add_at( p, s, T_len );
        }
        /// @brief insert a null-terminated string at a specified position
        /// @param p insertion position
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, const T_Chr* const& s ) {
            return add_at( p, _str<T_Chr>(s) );
        }
        /// @brief insert a null-terminated string at a specified position
        /// @param p insertion position
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, const T_Chr* const&& s ) {
            return add_at( p, s );
        }
        /// @brief insert a sized string at a specified position
        /// @param p insertion position
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, _view_str<T_Chr> s ) {
            return add_at( p, s.view( ), s.length( ) );
        }
        /// @brief insert an integer in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at( addr_t p, T_Nat v, len_t min_w = unit ) {
            return add_at_dec( p, v, min_w );
        }
        /// @brief insert an integer in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at( addr_t p, T_Int v, len_t min_w = unit ) {
            return add_at_dec( p, v, min_w );
        }
        /// @brief insert a floating-point value in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            _view_str<T_Chr> buff = _dec_buf<T_Flt>( v, prec );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a boolean value at a specified position
        /// @param p insertion position
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, bool& v ) {
            if constexpr ( _type::is_same<T_Chr,_cpu::chr_base> )
                return add_at( p, v ? pass_str : fail_str );
            else {
                view_base_str view = v ? pass_str : fail_str;
                const _text::len_t l = view.length( );
                _ptr<T_Chr> ptr = _mem::create_handle( sizeof(T_Chr) * l, alignof(T_Chr) );
                if ( ptr ) {
                    bool r = add_at( p, ptr, convert<_cpu::chr_base,T_Chr>( view.view( ), ptr, l ) );
                    _mem::delete_handle( ptr, alignof(T_Chr) );
                    return r;
                }
                return fail;
            }
        }
        /// @brief insert a boolean value at a specified position
        /// @param p insertion position
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, bool&& v ) {
            return add_at( p, v );
        }
        /// @brief insert a pointer string at a specified position
        /// @param p insertion position
        /// @param ptr pointer value
        /// @return whether the insertion succeeded
        constexpr bool add_at( addr_t p, _mem::_raw_ptr<void> ptr ) {
            return add_at( p, _edit{ptr} );
        }
        /// @brief reserve space at the beginning of the string
        /// @param l block length
        /// @return whether the reservation succeeded
        constexpr bool add_front_l( len_t l = unit ) {
            return data.__reserve_front( l );
        }
        /// @brief insert a character at the beginning
        /// @param v character value
        /// @return whether the insertion succeeded
        constexpr bool add_front( T_Chr v ) {
            if ( !add_front( ) ) return fail;
            set_front( v );
            return pass;
        }
        /// @brief insert repeated characters at the beginning
        /// @param v character value
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_front( T_Chr v, len_t l ) {
            if ( !add_front( l ) ) return fail;
            set_front( v, l );
            return pass;
        }
        /// @brief insert a block of characters at the beginning
        /// @param s source string
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_front( _str<T_Chr> s, len_t l ) {
            if ( !add_front( l ) ) return fail;
            set_front( s, l );
            return pass;
        }
        /// @brief insert a null-terminated string at the beginning
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_front( _str<T_Chr> s ) {
            return add_front( s, nt_len( s ) );
        }
        /// @brief insert an array at the beginning
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_front( const _mem::smart_arr<T_Chr>& arr ) {
            return add_front( arr, arr.span( ) );
        }
        /// @brief insert an array at the beginning
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_front( const _mem::smart_arr<T_Chr>&& arr ) {
            return add_front( arr );
        }
        /// @brief insert a character array at the beginning
        /// @param s source array
        /// @return whether the insertion succeeded
        template < size_t T_len >
        constexpr bool add_front( const T_Chr(&s)[T_len] ) {
            return add_front( s, T_len );
        }
        /// @brief insert a null-terminated string at the beginning
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_front( const T_Chr* const& s ) {
            return add_front( _str<T_Chr>(s) );
        }
        /// @brief insert a null-terminated string at the beginning
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_front( const T_Chr* const&& s ) {
            return add_front( s );
        }
        /// @brief insert a sized string at the beginning
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_front( _view_str<T_Chr> s ) {
            return add_front( s.view( ), s.length( ) );
        }
        /// @brief insert an integer in decimal form at the beginning
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_front( T_Nat v, len_t min_w = unit ) {
            return add_front_dec( v, min_w );
        }
        /// @brief insert an integer in decimal form at the beginning
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_front( T_Int v, len_t min_w = unit ) {
            return add_front_dec( v, min_w );
        }
        /// @brief insert a floating-point value in decimal form at the beginning
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_front( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            return add_front_dec( v, prec );
        }
        /// @brief insert a boolean value at the beginning
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_front( bool& v ) {
            return add_at( zero, v );
        }
        /// @brief insert a boolean value at the beginning
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_front( bool&& v ) {
            return add_front( v );
        }
        /// @brief insert a pointer string at the beginning
        /// @param ptr pointer value
        /// @return whether the insertion succeeded
        constexpr bool add_front( _mem::_raw_ptr<void> ptr ) {
            return add_front( _edit{ptr} );
        }
        /// @brief reserve space at the end of the string
        /// @param l block length
        /// @return whether the reservation succeeded
        constexpr bool add_back_l( len_t l = unit ) {
            return data.__reserve_back( l );
        }
        /// @brief append a character
        /// @param v character value
        /// @return whether the insertion succeeded
        constexpr bool add_back( T_Chr v ) {
            if ( !add_back_l( ) ) return fail;
            set_back( v );
            return pass;
        }
        /// @brief append repeated characters
        /// @param v character value
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_back( T_Chr v, len_t l ) {
            if ( !add_back( l ) ) return fail;
            set_back( v, l );
            return pass;
        }
        /// @brief append a block of characters
        /// @param s source string
        /// @param l block length
        /// @return whether the insertion succeeded
        constexpr bool add_back( _str<T_Chr> s, len_t l ) {
            if ( !add_back_l( l ) ) return fail;
            set_back( s, l );
            return pass;
        }
        /// @brief append a null-terminated string
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_back( _str<T_Chr> s ) {
            return add_back( s, nt_len( s ) );
        }
        /// @brief append an array
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_back( const _mem::smart_arr<T_Chr>& arr ) {
            return add_back( arr, arr.span( ) );
        }
        /// @brief append an array
        /// @param arr source array
        /// @return whether the insertion succeeded
        constexpr bool add_back( const _mem::smart_arr<T_Chr>&& arr ) {
            return add_back( arr );
        }
        /// @brief append a character array
        /// @param s source array
        /// @return whether the insertion succeeded
        template < size_t T_len >
        constexpr bool add_back( const T_Chr(&s)[T_len] ) {
            return add_back( s, T_len );
        }
        /// @brief append a null-terminated string
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_back( const T_Chr* const& s ) {
            return add_back( _str<T_Chr>(s) );
        }
        /// @brief append a null-terminated string
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_back( const T_Chr* const&& s ) {
            return add_back( s );
        }
        /// @brief append a sized string
        /// @param s source string
        /// @return whether the insertion succeeded
        constexpr bool add_back( _view_str<T_Chr> s ) {
            return add_back( s.view( ), s.length( ) );
        }
        /// @brief append a boolean value
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_back( bool& v ) {
            if constexpr ( _type::is_same<T_Chr,_cpu::chr_base> )
                return add_back( v ? pass_str : fail_str );
            else {
                view_base_str view = v ? pass_str : fail_str;
                const _text::len_t l = view.length( );
                _ptr<T_Chr> ptr = _mem::create_handle( sizeof(T_Chr) * l, alignof(T_Chr) );
                if ( ptr ) {
                    bool r = add_back( ptr, convert<_cpu::chr_base,T_Chr>( view.view( ), ptr, l ) );
                    _mem::delete_handle( ptr, alignof(T_Chr) );
                    return r;
                }
                return fail;
            }
        }
        /// @brief append a boolean value
        /// @param v value
        /// @return whether the insertion succeeded
        constexpr bool add_back( bool&& v ) {
            return add_back( v );
        }
        /// @brief append a pointer string
        /// @param ptr pointer value
        /// @return whether the insertion succeeded
        constexpr bool add_back( _mem::_raw_ptr<void> ptr ) {
            return add_back( _edit{ptr} );
        }
        //
        
        //
        /// @brief remove a block of characters at a specified position
        /// @param p starting position
        /// @param l block length
        constexpr void pop_at( addr_t p, len_t l = unit ) {
            data.raw_pop_at( p, l );
        }
        /// @brief remove characters from the beginning
        /// @param l block length
        constexpr void pop_front( len_t l = unit ) {
            data.pop_front( l );
        }
        /// @brief remove characters from the end
        /// @param l block length
        constexpr void pop_back( len_t l = unit ) {
            data.pop_back( l );
        }
        /// @brief clears the string
        constexpr void clear( ) {
            data.__clear( );
        }
        /// @brief wipes the whole string data
        constexpr void wipe( ) {
            data.__wipe( );
        }
        /// @brief reserve a block of storage
        /// @param p reserving position
        /// @param l block length
        /// @return weather reserving was successful
        constexpr bool _reserve_at( addr_t p, len_t l ) {
            return data.__reserve_at( p, l );
        }
        /// @brief reserve a block of storage
        /// @param l block length
        /// @return weather reserving was successful
        constexpr bool _reserve_front( len_t l ) {
            return data.__reserve_front( l );
        }
        /// @brief reserve a block of storage
        /// @param l block length
        /// @return weather reserving was successful
        constexpr bool _reserve_back( len_t l ) {
            return data.__reserve_back( l );
        }
        //
        /// @brief insert an unsigned integer in uppercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at_hex_u( addr_t p, T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, pass );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a signed integer in uppercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at_hex_u( addr_t p, T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, pass );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a floating-point value in uppercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at_hex_u( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, pass );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert an unsigned integer in lowercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at_hex_l( addr_t p, T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, fail );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a signed integer in lowercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at_hex_l( addr_t p, T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, fail );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a floating-point value in lowercase hexadecimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at_hex_l( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, fail );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert an unsigned integer in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at_dec( addr_t p, T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Nat>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a signed integer in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at_dec( addr_t p, T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Int>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a floating-point value in decimal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at_dec( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            _view_str<T_Chr> buff = _dec_buf( v, prec );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert an unsigned integer in octal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at_oct( addr_t p, T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Nat>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a signed integer in octal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at_oct( addr_t p, T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Int>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a floating-point value in octal form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at_oct( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, octa ) ) {
            _view_str<T_Chr> buff = oct_buf( v, prec );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert an unsigned integer in binary form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_nat T_Nat >
        constexpr bool add_at_bin( addr_t p, T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Nat>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a signed integer in binary form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param min_w minimum output width
        /// @return whether the insertion succeeded
        template < _cpu::check_any_int T_Int >
        constexpr bool add_at_bin( addr_t p, T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Int>( v, min_w );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        /// @brief insert a floating-point value in binary form at a specified position
        /// @param p insertion position
        /// @param v value
        /// @param prec fractional precision
        /// @return whether the insertion succeeded
        template < _cpu::check_any_flt T_Flt >
        constexpr bool add_at_bin( addr_t p, T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, dual ) ) {
            _view_str<T_Chr> buff = bin_buf( v, prec );
            bool r = add_at( p, buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
            return r;
        }
        //
        /// @brief prepend an unsigned integer in uppercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_front_hex_u( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, pass );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a signed integer in uppercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_front_hex_u( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, pass );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a floating-point value in uppercase hexadecimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_front_hex_u( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, pass );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend an unsigned integer in lowercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_front_hex_l( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, fail );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a signed integer in lowercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_front_hex_l( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, fail );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a floating-point value in lowercase hexadecimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_front_hex_l( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, fail );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend an unsigned integer in decimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_front_dec( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Nat>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a signed integer in decimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_front_dec( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Int>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a floating-point value in decimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_front_dec( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            _view_str<T_Chr> buff = _dec_buf( v, prec );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend an unsigned integer in octal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_front_oct( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Nat>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a signed integer in octal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_front_oct( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Int>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a floating-point value in octal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_front_oct( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, octa ) ) {
            _view_str<T_Chr> buff = oct_buf( v, prec );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend an unsigned integer in binary form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_front_bin( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Nat>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a signed integer in binary form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_front_bin( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Int>( v, min_w );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief prepend a floating-point value in binary form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_front_bin( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, dual ) ) {
            _view_str<T_Chr> buff = bin_buf( v, prec );
            add_front( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        //
        /// @brief append an unsigned integer in uppercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_back_hex_u( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, pass );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a signed integer in uppercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_back_hex_u( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, pass );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a floating-point value in uppercase hexadecimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_back_hex_u( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, pass );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append an unsigned integer in lowercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_back_hex_l( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Nat>( v, min_w, pass );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a signed integer in lowercase hexadecimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_back_hex_l( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = hex_buff<T_Int>( v, min_w, pass );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a floating-point value in lowercase hexadecimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_back_hex_l( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
            _view_str<T_Chr> buff = hex_buff( v, prec, fail );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append an unsigned integer in decimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_back_dec( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Nat>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a signed integer in decimal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_back_dec( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = dec_buf<T_Int>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a floating-point value in decimal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_back_dec( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
            _view_str<T_Chr> buff = _dec_buf( v, prec );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append an unsigned integer in octal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_back_oct( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Nat>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a signed integer in octal form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_back_oct( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = oct_buf<T_Int>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a floating-point value in octal form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_back_oct( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, octa ) ) {
            _view_str<T_Chr> buff = oct_buf( v, prec );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append an unsigned integer in binary form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_nat T_Nat >
        constexpr void add_back_bin( T_Nat v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Nat>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a signed integer in binary form
        /// @param v value
        /// @param min_w minimum output width
        template < _cpu::check_any_int T_Int >
        constexpr void add_back_bin( T_Int v, len_t min_w = unit ) {
            _view_str<T_Chr> buff = bin_buf<T_Int>( v, min_w );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        /// @brief append a floating-point value in binary form
        /// @param v value
        /// @param prec fractional precision
        template < _cpu::check_any_flt T_Flt >
        constexpr void add_back_bin( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, dual ) ) {
            _view_str<T_Chr> buff = bin_buf( v, prec );
            add_back( buff );
            _mem::delete_buffer( _mem::cast<void>( buff.view( ) ), alignof(T_Chr) );
        }
        //
        /// @brief finds the first occurrence of the given character
        /// @param p point
        /// @param v value
        /// @param out a reference where the index of the found character will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_at( addr_t p, T_Chr v, addr_t& out ) {
            const addr_t total = data.span( );
            for ( addr_t i = p; i < total; ++i ) {
                if ( data[i] == v ) {
                    out = i;
                    return pass;
                }
            }
            return fail;
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s string
        /// @param l block length
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_at( addr_t p, _str<T_Chr> s, len_t l, addr_t& out ) {
            const addr_t total = data.span( );
            if ( p > total || l > total - p ) return fail;
            for ( len_t i = zero; i < l; ++i )
                if ( data[p + i] != s[i] ) return fail;
            out = p;
            return pass;
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s null teminated string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_at( addr_t p, _str<T_Chr> s ) {
            return find_at( p, s, nt_len( s ) );
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s sized string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_at( addr_t p, _view_str<T_Chr> s ) {
            return find_at( p, s.view( ), s.length( ) );
        }
        /// @brief finds the first occurrence of the given character
        /// @param p point
        /// @param v value
        /// @param out a reference where the index of the found character will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_front( T_Chr v, addr_t& out ) {
            return find_at( zero, v, out );
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s string
        /// @param l block length
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_front( _str<T_Chr> s, len_t l, addr_t& out ) {
            const addr_t total = data.span( );
            if ( l > total ) return fail;
            for ( addr_t p = zero; p <= total - l; ++p )
                if ( find_at( p, s, l, out ) ) return pass;
            return fail;
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s null teminated string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_front( _str<T_Chr> s, addr_t& out ) {
            return find_front( s, nt_len( s ), out );
        }
        /// @brief finds the first occurrence of the given substring
        /// @param p point
        /// @param s sized string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_front( _view_str<T_Chr> s, addr_t& out ) {
            return find_front( s.view( ), s.length( ), out );
        }
        /// @brief finds the last occurrence of the given character
        /// @param p point
        /// @param v value
        /// @param out a reference where the index of the found character will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_back( T_Chr v, addr_t& out ) {
            const addr_t total = data.span( );
            for ( addr_t i = total; i > zero; --i ) {
                if ( data[i - unit] == v ) {
                    out = i - unit;
                    return pass;
                }
            }
            return fail;
        }
        /// @brief finds the last occurrence of the given substring
        /// @param p point
        /// @param s string
        /// @param l block length
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_back( _str<T_Chr> s, len_t l, addr_t& out ) {
            const addr_t total = data.span( );
            if ( l > total ) return fail;
            for ( addr_t i = total - l + unit; i > zero; --i )
                if ( find_at( i - unit, s, l, out ) ) return pass;
            return fail;
        }
        /// @brief finds the last occurrence of the given substring
        /// @param p point
        /// @param s null teminated string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_back( _str<T_Chr> s, addr_t& out ) {
            return find_back( s, nt_len( s ), out );
        }
        /// @brief finds the last occurrence of the given substring
        /// @param p point
        /// @param s sized string
        /// @param out a reference where the index of the found substring will be placed in case found
        /// @return boolean weather a instance was found
        constexpr bool find_back( _view_str<T_Chr> s, addr_t& out ) {
            return find_back( s.view( ), s.length( ), out );
        }
        /// @brief checks occurrence of the given character
        /// @param p point
        /// @param v value
        /// @return boolean weather a instance was found
        constexpr bool contains( T_Chr v ) {
            addr_t in;
            return find_front( v, in );
        }
        /// @brief checks occurrence of the given substring
        /// @param s string
        /// @param l block length
        /// @return boolean weather a instance was found
        constexpr bool contains( _str<T_Chr> s, len_t l ) {
            addr_t in;
            return find_front( s, l, in );
        }
        /// @brief checks occurrence of the given substring
        /// @param s sized string
        /// @return boolean weather a instance was found
        constexpr bool contains( _view_str<T_Chr> s ) {
            addr_t in;
            return find_front( s, in );
        }
        /// @brief get a copy of a substring
        /// @param p starting position
        /// @param l maximum substring length
        /// @return copied substring
        constexpr _edit substring( addr_t p, len_t l = max_len ) const {
            const addr_t total = data.span( );
            if ( p > total )
                return { };
            if ( l > total - p )
                l = total - p;
            _str<T_Chr> source = data._get( );
            source += p;
            return _edit( source, l );
        }
        /// @brief get a non-owning view of a substring
        /// @param p starting position
        /// @param l maximum substring length
        /// @return substring view
        constexpr _view_str<T_Chr> subview( addr_t p, len_t l = max_len ) const noexcept {
            const addr_t total = data.span( );
            if ( p > total )
                return { nullptr, zero };
            if ( l > total - p )
                l = total - p;
            _str<T_Chr> source = data._get( );
            source += p;
            return { source, l };
        }
        //
        /// @brief get a pointer to the string data
        /// @return pointer to the characters
        constexpr _ptr<T_Chr> ptr( ) const noexcept {
            return data._get( );
        }
        /// @brief get the string data as a string pointer
        /// @return string pointer
        constexpr _str<T_Chr> str( ) const noexcept {
            return data._get( );
        }
        /// @brief get the number of characters
        /// @return string length
        constexpr len_t len( ) const noexcept {
            return data.span( );
        }
        /// @brief get the amount of character data
        /// @return string length
        constexpr len_t cap( ) const noexcept {
            return data.capacity( );
        }
        //
        /// @brief get an iterator to the first character
        /// @return forward iterator
        constexpr auto begin( ) noexcept {
            return data.begin( );
        }
        /// @brief get a constant iterator to the first character
        /// @return forward iterator
        constexpr auto begin( ) const noexcept {
            return data.begin( );
        }
        /// @brief get an iterator past the last character
        /// @return forward iterator
        constexpr auto end( ) noexcept {
            return data.end( );
        }
        /// @brief get a constant iterator past the last character
        /// @return forward iterator
        constexpr auto end( ) const noexcept {
            return data.end( );
        }
        /// @brief get a constant iterator to the first character
        /// @return constant forward iterator
        constexpr auto cbegin( ) const noexcept {
            return data.cbegin( );
        }
        /// @brief get a constant iterator past the last character
        /// @return constant forward iterator
        constexpr auto cend( ) const noexcept {
            return data.cend( );
        }
        /// @brief get a reverse iterator to the last character
        /// @return reverse iterator
        constexpr auto rbegin( ) noexcept {
            return data.rbegin( );
        }
        /// @brief get a constant reverse iterator to the last character
        /// @return reverse iterator
        constexpr auto rbegin( ) const noexcept {
            return data.rbegin( );
        }
        /// @brief get a reverse iterator past the first character
        /// @return reverse iterator
        constexpr auto rend( ) noexcept {
            return data.rend( );
        }
        /// @brief get a constant reverse iterator past the first character
        /// @return reverse iterator
        constexpr auto rend( ) const noexcept {
            return data.rend( );
        }
        /// @brief get a constant reverse iterator to the last character
        /// @return constant reverse iterator
        constexpr auto crbegin( ) const noexcept {
            return data.crbegin( );
        }
        /// @brief get a constant reverse iterator past the first character
        /// @return constant reverse iterator
        constexpr auto crend( ) const noexcept {
            return data.crend( );
        }
        //
    };
    /// @brief editable base-character string type
    using edit_base = _edit<_cpu::chr_base>;
    /// @brief editable wide-character string type
    using edit_wide = _edit<_cpu::chr_wide>;
    /// @brief editable UTF-8 string type
    using edit__unit = _edit<_cpu::chr__unit>;
    /// @brief editable UTF-16 string type
    using edit__dual = _edit<_cpu::chr__dual>;
    /// @brief editable UTF-32 string type
    using edit__quad = _edit<_cpu::chr__quad>;
    /// @brief editable primary Unicode string type
    using uniedit = _edit<_cpu::unicode_t>;
    //
    using bstring = edit_base;
    using wstring = edit_wide;
    //
    /// @brief format a value as hexadecimal using uppercase digits
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base HEX_u( T_Nat v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_hex_u( v, min_w );
        return buff;
    }
    /// @brief format a value as hexadecimal using uppercase digits
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base HEX_u( T_Int v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_hex_u( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as hexadecimal using uppercase digits
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base HEX_u( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
        edit_base buff;
        buff.add_back_hex_u( v, prec );
        return buff;
    }
    /// @brief format a value as hexadecimal using lowercase digits
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base HEX_l( T_Nat v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_hex_l( v, min_w );
        return buff;
    }
    /// @brief format a value as hexadecimal using lowercase digits
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base HEX_l( T_Int v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_hex_l( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as hexadecimal using lowercase digits
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base HEX_l( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
        edit_base buff;
        buff.add_back_hex_l( v, prec );
        return buff;
    }
    /// @brief format an unsigned integer as hexadecimal
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param upper whether to use uppercase digits
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base HEX( T_Nat v, bool upper = fail, len_t min_w = unit ) {
        edit_base buff;
        if ( upper )
            buff.add_back_hex_u( v, min_w );
        else
            buff.add_back_hex_l( v, min_w );
        return buff;
    }
    /// @brief format a signed integer as hexadecimal
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param upper whether to use uppercase digits
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base HEX( T_Int v, bool upper = fail, len_t min_w = unit ) {
        edit_base buff;
        if ( upper )
            buff.add_back_hex_u( v, min_w );
        else
            buff.add_back_hex_l( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as hexadecimal
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param upper whether to use uppercase digits
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base HEX( T_Flt v, bool upper = fail, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, hexa ) ) {
        edit_base buff;
        if ( upper )
            buff.add_back_hex_u( v, prec );
        else
            buff.add_back_hex_l( v, prec );
        return buff;
    }
    /// @brief format an unsigned integer as decimal
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base DEC( T_Nat v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_dec( v, min_w );
        return buff;
    }
    /// @brief format a signed integer as decimal
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base DEC( T_Int v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_dec( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as decimal
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base DEC( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, deci ) ) {
        edit_base buff;
        buff.add_back_dec( v, prec );
        return buff;
    }
    /// @brief format an unsigned integer as octal
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base OCT( T_Nat v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_oct( v, min_w );
        return buff;
    }
    /// @brief format a signed integer as octal
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base OCT( T_Int v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_oct( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as octal
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base OCT( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, octa ) ) {
        edit_base buff;
        buff.add_back_oct( v, prec );
        return buff;
    }
    /// @brief format an unsigned integer as binary
    /// @tparam T_Nat unsigned integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_nat T_Nat >
    constexpr edit_base BIN( T_Nat v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_bin( v, min_w );
        return buff;
    }
    /// @brief format a signed integer as binary
    /// @tparam T_Int signed integer type
    /// @param v value to format
    /// @param min_w minimum output width
    /// @return formatted value
    template < _cpu::check_any_int T_Int >
    constexpr edit_base BIN( T_Int v, len_t min_w = unit ) {
        edit_base buff;
        buff.add_back_bin( v, min_w );
        return buff;
    }
    /// @brief format a floating-point value as binary
    /// @tparam T_Flt floating-point type
    /// @param v value to format
    /// @param prec number of fractional digits
    /// @return formatted value
    template < _cpu::check_any_flt T_Flt >
    constexpr edit_base BIN( T_Flt v, size_t prec = __flt_default_prec( _cpu::val_flt_fraction<T_Flt>, dual ) ) {
        edit_base buff;
        buff.add_back_bin( v, prec );
        return buff;
    }
    /// @brief format a boolean as a binary digit
    /// @param v value to format
    /// @return `1` for true or `0` for false
    constexpr edit_base BIN( bool v ) {
        edit_base buff;
        buff.add_back( _cpu::chr_base{ v ? '1' : '0' } );
        return buff;
    }
    /// @brief format a boolean as a textual value
    /// @param v value to format
    /// @return the corresponding pass or fail string
    constexpr edit_base BOOL( bool v ) {
        edit_base buff;
        buff.add_back( v ? pass_str : fail_str );
        return buff;
    }
    //
}


#endif




