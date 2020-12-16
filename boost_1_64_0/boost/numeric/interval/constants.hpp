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
woeYTwcynteGy/6ag7M+mTmvg2EHuyN3yfhcR3v+XoMzg7DPB7+2w5lBWPjRNpPwfV7Yb4P5f/5vccL+Wj4Ld6B4Ya0PReBsmizsvE+34djHhL2PGIjzdaawMVnD32A/EpaV+fgu7g/CBk6z6IOzhrBnL53jlH/HQdUenTuL86dCWM+ely5jzxE2Kjr3FWqPsI/vHjRG/IS1+jhEG/ETVtB191LET1j/S5u7IH7CehdNU36PFJYzcZIN4kdmwazo9pDdWGNkVszMxl3Kx5lBtFu0cmA/1HnRLqbedUusFTI7nvP+PR2Vf6dC9a626Kz2XzjXkVlxG3o/GPWazIavv5aBGN+En+Lb2mP/TOypZJrMkvtsaIg5EzatSsBT1CwybWa7+nu8xB5AZs5sXcgm1JCtZJbMOnc4lYScJzNlNl27A9bfXTIev7N6H05jDyBTMFPkXlX+PpyMz/Vej32FmOtfqs8MtDJpjdojzNmxLWpPAJkus5YDXg7F/kCmx+ez9eElyGsyHgeja8vGI35kJsyG3ci5iDMRGR+fbbf2xxEjMn3el09d1REHMp6ffWyrOyMO4pn705vswt5BxmPU/r1LPOJAZsZsyooe+K5fJMa+craJMudFX47Nd8Z+pPitmmdPzi2xxtmGTIdZdd2cPOwdv0U/V46/hhiR8bne+H3iKNQeMmM+ZxeX5yFGZDwOR3Pe5GAPJzNg1qHlPeU3JDJtvv4GpEdhjZHxGJ3vNKsZzq2in65pBQ9Ql8h4nr1xHoZzZCKZOZ+zMONnOJuK8TWad6EpahYZj/s340aIUY4Ye9uhyhpSRGbKzD71qx/2jj+qsd1+YwPqhA0ZH3ut3f074XemZEZ87J8HYB/zI+Pvu+aQPAN3WDLezxmj1o3A3YKMz5lOsyr2uMOS8Xx5sWvSRNQzMp67WxT7vBAHYXVqh4QgDmJ8Dntdf2PvIDNkNqH7iAKsMTG+omXtP+O8K8Y3efPZM9jfycyY1ag7vQ3WGBmPe8TRQEOcwWiFWfF63c19COJAxufFwzjHHWuFzII/s66dP2qWaJdWzQV5PYGMx9Yislc25lq067PeoTfOS6KdiY7y703sJzNgFhnYywN7B5k5s93ZlwYir8XYH42tWwv3cGHvdBdgzhRVNFXmOv9klQzsD2Qq589HtZAvAWTazO6EnUTcg8Qzc7efa4T5JLPka7rhwx+YTzKeg8Pt7DG+OGE/brx0wx5AZsbNND0IewCZgtmHUVZ5yE8yaz6fiRO1sQeQ2TL7T5mjA+aTjOdLoqkP6ryhuqbKWjEOSkNe25DpMJtt+RT7nwuZM7MNV6ProhaIZ9o6ze6G+xiZMbMqrX17oJaTGfBnXl48BnNNxnOp45IJyzGfZHyub1W5rryriWcGvoxFHHaSGfL6UnPgUsw1GZ/r0KQd0zHXYnw9StcsQi0Q43vxKnQwzvpkKnfKkI/rlH93R7VdvZT7j7HfkhkxO/2o8VrUCTI+dvN6Y1Gva4t26/xTtZHzZDyvvYemKr8FkfF+aoT5431Rol1Sp7gfiAOZDTOt2uP6Ya6FzbKZHY39j8yM2cb4tD04s5PxuH/5T1oH5LUY3+CXRcr51FQdg4mRzW/kNZkpn8+8dOWfAxT2dGnsLswZGe/n2v47ENtwMt7PNwoNY8yZMPvQlbVx1hDPHHjqfgrqLpklz4lO9njmCTILZtazJnRGfop2G69d6oscFO0m3TyEuqurpVp7tO+3S8O5TkvMWcD+BOSZsIZ31jfA2ZuMj93U8ATe14eM92VLaJnyfiTMLfnmIeSZeN+UJg5zMGdkfD5bdG1wFmtaWFa6E+rLTfG+I+Ou40z0msySx92kNkw=
*/