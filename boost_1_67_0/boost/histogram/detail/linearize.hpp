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
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
*/