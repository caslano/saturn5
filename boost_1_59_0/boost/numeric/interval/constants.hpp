/* Boost interval/constants.hpp template implementation file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_CONSTANTS_HPP
#define BOOST_NUMERIC_INTERVAL_CONSTANTS_HPP

namespace boost {
namespace numeric {
namespace interval_lib {
namespace constants {

// These constants should be exactly computed.
// Decimal representations wouldn't do it since the standard doesn't
// specify the rounding (even nearest) that should be used.

static const float pi_f_l = 13176794.0f/(1<<22);
static const float pi_f_u = 13176795.0f/(1<<22);
static const double pi_d_l = (3373259426.0 + 273688.0 / (1<<21)) / (1<<30);
static const double pi_d_u = (3373259426.0 + 273689.0 / (1<<21)) / (1<<30);

template<class T> inline T pi_lower() { return 3; }
template<class T> inline T pi_upper() { return 4; }
template<class T> inline T pi_half_lower() { return 1; }
template<class T> inline T pi_half_upper() { return 2; }
template<class T> inline T pi_twice_lower() { return 6; }
template<class T> inline T pi_twice_upper() { return 7; }

template<> inline float pi_lower<float>() { return pi_f_l; }
template<> inline float pi_upper<float>() { return pi_f_u; }
template<> inline float pi_half_lower<float>() { return pi_f_l / 2; }
template<> inline float pi_half_upper<float>() { return pi_f_u / 2; }
template<> inline float pi_twice_lower<float>() { return pi_f_l * 2; }
template<> inline float pi_twice_upper<float>() { return pi_f_u * 2; }

template<> inline double pi_lower<double>() { return pi_d_l; }
template<> inline double pi_upper<double>() { return pi_d_u; }
template<> inline double pi_half_lower<double>() { return pi_d_l / 2; }
template<> inline double pi_half_upper<double>() { return pi_d_u / 2; }
template<> inline double pi_twice_lower<double>() { return pi_d_l * 2; }
template<> inline double pi_twice_upper<double>() { return pi_d_u * 2; }

template<> inline long double pi_lower<long double>() { return pi_d_l; }
template<> inline long double pi_upper<long double>() { return pi_d_u; }
template<> inline long double pi_half_lower<long double>() { return pi_d_l / 2; }
template<> inline long double pi_half_upper<long double>() { return pi_d_u / 2; }
template<> inline long double pi_twice_lower<long double>() { return pi_d_l * 2; }
template<> inline long double pi_twice_upper<long double>() { return pi_d_u * 2; }

} // namespace constants

template<class I> inline
I pi()
{
  typedef typename I::base_type T;
  return I(constants::pi_lower<T>(),
           constants::pi_upper<T>(), true);
}

template<class I> inline
I pi_half()
{
  typedef typename I::base_type T;
  return I(constants::pi_half_lower<T>(),
           constants::pi_half_upper<T>(), true);
}

template<class I> inline
I pi_twice()
{
  typedef typename I::base_type T;
  return I(constants::pi_twice_lower<T>(),
           constants::pi_twice_upper<T>(), true);
}

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_CONSTANTS_HPP

/* constants.hpp
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
*/