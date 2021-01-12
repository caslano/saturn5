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
7d8yvj+oPLTx/UJlr+P7x5W9ju/VlXZ8n/cEGPmPlZ7xvagyY3xPBoAd39En/vfG97/7cyB/RlQOE7Xnhc7qZvBk8auZas8ll4Nsxm64MxOJyeehcGMFYvRMLhavyIgRiHekzzrQ787m/uY+KAsleM1OADQRonT/LMb1p0JZCCZ3rLczyj0AxkqFQR1HKn66gpe6mokGl0PWlqdmajN+ie6+7AD2//Js+1u7k4AOnL6AUpw6
*/