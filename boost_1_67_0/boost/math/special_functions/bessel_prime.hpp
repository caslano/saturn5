//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_BESSEL_DERIVATIVES_HPP
#define BOOST_MATH_BESSEL_DERIVATIVES_HPP

#ifdef _MSC_VER
#  pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/detail/bessel_jy_derivatives_asym.hpp>
#include <boost/math/special_functions/detail/bessel_jy_derivatives_series.hpp>
#include <boost/math/special_functions/detail/bessel_derivatives_linear.hpp>

namespace boost{ namespace math{

namespace detail{

template <class Tag, class T, class Policy>
inline T cyl_bessel_j_prime_imp(T v, T x, const Policy& pol)
{
   static const char* const function = "boost::math::cyl_bessel_j_prime<%1%>(%1%,%1%)";
   BOOST_MATH_STD_USING
   //
   // Prevent complex result:
   //
   if (x < 0 && floor(v) != v)
      return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function requires x >= 0", x, pol);
   //
   // Special cases for x == 0:
   //
   if (x == 0)
   {
      if (v == 1)
         return 0.5;
      else if (v == -1)
         return -0.5;
      else if (floor(v) == v || v > 1)
         return 0;
      else return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function is indeterminate for this order", x, pol);
   }
   //
   // Special case for large x: use asymptotic expansion:
   //
   if (boost::math::detail::asymptotic_bessel_derivative_large_x_limit(v, x))
      return boost::math::detail::asymptotic_bessel_j_derivative_large_x_2(v, x);
   //
   // Special case for small x: use Taylor series:
   //
   if ((abs(x) < 5) || (abs(v) > x * x / 4))
   {
      bool inversed = false;
      if (floor(v) == v && v < 0)
      {
         v = -v;
         if (itrunc(v, pol) & 1)
            inversed = true;
      }
      T r = boost::math::detail::bessel_j_derivative_small_z_series(v, x, pol);
      return inversed ? T(-r) : r;
   }
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return -boost::math::detail::cyl_bessel_j_imp<T>(1, x, Tag(), pol);
   //
   // Default case:
   //
   return boost::math::detail::bessel_j_derivative_linear(v, x, Tag(), pol);
}

template <class T, class Policy>
inline T sph_bessel_j_prime_imp(unsigned v, T x, const Policy& pol)
{
   static const char* const function = "boost::math::sph_bessel_prime<%1%>(%1%,%1%)";
   //
   // Prevent complex result:
   //
   if (x < 0)
      return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function requires x >= 0.", x, pol);
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return (x == 0) ? boost::math::policies::raise_overflow_error<T>(function, 0, pol)
         : static_cast<T>(-boost::math::detail::sph_bessel_j_imp<T>(1, x, pol));
   //
   // Special case for x == 0 and v > 0:
   //
   if (x == 0)
      return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function is indeterminate for this order", x, pol);
   //
   // Default case:
   //
   return boost::math::detail::sph_bessel_j_derivative_linear(v, x, pol);
}

template <class T, class Policy>
inline T cyl_bessel_i_prime_imp(T v, T x, const Policy& pol)
{
   static const char* const function = "boost::math::cyl_bessel_i_prime<%1%>(%1%,%1%)";
   BOOST_MATH_STD_USING
   //
   // Prevent complex result:
   //
   if (x < 0 && floor(v) != v)
      return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function requires x >= 0", x, pol);
   //
   // Special cases for x == 0:
   //
   if (x == 0)
   {
      if (v == 1 || v == -1)
         return 0.5;
      else if (floor(v) == v || v > 1)
         return 0;
      else return boost::math::policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function is indeterminate for this order", x, pol);
   }
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return boost::math::detail::cyl_bessel_i_imp<T>(1, x, pol);
   //
   // Default case:
   //
   return boost::math::detail::bessel_i_derivative_linear(v, x, pol);
}

template <class Tag, class T, class Policy>
inline T cyl_bessel_k_prime_imp(T v, T x, const Policy& pol)
{
   //
   // Prevent complex and indeterminate results:
   //
   if (x <= 0)
      return boost::math::policies::raise_domain_error<T>(
         "boost::math::cyl_bessel_k_prime<%1%>(%1%,%1%)",
         "Got x = %1%, but function requires x > 0", x, pol);
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return -boost::math::detail::cyl_bessel_k_imp<T>(1, x, Tag(), pol);
   //
   // Default case:
   //
   return boost::math::detail::bessel_k_derivative_linear(v, x, Tag(), pol);
}

template <class Tag, class T, class Policy>
inline T cyl_neumann_prime_imp(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // Prevent complex and indeterminate results:
   //
   if (x <= 0)
      return boost::math::policies::raise_domain_error<T>(
         "boost::math::cyl_neumann_prime<%1%>(%1%,%1%)",
         "Got x = %1%, but function requires x > 0", x, pol);
   //
   // Special case for large x: use asymptotic expansion:
   //
   if (boost::math::detail::asymptotic_bessel_derivative_large_x_limit(v, x))
      return boost::math::detail::asymptotic_bessel_y_derivative_large_x_2(v, x);
   //
   // Special case for small x: use Taylor series:
   //
   if (v > 0 && floor(v) != v)
   {
      const T eps = boost::math::policies::get_epsilon<T, Policy>();
      if (log(eps / 2) > v * log((x * x) / (v * 4)))
         return boost::math::detail::bessel_y_derivative_small_z_series(v, x, pol);
   }
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return -boost::math::detail::cyl_neumann_imp<T>(1, x, Tag(), pol);
   //
   // Default case:
   //
   return boost::math::detail::bessel_y_derivative_linear(v, x, Tag(), pol);
}

template <class T, class Policy>
inline T sph_neumann_prime_imp(unsigned v, T x, const Policy& pol)
{
   //
   // Prevent complex and indeterminate result:
   //
   if (x <= 0)
      return boost::math::policies::raise_domain_error<T>(
         "boost::math::sph_neumann_prime<%1%>(%1%,%1%)",
         "Got x = %1%, but function requires x > 0.", x, pol);
   //
   // Special case for v == 0:
   //
   if (v == 0)
      return -boost::math::detail::sph_neumann_imp<T>(1, x, pol);
   //
   // Default case:
   //
   return boost::math::detail::sph_neumann_derivative_linear(v, x, pol);
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_j_prime(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_j_prime_imp<tag_type, value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy()), "boost::math::cyl_bessel_j_prime<%1%,%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_j_prime(T1 v, T2 x)
{
   return cyl_bessel_j_prime(v, x, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type sph_bessel_prime(unsigned v, T x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T, T, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::sph_bessel_j_prime_imp<value_type>(v, static_cast<value_type>(x), forwarding_policy()), "boost::math::sph_bessel_j_prime<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_bessel_prime(unsigned v, T x)
{
   return sph_bessel_prime(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_i_prime(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_i_prime_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy()), "boost::math::cyl_bessel_i_prime<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_i_prime(T1 v, T2 x)
{
   return cyl_bessel_i_prime(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_k_prime(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_k_prime_imp<tag_type, value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy()), "boost::math::cyl_bessel_k_prime<%1%,%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_k_prime(T1 v, T2 x)
{
   return cyl_bessel_k_prime(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_neumann_prime(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_neumann_prime_imp<tag_type, value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy()), "boost::math::cyl_neumann_prime<%1%,%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_neumann_prime(T1 v, T2 x)
{
   return cyl_neumann_prime(v, x, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type sph_neumann_prime(unsigned v, T x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T, T, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::sph_neumann_prime_imp<value_type>(v, static_cast<value_type>(x), forwarding_policy()), "boost::math::sph_neumann_prime<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_neumann_prime(unsigned v, T x)
{
   return sph_neumann_prime(v, x, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_BESSEL_DERIVATIVES_HPP

/* bessel_prime.hpp
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
*/