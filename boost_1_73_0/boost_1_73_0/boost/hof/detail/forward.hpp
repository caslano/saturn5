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
vS5DPpURPf9dOV/cyq5FR5pFzjYtTM9gLG+VHU9Giy4lczWeXoY2U4bcpeva4UuYIDI7KqPm5CopOF6UPrNczixfwjNdf/5qz57uqfHb8uWu2B1LdjAvdh+kyGtHcePvg55WBm2MnaI/oTQqdkNx6yYv0rhKxVGamtfJPWLyRqF2/e5OvLKxLe/6qTWG13QlOXueM4yTOBXXNNtmvaWD086q8TgK9mtRweZ+mTkFm+qqK/Ay6ldrAOaqa+yePXs=
*/