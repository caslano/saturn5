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
Da9DswCxj3o37IqRcqm7lOOxJwEBUP290jkmxSJIDBupp6CH5SlmO2RoCJgF7nkPlstD0IuRRVuzTlQotMA1/YNGEcNOxU48ZiMn1ZL+/HVMaQ8kDHwEZf/7eHlowBxh1JcKu3O1BVDqzuyKhQKX3eBh3hsHY7S5a/k6ExLL1I3iKmVw/rOr4niAA8Pocu9pSTz4SfyUcH7qilC0oGOHkACB3PKZ9Ugrxwrv9t0SGVb2CKWI0l/xgOvUCjtSxWdWqzWHrX2zErnVygSEbdO6u2xI4vEJXZBl00Wb0QvehBwibSidByXTBEM8ENxOAvjt5odFqScJTkMICD/i86OhmYnO5Cn7xprmnv+l3VSoU2KaGp+ewoiDtutR+12s4bU6swwVa2omt6SrtdX8Qbq49HirfArPhAMMgZHTAXTHdZXUcYZ647Pl4YNNVNV/oAnP5wZ+C5g7CORtW8ctgT1he9zqvM5mwXfeBBrvaBtPo/3bbcbBNuJJ+wZaPjQCktWErRbF8kyEwJJPkVZx2XMTJnZurdpmXp/yRffP6Lf9A6oumcEgFPI/cdl4Gg==
*/