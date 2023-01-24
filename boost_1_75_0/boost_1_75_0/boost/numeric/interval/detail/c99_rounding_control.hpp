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
q6xqF5OatONns4nnLdfs2+4wU7Qra1UzqOORuTxEFOBLUntUU+o+KxqY5001xweIxscQuHjwADRfjs1jth/N/sAdeJwE3eHV7qzBZp5Yh+wfOnSAO0IodT+5ncdoOIdjxrTh2bgLv02dbiI3/yQ2PJvnlBqezndDYj8N8U9zFJkf21NSZDk8MkMH+s47ONBGbRjXlCo1eQKWTTRP4DmQikbH5pPqEAuGvmnN/trtGGMyOrtsn0TpvViz2+apGq5caJWcX86cHapKlmsqkUuEDrZSFCaLyMf+I9tclRiAOaoWN70KssFsAJ1A5PKsmDNUZhPScfszC41OVpAh5xSky2y0Vd7Z6gvPSfcqibCUCzLg723wN1VduMVkCk/JduyDp9ZIEklJWOBW1MgfuR0xhYWuk077OK/t8eeqMMbw1GBjO8DF5277YT53wIj+VSzmLhvmboAZRjdVzsGToq2OFmV8f+fmWT1zaJ4qeCLAmZRCU7PfPo2yrN8qs7EZPvjIl7MZTynzh/dPI3LLMIxIjMynzLDh4cak/bMYX8JtDjDIr6/ikRx0bgwzKxVS4YOHfHz2Vvj5ujzd/GE4B2uTj+3llik75LmgzpNZO1oZ1NXnPDI7mfYnIz5JGWN2Tsiebc+ZkE1xkX9ommMfnR4bGEmEq6Ny2U8BGybro+w6X6gzGhCu0emgJlzYkybSslsOT8jgJ8tOE2vXMY5O
*/