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
0lwSk2PaWfZEPx/BP9htHsEeJpzN//fjQU3puy32k76XGH7o2cTwO88lht+0lL/Vkv+VPYnhBy3lt1jKv/3dxPCllvrWWuqbaanvfkv5d5+x8i+klyg3by9WYuzoxwWcl0rvaRaEqkznKfVr7yyhZXPqp4yihypdsRTnUkp5R6W4YynZnPKCTAl7iCMKn3jaKI7uDC1XLpAeK+DllG/IAqTwdxn1Ye1Aam/tRVT32qxQZaoteD4VW6uKLWCh5utksXNQPDvtR+F3Q5408DuhAWf6DhAo5SQrS/s6baiCJXwN3iuvwXsfklTT3yOJzqS893xi1zPmgRW2M510wS46ppgSC1JGGGQQVpN+iwGfTorK05Axbf29RDXdeBO9MlvpX4MU3uomOkEl7Ql8qOmUDRVs4QraUt6F8r84gPLPUvmHl7S1fDrK30PlK6n8jra1n1o30Y3yfpSPjK9/AIWJvtzq92nwMhY3mpgKaaNOSrzET3MB2u3QXSbtNnhKmV8HQrPJnMmAmsnXtxOBysCJVho40UiFE238mqSjCqY0bX/0vwDdket5/uO8npmXJsY+y+Y92ChSrS22Yjs8ba7YyRJ/zoS/ap/YLnXdQxVE3WdXyuWg4I3daDJj06r72Pll97aT/oAZlINDypBfcCJJioi022a+Al4hVHJXgJCI66RkJvVMy4rbWncY9v+/b1he3XEHMcl+D0KT9nqBQbiexz12qxnwlrAU0SG0Y7Lbt9Hw/4aybBz0XmhNVj6gHplf4S4AInv2mRs8rXoFyBAl3OGZZs4rtYdvJHP18g1Ry9ZXpiMf+S1LIkDVjjLW2t6d5lprOBUv2E0DZAfh3GiJCPyYK29KQRQM6PeK/nssJDGW5SaGXMed5vSvs0kMK5MdZhi4wWM64WTim0qyh30qdSwFA/5EO746pHEgdyn8oy5l/CRFHvZrXTa9t4EkVHPKw9g5pdhmPrEmmdlyROMB6219vYEgrA4DOTinI71+ppZI3we0LfaNXGGX8hraIyQcwQxy4bQjyE1Lfez941noQAYs9WMhJNQvEtvT0L5B/5dvak6zpIvi51ukv6N+g/5/+vK8ELu0XB7jNej/qnzzdPFaY0vlaTnwG5zk2ULj7NJpUwnL0c53ii8ZO6CI6AtJsLfIFh1ffVIReobgFKgAISbvII6FuxuKA1Ev5lm8+5gSFO4Dws62J9V747WAjZJT9ygd5AwKDtA5fX8Rz4I0SV5mMFkb+c+5C6xoQs1P0w9N+FjTxaN7WoIPnaIShnV74qg+f0CnaBHnHcPD6QlzIxEibthcvm4H3/6gVDc5jQt/7Yy09Q9TDr9z50uLcV3uWbi5tf64cgGouskQlXwxWV1311NL1AmPX1z+hAJxtXy/N9a/uZj8n7TS31bwcdRPj8ES8a7U8q+dTFP+AI+9VDz80D/JArbaP+Z/8b1HEvUBA1b/5ypd7Q+r//PEdGGt35OQLnlX/LCvGlcItKbIDuTYW2OIq0GTQFLFWDTkwsBIXFfKpPRWeWNtfsA0GAqfNT56nM19XGoeCqqyC7ZIR0mjw8RQJoOZvGmHimwt80rBK8b/2d1cfzAQz/+xpit4Kf5P83QRX/88S7ryxx3FcmAhEUP9Lt8WHBwGa96n7QB4mElfj+1GtqoQGCVwudOxb4g6sX9u2MIBmYEIDiRHWTfe4TXenAdQg0+sQnHDGQVLgPtE6DHz9d5zKeNlRnVtckHN9Bw+xDo+pg6xIrr7MngNhPY65M3FXtj94mMMFPP3NSAtXuAku7gLlHD3ErZSu49xwoHYd7C805pHCekH8B2c+jRl5sYweJaSNACwGQDwiwrecZmhsS9hwmz6Au4=
*/