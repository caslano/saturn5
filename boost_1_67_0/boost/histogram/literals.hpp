// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_LITERALS_HPP
#define BOOST_HISTOGRAM_LITERALS_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
constexpr unsigned parse_number(unsigned n) { return n; }

template <class... Rest>
constexpr unsigned parse_number(unsigned n, char f, Rest... rest) {
  return parse_number(10u * n + static_cast<unsigned>(f - '0'), rest...);
}
} // namespace detail

namespace literals {
/// Suffix operator to generate literal compile-time numbers, 0_c, 12_c, etc.
template <char... digits>
auto operator"" _c() {
  return std::integral_constant<unsigned, detail::parse_number(0, digits...)>();
}
} // namespace literals
} // namespace histogram
} // namespace boost

#endif

/* literals.hpp
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
*/