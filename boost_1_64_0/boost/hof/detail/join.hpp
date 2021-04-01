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
EC97AdnZEpyTtG4n+H++p2UB/e4CLya8cOJBJwdXhuSQT2FFvef6ODpwbwLvQHsvcIdOMlu2FlFUfWGfbMTp8h6CO8VLYlU3vXKiSnqwGnclqWjM+O6e/e/2/HU+1mGHTn8O9MORBHXn86WqSabijQKKCBIFHuQdcjcr46bLPDQ3ORukEvNrV0+TXd31YD9m6ZMyr96zxbK1zSVt40xZZ5AufrzVnkGyTqb6fY8UNSZXergejmGNZKsgcfJBzyMbsHTKtciE3rklfruWtXgyGNatPg4SgtpH3JWwiC9T/UPijs2NoKcofVskquUWGGJ4AxVUymWWCMdCcicjZxHBLR43OnBC1AU3mzmIJtrnZP/VvVBVZk5BuonHToZkN8H8T7R4GbJHcTwufvjxpluGC54FkzSPfsaPGgffejdNH9evprjFXCO8pPJxI8AMdwEZk8d/WZHf2T30gXbvmYHRCoq61mDJ3bFq8/8M4ZwYyaKxojnhUHJyqQQhIfEpmOwwjFIVpJZH5lCA6Deus/vC+T3kjHt1jWA913P288jnit74bIrQgH39oFUkpg==
*/