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
yse9GG510qt7kHjReINOMyc2A/umiVWoVUIzFEoyNT/GBf4japs168CVVPwCidwCVjhEs171b55v5S6mMNCs1n8zo9ONZJEV/8380zAji6T0yYApWSXbtrlXiGthfyVjFL0xUKv5Q3hzCJymBrdihydxDgnkxB5AMY2uIEXGHgqN3kg5R4GFdHyAh8X+iu06C7kfTlh+VhxdCyOq1QH81dqozBn2ruLHI7HiaQ4M2j8YzvH6iv5uKA8OLO8JMyFEDlfeIdpRMCAcrY8zrnEQ+TLRtoSzX/3rdCFWadn3FcTjSD5Uizv4UGo463+WW66hhWn3KvnN6OIIPOx++bgr+1uAoCtYvF8dzb5zCx7u+YEzhjnjtV02OK3kOjEP+A95v0e5AtkaELZsx+ZlU9pZcu5pVI+MMAjY1CF/UuIKpl8jPlGNPjp9HMEhOqze+yAKVlxDJi/gxXLJVbqW6wG5CjAtW+sAsrIPokE2oJWDjKCFdivAGrRGqUUsdcVgCs0AgLmhGzgO9wzHNNpffUSngLuerZkeo8z0rNmHMLreIgW2aswYNEjyt4aMCHOe7TOLF0inqoseSv7plGvU08bwathpNZa9HJUjIVq7Ew5NTVoRE5qKUmsbt7xmkfLHh703y+3Zexzyzy5lQoH6eDo6UN2f5MxdQ5EFTnE8u3BVHfWNwfSkify0y3IEThseHI3HN4VkEI8ZqGlzKS6g
*/