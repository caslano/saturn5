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
  auto seen = detail::make_stack_buffer(old_axes, false);
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