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
HfzOeJq/KbmgzzP26pCMa8gzcaBJMgs5f3EcGz53g/oh72lq4XOi+MB+meoH/mF6Ji5owfNK2q89rp3nsfPVH3xvCw79+21v/Jx+dfz8svDgZ6vU4getJA94B+sZvmyHqc/Y3us9/x5ULvEn5nXG99A49DNA9HnP94U4G6X+2InvGc81NQ6+Fsse2HFtAl87R/rDfzqXT2UyPl9w/Pc6+8ejok+8WA/DsA9ydxUd7Io/IfdAx8cUwdFXf/XDnuM0HyDfu7bjx6JHv9vVH/9Fb/h9Uz3z/hzJg/xF9tvVgvO8TnTQ/1WJ3L8s1DN+ulHP8HFq0m/B2KRtkyG7EldniB5xR1wTn931nngeKTo8Oz77/pIp+SUn3yfotU/0t2eG/Z44od+n6g++G0QXfc6QnOjpgwR+XwfRwy+naRz9bvS8g9zE58NJOw6/hX9a4vtDtfhHP/WnzRKfxAHzOnYqFj30P0zv0cPbeoYe91Sx10Dj3aIWexxYKVUeOZrZn7uJT+K4ift38LrqMLXgedD+3F7v0e/Hoo9fTLc81W2fU+xnf1N/5JrnONlTIVURf9wjPfF+gPpj/+vM/2Trjd8VB185f9fuztI4+QHxBJz4xu7viQ52fUP44LO13oP3VcfF53rG3u2sp6MSfIfem8Dbr/T3lPkfvH08T3fITmUhxweeb4k79NFQ8zN+8Ybj5U3hQX7ueqKfuhV1Bwj5NQ7/+pNa5D5W75FzQIJnNnpmXOuE7mkbhA+/yVU//I11A23tSuJD/ccKjv35/sJHe8cl+NAP6zLwV7Q+mtg/rPeGh6offjFR/ECvVjK+U6bg2OPv6ocertYzeqmoFn12yUztRe+1rMeHNB7/2Cx903+a4MjLdwh6/j7Oe42Wec12Hav++MGOzNSRzF9L1R95L8pN1cQfm6s/cp5rfBdmpqZkSJ/4Jf5wlte54/Qeul/7+8H3hvhtaL9mvkZPRwhO3DWyHz2qFr3w/aef1s3Y8Ye/ii7yZZnPGnom/jxPNj/a+rpH4/Gr1wVHb2PMF3EBH49If+i3g+n/4Dj1PD+adQF+xLyL/RqoRb+O34X17NczEz4Gb9V44uwG4UUvd3n9Umq91tQ4xhtvK+ZZ6FyiFv4mqEWOd9Vizz1qGVfF82Btx/HNgmPX6yUPevf3fcINarHXPZ4nb9czfA9SP/R/XmaqNvPLRscJ/oE/s+5Azody9V56Zd2Nv9xo/7nL88mh9s8jhRd5j1ALvne9z7AeNv8q/ojXXcJLv/R8fbjG07+S+CFe+X6Bb7Pg+Nc9gmO399Vib+Zn4rON1wNb1dL/D57H8F/0xnyO3oCD9zLrE/mQm3UJ8VaslngbLjj6pz/62p30b/at/XF74mctWQejj22CQ/dp74c+Sey6fJX1dIzkg+/+Sf85Q23HxY63DK8zGyb9RrKeQx97K6Qqoy/sAz93iT+eU+6PHuD7M/UHzvxOfDDfQWeA7TtK8qC/++x3WgexXj/e8/wLy4yHfS12/FEt75Ebfd2b0Gv4mfBgr6f1jPzZyfP0yp6fj1CL3As1Hn39IPzop5f9uofwoaeHkrYv8zr8MO8Td3Ns/z96fp4jPMQd73keIzj8tvM8Md52OsL78iLPu99ZD3zv8bNnc1PloHOc1/cHCw4f9EffxC/+XqFcYpdctcjPdwC5e4gP+lcXHez5o8bjd7vUEleTvW5ln4keG3q+ZT1DfNyRrIOmTtIz9J6gH/OX56OJgqPPa6yf57wuWKv3+CP7I/TJvh4+L0rgP2xUf/TwsVr0t0zv8YOGesb/79czeG4TfehuFxz+JmalzgHfasd9OeuTfQb2cnwuaSE48d9KeMBPvgL9POM=
*/