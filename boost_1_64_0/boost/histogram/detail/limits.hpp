// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LIMITS_HPP
#define BOOST_HISTOGRAM_DETAIL_LIMITS_HPP

#include <limits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr T lowest() {
  return std::numeric_limits<T>::lowest();
}

template <>
constexpr double lowest() {
  return -std::numeric_limits<double>::infinity();
}

template <>
constexpr float lowest() {
  return -std::numeric_limits<float>::infinity();
}

template <class T>
constexpr T highest() {
  return (std::numeric_limits<T>::max)();
}

template <>
constexpr double highest() {
  return std::numeric_limits<double>::infinity();
}

template <>
constexpr float highest() {
  return std::numeric_limits<float>::infinity();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* limits.hpp
usIsL9uz2PY9Kv0wu2eptsEW0lXJkrz7XJ2W31ZjrWcM+NSwzMvGutUgJH79teCfJMJzwwcKIlfFSwvstb3hZYQ6U0aMWxRCanNRo+v5rpgcBjNywy/kDjlJ3p8ULkFaPM5AiaELYDgDPSmM+XPr1UguefhoIRtUGQcZg9TkCJ7lYuP1f02oKPv3sOnEssKKNBoMs442k446dUHfBezDx/S/OI6ENcXQGu47c3Claqt/lLUplv0VEcn1PW9sJWHr5aUJbeb34heXG+9Ll1ZvC5ruC5UYvKVWWm5UWm32vdXn2vXrjf7f5FxxU6AzfcBOV4qHnN3fGKVD9S4Q/wGSMHFE2U1aE7Ss5CMmVQDCBBvrrRZX+K6Ur7774KXBFJbAkN/dhCg8EsD4rMFmU//wxj7vWD8a8ko0CQFUeNTHil4IF68bG1s3vGawVKe65lHtgVmgxNiUyPau3nUtRxx7GUa8sSkYAwyc1cnjAWZxRLkU3JGfJLNbMOr9KKbZCpxW2w3QGsG6OJV0NnKK2tEPRRrAt7WRICd2TbfpmycsyxDsMCR/Ix37jvAnYA==
*/