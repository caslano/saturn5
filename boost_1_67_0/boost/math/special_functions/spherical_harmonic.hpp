
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
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
*/