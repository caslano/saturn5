// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TRY_CAST_HPP
#define BOOST_HISTOGRAM_DETAIL_TRY_CAST_HPP

#include <boost/config.hpp>
#include <boost/core/demangle.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
template <class T, class E, class U>
BOOST_NORETURN T try_cast_impl(mp11::mp_int<0>, U&&) {
  BOOST_THROW_EXCEPTION(E("cannot cast " + type_name<T>() + " to " + type_name<U>()));
}

template <class T, class E, class U>
T try_cast_impl(mp11::mp_int<1>, U&& u) noexcept {
  return static_cast<T>(u);
}

template <class T, class E, class U>
decltype(auto) try_cast_impl(mp11::mp_int<2>, U&& u) noexcept {
  return std::forward<U>(u);
}

// cast fails at runtime with exception E instead of compile-time, T must be a value
template <class T, class E, class U>
decltype(auto) try_cast(U&& u) noexcept(std::is_convertible<U, T>::value) {
  return try_cast_impl<T, E>(mp11::mp_int<(std::is_convertible<U, T>::value +
                                           std::is_same<T, std::decay_t<U>>::value)>{},
                             std::forward<U>(u));
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* try_cast.hpp
Xv+Bbwn7olVf94vKUEKsmtn4Or9SYMTuzzRWNd75bX/ilsyHFDX2NpJ3c6oIemtyUX663DPwPfUX51QW8c6/7mHRX5OHAkpSDKNUu/ZMnrW7Mg7slbq02xhQl37EMpurI++1/6MIGD68q3fGR20kJxTto2vNitak3RrH8mw/yNs7hD2YkbcoEmkinlILvS7/vEUOP4celmaH1Bdxvc9U5r54kXjbVx3q1jX0KQHZI+7QYA6nJ+pIMRn3IYTAyR81lgG2+1H0CFsyZdBYeZaGq9/AjMcZ9XAabF0n+lakLN1mvOq4tAj4Its8n8l66E3sysB74EzCN4PdoJp0t/LKcfrpoOzG6cOjbTdGeu3NGq+s1aur/8Z07MEHzbwg+Akand6hkBaGa/5kTSdOhLJA5pOLf/5gATiqvENXdOTK+gHwpROkIBjq69wW61TmpjlzRljykv575EYyqNv5/ioznNMloaUFx7Y0flGVJIaYOZky9ohOv+6soALQgc3P5eZOhyRDrC0q3lZ/AhBrLnc/qBphaOUBrI0nVQU9ZG96QkaYxsU+F54gi3bhMg==
*/