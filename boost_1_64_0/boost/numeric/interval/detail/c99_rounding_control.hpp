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
qLNXUzV+NEhe7PJnifJ5QTRyEkZ3JbUHxSgvZR7+NnDXeIgOoQpl4dp2mgdlFJwPRC4Tqp36HBG1KnD4aZYYkTLWj1AZg8SVHm3XOM2JCn57Z5s6oKLIzUjnezL8c8AaPC7KExNCYkcy0FD/drR7jRzkuHOuyClTOmtOqEozNoXh3Fz3h5mtd62yA/PlwmvFn0bfbwizaQNI+7fz6z2Ij5vtTquIvbQp5Mf9CgYGA7ORjUy7lffiI6ejYyoYCzfEoho7UnoQlXAGLv9AYcVQXekRmIjSnJH7Srqch61mBGtpMmvDWwK1Abjfw78XzTal3KF6Znvr2aZDRvg3EdLqp+ScOZ0fNEqW6uiFCsaoTgv0+C+UOHshzQKoDGXDDDVZPPfC2y/wIcYaarOVw5DlQYael/UshZj0xcqQlO9IfOPvHlb4USY7wZnn7LxUgmy+KZKV+q7tal1+1aUHOJ1BCNGV3e0qqcZVTzi4vMpO1666p5nKbPfd/VliiJOOva+rj7A5QIL2nUwYgydjdnGIFhVjx8wrvBMjAOGB4gK8U/gtUzA8xxcBuGK/7A==
*/