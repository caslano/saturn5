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
e9hKMeYOuCDmTCQTp1yaDXxICt4fiL07Maw8Ell8aS+9X/k3ZJmZNW3kGVZujQovCkdxRkArfOnnjcozziiphPeYKmz5NCwkvUedNQr40rGb42kGsAThVgdxKcgdLQclxjoS8v2hDpJ6fTf3/P1Okuhk1llHU/9OxHpv6fhnoavzhaocUdiVbSPAkaut3xvgWXBZ0aK8jOlc8hTnqJ+JzMEtzEzzGdfBd35tIVcQc7He4JCB/GlJdcxy33JTWodtytBa7Mb3ELzI4ldL2X11+swr8nSvGzeZySxVHhkmn0vEayzZeCJC5Jp7l3tduDoP68eWKGolKDXAI7uvWvPxQaFvlYWsJrXmPbJbIY8Bj1BuBb2WzcbzRvGIEM7cZkSM7bRTp8YdTxl/EeL6PyYaiTGQtHoJLjx22h224b4Va9TMmqWQiNrpA3Ushq0OOZ5udtJ2TlvpZfv+scMFC0vKfLuqUYww/iwpans2Dpdpma2RMqGtRFph5iiVQmFj3tR02xMrJ6Y5+yd5vyQgDEXXRtMesp/a6pRi+p97mEKFw+f/chrKFzaitK3/WD7BoI5RpnAxYopjq5y1cGfIlIxGLMdsHFikaawOuU6MBs5eCQPeQoiJlUraE2cYrjYafR1NB28ik1ZzpNHBZXo2uQQFoL7b+dC+07/5Jg4cBz9xbQuCx2QnTW+KissgcGnTaOviQjTVJ563OuPVq/iu
*/