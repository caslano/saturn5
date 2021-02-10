/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    join.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DETAIL_JOIN_H
#define BOOST_HOF_GUARD_FUNCTION_DETAIL_JOIN_H

#include <boost/hof/detail/holder.hpp>

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct join_args
{};

template<template <class...> class T, class Args, class=void>
struct join_impl
{};

template<template <class...> class T, class... Args>
struct join_impl<T, join_args<Args...>, typename holder<
    T<Args...>
>::type>
{ typedef T<Args...> type; };

template<template <class...> class T, class... Args>
struct join
: join_impl<T, join_args<Args...>>
{};

}}} // namespace boost::hof

#if defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_JOIN(c, ...) typename boost::hof::detail::join<c, __VA_ARGS__>::type
#else
#define BOOST_HOF_JOIN(c, ...) c<__VA_ARGS__>

#endif

#endif

/* join.hpp
+4OQPNlagKzIEnjlJxAmr2DJNNcefAnT69ldCl/8+dyP0gXMJuBHC5J1E0YjijcnTQrwoVaoSbMCvqkFx8IpbG+1JetnSvwnlpNz69+MJ+F0DJF/Ox7YBeDyacO+/hc5bdkzGifBPIzTcBYdrYFDxOlr84HMQldmKwqT4Etn6y+zp6V4dfw4hquPENzNp51OGk+y+V2U0Z7Mgusb+59o1mkxO0YEUWUrdw+sKLjtJ0xYtDRUiMWh7gSvvrbn4TT8lDgX54sYgiSZ/gJ/bPyx2j53Ytlwaquue1IrawS255HNNFOvMtJoHbOJRgi+IL/+SC2VxoEW35Op82CmzPdkvdcGN21Ck+B6g5Vx3XaJ1J43NVVHATvqabDO8xNFtafTSrLJRI2XRpmRan/V4VUumgLhoreTqoC3Hj1QZHJGLxc9qlVkeQkFkV32z2Zp37uguWLRk43K0Q2xIUkd3h4rfEAy+314/ppV0mQrSaOi3wmyZB7YwFz0gmR2Nw/GSb9NYP1j4Wg32uQWleI08F3feY4rrARb6/bSrgu6qQ+DiAYS4WuDyWheVmt9umfUUllyLgu86gSTqf85yWxvsSl2ubMyaMSDLcIu9J5MDwji3+wVZkm3hGrF15eUmoPSzdb+P+SM7pJxNovH0aGY
*/