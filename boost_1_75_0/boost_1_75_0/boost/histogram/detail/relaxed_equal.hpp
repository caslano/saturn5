// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP
#define BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr bool relaxed_equal(const T& a, const T& b) noexcept {
  return static_if<has_operator_equal<T>>(
      [](const auto& a, const auto& b) { return a == b; },
      [](const auto&, const auto&) { return true; }, a, b);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* relaxed_equal.hpp
08nXZ38ilNFNRiZ+puxcZjx97KGnuPwYsKNrIukIY8vzWmTLzdveYw7CqdM9BAsIuK0u243kLS3mri8WZR3N5ZIArzf67katQGJt2fuvXH3PkDW+ybb2zUlNIXGwwjexabT4bbgNrgv/6oHhplTHruUm8pt+yaxgh0u0rOprlabtveU4AiEOJ6+kNP/o6hzBrag1BNHmL4RnBR0NWIaj90lOdeii8W/xtpH9xJoLeOIDno4wLEQKcG8tieEoyLhyesqPwtxRcgaGe/8Qp1fOSz++cMwWeq25Qx9K+6l2q6ry0MVkwHSuUhxsM9IVQSwpT/1ERLiyET/TPKXry/xkBzdO53/zWgEowNpCCl32Xb3wMnWaOxT35YMKWxwRWuP47fkcXhv6IjXZfap4mGYvLL7d3lABhnZwywKZXCnysWZeOw2KoHg5t1e/UylCU4HIIkFZ5BGWDrdCr1g9fkr2CD3x5hWny6vd+BU7sT89Irk/0wRk5g78unm+ZbEFlyEfYX26iyhOrB+0JJHZ93mitmauapHf/yqB4pgmNrDs1hggCrAWPJoMDlI2yifsemR3OeaI7TGajWGAUr1idafD0dvmW/wnJigZVMRW8MjuwytWx3jF6mlh9kalTlNiwYMWT3RQaigulBv6FlrROxlAxHsUpnk87SkEbsf/IiYBg/8KjBD4aNG27JYbWro10jrRNkHotoKsUo0Widd6
*/