/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    forward.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FORWARD_H
#define BOOST_HOF_GUARD_FORWARD_H

#include <utility>

namespace boost { namespace hof {

// contexpr-friendly forwarding

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{ return static_cast<T&&>(t); }


template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
  static_assert(!std::is_lvalue_reference<T>::value, "T must not be an lvalue reference type");
  return static_cast<T&&>(t);
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined(_MSC_VER)
#define BOOST_HOF_FORWARD(...) boost::hof::forward<__VA_ARGS__>
#else
#define BOOST_HOF_FORWARD(...) static_cast<__VA_ARGS__ &&>
#endif

}} // namespace boost::hof

#endif

/* forward.hpp
0GkPvPlJPOTEOPLHtdDkEETcEshj0ReZa4lMu1OxNN7Y7+4HZI526NtXEx8trkLqSe9Lkw2L4iG7pF4PXsGVeFXnTQ+2GrPsNpszudOUkN+95gewf22JyLzDx8svixqqFdVfspNy03WjcIKIaAQSbxarO/NycBoGZ0r98jt20f3dFaegBBxkwMTaO+mbl0qCyttargKVm21vut5RKfbK+rnK7vrZ4pNc+mGvHYKQlrSE+sPn8nuOKvRGTuuNlY5IKUSGCB62WysES/9Fi31MlzdLPw7Px79Vjav3iNFC07KJ1dl1MR8tJ3Kvb3wBi2pSTkeCxzh1/3HMKZrzSwu777ghEckxcA5ElEGpSLhPschx+qm2Yd7k84GOvXPVH+wwYrvqK9Vn+5robalw7UWTb1aNe5TC73nJN7s1LJ+O00rgFFGHqbjcBm3KFURLPhrt2D7Or/i4PhKqdcwyKOOdcJ+NFaNGrLZPY48DkPqoL402uKgTJi/Vaf0ZQxxt8cfIvoHBMAEHfWgW/mtVVfNLl+UpSnz9oPK4HXucdxZioqh0szmovhSBgFKHyg==
*/