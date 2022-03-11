/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    compressed_pair.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_COMPRESSED_PAIR_H
#define BOOST_HOF_GUARD_COMPRESSED_PAIR_H

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/config.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/alias.hpp>

#ifndef BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND
#define BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND !BOOST_HOF_HAS_EBO
#endif

namespace boost { namespace hof { namespace detail {

template<class First, class Second, class=void>
struct compressed_pair;

template<int I, class T, class U>
struct pair_tag
{};

#if BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND

template<class T, class U>
struct is_same_template
: std::false_type
{};

template<template<class...> class X, class... Ts, class... Us>
struct is_same_template<X<Ts...>, X<Us...>>
: std::true_type
{};

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)

template<class T, class U>
struct is_related_template
: std::false_type
{};

#else

template<class T, class U>
struct is_related_template
: is_same_template<T, U>
{};

#endif

template<class T, class U>
struct is_related
: std::integral_constant<bool, std::is_base_of<T, U>::value || std::is_base_of<U, T>::value || is_related_template<T, U>::value>
{};

template<int I, class T, class U>
struct pair_holder
: std::conditional<(
    is_related<T, U>::value), 
    detail::alias_empty<T, pair_tag<I, T, U>>,
    detail::alias_try_inherit<T, pair_tag<I, T, U>>
>::type
{};
#else
template<int I, class T, class U>
struct pair_holder
: detail::alias_try_inherit<T, pair_tag<I, T, U>>
{};
#endif

// TODO: Empty optimizations for MSVC
template<
    class First, 
    class Second
>
struct compressed_pair<First, Second>
: pair_holder<0, First, Second>::type, pair_holder<1, Second, First>::type
{
    typedef typename pair_holder<0, First, Second>::type first_base;
    typedef typename pair_holder<1, Second, First>::type second_base;
    template<class X, class Y, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(First, X&&), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Second, Y&&)
    >
    constexpr compressed_pair(X&& x, Y&& y) 
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(first_base, X&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(second_base, Y&&))
    : first_base(BOOST_HOF_FORWARD(X)(x)), second_base(BOOST_HOF_FORWARD(Y)(y))
    {}

    BOOST_HOF_INHERIT_DEFAULT(compressed_pair, first_base, second_base)

    template<class Base, class... Xs>
    constexpr const Base& get_alias_base(Xs&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Xs>
    constexpr const First& first(Xs&&... xs) const noexcept
    {
        return boost::hof::alias_value(this->get_alias_base<first_base>(xs...), xs...);
    }

    template<class... Xs>
    constexpr const Second& second(Xs&&... xs) const noexcept
    {
        return boost::hof::alias_value(this->get_alias_base<second_base>(xs...), xs...);
    }

};

template<class T, class U>
constexpr compressed_pair<T, U> make_compressed_pair(T x, U y)
noexcept(BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T) && BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(U))
{
    return {static_cast<T&&>(x), static_cast<U&&>(y)};
}


}}} // namespace boost::hof

#endif

/* compressed_pair.hpp
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
*/