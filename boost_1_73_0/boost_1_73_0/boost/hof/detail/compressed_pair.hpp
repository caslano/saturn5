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
ZGWlgc47QL9q3vLjlEA1c2m4tZfMZ/LXUMyNsyDj1+kVOzyc0fGDOe0J56E1jfuZYgDnqyX57GuWzueQWqTzqpjwVkNv7i+j+LbPnkgRqQGgArP9zKpRgnxmxolKvuYmE0o+cfmPth+ObL+Qm8E+NG0r0loqU2WjB6UDEo0AcwsWjbT9i5wU5ynG33iXp9MfvpIjKNANZeCt2jOoJK2oMGubZKWqotNUtW4gt4XBtltFDoCAp1XiZX6xUBmwEur2/p1aNd2Ch9SDWFRFEp7zXZMsr1PUktV8lzWrA1dF4T7d5bo5kfbmPAmidozUODKdxauCLP1Xu0nTZZvNyjUh4M9w6Ts4MEXLducl6iyv2VXdjPE8KYS+qxdZOOqIAbt/iodahHZYs1INNBVrw4+pYY7ZVoOAcINAUxi4RyC4Uyiwg4FUxR1DwH2DgFzaULifsV2aGNSWsmvPgxlTqaYla2JG59DAYb0eVBoCi3zfPC1miHxyNyFUL6u3Qo1ZLKDfp8K1zYQHBQ2/RTisd/9473kZLPAptpeno6agoANNLO1B54+VDOVxLOGWGDR0s9WndmMK+qOVJSnikfB6oOwzjSHqN7GOqy/tfNM94n8s4xaKu3JOtN+PbQE5ZZEaxhuv2qFzveZW7SaL7+6W
*/