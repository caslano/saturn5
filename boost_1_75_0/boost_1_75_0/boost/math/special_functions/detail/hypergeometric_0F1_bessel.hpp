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
BchiHMOhss8IlawO+9jx6Jx4DoWcAI3hl+e8RHx2d4FyhIDJkt841PylONTIAgYTsGOGyeWNW9RtT6f8nuaVp0YPzoQvsnSkWDWLjopeGHl1OBDC3XnncHW8UTKwX7Jk2Ngt9gvxKGnSqWTSWRjGRJ+Kpc9aGQrN+pnF2BjHb2MPFYQSv6qxoTg9Y7yepFfbmFxr0ldr1Vop5/wAMYQoZAbas97+2BRzmSBtpXjhLTuYbizhU1xKJgOtodaZ4KjIGrMWrJVt0onMvmPxI7cyJ7cyVV5/R2TU/ihWP0BNwk9mWNdfP0Y6uCsQ+KkBr/fyWwzPOP6bS4nomPxZb1aSed0Ifv0+p35qVNbF7r4kryT+EqkHJG3Q8tz0V3QMrjEYLOsJb8Yooqd6CJToyAjyKysVJXuOQGh3DlleDWKwJUYyfLsgr3fQEmM2y+twEgZsnBUA+oxrSK9N5ExyAT3LqedP3FMmk6YRkyYRq6/dvz9FxEQ4i+Xn9GKLSxLGJiqYFBnBBN1phfICnyhqD2HaIlLFHypjOuRUIxKKX0wAD/aPuwg2usbdsZ2z69yJmMv//BF3T3gWIXAx+Hn10hN26w54WPtGjX/j21DN+BFcQHnR//vWL06wa5qlzdMim8WH6oGYT4ny5z3pughB2j5PO/phea/L3O0hDkwG8Ue7HOoDKiqBpc12PjyFYWDG3cdoEW7ug3Ge+croJ3iy
*/