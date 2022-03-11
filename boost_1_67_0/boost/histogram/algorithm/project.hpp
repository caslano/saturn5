// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_PROJECT_HPP
#define BOOST_HISTOGRAM_ALGORITHM_PROJECT_HPP

#include <algorithm>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/histogram.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/set.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace boost {
namespace histogram {
namespace algorithm {

/**
  Returns a lower-dimensional histogram, summing over removed axes.

  Arguments are the source histogram and compile-time numbers, the remaining indices of
  the axes. Returns a new histogram which only contains the subset of axes. The source
  histogram is summed over the removed axes.
*/
template <class A, class S, unsigned N, typename... Ns>
auto project(const histogram<A, S>& h, std::integral_constant<unsigned, N>, Ns...) {
  using LN = mp11::mp_list<std::integral_constant<unsigned, N>, Ns...>;
  static_assert(mp11::mp_is_set<LN>::value, "indices must be unique");

  const auto& old_axes = unsafe_access::axes(h);
  auto axes = detail::static_if<detail::is_tuple<A>>(
      [&](const auto& old_axes) {
        return std::make_tuple(std::get<N>(old_axes), std::get<Ns::value>(old_axes)...);
      },
      [&](const auto& old_axes) {
        return std::decay_t<decltype(old_axes)>({old_axes[N], old_axes[Ns::value]...});
      },
      old_axes);

  const auto& old_storage = unsafe_access::storage(h);
  using A2 = decltype(axes);
  auto result = histogram<A2, S>(std::move(axes), detail::make_default(old_storage));
  auto idx = detail::make_stack_buffer<int>(unsafe_access::axes(result));
  for (auto&& x : indexed(h, coverage::all)) {
    auto i = idx.begin();
    mp11::mp_for_each<LN>([&i, &x](auto J) { *i++ = x.index(J); });
    result.at(idx) += *x;
  }
  return result;
}

/**
  Returns a lower-dimensional histogram, summing over removed axes.

  This version accepts a source histogram and an iterable range containing the remaining
  indices.
*/
template <class A, class S, class Iterable, class = detail::requires_iterable<Iterable>>
auto project(const histogram<A, S>& h, const Iterable& c) {
  using namespace boost::mp11;
  const auto& old_axes = unsafe_access::axes(h);

  // axes is always std::vector<...>, even if A is tuple
  auto axes = detail::make_empty_dynamic_axes(old_axes);
  axes.reserve(c.size());
  auto seen = detail::make_stack_buffer<bool>(old_axes, false);
  for (auto d : c) {
    if (static_cast<unsigned>(d) >= h.rank())
      BOOST_THROW_EXCEPTION(std::invalid_argument("invalid axis index"));
    if (seen[d]) BOOST_THROW_EXCEPTION(std::invalid_argument("indices are not unique"));
    seen[d] = true;
    axes.emplace_back(detail::axis_get(old_axes, d));
  }

  const auto& old_storage = unsafe_access::storage(h);
  auto result =
      histogram<decltype(axes), S>(std::move(axes), detail::make_default(old_storage));
  auto idx = detail::make_stack_buffer<int>(unsafe_access::axes(result));
  for (auto&& x : indexed(h, coverage::all)) {
    auto i = idx.begin();
    for (auto d : c) *i++ = x.index(d);
    result.at(idx) += *x;
  }

  return result;
}

} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* project.hpp
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
*/