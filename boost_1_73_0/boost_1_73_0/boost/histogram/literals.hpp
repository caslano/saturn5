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
s9nWrg1F5RK8iwX0CIP7eoQhEZFlZRVslqlbabXd4aweTDqML3e+4aiQiL+XFXQRVHGJ23twgGIwMSr4Mir5fenSvXNfjAVn9pVFClbd3WmEZG1g6tZMfYzxTQNnjKZjBYkQ35iEt/jwvzEt9uNg2YY9SeqWzeJmaXQw5XCQ70mar8F7/8PatYBXUV3rPScnIZzwCAF5VTDgEREUk5BAfOYEAgQJBAQKKjSJySGJhBCSEx5aZRBpk4Zc0dYq1+s=
*/