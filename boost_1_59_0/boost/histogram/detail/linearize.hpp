// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LINEARIZE_HPP
#define BOOST_HISTOGRAM_DETAIL_LINEARIZE_HPP

#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/multi_index.hpp>
#include <cassert>

namespace boost {
namespace histogram {
namespace detail {

// initial offset to out must be set;
// this faster code can be used if all axes are inclusive
template <class Opts>
std::size_t linearize(Opts, std::size_t& out, const std::size_t stride,
                      const axis::index_type size, const axis::index_type idx) {
  constexpr bool u = Opts::test(axis::option::underflow);
  constexpr bool o = Opts::test(axis::option::overflow);
  assert(idx >= (u ? -1 : 0));
  assert(idx < (o ? size + 1 : size));
  assert(idx >= 0 || static_cast<std::size_t>(-idx * stride) <= out);
  out += idx * stride;
  return size + u + o;
}

// initial offset to out must be set
// this slower code must be used if not all axes are inclusive
template <class Opts>
std::size_t linearize(Opts, optional_index& out, const std::size_t stride,
                      const axis::index_type size, const axis::index_type idx) {
  constexpr bool u = Opts::test(axis::option::underflow);
  constexpr bool o = Opts::test(axis::option::overflow);
  assert(idx >= -1);
  assert(idx < size + 1);
  const bool is_valid = (u || idx >= 0) && (o || idx < size);
  if (is_valid)
    out += idx * stride;
  else
    out = invalid_index;
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

/**
  Must be used when axis is potentially growing. Also works for non-growing axis.

  Initial offset of `out` must be zero. We cannot assert on this, because we do not
  know if this is the first call of `linearize_growth`.
*/
template <class Index, class Axis, class Value>
std::size_t linearize_growth(Index& out, axis::index_type& shift,
                             const std::size_t stride, Axis& a, const Value& v) {
  axis::index_type idx;
  std::tie(idx, shift) = axis::traits::update(a, v);
  constexpr bool u = axis::traits::get_options<Axis>::test(axis::option::underflow);
  if (u) ++idx;
  if (std::is_same<Index, std::size_t>::value) {
    assert(idx < axis::traits::extent(a));
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
                            const axis::index_type idx) noexcept {
  const auto opt = axis::traits::get_options<A>();
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

template <class A, std::size_t N>
optional_index linearize_indices(const A& axes, const multi_index<N>& indices) noexcept {
  assert(axes_rank(axes) == detail::size(indices));

  optional_index idx{0}; // offset not used by linearize_index
  auto stride = static_cast<std::size_t>(1);
  using std::begin;
  auto i = begin(indices);
  for_each_axis(axes,
                [&](const auto& a) { stride *= linearize_index(idx, stride, a, *i++); });
  return idx;
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