/* Boost interval/detail/c99_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP

#include <boost/numeric/interval/detail/c99sub_rounding_control.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<>
struct rounding_control<float>:
  detail::c99_rounding_control
{
  static float force_rounding(float const &r)
  { volatile float r_ = r; return r_; }
};

template<>
struct rounding_control<double>:
  detail::c99_rounding_control
{
  static double force_rounding(double const &r)
  { volatile double r_ = r; return r_; }
};

template<>
struct rounding_control<long double>:
  detail::c99_rounding_control
{
  static long double force_rounding(long double const &r)
  { volatile long double r_ = r; return r_; }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_C99_ROUNDING_CONTROL_HPP

/* c99_rounding_control.hpp
msHfAcAJrs5hPy+F5fA7DK8GgyOEnbgs8zQx6ye+XmDyULDjHrEiJR4vludsQYW/kxlLlWZkSbmNKoSmWG0PHAWoFC4UT5ro1j8Ziy1CHDOCwlzOw6bH50LNqCBcchs6juRsMHrXHZDuYFAJeMbVe7+s0PY+SNyT9BMrC8A6IPSQFZL32Sd2IdXSuVsbK5QQlbHIJyICPFNcUiN4WSXDCz8I6kt7LlFpuAax/fBhVyf6glUTjuGXTqcJrigAaaEx12loLHaMjqDxwhy+SMCdBGRLFmthsc18jylgVIvVjWxEwe45/74/6BES4WrQH+LKBwF1Hf1W6o3H5Lz752hM3nVPq7dzhW3ryxILRmVZOPizC43OFFZMyU3RmCptuEm/1SugYLCSeIjtFAId1twr+H7d/i9FevtviySoZU9eIzwAF1yVZl2f+vMllfUIIOS/WM8N9EQNJJT1X8ed/sFQQ+6PXuAY7PaAP4JXr3hzzem5x566x/Z4Cj9Un+EknPaHPx804eXLLUS+hlUgsoIb73j35cn1Gb7Ht9Ue6S2Y3GySB91svtXOraBKyEjClMtELQ2EbkDlcSnczsdRDq2W7uiGcy7Pps3Ij2dGxZ+YLSjXlX7pBmSs1/0i1Lut6SY1zahAa9SsZJxpJZFa
*/