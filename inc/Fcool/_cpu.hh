/**
 * @headerfile Fcool/_cpu.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.1
 * @copyright (C) Matias Viitanen 2025 - 2026
 * This file is part of the Fcool library
 */



#ifndef FCOOL_HEAD__CPU
#define FCOOL_HEAD__CPU 0.1


#include "__fcool.hh"
#include "_type.hh"

#pragma region // macros

#ifndef FCOOLMACRO_HEXA
#ifdef __SIZEOF_INT128__
static_assert(__SIZEOF_INT128__ == 16);
#define FCOOLMACRO_HEXA 1
#else
#define FCOOLMACRO_HEXA 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT16
#if defined(__FLT16_MANT_DIG__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT16 1
#else
#define FCOOLMACRO_FLOAT16 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT32
#if defined(__FLT32_MANT_DIG__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT32 1
#else
#define FCOOLMACRO_FLOAT32 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT32X
#if defined(__FLT32X_MANT_DIG__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT32X 1
#else
#define FCOOLMACRO_FLOAT32X 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT64
#if defined(__FLT64_MANT_DIG__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT64 1
#else
#define FCOOLMACRO_FLOAT64 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT64X
#if defined(__FLT64X_MANT_DIG__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT64X 1
#else
#define FCOOLMACRO_FLOAT64X 0
#endif
#endif

#ifndef FCOOLMACRO_FLOAT128
#if defined(__SIZEOF_FLOAT128__) && !defined(_MSC_VER)
#define FCOOLMACRO_FLOAT128 1
#else
#define FCOOLMACRO_FLOAT128 0
#endif
#endif

#pragma endregion

