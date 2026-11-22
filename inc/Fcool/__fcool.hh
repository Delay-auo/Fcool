/**
 * @headerfile Fcool/__fcool.hh
 * @version 1.0
 * @author Matias Viitanen
 * @copyright (C) Matias Viitanen 2025 - 2026
 * This file is part of the Fcool library
 */


#ifdef FCOOLMACRO_TEMP
#   undef FCOOLMACRO_TEMP
#endif


#ifndef FCOOL_HEAD___FCOOL
#define FCOOL_HEAD___FCOOL 1.0


#pragma region // macros

#ifndef FCOOLMACRO_ADDR_T
#   ifdef __UINTPTR_TYPE__
#       define FCOOLMACRO_ADDR_T __UINTPTR_TYPE__
#   else
#       error "Fcool needs FCOOLMACRO_ADDR_T or __UINTPTR_TYPE__ to represent Fcool::addr_t"
#   endif
#endif

#ifndef FCOOLMACRO__PTR_T
#   ifdef __INTPTR_TYPE__
#       define FCOOLMACRO__PTR_T __INTPTR_TYPE__
#   else
#       error "Fcool needs FCOOLMACRO__PTR_T or __INTPTR_TYPE__ to represent Fcool::addr_t"
#   endif
#endif

#pragma endregion

