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
18e0wrOsr+TM9ZXY+iacrr5hr1kfGeaXwgUdwgVTunDBHxZk6Lo+JWBbiwAWKMgG2wUw1u09yuWhfEVBiQoPLtcd4OtV0lCSRdIagzW22b/2RDWEfDRcLzrC5rXZkfknTpFxb8k+Hg7u9njIc8ByJKigYIiiZF6FlSpK5+pdCscsfEI1gXPlMPxOj9riEzx2GUeAVUe2I6DIjoAd8203wB6Hz08OLOBhWJqT0S1r5mdz/2vK
*/