namespace Fcool::_cpu
{

#pragma region // ---------------- types

/// @brief ### natural unit size 8bit register (byte)
using nat_unit = byte_t;
/// @brief ### integral unit size 8bit signed register (tiny)
using int_unit = tiny_t;
static_assert( sizeof(nat_unit) == unit );
static_assert( sizeof(int_unit) == unit );
/// @brief ### natural dual size 16-bit register (word)
using nat_dual = word_t;
/// @brief ### integral dual size 16-bit signed register (body)
using int_dual = body_t;
static_assert( sizeof(nat_dual) == dual );
static_assert( sizeof(int_dual) == dual );
/// @brief ### natural quad size 32-bit register (U)
using nat_quad = unsigned int;
/// @brief ### integral quad size 32-bit signed register ()
using int_quad = signed int;
static_assert( sizeof(nat_quad) == quad );
static_assert( sizeof(int_quad) == quad );
/// @brief ### natural octa size 64-bit register (ULL)
using nat_octa = unsigned long long;
/// @brief ### integral octa size 64-bit signed register (LL)
using int_octa = signed long long;
static_assert( sizeof(nat_octa) == octa );
static_assert( sizeof(int_octa) == octa );
/// @brief ### natural long size abstract register (UL)
using nat_vary = unsigned long;
/// @brief ### integral long size abstract signed register (L)
using int_vary = signed long;
/// @brief ### single precision float register
using flt_single = float;
static_assert( sizeof(flt_single) == quad );
/// @brief ### double precision float register
using flt_double = double;
static_assert( sizeof(flt_double) == octa );
/// @brief ### extended precision float register
using flt_extent = long double;
/// @brief ### base range character register
using chr_code = char;
static_assert( sizeof(chr_code) == unit );
/// @brief ### wide range character register
using chr_wide = wchar_t;
/// @brief check if chr_wide is dual sized;
constexpr bool __wide_match_dual = sizeof(chr_wide) == dual;
/// @brief check if chr_wide is quad sized;
constexpr bool __wide_match_quad = sizeof(chr_wide) == quad;
static_assert(
    ( __wide_match_dual && !__wide_match_quad ) ||
    ( __wide_match_quad && !__wide_match_dual )
);



#if FCOOLMACRO_HEXA
    /// @brief ### natural hexa size 128-bit value
    /// @warning ### declared only if *FCOOLMACRO_HEXA*
    /// @warning #### not portable across compilers
    using nat_hexa = __uint128_t;
    /// @brief ### integral hexa size 128-bit signed value
    /// @warning ### declared only if *FCOOLMACRO_HEXA*
    /// @warning #### not portable across compilers
    using int_hexa = __int128_t;
    /// @brief #### largest natural type
    using _nat_max = nat_hexa;
    /// @brief #### largest integral type
    using _int_max = nat_hexa;
    static_assert( sizeof(nat_hexa) == hexa );
    static_assert( sizeof(int_hexa) == hexa );
#else
    /// @brief #### largest natural type
    using _nat_max = nat_octa;
    /// @brief #### largest integral type
    using _int_max = nat_octa;
#endif
#if FCOOLMACRO_FLOAT16
    /// @brief half precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT16*
    /// @warning #### not portable across compilers
    using flt_halved = _Float16;
    static_assert( sizeof(flt_halved) == dual );
#endif
#if FCOOLMACRO_FLOAT32
    /// @brief exactly 32-bit precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT32*
    /// @warning #### not portable across compilers
    using flt_32 = _Float32;
    static_assert( sizeof(flt_32) == quad );
#endif
#if FCOOLMACRO_FLOAT32X
    /// @brief at least 32-bit extended precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT32X*
    /// @warning #### not portable across compilers
    using flt_32x = _Float32x;
#endif
#if FCOOLMACRO_FLOAT64
    /// @brief exactly 64-bit precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT64*
    /// @warning #### not portable across compilers
    using flt_64 = _Float64;
    static_assert( sizeof(flt_64) == octa );
#endif
#if FCOOLMACRO_FLOAT64X
    /// @brief at least 64-bit extended precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT64X*
    /// @warning #### not portable across compilers
    using flt_64x = _Float64x;
#endif
#if FCOOLMACRO_FLOAT128
    /// @brief 128-bit precision float value
    /// @warning ### declared only if *FCOOLMACRO_FLOAT128*
    /// @warning #### not portable across compilers
    using flt_128 = __float128;
    static_assert( sizeof(flt_128) == hexa );
#endif

#pragma region // chr
/// @brief ### UTF-8 character value
using chr__unit =
#if defined(__cplusplus) && __cplusplus >= 202002L
    char8_t;
#elif defined(__CHAR8_TYPE__)
    __CHAR8_TYPE__;
#else
    nat_unit;
#endif
static_assert( sizeof(chr__unit) == unit );
/// @brief ### UTF-16 character value
using chr__dual =
#if defined(__cplusplus) && __cplusplus >= 201703L
    char16_t;
#elif defined(__CHAR16_TYPE__)
    __CHAR16_TYPE__;
#else
    nat_dual;
#endif
static_assert( sizeof(chr__dual) == dual );
/// @brief ### UTF-32 character value
using chr__quad =
#if defined(__cplusplus) && __cplusplus >= 201103L
    char32_t;
#elif defined(__CHAR32_TYPE__)
    __CHAR32_TYPE__;
#else
    nat_quad;
#endif
static_assert( sizeof(chr__quad) == quad );
/// @brief The corresponding UTF type to cast chr_wide
using __wide_match_t = _type::_cond< __wide_match_dual,
    _type::_cond< __wide_match_quad,
        void,
        chr__dual
    >,
    _type::_cond< __wide_match_quad,
        chr__quad,
        void
    >
>;
/// @brief The primary Unicode character unit type in UTF-16
using unicode_t = _type::_cond< __wide_match_dual, chr_wide, chr__dual >;

#pragma endregion

#pragma endregion

#pragma region // ---------------- groups

#pragma region // reg
/// @brief ### meta type group including all the natural registers
using _reg_group_nat = _type::group<
    nat_unit,
    nat_dual,
    nat_quad,
    nat_octa,
    nat_vary
>;
/// @brief ### meta type group including all the integral signed registers
using _reg_group_int = _type::group<
    int_unit,
    int_dual,
    int_quad,
    int_octa,
    int_vary
>;
/// @brief ### meta type group including all the floating registers
using _reg_group_flt = _type::group<
    flt_single,
    flt_double,
    flt_extent
>;
/// @brief ### meta type group including all the character registers
using _reg_group_chr = _type::group<
    chr_code,
    chr_wide
>;
#pragma endregion

#pragma region // ext
/// @brief #### meta type group including all the natural non-register values
using __ext_group_nat = _type::group<
#if FCOOLMACRO_HEXA
    nat_hexa
#endif
>;
/// @brief ### meta type group including all the integral signed non-register values
using __ext_group_int = _type::group<
#if FCOOLMACRO_HEXA
    int_hexa
#endif
>;
/// @brief ### meta type group including all the floating non-register values
using __ext_group_flt = _type::group<
#if FCOOLMACRO_FLOAT16
    flt_halved
#   define FCOOLMACRO_TEMP
#endif
#if FCOOLMACRO_FLOAT32
#   ifdef FCOOLMACRO_TEMP
        ,
#   else
#       define FCOOLMACRO_TEMP
#   endif
    flt_32
#endif
#if FCOOLMACRO_FLOAT32X
#   ifdef FCOOLMACRO_TEMP
        ,
#   else
#       define FCOOLMACRO_TEMP
#   endif
    flt_32x
#endif
#if FCOOLMACRO_FLOAT64
#   ifdef FCOOLMACRO_TEMP
        ,
#   else
#       define FCOOLMACRO_TEMP
#   endif
    flt_64
#endif
#if FCOOLMACRO_FLOAT64X
#   ifdef FCOOLMACRO_TEMP
        ,
#   else
#       define FCOOLMACRO_TEMP
#   endif
    flt_64x
#endif
#if FCOOLMACRO_FLOAT128
#   ifdef FCOOLMACRO_TEMP
        ,
#   endif
    flt_128
#endif
#ifdef FCOOLMACRO_TEMP
#   undef FCOOLMACRO_TEMP
#endif
>;

/// @brief ### meta type group including all the character non-register values
using __ext_group_chr = _type::group<
    chr__unit,
    chr__dual,
    chr__quad
>;
#pragma endregion

#pragma region // full

static_assert( _reg_group_nat::has< size_t > );
static_assert( _reg_group_nat::has< addr_t > );
static_assert( _reg_group_int::has< _ptr_t > );
static_assert( _reg_group_int::has< code_t > );
static_assert( _reg_group_nat::has< _ali_t > );
static_assert( !_type::groups_collide< _reg_group_nat, __ext_group_nat > );
static_assert( !_type::groups_collide< _reg_group_int, __ext_group_int > );
static_assert( !_type::groups_collide< _reg_group_flt, __ext_group_flt > );
static_assert( !_type::groups_collide< _reg_group_chr, __ext_group_chr > );

/// @brief #### meta type group including all the natural values
using _group_nat = _type::group_combine< _reg_group_nat, __ext_group_nat >;
/// @brief #### meta type group including all the integral values
using _group_int = _type::group_combine< _reg_group_int, __ext_group_int >;
/// @brief #### meta type group including all the floating values
using _group_flt = _type::group_combine< _reg_group_flt, __ext_group_flt >;
/// @brief #### meta type group including all the character values
using _group_chr = _type::group_combine< _reg_group_chr, __ext_group_chr >;

#pragma endregion

#pragma endregion

#pragma region // ---------------- concepts

/// @brief enforced natural register check
template < typename T_Tp > concept check_reg_nat = _reg_group_nat::has< T_Tp >;
/// @brief enforced natural value check
template < typename T_Tp > concept check_any_nat = _group_nat::has< T_Tp >;
/// @brief enforced integral register check
template < typename T_Tp > concept check_reg_int = _reg_group_int::has< T_Tp >;
/// @brief enforced integral value check
template < typename T_Tp > concept check_any_int = _group_int::has< T_Tp >;
/// @brief enforced floating register check
template < typename T_Tp > concept check_reg_flt = _reg_group_flt::has< T_Tp >;
/// @brief enforced floating value check
template < typename T_Tp > concept check_any_flt = _group_flt::has< T_Tp >;
/// @brief enforced character register check
template < typename T_Tp > concept check_reg_chr = _reg_group_flt::has< T_Tp >;
/// @brief enforced character value check
template < typename T_Tp > concept check_any_chr = _group_chr::has< T_Tp >;
/// @brief enforced numeral register check
template < typename T_Tp > concept check_reg_numb = check_reg_nat<T_Tp> || check_reg_int<T_Tp>;
/// @brief enforced numeral value check
template < typename T_Tp > concept check_any_numb = check_any_nat<T_Tp> || check_any_int<T_Tp>;
/// @brief enforced real register check
template < typename T_Tp > concept check_reg_real = check_reg_int<T_Tp> || check_reg_flt<T_Tp>;
/// @brief enforced real value check
template < typename T_Tp > concept check_any_real = check_any_int<T_Tp> || check_any_flt<T_Tp>;
/// @brief enforced register check
template < typename T_Tp > concept check_reg = check_reg_nat<T_Tp> || check_reg_int<T_Tp> || check_reg_flt<T_Tp>;
/// @brief enforced value check
template < typename T_Tp > concept check_any = check_any_nat<T_Tp> || check_any_int<T_Tp> || check_any_flt<T_Tp>;
/// @brief enforced boolean check
template < typename T_Tp > concept check_bool = _type::is_bool< T_Tp >;
/// @brief enforced at least wordsize numeral value check
template < typename T_Tp > concept check_word = check_any_numb< T_Tp > && sizeof(T_Tp) >= sizeof(word_t);
/// @brief enforced at least wordsize natural value check
template < typename T_Tp > concept check_word_nat = check_any_nat< T_Tp > && sizeof(T_Tp) >= sizeof(word_t);
/// @brief enforced at least wordsize integral value check
template < typename T_Tp > concept check_word_int = check_any_int< T_Tp > && sizeof(T_Tp) >= sizeof(word_t);

/// @brief 
/// @tparam T_size the size of the type
template < size_t T_size >
using _nat_from_size =
_type::_cond< T_size == zero, void,
_type::_cond< T_size % octa == zero, nat_octa,
_type::_cond< T_size % quad == zero, nat_quad,
_type::_cond< T_size % dual == zero, nat_dual,
_type::_cond< T_size % unit == zero, nat_unit,
void
>>>>>;
/// @brief count of the elements gotten from size
/// @tparam T_size 
template < size_t T_size >
constexpr size_t _from_size_count = T_size / sizeof(_nat_from_size<T_size>);
/// @brief get the binary square root type from another.
/// @tparam T_val at least wordsize natural value
template < check_word_nat T_val >
using _nat_half = _nat_from_size< sizeof(T_val) / dual >;

/// @brief get the same size integral type
/// @tparam T_val 
template < check_any_numb T_val >
using _int_from_type =
_type::_cond< check_any_int<T_val>, T_val,
_type::_cond< _type::is_same< T_val, nat_unit >, int_unit,
_type::_cond< _type::is_same< T_val, nat_dual >, int_dual,
_type::_cond< _type::is_same< T_val, nat_quad >, int_quad,
_type::_cond< _type::is_same< T_val, nat_octa >, int_octa,
_type::_cond< _type::is_same< T_val, nat_vary >, int_vary,
void > > > > > >;
/// @brief get the same size natural type
/// @tparam T_val 
template < check_any_numb T_val >
using _nat_from_type =
_type::_cond< check_any_nat<T_val>, T_val,
_type::_cond< check_any_int<T_val> && ( _from_size_count<sizeof(T_val)> == unit ), _nat_from_size< sizeof(T_val) >,
void > >;

/// @brief count of the elements gotten from size
/// @tparam T_size 
template < size_t T_size >
using _int_from_size = _int_from_type< _nat_from_size< T_size > >;
/// @brief get the binary square root type from another.
/// @tparam T_val at least wordsize integral value
template < check_word_int T_val >
using _int_half = _int_from_size< sizeof(T_val) / dual >;

static_assert( !_type::groups_collide< _group_nat, _group_int > );
static_assert( !_type::groups_collide< _group_nat, _group_flt > );

static_assert( !_type::groups_collide< _group_int, _group_nat > );
static_assert( !_type::groups_collide< _group_int, _group_flt > );
static_assert( !_type::groups_collide< _group_int, _group_chr > );

static_assert( !_type::groups_collide< _group_flt, _group_nat > );
static_assert( !_type::groups_collide< _group_flt, _group_int > );
static_assert( !_type::groups_collide< _group_flt, _group_chr > );

static_assert( !_type::groups_collide< _group_chr, _group_int > );
static_assert( !_type::groups_collide< _group_chr, _group_flt > );

#pragma endregion

#pragma region // ---------------- unions

/// @brief ### natural register type union
union _union_nat
{
    nat_unit unit, byte;
    nat_dual dual, word;
    nat_quad quad;
    nat_octa octa;
    nat_vary vary;
    size_t size;
    addr_t addr;
};
/// @brief ### integral register type union
union _union_int
{
    int_unit unit, tiny;
    int_dual dual, body;
    int_quad quad;
    int_octa octa;
    int_vary vary;
    _ptr_t _ptr;
};
/// @brief ### floating register type union
union _union_flt
{
    flt_single _single;
    flt_double _double;
    flt_extent _extent;
};
/// @brief ### character register type union
union _union_chr
{
    chr_code code;
    chr_wide wide;
};

/// @brief ### natural type union
union union_nat
{
    nat_unit unit;
    nat_dual dual;
    nat_quad quad;
    nat_octa octa;
    nat_vary vary;
    size_t size;
    addr_t addr;
#   if FCOOLMACRO_HEXA
        nat_hexa hexa;
#   endif
};
/// @brief ### integral type union
union union_int
{
    nat_unit unit;
    nat_dual dual;
    nat_quad quad;
    nat_octa octa;
    nat_vary vary;
#   if FCOOLMACRO_HEXA
        int_hexa hexa;
#   endif
};
/// @brief ### floating type union
union union_flt
{
    flt_single _single;
    flt_double _double;
    flt_extent _extent;
#   if FCOOLMACRO_FLOAT16
    flt_halved _halved;
#   endif
#   if FCOOLMACRO_FLOAT32
    flt_32 _32;
#   endif
#   if FCOOLMACRO_FLOAT32X
    flt_32x _32x;
#   endif
#   if FCOOLMACRO_FLOAT64
    flt_64 _64;
#   endif
#   if FCOOLMACRO_FLOAT64X
    flt_64x _64x;
#   endif
#   if FCOOLMACRO_FLOAT128
    flt_128 _128;
#   endif
};
/// @brief ### character type union
union union_chr
{
    chr_code code;
    chr_wide wide;
#   if FCOOLMACRO_CHAR8
    chr__unit unit;
#   endif
#   if FCOOLMACRO_CHAR16
    chr__dual dual;
#   endif
#   if FCOOLMACRO_CHAR32
    chr__quad quad;
#   endif
};

#pragma endregion

#pragma region // ---------------- values

#pragma region // ext

/// @brief the max value of a natural value
/// @tparam T_nat 
template < check_any_nat T_nat >
constexpr T_nat val_max_nat = static_cast<T_nat>(-unit);
/// @brief the min value of a natural value
/// @tparam T_nat 
template < check_any_nat T_nat >
constexpr T_nat val_min_nat = zero;
/// @brief the min value of a integral value
/// @tparam T_nat 
template < check_any_int T_int >
constexpr T_int val_min_int = static_cast<T_int>(
    -(T_int(unit) << (octa * sizeof(T_int) - dual)) -
     (T_int(unit) << (octa * sizeof(T_int) - dual))
);
/// @brief the max value of a integral value
/// @tparam T_nat 
template < check_any_int T_int >
constexpr T_int val_max_int = static_cast<T_int>( ~val_min_int<T_int> );

struct ___flt_info
{
    size_t precision;
    size_t max_exponent;
    bool has_denorm;
    bool has_infinity;
    bool has_quiet_nan;
};
template < check_any_flt T_flt >
constexpr ___flt_info ___val_flt_info( )
{
#define FCOOLMACRO_TEMP(Tp, Mant, MaxExp, Denorm, Infinity, QuietNaN) \
    if constexpr ( _type::is_same<T_flt, Tp> ) \
        return { Mant, MaxExp, Denorm, Infinity, QuietNaN }; \
    else
    FCOOLMACRO_TEMP( flt_single, __FLT_MANT_DIG__, __FLT_MAX_EXP__,
        __FLT_HAS_DENORM__, __FLT_HAS_INFINITY__, __FLT_HAS_QUIET_NAN__ )
    FCOOLMACRO_TEMP( flt_double, __DBL_MANT_DIG__, __DBL_MAX_EXP__,
        __DBL_HAS_DENORM__, __DBL_HAS_INFINITY__, __DBL_HAS_QUIET_NAN__ )
    FCOOLMACRO_TEMP( flt_extent, __LDBL_MANT_DIG__, __LDBL_MAX_EXP__,
        __LDBL_HAS_DENORM__, __LDBL_HAS_INFINITY__, __LDBL_HAS_QUIET_NAN__ )
#if FCOOLMACRO_FLOAT16
    FCOOLMACRO_TEMP( flt_halved, __FLT16_MANT_DIG__, __FLT16_MAX_EXP__,
        __FLT16_HAS_DENORM__, __FLT16_HAS_INFINITY__, __FLT16_HAS_QUIET_NAN__ )
#endif
#if FCOOLMACRO_FLOAT32
    FCOOLMACRO_TEMP( flt_32, __FLT32_MANT_DIG__, __FLT32_MAX_EXP__,
        __FLT32_HAS_DENORM__, __FLT32_HAS_INFINITY__, __FLT32_HAS_QUIET_NAN__ )
#endif
#if FCOOLMACRO_FLOAT32X
    FCOOLMACRO_TEMP( flt_32x, __FLT32X_MANT_DIG__, __FLT32X_MAX_EXP__,
        __FLT32X_HAS_DENORM__, __FLT32X_HAS_INFINITY__, __FLT32X_HAS_QUIET_NAN__ )
#endif
#if FCOOLMACRO_FLOAT64
    FCOOLMACRO_TEMP( flt_64, __FLT64_MANT_DIG__, __FLT64_MAX_EXP__,
        __FLT64_HAS_DENORM__, __FLT64_HAS_INFINITY__, __FLT64_HAS_QUIET_NAN__ )
#endif
#if FCOOLMACRO_FLOAT64X
    FCOOLMACRO_TEMP( flt_64x, __FLT64X_MANT_DIG__, __FLT64X_MAX_EXP__,
        __FLT64X_HAS_DENORM__, __FLT64X_HAS_INFINITY__, __FLT64X_HAS_QUIET_NAN__ )
#endif
#if FCOOLMACRO_FLOAT128
    FCOOLMACRO_TEMP( flt_128, __FLT128_MANT_DIG__, __FLT128_MAX_EXP__,
        __FLT128_HAS_DENORM__, __FLT128_HAS_INFINITY__, __FLT128_HAS_QUIET_NAN__ )
#endif
    {
        static_assert( !_type::is_same<T_flt, T_flt>,
            "Compiler floating-point metadata is unavailable for this type" );
    }
#undef FCOOLMACRO_TEMP
}

template < check_any_flt T_flt >
constexpr bool ___val_flt_bits_sign( )
{
    return pass;
}
template < check_any_flt T_flt >
constexpr size_t ___val_flt_exp_bias( )
{
    return ___val_flt_info<T_flt>( ).max_exponent - unit;
}
template < check_any_flt T_flt >
constexpr size_t ___val_flt_exp_repr( )
{
    const size_t bias = ___val_flt_exp_bias<T_flt>( );
    return bias + bias + unit;
}
template < check_any_flt T_flt >
constexpr size_t ___val_flt_exp_bits( )
{
    size_t repr = ___val_flt_exp_repr<T_flt>( );
    size_t bits = zero;
    while ( repr != zero )
    {
        ++bits;
        repr >>= unit;
    }
    return bits;
}
template < check_any_flt T_flt >
constexpr size_t ___val_flt_fraction( )
{
    return ___val_flt_info<T_flt>( ).precision - unit;
}
template < check_any_flt T_flt >
constexpr diff_t ___val_flt_rounding( )
{
#if __FLT_ROUNDS__ == 2
    return diff_t::positive;
#elif __FLT_ROUNDS__ == 3
    return diff_t::negative;
#else
    return diff_t::neutral;
#endif
}
template < check_any_flt T_flt >
constexpr bool ___val_flt_handling( )
{
    return ___val_flt_info<T_flt>( ).has_denorm;
}
template < check_any_flt T_flt >
constexpr bool ___val_flt_special_values( )
{
    const ___flt_info info = ___val_flt_info<T_flt>( );
    return info.has_infinity && info.has_quiet_nan;
}
template < check_any_flt T_flt >
constexpr size_t ___val_flt_NaN_payload( )
{
    const ___flt_info info = ___val_flt_info<T_flt>( );
    const size_t fraction = info.precision - unit;
    return info.has_quiet_nan && fraction > zero
        ? fraction - unit
        : static_cast<size_t>( zero );
}
template < check_any_flt T_flt >
constexpr bool ___val_flt_NaN_signaling( )
{
    return ___val_flt_NaN_payload<T_flt>( ) > zero;
}
template < check_any_flt T_flt >
constexpr diff_t ___val_flt_endianness( )
{
#if defined(__FLOAT_WORD_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
#   if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return diff_t::positive;
#   elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
    return diff_t::negative;
#   else
    return diff_t::neutral;
#   endif
#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return diff_t::positive;
#   elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    return diff_t::negative;
#   else
    return diff_t::neutral;
#   endif
#else
#   error "Fcool requires compiler byte-order metadata to determine floating-point endianness"
#endif
}

/// @brief number of sign bits in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_sign_bits = ___val_flt_bits_sign<T_flt>( );
/// @brief floating-point exponent bias in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_exp_bias = ___val_flt_exp_bias<T_flt>( );
/// @brief number of exponent bits in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_exp_bits = ___val_flt_exp_bits<T_flt>( );
/// @brief exponent representation in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_exp_repr = ___val_flt_exp_repr<T_flt>( );
/// @brief number of fraction bits in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_fraction = ___val_flt_fraction<T_flt>( );
/// @brief floating-point rounding mode in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_rounding = ___val_flt_rounding<T_flt>( );
/// @brief floating-point exception handling mode in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_handling = ___val_flt_handling<T_flt>( );
/// @brief whether special values are supported in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_special_values = ___val_flt_special_values<T_flt>( );
/// @brief NaN payload behavior in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_NaN_payload = ___val_flt_NaN_payload<T_flt>( );
/// @brief NaN signaling behavior in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_NaN_signaling = ___val_flt_NaN_signaling<T_flt>( );
/// @brief floating-point byte order in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_endianness = ___val_flt_endianness<T_flt>( );
/// @brief total number of bits used by the format in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_used_bits = val_flt_sign_bits<T_flt> + val_flt_exp_bits<T_flt> + val_flt_fraction<T_flt>;
/// @brief number of storage bits unused by the format in a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr auto val_flt_unused_bits = ( sizeof(T_flt) * octa > val_flt_used_bits<T_flt> ) ? sizeof(T_flt) * octa - val_flt_used_bits<T_flt> : zero;

template < check_any_flt T_flt >
constexpr T_flt ___val_flt_max( )
{
    T_flt two_to_fraction = T_flt(1);
    for (size_t i = 0; i < val_flt_fraction<T_flt>; ++i)
        two_to_fraction *= T_flt(2);
    T_flt two_to_exp_bits = T_flt(1);
    for (size_t i = 0; i < val_flt_exp_bits<T_flt>; ++i)
        two_to_exp_bits *= T_flt(2);
    T_flt significand =
        T_flt(2) - T_flt(1) / two_to_fraction;
    // Largest finite encoded exponent is 2^E - 2.
    T_flt unbiased_exp =
        two_to_exp_bits -
        T_flt(2) -
        T_flt(val_flt_exp_bias<T_flt>);
    T_flt result = significand;
    if (unbiased_exp >= T_flt(0)) {
        for (T_flt i = T_flt(0); i < unbiased_exp; ++i)
            result *= T_flt(2);
    }
    else {
        for (T_flt i = T_flt(0); i > unbiased_exp; --i)
            result *= T_flt(0.5);
    }
    return result;
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_max_exp( )
{
    T_flt two_to_exp_bits = T_flt(1);
    for (size_t i = 0; i < val_flt_exp_bits<T_flt>; ++i)
        two_to_exp_bits *= T_flt(2);
    return two_to_exp_bits -
           T_flt(1) -
           T_flt(val_flt_exp_bias<T_flt>);
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_min( )
{
    T_flt result = T_flt(1);
    T_flt exponent =
        T_flt(1) -
        T_flt(val_flt_exp_bias<T_flt>);

    for (T_flt i = T_flt(0); i > exponent; --i)
        result *= T_flt(0.5);

    for (T_flt i = T_flt(0); i < exponent; ++i)
        result *= T_flt(2);

    return result;
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_min_exp( )
{
    return T_flt(1) -
           T_flt(val_flt_exp_bias<T_flt>);
}

/// @brief the max value of a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_max = ___val_flt_max<T_flt>( );
/// @brief the max exponent of a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_max_exp = ___val_flt_max<T_flt>( );
/// @brief the min value of a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_min = ___val_flt_min<T_flt>( );
/// @brief the min exponent of a floating value
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_min_exp = ___val_flt_min<T_flt>( );

template < check_any_flt T_flt >
constexpr T_flt ___val_flt_nan( )
{
    if constexpr ( val_flt_special_values< T_flt > )
        return T_flt( __builtin_nan("") );
    else
        return T_flt( zero );
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_pos_inf( )
{
    if constexpr ( val_flt_special_values< T_flt > )
        return T_flt( +__builtin_huge_val( ) );
    else
        return val_flt_max< T_flt >;
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_neg_inf( )
{
    if constexpr ( val_flt_special_values< T_flt > )
        return T_flt( -__builtin_huge_val( ) );
    else
        return val_flt_min<T_flt>;
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_pos_zer( )
{
    if constexpr ( val_flt_special_values< T_flt > )
        return T_flt( +unit ) * T_flt( zero );
    else
        return T_flt( zero );
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_neg_zer( )
{
    if constexpr ( val_flt_special_values< T_flt > )
        return T_flt( -unit ) * T_flt( zero );
    else
        return T_flt( zero );
}
template < check_any_flt T_flt >
constexpr T_flt ___val_flt_epsilon( )
{
    constexpr T_flt half = T_flt( unit ) / T_flt(dual);
    T_flt result = T_flt( unit );
    for ( size_t i = 0; i < val_flt_fraction<T_flt>; ++i )
        result *= half;
    return result;
}

/// @brief NaN float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_nan = ___val_flt_nan<T_flt>( );
/// @brief infinity float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_pos_inf = ___val_flt_pos_inf<T_flt>( );
/// @brief negative infinity float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_neg_inf = ___val_flt_neg_inf<T_flt>( );
/// @brief imperfect zero float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_pos_zer = ___val_flt_pos_zer<T_flt>( );
/// @brief negative imperfect zero float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_neg_zer = ___val_flt_neg_zer<T_flt>( );
/// @brief epsilon float constant
/// @tparam T_flt 
template < check_any_flt T_flt >
constexpr T_flt val_flt_epsilon = ___val_flt_epsilon<T_flt>( );

/// @brief the max value of a numeric value
/// @tparam T_numb 
template < check_any_numb T_numb >
constexpr T_numb val_max_numb = [] {
    if constexpr ( check_any_nat<T_numb> )
        return val_max_nat<T_numb>;
    else
        return val_max_int<T_numb>;
}( );
/// @brief the min value of a numeric value
/// @tparam T_numb 
template < check_any_numb T_numb >
constexpr T_numb val_min_numb = [] {
    if constexpr ( check_any_nat<T_numb> )
        return val_min_nat<T_numb>;
    else
        return val_min_int<T_numb>;
}( );
/// @brief the max value of a real value
/// @tparam T_real 
template < check_any_real T_real >
constexpr T_real val_max_real = [] {
    if constexpr ( check_any_int<T_real> )
        return val_max_int<T_real>;
    else
        return val_flt_max<T_real>;
}( );
/// @brief the min value of a real value
/// @tparam T_real 
template < check_any_real T_real >
constexpr T_real val_min_real = [] {
    if constexpr ( check_any_int<T_real> )
        return val_min_int<T_real>;
    else
        return val_flt_min<T_real>;
}( );

#pragma endregion

#pragma region // cpu

/// @brief the max value of a natural register
/// @tparam T_nat 
template < check_reg_nat T_nat >
constexpr T_nat _val_max_nat = val_max_nat<T_nat>;
/// @brief the min value of a natural register
/// @tparam T_nat 
template < check_reg_nat T_nat >
constexpr T_nat _val_min_nat = val_min_nat<T_nat>;
/// @brief the max value of a integral register
/// @tparam T_int 
template < check_reg_int T_int >
constexpr T_int _val_max_int = val_min_int<T_int>;
/// @brief the min value of a integral register
/// @tparam T_int 
template < check_reg_int T_int >
constexpr T_int _val_min_int = val_max_int<T_int>;

/// @brief number of sign bits in a floating register
/// @tparam T_int 
template < check_reg_flt T_flt >
constexpr bool _val_flt_sign_bits = val_flt_sign_bits<T_flt>;
/// @brief floating-point exponent bias in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_exp_bias = val_flt_exp_bias<T_flt>;
/// @brief number of exponent bits in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_exp_bits = val_flt_exp_bits<T_flt>;
/// @brief exponent representation in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_exp_repr = val_flt_exp_repr<T_flt>;
/// @brief number of fraction bits in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_fraction = val_flt_fraction<T_flt>;
/// @brief floating-point rounding mode in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr diff_t _val_flt_rounding = val_flt_rounding<T_flt>;
/// @brief floating-point exception handling mode in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr bool _val_flt_handling = val_flt_handling<T_flt>;
/// @brief whether special values are supported in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr bool _val_flt_special_values = val_flt_special_values<T_flt>;
/// @brief NaN payload behavior in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_NaN_payload = val_flt_NaN_payload<T_flt>;
/// @brief NaN signaling behavior in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr bool _val_flt_NaN_signaling = val_flt_NaN_signaling<T_flt>;
/// @brief floating-point byte order in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr diff_t _val_flt_endianness = val_flt_endianness<T_flt>;
/// @brief total number of bits used by the format in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_used_bits = val_flt_used_bits<T_flt>;
/// @brief number of storage bits unused by the format in a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr size_t _val_flt_unused_bits = val_flt_unused_bits<T_flt>;

/// @brief the max value of a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr T_flt _val_flt_max = val_flt_max<T_flt>;
/// @brief the min value of a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr T_flt _val_flt_min = val_flt_max<T_flt>;
/// @brief the max exponent of a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr T_flt _val_flt_max_exp = val_flt_max_exp<T_flt>;
/// @brief the min exponent of a floating register
/// @tparam T_flt 
template < check_reg_flt T_flt >
constexpr T_flt _val_flt_min_exp = val_flt_min_exp<T_flt>;

#pragma endregion

/// @brief ### Get bits
/// @tparam T_nat 
/// @param value 
/// @return 
template < check_any_nat T_nat >
constexpr T_nat _bits( T_nat value ) {
    return
    value == zero ?
    T_nat( zero ) :
    unit + _bits< T_nat >( value >> unit );
};

static_assert( _group_nat::foreach<[]< typename T_nat >() { return (
    val_max_nat< T_nat > > val_min_nat< T_nat > &&
    static_cast<T_nat>(val_max_nat< T_nat > + unit) == val_min_nat< T_nat > &&
    octa * sizeof(T_nat) == _bits<T_nat>( val_max_nat< T_nat > )
); }> );
static_assert( _group_int::foreach<[]< typename T_int >() { return (
    val_max_int< T_int > > zero &&
    val_min_int< T_int > < zero &&
    static_cast<T_int>(val_max_int< T_int > + val_min_int< T_int >) == -unit
); }> );

/// @brief size_t max value
constexpr size_t val_max_size = val_max_nat<size_t>;
/// @brief addr_t max value
constexpr addr_t val_max_addr = val_max_nat<addr_t>;
/// @brief byte_t max value
constexpr byte_t val_max_byte = val_max_nat<byte_t>;
/// @brief word_t max value
constexpr word_t val_max_word = val_max_nat<word_t>;

#pragma endregion

}


#endif




