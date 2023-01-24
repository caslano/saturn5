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
ry/Ks4HobJ60cTvZjowzMRM0gu8Wt4rxY9XrAXOgJ6O2mQRvY9tHIwu7BAYgGdPHohheAuMzdGXu2agpWqhZpF/ttPTMmtRvCumUsxlExid+MnyrjvJh13TUQ30NZV9jI5O8sNZyRapU5OolVSO/62XG5uJlLxLo/hEehkzBOBmJYd4v7SQBQI1O7qqsQqxCj5C8+mlnOuP2ivmtstGOtiZNh+GWdbEVmCQQUvpC4Zfln0V9THOM2CnHXRbrnyAAu7aQf0FzUjLN+wmMGt6WKiheo5Lij1b3onpv9YryDngPWt/jc6U3lzS8m0qQ7pZLPdY8dvPGraffHwWn6aqCD8rLFkc99r2fmQfP5Q35/TALX3TuqV7ZOuW7RT2+OYeefNLIeHL5+kQyEB79EI1HfeV3Ne+4cWSvMZeT7QBBANZs5Ze5wFdD8ctcglOls5k6ZE4Zdxp+T37dJHdjvqn5PUnNhewm4KRV2hAep2SBeRTMGxv2yQ0NE/t0vRfrlHGPM3+SqZzTrVq5hg7iwbBAILRRkrrkd+KwhRv88tFOb1JsL74/OckfkFMfpTUul8DbvX0XDrGkt+u/12eI5jbdcIgZxDJ5o9PRZJn0dvBcJmb9wp/rszzwFu42LZXe9raaWaLi6us+S4JKg13WTyX7RJVQiPRwsljtkRV3tz5kOhqWTkcpDqqieNzgmcuH86vhybXPfJ6zwwa22e0q
*/