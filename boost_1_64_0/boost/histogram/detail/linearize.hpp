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
XIQN2gjkNgCl994iiOzQrg2hNwhW5bvFqv00x2P0VmN0/A/q7keoQv+aECoU35Xpc4/sUJOwEwmpArT/qeva1Ra5Ziosb8sQjdkMlu6zBb4wvL7f5XCHOYS2yp9ndnMnA0bk+vOqtpAGI5RhTdmyxn7U+SlwbRk8t93CKMJ6CC5a+vxwA6B28AxKYemhZG6mzn7ImnlND9AaJt1jPg/Y57V4MY42hcDaZ57ihzPT1lFaknN4q1UytCXZcSAwG3TxQbj2hktv0wkzYNoZJz8rXsblbmN7K4727fGUpW1TGyAQ7J8gckW1ZpkjhpBC7WQKozMUtrjMOqL0dlSuXJFv9/z1YpRPr1Sp8m8p09Rp8OTgxLFg15R33xBCn7X3vW6CjtYBj0Bh+kYYxz1UpFfoziOOuHLaHY0dgnXGpbLNL7DSnYlRdwUd2HWxHo3EuN1B5UJPCBu8b7hM70dmz1YQ6PXMXDx3ZtoCdmjkNrTNHE7DkhV+v/mSzIQ7zqgJa/tcE9QUE6oiyFCvEs2XXd6pagd1i3T0XhMEoK1drBOnSzNCGMcT+/jid95qew==
*/