/// @brief ## Fcool library
namespace Fcool
{

#pragma region // primary types

/// @brief ### primary size type
using size_t = decltype( sizeof( nullptr ) );
/// @brief ### primary address type
using addr_t = FCOOLMACRO_ADDR_T;
/// @brief ### alignment type
/// @brief secondary size type
using _ali_t = decltype( alignof( int ) );
/// @brief ### pointer type
/// @brief secondary address type
using _ptr_t = FCOOLMACRO__PTR_T;
/// @brief #### byte type
using byte_t = unsigned char;
/// @brief #### signed byte type
using tiny_t = signed char;
/// @brief #### smallest word type
using word_t = unsigned short;
/// @brief #### signed smallest word type
using body_t = signed short;

/// @brief #### process return type
using code_t = int;

#pragma endregion


#pragma region // enumerated types

/// @brief ### conditional
enum cond_t : bool
{
    /// @brief logical false
    fail = false,
    /// @brief logical true
    pass = true
};
/// @brief represents a bit in byte
enum class _bit_t : byte_t
{
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    /// @brief N as the amount of bits in a byte
    __N
};
/// @brief ### ∣∅∣
/// @brief mathematical zero
constexpr byte_t zero = cond_t{ pass && fail };
/// @brief ### powers of two
enum _pow_t : body_t
{
    /// @brief ### ∣{ ∅ }∣
    /// @brief ### 2^0
    /// @brief mathematical unit
    unit = body_t{ cond_t{ pass || fail } },
    /// @brief ### ∣{ ∅, ∣∅∣ }∣
    /// @brief ### 2^1
    /// @brief ### first prime number
    dual = body_t{ unit } + body_t{ unit },
    /// @brief #### 4
    /// @brief ### 2^2
    quad = body_t{ dual } + body_t{ dual },
    /// @brief #### 8
    /// @brief #### 2^3
    octa = body_t{ quad } + body_t{ quad },
    /// @brief #### 16
    /// @brief #### 2^4
    hexa = body_t{ octa } + body_t{ octa },
    /// @brief #### 32
    /// @brief #### 2^5
   _dode = body_t{ hexa } + body_t{ hexa },
    /// @brief #### 64
    /// @brief #### 2^6
   _tess = body_t{_dode } + body_t{_dode },
    /// @brief #### 128
    /// @brief #### 2^7
   _hept = body_t{_tess } + body_t{_tess },
    /// @brief #### 256
    /// @brief #### 2^8
   _octo = body_t{_hept } + body_t{_hept },
};
/// @brief represents a value difference
enum class diff_t : tiny_t
{
    positive = pass - fail,
    negative = fail - pass,
    neutral = pass - pass
};
/// @brief represents prime numbers from 2 to 257
enum class _prime_t : body_t
{
    /// @brief 2
    dual = 2,
    /// @brief 3
    tri = 3,
    /// @brief 5
    penta = 5,
    /// @brief 7
    hepta = 7,
    /// @brief 11
    hendeca = 11,
    /// @brief 13
    trideca = 13,
    /// @brief 17
    heptadeca = 17,
    /// @brief 19
    enneadeca = 19,
    /// @brief 23
    tricosa = 23,
    /// @brief 29
    enneacosa = 29,
    /// @brief 31
    triaconta = 31,
    /// @brief 37
    heptatriaconta = 37,
    /// @brief 41
    hentetraconta = 41,
    /// @brief 43
    triaetetraconta = 43,
    /// @brief 47
    heptatetraconta = 47,
    /// @brief 53
    triahexaconta = 53,
    /// @brief 59
    enneahexaconta = 59,
    /// @brief 61
    henahexaconta = 61,
    /// @brief 67
    heptahexaconta = 67,
    /// @brief 71
    henheptaconta = 71,
    /// @brief 73
    triaheptaconta = 73,
    /// @brief 79
    enneaheptaconta = 79,
    /// @brief 83
    triaoctaconta = 83,
    /// @brief 89
    enneaocaconta = 89,
    /// @brief 97
    heptanonaconta = 97,
    /// @brief 101
    henahecta = 101,
    /// @brief 103
    triahecta = 103,
    /// @brief 107
    heptahecta = 107,
    /// @brief 109
    enneahecta = 109,
    /// @brief 113
    triahectadeca = 113,
    /// @brief 127
    heptakaihecta = 127,
    /// @brief 131
    henahectotri = 131,
    /// @brief 137
    heptahectotri = 137,
    /// @brief 139
    enneahectotri = 139,
    /// @brief 149
    enneahectotetra = 149,
    /// @brief 151
    henahectopenta = 151,
    /// @brief 157
    heptahectopenta = 157,
    /// @brief 163
    triahectotri = 163,
    /// @brief 167
    heptahectotri_alt = 167,
    /// @brief 173
    triahectotetra = 173,
    /// @brief 179
    enneahectotetradeca = 179,
    /// @brief 181
    henahectotetra = 181,
    /// @brief 191
    enneahectonen = 191,
    /// @brief 193
    triahectonen = 193,
    /// @brief 197
    heptahectonen = 197,
    /// @brief 199
    enneahectonennea = 199,
    /// @brief 211
    henahectohendeca = 211,
    /// @brief 223
    triahectododeca = 223,
    /// @brief 227
    heptahectododeca = 227,
    /// @brief 229
    enneahectododeca = 229,
    /// @brief 233
    triahectotrideca = 233,
    /// @brief 239
    enneahectotrideca = 239,
    /// @brief 241
    henahectotetradeca = 241,
    /// @brief 251
    henahectopentaconta = 251,
    /// @brief 257
    dihectopentacontahepta = 257
};
/// @brief ### 10
/// @brief #### used by base most measurement systems
constexpr body_t deci = 10;

/// @brief converts a core enum to a register
/// @param cond 
/// @return a boolean
constexpr bool bit( cond_t cond ) noexcept { return static_cast<bool>(cond); }
/// @brief converts a core enum to a register
/// @param bit 
/// @return a bit index
constexpr byte_t bit( _bit_t  bit ) noexcept { return static_cast<byte_t>( bit); }
/// @brief converts a core enum to a register
/// @param pow 
/// @return a power of two
constexpr body_t num( _pow_t  pow ) noexcept { return static_cast<body_t>( pow); }
/// @brief converts a core enum to a register
/// @param diff 
/// @return 0, 1 or -1
constexpr tiny_t num( diff_t diff ) noexcept { return static_cast<tiny_t>(diff); }
/// @brief converts a core enum to a register
/// @param prime 
/// @return a prime number
constexpr body_t num( _prime_t prime ) noexcept { return static_cast<body_t>(prime); }

#pragma endregion


#pragma region // static assertions

#ifdef __CHAR_BIT__
    static_assert( bit( _bit_t::__N ) == __CHAR_BIT__ );
#endif

constexpr bool _diff_positive( diff_t diff ) noexcept { return diff > diff_t::neutral; }
constexpr bool _diff_negative( diff_t diff ) noexcept { return diff < diff_t::neutral; }
constexpr bool _diff_neutral( diff_t diff ) noexcept { return diff == diff_t::neutral; }

static_assert( zero == -zero );
static_assert( zero == +zero );
static_assert( zero < +unit );
static_assert( zero > -unit );
static_assert( sizeof(addr_t) == sizeof(void*) );
static_assert( sizeof(addr_t) >= sizeof(size_t) );
static_assert( static_cast<size_t>( -unit ) > zero );
static_assert( static_cast<size_t>( +unit ) > zero );
static_assert( static_cast<addr_t>( -unit ) > zero );
static_assert( static_cast<addr_t>( +unit ) > zero );
static_assert( static_cast<_ali_t>( -unit ) > zero );
static_assert( static_cast<_ali_t>( +unit ) > zero );
static_assert( static_cast<_ptr_t>( -unit ) < zero );
static_assert( static_cast<_ptr_t>( +unit ) > zero );
static_assert( static_cast<byte_t>( -unit ) > zero );
static_assert( static_cast<byte_t>( +unit ) > zero );
static_assert( static_cast<word_t>( -unit ) > zero );
static_assert( static_cast<word_t>( +unit ) > zero );
static_assert( static_cast<code_t>( -unit ) < zero );
static_assert( static_cast<code_t>( +unit ) > zero );

#pragma endregion

}


#endif




