///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/gamma.hpp>

  namespace boost { namespace math { namespace detail {

  template <class T, class Policy>
  inline T hypergeometric_0F1_bessel(const T& b, const T& z, const Policy& pol)
  {
    BOOST_MATH_STD_USING

    const bool is_z_nonpositive = z <= 0;

    const T sqrt_z = is_z_nonpositive ? T(sqrt(-z)) : T(sqrt(z));
    const T bessel_mult = is_z_nonpositive ?
      boost::math::cyl_bessel_j(b - 1, 2 * sqrt_z, pol) :
      boost::math::cyl_bessel_i(b - 1, 2 * sqrt_z, pol) ;

    if (b > boost::math::max_factorial<T>::value)
    {
       const T lsqrt_z = log(sqrt_z);
       const T lsqrt_z_pow_b = (b - 1) * lsqrt_z;
       T lg = (boost::math::lgamma(b, pol) - lsqrt_z_pow_b);
       lg = exp(lg);
       return lg * bessel_mult;
    }
    else
    {
       const T sqrt_z_pow_b = pow(sqrt_z, b - 1);
       return (boost::math::tgamma(b, pol) / sqrt_z_pow_b) * bessel_mult;
    }
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

/* hypergeometric_0F1_bessel.hpp
0gHLBQ67BBUuakP2L+puO9ieuP0VM9MFwbUwvoZJjsGAhnffLqWo9NY+GDtBtiDpndsnxvEGdo6hpdg7RhMJFbW0m29kOP6Dq7jHG2Jj3Rz5Ujaq4VpA7asPfCnCXQzFX0EmgVdfSs//INCdY6lDI7jW9CdCAJ5wNNqgMo+FmB5q3Rr0ScQRpXgjEO6qXtIxtN81Fd+SKeDJPPYt/93S5Dl6fex/ncwLPC0gJi/pH6UgDMTxxx6CPvxIk+Mko/U+/TbhdpPa05NEyWxMVFqboI6CoJ+g/c1AV9tHvL28Vy0O5d6XHvQLQgSDw3EkH3Dy8eFhrD7hak/yQEUPqGlHNBC/8bIfqajGi7zQIsy8kia3Cu78gT+g1WVlBEFBAfBK5UpxVhHiKZMIa82VJqigryTbaP1PQMPgkuhNSA+AXS44aKzmclFmX4T2CX807brfj9nWGfUStJsvnr8dVRhGNaYaODTbP52GyoNBNW8U88Pja/uy2kDYryOhMf32oIf5na+e7UQ6gGFUKn7g9wc2X5UwPNNkPFIzbl+q5Zfh95Nbe/nmcKv0Q2n53w==
*/