// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LINEARIZE_HPP
#define BOOST_HISTOGRAM_DETAIL_LINEARIZE_HPP

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/fwd.hpp>

namespace boost {
namespace histogram {
namespace detail {

// initial offset to out must be set
template <class Index, class Opts>
std::size_t linearize(Opts, Index& out, const std::size_t stride,
                      const axis::index_type size, const axis::index_type idx) {
  constexpr bool u = Opts::test(axis::option::underflow);
  constexpr bool o = Opts::test(axis::option::overflow);
#ifdef BOOST_NO_CXX17_IF_CONSTEXPR
  if
#else
  if constexpr
#endif
      (std::is_same<Index, std::size_t>::value || (u && o)) {
    BOOST_ASSERT(idx >= (u ? -1 : 0));
    BOOST_ASSERT(idx < (o ? size + 1 : size));
    BOOST_ASSERT(idx >= 0 || static_cast<std::size_t>(-idx * stride) <= out);
    out += idx * stride;
  } else {
    BOOST_ASSERT(idx >= -1);
    BOOST_ASSERT(idx < size + 1);
    if ((u || idx >= 0) && (o || idx < size))
      out += idx * stride;
    else
      out = invalid_index;
  }
  return size + u + o;
}

template <class Index, class Axis, class Value>
std::size_t linearize(Index& out, const std::size_t stride, const Axis& ax,
                      const Value& v) {
  // mask options to reduce no. of template instantiations
  constexpr auto opts = axis::traits::get_options<Axis>{} &
                        (axis::option::underflow | axis::option::overflow);
  return linearize(opts, out, stride, ax.size(), axis::traits::index(ax, v));
}

// initial offset of out must be zero
template <class Index, class Axis, class Value>
std::size_t linearize_growth(Index& out, axis::index_type& shift,
                             const std::size_t stride, Axis& a, const Value& v) {
  axis::index_type idx;
  std::tie(idx, shift) = axis::traits::update(a, v);
  constexpr bool u = axis::traits::get_options<Axis>::test(axis::option::underflow);
  if (u) ++idx;
  if (std::is_same<Index, std::size_t>::value) {
    BOOST_ASSERT(idx < axis::traits::extent(a));
    out += idx * stride;
  } else {
    if (0 <= idx && idx < axis::traits::extent(a))
      out += idx * stride;
    else
      out = invalid_index;
  }
  return axis::traits::extent(a);
}

// initial offset of out must be zero
template <class A>
std::size_t linearize_index(optional_index& out, const std::size_t stride, const A& ax,
                            const axis::index_type idx) {
  // cannot use get_options here, since A may be variant
  const auto opt = axis::traits::options(ax);
  const axis::index_type begin = opt & axis::option::underflow ? -1 : 0;
  const axis::index_type end = opt & axis::option::overflow ? ax.size() + 1 : ax.size();
  const axis::index_type extent = end - begin;
  // i may be arbitrarily out of range
  if (begin <= idx && idx < end)
    out += (idx - begin) * stride;
  else
    out = invalid_index;
  return extent;
}

template <class Index, class... Ts, class Value>
std::size_t linearize(Index& o, const std::size_t s, const axis::variant<Ts...>& a,
                      const Value& v) {
  return axis::visit([&o, &s, &v](const auto& a) { return linearize(o, s, a, v); }, a);
}

template <class Index, class... Ts, class Value>
std::size_t linearize_growth(Index& o, axis::index_type& sh, const std::size_t st,
                             axis::variant<Ts...>& a, const Value& v) {
  return axis::visit([&](auto& a) { return linearize_growth(o, sh, st, a, v); }, a);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DETAIL_LINEARIZE_HPP

/* linearize.hpp
jqMGWVHQzuUMJ+wlorSMPo7Od/dyizVrmDUyRGRjYqzw8z0mXlwLHVb+TibHESVQtIUO/X3xAeXd/zpv0IQLlwK1HN7wKQp3AvsSDncGpnN4WIb/WnqcgnWD1nT+1r/EP+9hO3BJKP2IdWkJB4rqvsTrxLGAvBDifgs8I87w8yFHnziE03lkmKid4utv6FFM7IvjhvA6dhBnN/l6q5MfkzfywYqRL8wFSSqiYgCdbiZ55d2ccwUK/znw3q19HLypXu5Vzt+fu6D7P6W9S93n5PmD2mZrvomdCqbZP/saHnDuTTzTyxGBXQjuuXiCd9L5mgvOlrjBL69rGKgjfEFHoFoTF98uHdOU55tC9YjSI5gq0u7lYnIz7+95E25DblJ5y6JsizW9qJCtN+GmXnO4koPGZnFQJ8Tf90xCzOagi20JRKc02WESKuAbKUbARhhGxW9qxDm0VOTySnx34HsI36D++wC+Tz/z0Z1HIvlxQn5+fltCfnCzfR14DDz9HBzwf8WEJyrXoFV4V7NE44gpX5qW4+NqcIrP9mWRjDwPTxZPISa8QeJMxjmJgl7/9+G8A9fJTdMhCdSD2FDLgVQH3ziU6hN/QTj6AMjZKJSiFaUduidyKjW8CHdUoa70yz5Cg6QbolKf+FlA9TxZuPRwrrph/aZGd9ARoFyKM/cYslAgjnpYFnwKeCgBzBcvSeBGCwk4ai2Ffi/MGknm964Nx+OQU13acVcmN2+x/nbVmMYQYasutDcmeMkRv6hn+yN12zWEKHgF1xTf5FC5hFuqa9O5cqef/2ngvgDHiomom3oPFL+wT1M92zXxknxZKUCuZxp85ZaLSQetAU1KiOvT+hUNyAZKOpXFY2FDwiXK+Zqqsz0Q39bP9yQ7tBr6Lx4OqCtScjncyeFOscoIt6mb++s+9BJwZR2EfK2/T+VrYLBW5esBma+Zq/R86ZnKFF9bf05+XkhYqWaIuVkPMnOE3Vn+13crD4WIIK/nywnOlBxVBtZJjp5fyRxRTSdkxQRpyV9sSEuuqL1JbzZha/Dm1qeZ23MVjST5+K3WrXycebQ7+ajakJCPzuXYZ2U38nGjduHyweWLoop9kXPd2B1cv1n9C8slSrfxj99gALuF373weLy7gvN49cvo3tJqaNTMcIsiSUcTGjnfD+lqhQdXnd1huGG7CnlFV5VrCg2JrMhGj+sNHEVB+cRQTeFsSAXOxkyoEs9k41/rpV7oIYSSlUB5ncaWWkIhlcOD7ngJDftn7uZSJkIxYHC40+sTryfCf2DSGbCv/oJCyQ7MZQJPJ9A+rWA5gRDDvqFgoSCH5wZWcvhaI/xGDs8PrOfwBUb4KA4vCHyVw2cY4ZdxeFHgMQ6vMMJ7QllikZjZ+C+8oJHqmzL+rZU0IhWLh+voapxXb6L/S2ZxwbOHl0sCD5vVEPldGiK/KgV8GFe+s5P3rc7+Eu5aCwd1LDj5ke1xPx2sNFH47x46btxblVY3h08yk4rMGo9fbFikbmOs0hAK9t6dw7JGI2Gm7nmPI41+iMbxgsB2Yxz/JjH5iGSyYRkzWTcHI7lOQ6l6RdBn+OoeuI7JC7xoRH80KfoUGb3FBXLUgHFLp8hP57ar3zS2OptAI8RP2uNKx6bQFIR6tbtsuHrk3njYJMol96O/J5WOwwa1byVRO3yvpPYcXrXx1kipFah/MlC/kYT6hI76sDy8Ctf9zRU2E8fjM1wUVkB3AAeBHTAbykV0sj6m1n+cxlgoHumABUxgi8BBAzyOOlWAexD4lA6eZIDzqTS8gZ7Jka+WUDULmLp/tl/cAOteVlHvnSrvSGuUdf0vkfDz+2zM5v4fcyV5k00BvOP4yBpKFDw=
*/