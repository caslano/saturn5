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
nG61x+32Ofrrzz/PXjZL1qOf5+tZ9PMsZclPj9snpHd3jKan6Rdt/bzVtmvtJQp/1OCbH7Wn9XzxAH8ydrEfPr/cLxfR44874lijq/nP640WhctlBsg+XoRR3JVQ8xK+/Qjvas+sF4st/BGtVxG09+vj+qnwImNwBvXwslmxJhmD2JvzNRuEH7WX1Tzc8C84S9J2Eo5z9h8whLs+zLX1itGm/dnwNMv7s3Y/jRbRj9qt5V85E1+7NVzXsP07zRlkaIZ9p11bdp9JzIK1vdHC3543YcRo2WiLp+flIpxLJKR/Nj4zJH/+vHjQVustk8eHxSqcf9ebuMOA/8eye8H36Vvxr7XibyV2wcM6bjOG/jUWSC7Viejeh9qnkEkLE/joy2qm/cqYoPXYP2fLl3msAJHU/8b7XTlfaGwmWEXb6WobvTLj59rQ6nJO3piuZzn2Tz/9lP5GfGYIne/+Jnz/t3clwMHI+LvjKsKL6DHI30qbsOwGmgCQ0ibGht+7qtsEByltwp6MFBv48O7kRGqEwciD4Vsj0/ON0Zg8zhlCCr4TJf57z+ldm37QNfqKTfylheFAc2wiI2JVzy8j40Nw61q+GXjWP0x0kim+UiCw+CtFAltn7fNO2mC4YivVoQRf+f44uDKNvumWUpx7
*/