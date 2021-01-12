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
708o7hbEW+x82WeD+CQA9GhlfvrRiv24VxB7Gt7pMTaIS63+p5f5o0r6+P5BvEDqPx4LIsbePzspiOeFb1b8z0uOUvx3U4JYSta/JeGjdae/V9iHsQOCyJje99/lDw5io+Ydf508NIjr2fn2uBDN2z+J2UFcQvaXMocF8SXCY3OCeN3wfv9EZF4QSb9kI1TOnz5XWT8cH0Tc8H6/cG5BEFukfrYofPgcpf5PDuJC0r7RU4I4
*/