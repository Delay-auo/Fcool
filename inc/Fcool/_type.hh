/**
 * @headerfile Fcool/_type.hh
 * @version 1.1
 * @author Matias Viitanen
 * @since Fcool 0.1
 * @copyright (C) Matias Viitanen 2025 - 2026
 * This file is part of the Fcool library
 */



#ifndef FCOOL_HEAD__TYPE
#define FCOOL_HEAD__TYPE 1.0


#include "__fcool.hh"


namespace Fcool::_type
{

#pragma region // basic types checks
/// @brief ### check if two types are a exact match
/// @tparam T_TpL 
/// @tparam T_TpR 
template < typename T_TpL, typename T_TpR > constexpr bool is_same  = fail;
/// @brief ### check if two types are a exact match (true)
/// @tparam T_TpL 
/// @tparam T_TpR 
template < typename T_Tp > constexpr bool is_same< T_Tp, T_Tp >     = pass;
/// @brief #### check if a type is in a group
/// @tparam T_Tp the type to check
/// @tparam ...TS_Whitelist a group of whitelisted types
template< typename T_Tp, typename... TS_Whitelist >
concept _whitelist = ( is_same < T_Tp, TS_Whitelist> || ...);
/// @brief completely blank type
struct blank_t
{
    blank_t( ) = delete;
    blank_t( const blank_t& ) = delete;
    blank_t( blank_t&& ) = delete;
    blank_t& operator=( const blank_t& ) = delete;
    blank_t& operator=( blank_t&& ) = delete;
    blank_t* operator&( ) = delete;
};
#pragma endregion


#pragma region // groups and id types
/// @brief ### type group
/// @tparam ...TS_Tp 
template < typename... TS_Tp >
struct group : blank_t
{
    /// @brief 
    /// @tparam T_Tp 
    template < typename T_Tp >
    constexpr static size_t count = sizeof...( TS_Tp );
    /// @brief 
    /// @tparam T_Tp 
    template < typename T_Tp >
    constexpr static bool has = _whitelist< T_Tp, TS_Tp... >;
    /// @brief 
    /// @tparam ...TS_Query 
    template < typename... TS_Query >
    constexpr static bool has_any = (_whitelist< TS_Query, TS_Tp... > || ...);
    /// @brief 
    /// @tparam ...TS_Query 
    template < typename... TS_Query >
    constexpr static bool has_all = (_whitelist< TS_Query, TS_Tp... > && ...);
    /// @brief checks whether every type in the group satisfies a predicate
    /// @tparam T_Predicate generic constexpr callable returning bool for a type
    template < auto T_Predicate >
    constexpr static bool foreach = ( T_Predicate.template operator()< TS_Tp >() && ... );
    /// @brief 
    /// @tparam ...TS_Query 
    template < typename... TS_Query >
    constexpr static bool is = has_all< TS_Query... > && group<TS_Query...>::template has_all< TS_Tp... >;
};
/// @brief ### type pair
/// @tparam T_TpL 
/// @tparam T_TpR 
template < typename T_TpL, typename T_TpR >
struct pair : blank_t
{
    /// @brief left type
    using L = T_TpL;
    /// @brief right type
    using R = T_TpR;
};
/// @brief check if type is a group
/// @tparam T_Tp potential group
template < typename T_Tp > constexpr bool is_group                          = fail;
/// @brief check if type is a group
/// @tparam T_Tp group
template < typename... TS_Tp > constexpr bool is_group< group< TS_Tp... > > = pass;
/// @brief enforced group check
template < typename T_Tp >
concept _group = is_group< T_Tp >;
/// @brief ### type identifier
/// @tparam T_Tp Tp
template < typename T_Tp >
struct _tp_t : blank_t
{
    /// @brief the stored type
    using Tp = T_Tp;
};
/// @brief ### value identifier
/// @tparam T_Tp Tp
/// @tparam T_vl vl
template < typename T_Tp, T_Tp T_vl >
struct _vl_t : _tp_t<T_Tp>
{
    /// @brief the stored value
    static constexpr T_Tp vl = T_vl;
};
/// @brief #### conditional constant
/// @tparam T_bool vl
template < bool T_bool >
using _bool = _vl_t< bool, T_bool >;
/// @brief #### constant false
using _bool_fail = _bool< fail >;
/// @brief #### constant true
using _bool_pass = _bool< pass >;
#pragma endregion

/// @brief meta structure collection
namespace _meta
{
    template < typename TG_L, typename TG_R >
    struct _groups_collide;
    template < typename... TS_L, typename... TS_R >
    struct _groups_collide< group< TS_L... >, group< TS_R... > > : _bool< group< TS_L... >::template has_any< TS_R... > > { };
    template < typename TG_L, typename TG_R >
    struct _group_includes;
    template < typename... TS_L, typename... TS_R >
    struct _group_includes< group< TS_L... >, group< TS_R... > > : _bool< group< TS_L... >::template has_all< TS_R... > > { };
    template < typename TG_L, typename TG_R >
    struct _group_matches;
    template < typename... TS_L, typename... TS_R >
    struct _group_matches< group< TS_L... >, group< TS_R... > > : _bool< group< TS_L... >::template is< TS_R... > > { };
    template < typename TG_L, typename TG_R >
    struct _group_combine;
    template < typename... TS_L, typename... TS_R >
    struct _group_combine< group< TS_L... >, group< TS_R... > > : _tp_t< group< TS_L..., TS_R... > > {};
    //
    template < bool T_cond, typename T_True >
    struct logical_if : _tp_t< T_True >
        { static_assert( T_cond, "Condition failed!" ); };
    //
    template < bool T_cond, typename T_True, typename T_False >
    struct logical_if_else
        : _tp_t< T_False > { };
    template < typename T_True, typename T_False >
    struct logical_if_else< true, T_True, T_False >
        : _tp_t< T_True> { };
    //
    template< typename T_Tp >
    T_Tp&& declval() noexcept;
    //
    template < typename T_Tp, typename... TS_Tp >
    struct logical_is_constructible_help
    {
    private:
        template< typename U, typename = decltype( U( declval< TS_Tp >( )... ) ) >
        static _bool_pass test( int );
        template< typename >
        static _bool_fail test( ... );
    public:
        static constexpr bool getter = decltype( test< T_Tp >( zero ) )::vl;
    };
    template < typename T_Tp, typename... TS_Tp >
    struct logical_is_constructible
        : _bool< logical_is_constructible_help<T_Tp, TS_Tp... >::getter > { };
    //
    template < typename T_To, typename T_From >
    struct logical_is_convertible_help
    {
    private:
        static _bool_pass test( T_To );
        static _bool_fail test( ... );
    public:
        static constexpr bool getter = decltype( test( declval< T_From >( ) ) )::vl;
    };
    template < typename T_To, typename T_From >
    struct logical_is_convertible
        : _bool< logical_is_convertible_help< T_To, T_From >::getter > { };
    //
    template < typename T_To, typename T_From >
    struct logical_is_assignable_help
    {
    private:
        template <
            typename U,
            typename = decltype( declval< U >( ) = declval< T_From >( ) )
        >
        static _bool_pass test( int );
        template < typename >
        static _bool_fail test( ... );
    public:
        static constexpr bool getter = decltype( test< T_To >( zero ) )::vl;
    };
    template < typename T_To, typename T_From >
    struct logical_is_assignable
        : _bool< logical_is_assignable_help< T_To, T_From >::getter > { };
    //
    template < typename T_Tp > struct trait_remove_lval : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_lval<T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_rval : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_rval<T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_lrval : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_lrval<T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_lrval<T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_ptr : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_ptr<T_Tp*> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_ptr<T_Tp* const> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_ptr<T_Tp* volatile> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_ptr<T_Tp* const volatile> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_c : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_c<const T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_c<const volatile T_Tp> : _tp_t< volatile T_Tp > { };
    template < typename T_Tp > struct trait_remove_v : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_v<volatile T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_v<const volatile T_Tp> : _tp_t< const T_Tp > { };
    template < typename T_Tp > struct trait_remove_cv : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cv<const T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cv<volatile T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cv<const volatile T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<volatile T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const volatile T_Tp> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<volatile T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const volatile T_Tp&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<volatile T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_cvlrval<const volatile T_Tp&&> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_array : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_remove_array<T_Tp[]> : _tp_t< T_Tp > { };
    template < typename T_Tp, size_t T_span > struct trait_remove_array<T_Tp[T_span]> : _tp_t< T_Tp > { };
    template < typename T_Tp > struct trait_is_lval : _bool_fail { };
    template < typename T_Tp > struct trait_is_lval<T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_rval : _bool_fail { };
    template < typename T_Tp > struct trait_is_rval<T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_lrval : _bool_fail { };
    template < typename T_Tp > struct trait_is_lrval<T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_lrval<T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_ptr : _bool_fail { };
    template < typename T_Tp > struct trait_is_ptr<T_Tp*> : _bool_pass { };
    template < typename T_Tp > struct trait_is_ptr<T_Tp* const> : _bool_pass { };
    template < typename T_Tp > struct trait_is_ptr<T_Tp* volatile> : _bool_pass { };
    template < typename T_Tp > struct trait_is_ptr<T_Tp* const volatile> : _bool_pass { };
    template < typename T_Tp > struct trait_is_c : _bool_fail { };
    template < typename T_Tp > struct trait_is_c<const T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_c<const volatile T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_v : _bool_fail { };
    template < typename T_Tp > struct trait_is_v<volatile T_Tp > : _bool_pass { };
    template < typename T_Tp > struct trait_is_v<const volatile T_Tp > : _bool_pass { };
    template < typename T_Tp > struct trait_is_cv : _bool_fail { };
    template < typename T_Tp > struct trait_is_cv<const T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cv<volatile T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cv<const volatile T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval : _bool_fail { };
    template < typename T_Tp > struct trait_is_cvlrval<const T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<volatile T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<const volatile T_Tp> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<const T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<volatile T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<const volatile T_Tp&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<const T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<volatile T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_cvlrval<const volatile T_Tp&&> : _bool_pass { };
    template < typename T_Tp > struct trait_is_array : _bool_fail { };
    template < typename T_Tp > struct trait_is_array<T_Tp[]> : _bool_pass { };
    template < typename T_Tp, size_t T_span > struct trait_is_array<T_Tp[T_span]> : _bool_pass { };
    //
};


#pragma region // meta helpers > getters

/// @brief enforced type identifier check
template < typename T_Tp > concept _check_tp = requires {
    typename _tp_t< typename T_Tp::Tp >;
};
/// @brief enforced value identifier check
template < typename T_Tp > concept _check_vl = requires {
    typename _vl_t< typename T_Tp::Tp, T_Tp::vl >;
};
/// @brief get type identifier type
/// @tparam T_TTp type identifier
template < _check_tp T_TTp > using _tp_get = typename T_TTp::Tp;
/// @brief get value identifier value
/// @tparam T_VTp value identifier
template < _check_vl T_VTp > constexpr _tp_get<T_VTp> _vl_get = T_VTp::vl;

/// @brief check if two different type groups collide
/// @tparam TG_L 
/// @tparam TG_R 
template < _group TG_L, _group TG_R >
constexpr bool groups_collide = _vl_get< _meta::_groups_collide< TG_L, TG_R > >;
/// @brief check if a group has a type
/// @tparam TG_L 
/// @tparam TG_R 
template < _group TG_L, _group TG_R >
constexpr bool group_includes = _vl_get< _meta::_group_includes< TG_L, TG_R > >;
/// @brief check if two different groups are an exact match
/// @tparam TG_L 
/// @tparam TG_R 
template < _group TG_L, _group TG_R >
constexpr bool group_matches = _vl_get< _meta::_group_matches< TG_L, TG_R > >;
/// @brief merge two groups intp one
/// @tparam TG_L 
/// @tparam TG_R 
template < _group TG_L, _group TG_R >
using group_combine = _tp_get< _meta::_group_combine< TG_L, TG_R > >;
/// @brief check if a type is union
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_union = __is_union( T_Tp );
/// @brief enforced union check
template < typename T_Tp > concept _union = is_union< T_Tp >;

#pragma endregion


#pragma region // meta helpers > type traits

/// @brief enforce a type check condition.
/// @tparam T_cond 
/// @tparam T_Pass 
/// @tparam T_Fail 
template < bool T_cond, typename T_Pass, typename T_Fail >
using _cond = _tp_get< _meta::logical_if_else< T_cond, T_Pass, T_Fail > >;

/// @brief removes a lvalue reference from a type
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_l =     _tp_get< _meta::trait_remove_lval< T_Tp > >;
/// @brief removes a rvalue reference from a type
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_r =     _tp_get< _meta::trait_remove_rval< T_Tp > >;
/// @brief removes lvalue or rvalue reference from a type
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_ref =   _tp_get< _meta::trait_remove_lrval< T_Tp > >;
/// @brief removes one pointer
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_p =     _tp_get< _meta::trait_remove_ptr< T_Tp > >;
/// @brief removes constant qualifier
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_c =     _tp_get< _meta::trait_remove_c< T_Tp > >;
/// @brief removes volatile qualifier
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_v =     _tp_get< _meta::trait_remove_v< T_Tp > >;
/// @brief removes all qualifiers
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_cv =    _tp_get< _meta::trait_remove_cv< T_Tp > >;
/// @brief removes all qualifiers and references
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_cvref = _tp_get< _meta::trait_remove_cvlrval< T_Tp > >;
/// @brief removes a array reference
/// @tparam T_Tp 
template < typename T_Tp > using _Clear_arr =   _tp_get< _meta::trait_remove_array< T_Tp > >;
/// @brief check if a type is a lvalue reference
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_l =     _vl_get< _meta::trait_is_lval< T_Tp > >;
/// @brief check if a type is a rvalue reference
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_r =     _vl_get< _meta::trait_is_rval< T_Tp > >;
/// @brief check if a type is lvalue or rvalue reference
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_ref =   _vl_get< _meta::trait_is_lrval< T_Tp > >;
/// @brief check if a type is a pointer
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_p =     _vl_get< _meta::trait_is_ptr< T_Tp > >;
/// @brief check if a type is constant qualified
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_c =     _vl_get< _meta::trait_is_c< T_Tp > >;
/// @brief check if a type is volatile qualified
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_v =     _vl_get< _meta::trait_is_v< T_Tp > >;
/// @brief check if a type has any qualifiers
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_cv =    _vl_get< _meta::trait_is_cv< T_Tp > >;
/// @brief check if a type has qualifiers or references
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_cvref = _vl_get< _meta::trait_is_cvlrval< T_Tp > >;
/// @brief check if a type is a array
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool _Check_arr =   _vl_get< _meta::trait_is_array< T_Tp > >;

#pragma endregion


#pragma region // necessary helpers

/// @brief Assign a lvalue to a type
/// @tparam T_Tp 
template < typename T_Tp > using _Place_l = _Clear_ref<T_Tp>&;
/// @brief Assign a rvalue to a type
/// @tparam T_Tp 
template < typename T_Tp > using _Place_r = _Clear_ref<T_Tp>&&;
/// @brief Assign a pointer layer to a type
/// @tparam T_Tp 
template < typename T_Tp > using _Place_p = T_Tp*;
/// @brief Assign a constant qualifier to a type
/// @tparam T_Tp 
template < typename T_Tp > using _Place_c = const _Clear_c< T_Tp >;
/// @brief Make a type only constant qualified
/// @tparam T_Tp 
template < typename T_Tp > using _Place_c_ex = const _Clear_cv< T_Tp >;
/// @brief Assign a volatile qualifier to a type
/// @tparam T_Tp 
template < typename T_Tp > using _Place_v = volatile _Clear_v< T_Tp >;
/// @brief Make a type only volatile qualified
/// @tparam T_Tp 
template < typename T_Tp > using _Place_v_ex = volatile _Clear_cv< T_Tp >;
/// @brief Assign constant and volatile qualifiers to a type
/// @tparam T_Tp 
template < typename T_Tp >
using _Place_cv = const volatile _Clear_cv< T_Tp >;

template < typename T_Tp >
using _Place_ex_c = _Place_c_ex< _Clear_ref< T_Tp > >;
template < typename T_Tp >
using _Place_ex_v = _Place_v_ex< _Clear_ref< T_Tp > >;
template < typename T_Tp >
using _Place_ex_cv = _Place_cv< _Clear_ref< T_Tp > >;
template < typename T_Tp >
using _Place_ex_l = _Clear_cv< _Place_l< T_Tp > >;
template < typename T_Tp >
using _Place_ex_lc = _Place_c_ex< _Place_l< T_Tp > >;
template < typename T_Tp >
using _Place_ex_lv = _Place_v_ex< _Place_l< T_Tp > >;
template < typename T_Tp >
using _Place_ex_lcv = _Place_cv< _Place_l< T_Tp > >;
template < typename T_Tp >
using _Place_ex_r = _Clear_cv< _Place_r< T_Tp > >;
template < typename T_Tp >
using _Place_ex_rc = _Place_c_ex< _Place_r< T_Tp > >;
template < typename T_Tp >
using _Place_ex_rv = _Place_v_ex< _Place_r< T_Tp > >;
template < typename T_Tp >
using _Place_ex_rcv = _Place_cv< _Place_r< T_Tp > >;
/// @brief set the qualifiers of the type
/// @tparam T_Tp 
template < typename T_Tp, bool C, bool V >
using _Set_cv =
    _cond< C, _cond< V, _Place_cv< T_Tp >, _Place_c_ex< T_Tp > >, _cond< V, _Place_v_ex< T_Tp >, _Clear_cv< T_Tp > > >;

/// @brief check if two types are a match regardless of qualifiers
/// @tparam T_Tp 
/// @tparam T__Tp 
template < typename T_Tp, typename T__Tp > constexpr bool is_same_cv     = is_same< _Clear_cv<T_Tp>, _Clear_cv<T__Tp> >;
/// @brief check if two types are a match regardless of reference
/// @tparam T_Tp 
/// @tparam T__Tp 
template < typename T_Tp, typename T__Tp > constexpr bool is_same_ref    = is_same< _Clear_ref<T_Tp>, _Clear_ref<T__Tp> >;
/// @brief check if two types are a match regardless of qualifiers pr references
/// @tparam T_Tp 
/// @tparam T__Tp 
template < typename T_Tp, typename T__Tp > constexpr bool is_same_cvref  = is_same< _Clear_cvref<T_Tp>, _Clear_cvref<T__Tp> >;
/// @brief check if two types have the same qualifiers
/// @tparam T_Tp 
/// @tparam T__Tp 
template < typename T_Tp, typename T__Tp > constexpr bool cv_matches     = _Check_c<T_Tp> == _Check_c<T__Tp> && _Check_v<T_Tp> == _Check_v<T__Tp>;
/// @brief check if a type is qualified void
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_void                        = is_same_cv< T_Tp, void >;
/// @brief check if a type is qualified or referenced bool
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_bool                        = is_same_cvref< T_Tp, bool >;
/// @brief check if a type is vectorizable
/// @brief ###### ( is non void and isn't a boolean because of reserving seven unused bits )
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_full                        = !is_void< T_Tp > && !is_bool< T_Tp >;
/// @brief check if a type doesn't have constant qualifier
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_mutable                     = !_Check_c< T_Tp >;
/// @brief check if a type doesn't have volatile qualifier
/// @tparam T_Tp 
template < typename T_Tp > constexpr bool is_optimal                     = !_Check_v< T_Tp >;
/// @brief check if type is constructible with given typed arguments
/// @tparam T_Tp 
/// @tparam ...TS_Tp argumens
template < typename T_Tp, typename... TS_Tp> constexpr bool is_constructible = _vl_get< _meta::logical_is_constructible< _Clear_cvref<T_Tp>, TS_Tp... > >;
/// @brief check if type is convertible to another type
/// @tparam T_From 
/// @tparam T_To 
template < typename T_From, typename T_To > constexpr bool is_convertible = _vl_get< _meta::logical_is_convertible< _Clear_cvref<T_To>, T_From > >;
/// @brief check if type is assignable from another type
/// @tparam T_From 
/// @tparam T_To 
template < typename T_From, typename T_To > constexpr bool is_assignable = _vl_get< _meta::logical_is_assignable< T_To, T_From > >;
/// @brief get a type with another types qualifiers
/// @tparam T_From 
/// @tparam T_To 
template < typename T_From, typename T_To >
using copy_cv = _Set_cv< T_To, _Check_c< T_From >, _Check_v< T_From > >;

template < typename T_Tp > concept check_constructible_copyable = is_constructible< T_Tp, _Place_ex_lc< T_Tp > >;
template < typename T_Tp > concept check_constructible_moveable = is_constructible< T_Tp, _Place_ex_r< T_Tp > >;
template < typename T_Tp > concept check_constructible_ = check_constructible_copyable< T_Tp > && check_constructible_moveable< T_Tp >;
template < typename T_Tp > concept check_assignable_copyable = is_assignable< T_Tp, _Place_ex_lc< T_Tp > >;
template < typename T_Tp > concept check_assignable_moveable = is_assignable< T_Tp, _Place_ex_r< T_Tp > >;
template < typename T_Tp > concept check_assignable_ = check_assignable_copyable< T_Tp > && check_assignable_moveable< T_Tp >;
template < typename T_Tp > concept check_general_copyable = is_assignable< T_Tp, _Place_ex_lc< T_Tp > >;
template < typename T_Tp > concept check_general_moveable = is_assignable< T_Tp, _Place_ex_r< T_Tp > >;
template < typename T_Tp > concept check_general_ = check_general_copyable< T_Tp > && check_general_moveable< T_Tp >;



/// @brief move helper
/// @tparam T_Tp 
/// @param val 
/// @return 
template < typename T_Tp >
constexpr _Clear_ref<T_Tp>&& move( T_Tp&& val ) {
    return static_cast< _Clear_ref< T_Tp >&& >( val );
}
/// @brief forward lvalue helper
/// @tparam T_Tp 
/// @param val 
/// @return 
template< typename T_Tp > constexpr T_Tp&& forward( _Clear_ref<T_Tp>& val ) noexcept {
    return static_cast< T_Tp&& >( val );
}
/// @brief forward rvalue helper
/// @tparam T_Tp 
/// @param val 
/// @return 
template< typename T_Tp > constexpr T_Tp&& forward( _Clear_ref<T_Tp>&& val ) noexcept {
    static_assert( !_Check_l<T_Tp> );
    return static_cast< T_Tp&& >( val );
}

#pragma endregion

}


#endif




