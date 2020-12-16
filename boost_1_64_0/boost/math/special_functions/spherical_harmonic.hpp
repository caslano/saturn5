
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_SPHERICAL_HARMONIC_HPP
#define BOOST_MATH_SPECIAL_SPHERICAL_HARMONIC_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/tools/workaround.hpp>
#include <complex>

namespace boost{
namespace math{

namespace detail{

//
// Calculates the prefix term that's common to the real
// and imaginary parts.  Does *not* fix up the sign of the result
// though.
//
template <class T, class Policy>
inline T spherical_harmonic_prefix(unsigned n, unsigned m, T theta, const Policy& pol)
{
   BOOST_MATH_STD_USING

   if(m > n)
      return 0;

   T sin_theta = sin(theta);
   T x = cos(theta);

   T leg = detail::legendre_p_imp(n, m, x, static_cast<T>(pow(fabs(sin_theta), T(m))), pol);
   
   T prefix = boost::math::tgamma_delta_ratio(static_cast<T>(n - m + 1), static_cast<T>(2 * m), pol);
   prefix *= (2 * n + 1) / (4 * constants::pi<T>());
   prefix = sqrt(prefix);
   return prefix * leg;
}
//
// Real Part:
//
template <class T, class Policy>
T spherical_harmonic_r(unsigned n, int m, T theta, T phi, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std functions

   bool sign = false;
   if(m < 0)
   {
      // Reflect and adjust sign if m < 0:
      sign = m&1;
      m = abs(m);
   }
   if(m&1)
   {
      // Check phase if theta is outside [0, PI]:
      T mod = boost::math::tools::fmod_workaround(theta, T(2 * constants::pi<T>()));
      if(mod < 0)
         mod += 2 * constants::pi<T>();
      if(mod > constants::pi<T>())
         sign = !sign;
   }
   // Get the value and adjust sign as required:
   T prefix = spherical_harmonic_prefix(n, m, theta, pol);
   prefix *= cos(m * phi);
   return sign ? T(-prefix) : prefix;
}

template <class T, class Policy>
T spherical_harmonic_i(unsigned n, int m, T theta, T phi, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std functions

   bool sign = false;
   if(m < 0)
   {
      // Reflect and adjust sign if m < 0:
      sign = !(m&1);
      m = abs(m);
   }
   if(m&1)
   {
      // Check phase if theta is outside [0, PI]:
      T mod = boost::math::tools::fmod_workaround(theta, T(2 * constants::pi<T>()));
      if(mod < 0)
         mod += 2 * constants::pi<T>();
      if(mod > constants::pi<T>())
         sign = !sign;
   }
   // Get the value and adjust sign as required:
   T prefix = spherical_harmonic_prefix(n, m, theta, pol);
   prefix *= sin(m * phi);
   return sign ? T(-prefix) : prefix;
}

template <class T, class U, class Policy>
std::complex<T> spherical_harmonic(unsigned n, int m, U theta, U phi, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // Sort out the signs:
   //
   bool r_sign = false;
   bool i_sign = false;
   if(m < 0)
   {
      // Reflect and adjust sign if m < 0:
      r_sign = m&1;
      i_sign = !(m&1);
      m = abs(m);
   }
   if(m&1)
   {
      // Check phase if theta is outside [0, PI]:
      U mod = boost::math::tools::fmod_workaround(theta, U(2 * constants::pi<U>()));
      if(mod < 0)
         mod += 2 * constants::pi<U>();
      if(mod > constants::pi<U>())
      {
         r_sign = !r_sign;
         i_sign = !i_sign;
      }
   }
   //
   // Calculate the value:
   //
   U prefix = spherical_harmonic_prefix(n, m, theta, pol);
   U r = prefix * cos(m * phi);
   U i = prefix * sin(m * phi);
   //
   // Add in the signs:
   //
   if(r_sign)
      r = -r;
   if(i_sign)
      i = -i;
   static const char* function = "boost::math::spherical_harmonic<%1%>(int, int, %1%, %1%)";
   return std::complex<T>(policies::checked_narrowing_cast<T, Policy>(r, function), policies::checked_narrowing_cast<T, Policy>(i, function));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline std::complex<typename tools::promote_args<T1, T2>::type> 
   spherical_harmonic(unsigned n, int m, T1 theta, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return detail::spherical_harmonic<result_type, value_type>(n, m, static_cast<value_type>(theta), static_cast<value_type>(phi), pol);
}

template <class T1, class T2>
inline std::complex<typename tools::promote_args<T1, T2>::type> 
   spherical_harmonic(unsigned n, int m, T1 theta, T2 phi)
{
   return boost::math::spherical_harmonic(n, m, theta, phi, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   spherical_harmonic_r(unsigned n, int m, T1 theta, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::spherical_harmonic_r(n, m, static_cast<value_type>(theta), static_cast<value_type>(phi), pol), "bost::math::spherical_harmonic_r<%1%>(unsigned, int, %1%, %1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   spherical_harmonic_r(unsigned n, int m, T1 theta, T2 phi)
{
   return boost::math::spherical_harmonic_r(n, m, theta, phi, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::spherical_harmonic_i(n, m, static_cast<value_type>(theta), static_cast<value_type>(phi), pol), "boost::math::spherical_harmonic_i<%1%>(unsigned, int, %1%, %1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi)
{
   return boost::math::spherical_harmonic_i(n, m, theta, phi, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_SPHERICAL_HARMONIC_HPP




/* spherical_harmonic.hpp
xLirY0s7Z6S75mZu7a/d05ywy/iIeqQdVq+pHWPSP6r9+6j3Qco7jtxbf51XjqqbpvPNe+n//cR7X+N8zLG0RYU8Wyy6n5bGCVh5gDFxLX9Uv9W9qs70cfeZ3l8c7u2wp761C6yLo+KUVl1bfsQhn68Vr3pOk788jzgm8pwiRl59c3UNyVCVJ+naKeWPR8WYsqZuJWa2KNFhSvRc16yvUVKM1lvrPG261rqD+JSrOD59x0iQc9xxXHBcc3zS8USeVcfbjpOun3bclk6lE+syvKQeaZ/SLTzvdBkRCowFVebU/mdviP+e7e9Wzw6qc3tFsDI7OzhNlhp9gn+6x3G2KNFmQvxfnmf27R108uueecfrw7O916X8X6QT+2L4XGNLOiHxZ2UvtRfIsYUgfpk9Jf6kjj943jlyoc/TSOPSirTL7FLf7/xR/UdCwZFtX2cd7z47FGxLT/Z9fyTtEbrk7CD5WzGyTYWV1gF7ETn/tX6w9Bv3OSzWPNGhNn+hTxdfvieJY7aps0/yI/KTpcmM1EfPDtbYpUPwMft3sMYufaI1dbFNnRGLHz87OEGWPYJPiI8NyvSJffLs4Bg7tJiRrqubXdrMWfmUmKkxJvlpc0aRHrHPGE9ydAg1lGGdEj1CnzX2bFFjRPxz2idDgwmpz6ubAnsETXPHGYp0CX3BNdYp0Sf2RTGwQ5MpqS+dHZyiwB5T0i39o0iPyJfND5vUmJD4inKU6JD/8SGfgT/o87Hmh+4L/V5U2iL0ooNBeE89Fx8KjkhzdAh/Td8o0Kb4Jfm+7ho7tJiR+oZ+UGafZNs6o0CHyDfNIznahL5lrsnSJf5tsZKnw+YH/b1SRx6y7BH+jrjJ0WLK8netBWrsE6r6mf17xoYSA+JdbTM+32fcpV1i33eNAj1iP3DOLgMSPzRX7NIn3tM2m9f3O2hphzmpH4mbIn2iP3ZOgQHxnzinRI9EX/8/7vsWaZl9hu8xPu+Vp2C9STvS09Lkm/VVevpN+rPrmXCclw6k4bI1wBp51t5qTKRjluWJvc/Y0XN97nzd8e5bkLbpOp5Ik+83T+yw5lr9AmPpOCftS4MPaIeTZKkzJFIRK6fJMSD8QW1ziiwNRpx4l+dFn2ak9CVHmxknLu8jTaakxBCIt01a7EVCb1Mva5TZJ/l27VCkT7jonCozUu8QGzmKd/UK/pgDQfrZ6nU+Z/md7pOj8BJ1kn6pmH+5EIQ+tRBsOS7TI7Sj7Z/6mwPpGSrEfnfQ987ieJk1wR5zTr5cOYYkX2Ft0iDIemYoMSb5SvGSZ485qVepiybBq80f1UIoyElbzFjKqZM6+yy9Rkw0GBN/rXVKlhbLF5lbIi/WHtO7H/D/Trxf4LjBPvVLQ8Hwtt6LyOjX7Q4E2y/yGvR8sbDH8vOU3bJenmuMnqOPZKgz+KrPP2y6Zmzz9iIpOQ6x+yx9fLo+s0X/a76Hf82BoOF4TOiJB+3lGwqKTzVWBa8pbzrof+KbE6ZnPCdP0g8y1OgTebL7TzBf7BF6otioEV5zzPBVB4LT0ulP/IxwOGT/Cu3TIXfnULD4OOlp5+/weS5p7DHqpMKE/CPVQexRxp+Tj1D/w8zJQ62d48b3QeIizz6xC4wV+6xc7Ov4OQf8jG/d//ZgcFraq/taS8Fxl/gJ8/VA6+A8fSJ2Z+XZpsGYpVXrjRI9QndRN2co0iV0vq9DbFCmT/yuYmOHJhOWDntNupO19ZSDweHby0+J7uVuZ91xhMKtrBfGxM91jQ2KtFm+tXqps080bdxuaSxpEE6J9RbaWT/o/0bJZx7SN5OHAi2WX3bA91rOf+lne07c1LUbiv964id6fe2yTZ0xSzew7l/v8zY=
*/