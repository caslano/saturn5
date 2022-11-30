#ifndef BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED
#define BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED

// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/describe/modifiers.hpp>
#include <boost/describe/bases.hpp>
#include <boost/describe/detail/void_t.hpp>
#include <boost/describe/detail/cx_streq.hpp>
#include <boost/describe/detail/config.hpp>

#if defined(BOOST_DESCRIBE_CXX11)

#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/bind.hpp>
#include <type_traits>

namespace boost
{
namespace describe
{
namespace detail
{

// _describe_members<T>

template<class T> using _describe_public_members = decltype( boost_public_member_descriptor_fn( static_cast<T**>(0) ) );
template<class T> using _describe_protected_members = decltype( boost_protected_member_descriptor_fn( static_cast<T**>(0) ) );
template<class T> using _describe_private_members = decltype( boost_private_member_descriptor_fn( static_cast<T**>(0) ) );

template<class T> using _describe_members = mp11::mp_append<_describe_public_members<T>, _describe_protected_members<T>, _describe_private_members<T>>;

// describe_inherited_members<T>

// T: type
// V: list of virtual bases visited so far
template<class T, class V> struct describe_inherited_members_impl;
template<class T, class V> using describe_inherited_members = typename describe_inherited_members_impl<T, V>::type;

// L: list of base class descriptors
// T: derived type
// V: list of virtual bases visited so far
template<class L, class T, class V> struct describe_inherited_members2_impl;
template<class L, class T, class V> using describe_inherited_members2 = typename describe_inherited_members2_impl<L, T, V>::type;

template<class T, class V> struct describe_inherited_members_impl
{
    using R1 = describe_inherited_members2<describe_bases<T, mod_any_access>, T, V>;
    using R2 = _describe_members<T>;

    using type = mp11::mp_append<R1, R2>;
};

template<template<class...> class L, class T, class V> struct describe_inherited_members2_impl<L<>, T, V>
{
    using type = L<>;
};

template<class D1, class D2> using name_matches = mp11::mp_bool< cx_streq( D1::name, D2::name ) >;

template<class D, class L> using name_is_hidden = mp11::mp_any_of_q<L, mp11::mp_bind_front<name_matches, D>>;

constexpr unsigned cx_max( unsigned m1, unsigned m2 )
{
    return m1 > m2? m1: m2;
}

template<class T, unsigned Bm> struct update_modifiers
{
    template<class D> struct fn
    {
        using L = _describe_members<T>;
        static constexpr unsigned hidden = name_is_hidden<D, L>::value? mod_hidden: 0;

        static constexpr unsigned mods = D::modifiers;
        static constexpr unsigned access = cx_max( mods & mod_any_access, Bm & mod_any_access );

        static constexpr decltype(D::pointer) pointer = D::pointer;
        static constexpr decltype(D::name) name = D::name;
        static constexpr unsigned modifiers = ( mods & ~mod_any_access ) | access | mod_inherited | hidden;
    };
};

template<class T, unsigned Bm> template<class D> constexpr decltype(D::pointer) update_modifiers<T, Bm>::fn<D>::pointer;
template<class T, unsigned Bm> template<class D> constexpr decltype(D::name) update_modifiers<T, Bm>::fn<D>::name;
template<class T, unsigned Bm> template<class D> constexpr unsigned update_modifiers<T, Bm>::fn<D>::modifiers;

template<class D> struct gather_virtual_bases_impl;
template<class D> using gather_virtual_bases = typename gather_virtual_bases_impl<D>::type;

template<class D> struct gather_virtual_bases_impl
{
    using B = typename D::type;
    static constexpr unsigned M = D::modifiers;

    using R1 = mp11::mp_transform<gather_virtual_bases, describe_bases<B, mod_any_access>>;
    using R2 = mp11::mp_apply<mp11::mp_append, R1>;

    using type = mp11::mp_if_c<(M & mod_virtual) != 0, mp11::mp_push_front<R2, B>, R2>;
};

template<template<class...> class L, class D1, class... D, class T, class V> struct describe_inherited_members2_impl<L<D1, D...>, T, V>
{
    using B = typename D1::type;
    static constexpr unsigned M = D1::modifiers;

    using R1 = mp11::mp_if_c<(M & mod_virtual) && mp11::mp_contains<V, B>::value, L<>, describe_inherited_members<B, V>>;

    using R2 = mp11::mp_transform_q<update_modifiers<T, M>, R1>;

    using V2 = mp11::mp_append<V, gather_virtual_bases<D1>>;
    using R3 = describe_inherited_members2<L<D...>, T, V2>;

    using type = mp11::mp_append<R2, R3>;
};

// describe_members<T, M>

template<class T, unsigned M> using describe_members = mp11::mp_eval_if_c<(M & mod_inherited) == 0, _describe_members<T>, describe_inherited_members, T, mp11::mp_list<>>;

// member_filter

template<unsigned M> struct member_filter
{
    template<class T> using fn = mp11::mp_bool<
        (M & mod_any_access & T::modifiers) != 0 &&
        ( (M & mod_any_member) != 0 || (M & mod_static) == (T::modifiers & mod_static) ) &&
        ( (M & mod_any_member) != 0 || (M & mod_function) == (T::modifiers & mod_function) ) &&
        (M & mod_hidden) >= (T::modifiers & mod_hidden)
    >;
};

// has_describe_members

template<class T, class En = void> struct has_describe_members: std::false_type
{
};

template<class T> struct has_describe_members<T, void_t<_describe_members<T>>>: std::true_type
{
};

} // namespace detail

template<class T, unsigned M> using describe_members = mp11::mp_copy_if_q<detail::describe_members<T, M>, detail::member_filter<M>>;

template<class T> using has_describe_members = detail::has_describe_members<T>;

} // namespace describe
} // namespace boost

#endif // !defined(BOOST_DESCRIBE_CXX11)

#endif // #ifndef BOOST_DESCRIBE_DATA_MEMBERS_HPP_INCLUDED

/* members.hpp
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
*/