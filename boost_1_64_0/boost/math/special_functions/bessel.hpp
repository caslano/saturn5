//  Copyright (c) 2007, 2013 John Maddock
//  Copyright Christopher Kormanyos 2013.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// This header just defines the function entry points, and adds dispatch
// to the right implementation method.  Most of the implementation details
// are in separate headers and copyright Xiaogang Zhang.
//
#ifndef BOOST_MATH_BESSEL_HPP
#define BOOST_MATH_BESSEL_HPP

#ifdef _MSC_VER
#  pragma once
#endif

#include <limits>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/detail/bessel_jy.hpp>
#include <boost/math/special_functions/detail/bessel_jn.hpp>
#include <boost/math/special_functions/detail/bessel_yn.hpp>
#include <boost/math/special_functions/detail/bessel_jy_zero.hpp>
#include <boost/math/special_functions/detail/bessel_ik.hpp>
#include <boost/math/special_functions/detail/bessel_i0.hpp>
#include <boost/math/special_functions/detail/bessel_i1.hpp>
#include <boost/math/special_functions/detail/bessel_kn.hpp>
#include <boost/math/special_functions/detail/iconv.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/special_functions/sinc.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/roots.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
struct sph_bessel_j_small_z_series_term
{
   typedef T result_type;

   sph_bessel_j_small_z_series_term(unsigned v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      if(v + 3 > max_factorial<T>::value)
      {
         term = v * log(mult) - boost::math::lgamma(v+1+T(0.5f), Policy());
         term = exp(term);
      }
      else
         term = pow(mult, T(v)) / boost::math::tgamma(v+1+T(0.5f), Policy());
      mult *= -mult;
   }
   T operator()()
   {
      T r = term;
      ++N;
      term *= mult / (N * T(N + v + 0.5f));
      return r;
   }
private:
   unsigned N;
   unsigned v;
   T mult;
   T term;
};

template <class T, class Policy>
inline T sph_bessel_j_small_z_series(unsigned v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   sph_bessel_j_small_z_series_term<T, Policy> s(v, x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   policies::check_series_iterations<T>("boost::math::sph_bessel_j_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   return result * sqrt(constants::pi<T>() / 4);
}

template <class T, class Policy>
T cyl_bessel_j_imp(T v, T x, const bessel_no_int_tag& t, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::bessel_j<%1%>(%1%,%1%)";
   if(x < 0)
   {
      // better have integer v:
      if(floor(v) == v)
      {
         T r = cyl_bessel_j_imp(v, T(-x), t, pol);
         if(iround(v, pol) & 1)
            r = -r;
         return r;
      }
      else
         return policies::raise_domain_error<T>(
            function,
            "Got x = %1%, but we need x >= 0", x, pol);
   }
   
   T j, y;
   bessel_jy(v, x, &j, &y, need_j, pol);
   return j;
}

template <class T, class Policy>
inline T cyl_bessel_j_imp(T v, T x, const bessel_maybe_int_tag&, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std names.
   int ival = detail::iconv(v, pol);
   // If v is an integer, use the integer recursion
   // method, both that and Steeds method are O(v):
   if((0 == v - ival))
   {
      return bessel_jn(ival, x, pol);
   }
   return cyl_bessel_j_imp(v, x, bessel_no_int_tag(), pol);
}

template <class T, class Policy>
inline T cyl_bessel_j_imp(int v, T x, const bessel_int_tag&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   return bessel_jn(v, x, pol);
}

template <class T, class Policy>
inline T sph_bessel_j_imp(unsigned n, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   if(x < 0)
      return policies::raise_domain_error<T>(
         "boost::math::sph_bessel_j<%1%>(%1%,%1%)",
         "Got x = %1%, but function requires x > 0.", x, pol);
   //
   // Special case, n == 0 resolves down to the sinus cardinal of x:
   //
   if(n == 0)
      return boost::math::sinc_pi(x, pol);
   //
   // Special case for x == 0:
   //
   if(x == 0)
      return 0;
   //
   // When x is small we may end up with 0/0, use series evaluation
   // instead, especially as it converges rapidly:
   //
   if(x < 1)
      return sph_bessel_j_small_z_series(n, x, pol);
   //
   // Default case is just a naive evaluation of the definition:
   //
   return sqrt(constants::pi<T>() / (2 * x)) 
      * cyl_bessel_j_imp(T(T(n)+T(0.5f)), x, bessel_no_int_tag(), pol);
}

template <class T, class Policy>
T cyl_bessel_i_imp(T v, T x, const Policy& pol)
{
   //
   // This handles all the bessel I functions, note that we don't optimise
   // for integer v, other than the v = 0 or 1 special cases, as Millers
   // algorithm is at least as inefficient as the general case (the general
   // case has better error handling too).
   //
   BOOST_MATH_STD_USING
   if(x < 0)
   {
      // better have integer v:
      if(floor(v) == v)
      {
         T r = cyl_bessel_i_imp(v, T(-x), pol);
         if(iround(v, pol) & 1)
            r = -r;
         return r;
      }
      else
         return policies::raise_domain_error<T>(
         "boost::math::cyl_bessel_i<%1%>(%1%,%1%)",
            "Got x = %1%, but we need x >= 0", x, pol);
   }
   if(x == 0)
   {
      return (v == 0) ? static_cast<T>(1) : static_cast<T>(0);
   }
   if(v == 0.5f)
   {
      // common special case, note try and avoid overflow in exp(x):
      if(x >= tools::log_max_value<T>())
      {
         T e = exp(x / 2);
         return e * (e / sqrt(2 * x * constants::pi<T>()));
      }
      return sqrt(2 / (x * constants::pi<T>())) * sinh(x);
   }
   if(policies::digits<T, Policy>() <= 113)
   {
      if(v == 0)
      {
         return bessel_i0(x);
      }
      if(v == 1)
      {
         return bessel_i1(x);
      }
   }
   if((v > 0) && (x / v < 0.25))
      return bessel_i_small_z_series(v, x, pol);
   T I, K;
   bessel_ik(v, x, &I, &K, need_i, pol);
   return I;
}

template <class T, class Policy>
inline T cyl_bessel_k_imp(T v, T x, const bessel_no_int_tag& /* t */, const Policy& pol)
{
   static const char* function = "boost::math::cyl_bessel_k<%1%>(%1%,%1%)";
   BOOST_MATH_STD_USING
   if(x < 0)
   {
      return policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but we need x > 0", x, pol);
   }
   if(x == 0)
   {
      return (v == 0) ? policies::raise_overflow_error<T>(function, 0, pol)
         : policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but we need x > 0", x, pol);
   }
   T I, K;
   bessel_ik(v, x, &I, &K, need_k, pol);
   return K;
}

template <class T, class Policy>
inline T cyl_bessel_k_imp(T v, T x, const bessel_maybe_int_tag&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   if((floor(v) == v))
   {
      return bessel_kn(itrunc(v), x, pol);
   }
   return cyl_bessel_k_imp(v, x, bessel_no_int_tag(), pol);
}

template <class T, class Policy>
inline T cyl_bessel_k_imp(int v, T x, const bessel_int_tag&, const Policy& pol)
{
   return bessel_kn(v, x, pol);
}

template <class T, class Policy>
inline T cyl_neumann_imp(T v, T x, const bessel_no_int_tag&, const Policy& pol)
{
   static const char* function = "boost::math::cyl_neumann<%1%>(%1%,%1%)";

   BOOST_MATH_INSTRUMENT_VARIABLE(v);
   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   if(x <= 0)
   {
      return (v == 0) && (x == 0) ?
         policies::raise_overflow_error<T>(function, 0, pol)
         : policies::raise_domain_error<T>(
               function,
               "Got x = %1%, but result is complex for x <= 0", x, pol);
   }
   T j, y;
   bessel_jy(v, x, &j, &y, need_y, pol);
   // 
   // Post evaluation check for internal overflow during evaluation,
   // can occur when x is small and v is large, in which case the result
   // is -INF:
   //
   if(!(boost::math::isfinite)(y))
      return -policies::raise_overflow_error<T>(function, 0, pol);
   return y;
}

template <class T, class Policy>
inline T cyl_neumann_imp(T v, T x, const bessel_maybe_int_tag&, const Policy& pol)
{
   BOOST_MATH_STD_USING

   BOOST_MATH_INSTRUMENT_VARIABLE(v);
   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   if(floor(v) == v)
   {
      T r = bessel_yn(itrunc(v, pol), x, pol);
      BOOST_MATH_INSTRUMENT_VARIABLE(r);
      return r;
   }
   T r = cyl_neumann_imp<T>(v, x, bessel_no_int_tag(), pol);
   BOOST_MATH_INSTRUMENT_VARIABLE(r);
   return r;
}

template <class T, class Policy>
inline T cyl_neumann_imp(int v, T x, const bessel_int_tag&, const Policy& pol)
{
   return bessel_yn(v, x, pol);
}

template <class T, class Policy>
inline T sph_neumann_imp(unsigned v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names
   static const char* function = "boost::math::sph_neumann<%1%>(%1%,%1%)";
   //
   // Nothing much to do here but check for errors, and
   // evaluate the function's definition directly:
   //
   if(x < 0)
      return policies::raise_domain_error<T>(
         function,
         "Got x = %1%, but function requires x > 0.", x, pol);

   if(x < 2 * tools::min_value<T>())
      return -policies::raise_overflow_error<T>(function, 0, pol);

   T result = cyl_neumann_imp(T(T(v)+0.5f), x, bessel_no_int_tag(), pol);
   T tx = sqrt(constants::pi<T>() / (2 * x));

   if((tx > 1) && (tools::max_value<T>() / tx < result))
      return -policies::raise_overflow_error<T>(function, 0, pol);

   return result * tx;
}

template <class T, class Policy>
inline T cyl_bessel_j_zero_imp(T v, int m, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names, needed for floor.

   static const char* function = "boost::math::cyl_bessel_j_zero<%1%>(%1%, int)";

   const T half_epsilon(boost::math::tools::epsilon<T>() / 2U);

   // Handle non-finite order.
   if (!(boost::math::isfinite)(v) )
   {
     return policies::raise_domain_error<T>(function, "Order argument is %1%, but must be finite >= 0 !", v, pol);
   }

   // Handle negative rank.
   if(m < 0)
   {
      // Zeros of Jv(x) with negative rank are not defined and requesting one raises a domain error.
      return policies::raise_domain_error<T>(function, "Requested the %1%'th zero, but the rank must be positive !", static_cast<T>(m), pol);
   }

   // Get the absolute value of the order.
   const bool order_is_negative = (v < 0);
   const T vv((!order_is_negative) ? v : T(-v));

   // Check if the order is very close to zero or very close to an integer.
   const bool order_is_zero    = (vv < half_epsilon);
   const bool order_is_integer = ((vv - floor(vv)) < half_epsilon);

   if(m == 0)
   {
      if(order_is_zero)
      {
         // The zero'th zero of J0(x) is not defined and requesting it raises a domain error.
         return policies::raise_domain_error<T>(function, "Requested the %1%'th zero of J0, but the rank must be > 0 !", static_cast<T>(m), pol);
      }

      // The zero'th zero of Jv(x) for v < 0 is not defined
      // unless the order is a negative integer.
      if(order_is_negative && (!order_is_integer))
      {
         // For non-integer, negative order, requesting the zero'th zero raises a domain error.
         return policies::raise_domain_error<T>(function, "Requested the %1%'th zero of Jv for negative, non-integer order, but the rank must be > 0 !", static_cast<T>(m), pol);
      }

      // The zero'th zero does exist and its value is zero.
      return T(0);
   }

   // Set up the initial guess for the upcoming root-finding.
   // If the order is a negative integer, then use the corresponding
   // positive integer for the order.
   const T guess_root = boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::initial_guess<T, Policy>((order_is_integer ? vv : v), m, pol);

   // Select the maximum allowed iterations from the policy.
   boost::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

   const T delta_lo = ((guess_root > 0.2F) ? T(0.2) : T(guess_root / 2U));

   // Perform the root-finding using Newton-Raphson iteration from Boost.Math.
   const T jvm =
      boost::math::tools::newton_raphson_iterate(
         boost::math::detail::bessel_zero::cyl_bessel_j_zero_detail::function_object_jv_and_jv_prime<T, Policy>((order_is_integer ? vv : v), order_is_zero, pol),
         guess_root,
         T(guess_root - delta_lo),
         T(guess_root + 0.2F),
         policies::digits<T, Policy>(),
         number_of_iterations);

   if(number_of_iterations >= policies::get_max_root_iterations<Policy>())
   {
      return policies::raise_evaluation_error<T>(function, "Unable to locate root in a reasonable time:"
         "  Current best guess is %1%", jvm, Policy());
   }

   return jvm;
}

template <class T, class Policy>
inline T cyl_neumann_zero_imp(T v, int m, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names, needed for floor.

   static const char* function = "boost::math::cyl_neumann_zero<%1%>(%1%, int)";

   // Handle non-finite order.
   if (!(boost::math::isfinite)(v) )
   {
     return policies::raise_domain_error<T>(function, "Order argument is %1%, but must be finite >= 0 !", v, pol);
   }

   // Handle negative rank.
   if(m < 0)
   {
      return policies::raise_domain_error<T>(function, "Requested the %1%'th zero, but the rank must be positive !", static_cast<T>(m), pol);
   }

   const T half_epsilon(boost::math::tools::epsilon<T>() / 2U);

   // Get the absolute value of the order.
   const bool order_is_negative = (v < 0);
   const T vv((!order_is_negative) ? v : T(-v));

   const bool order_is_integer = ((vv - floor(vv)) < half_epsilon);

   // For negative integers, use reflection to positive integer order.
   if(order_is_negative && order_is_integer)
      return boost::math::detail::cyl_neumann_zero_imp(vv, m, pol);

   // Check if the order is very close to a negative half-integer.
   const T delta_half_integer(vv - (floor(vv) + 0.5F));

   const bool order_is_negative_half_integer =
      (order_is_negative && ((delta_half_integer > -half_epsilon) && (delta_half_integer < +half_epsilon)));

   // The zero'th zero of Yv(x) for v < 0 is not defined
   // unless the order is a negative integer.
   if((m == 0) && (!order_is_negative_half_integer))
   {
      // For non-integer, negative order, requesting the zero'th zero raises a domain error.
      return policies::raise_domain_error<T>(function, "Requested the %1%'th zero of Yv for negative, non-half-integer order, but the rank must be > 0 !", static_cast<T>(m), pol);
   }

   // For negative half-integers, use the corresponding
   // spherical Bessel function of positive half-integer order.
   if(order_is_negative_half_integer)
      return boost::math::detail::cyl_bessel_j_zero_imp(vv, m, pol);

   // Set up the initial guess for the upcoming root-finding.
   // If the order is a negative integer, then use the corresponding
   // positive integer for the order.
   const T guess_root = boost::math::detail::bessel_zero::cyl_neumann_zero_detail::initial_guess<T, Policy>(v, m, pol);

   // Select the maximum allowed iterations from the policy.
   boost::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

   const T delta_lo = ((guess_root > 0.2F) ? T(0.2) : T(guess_root / 2U));

   // Perform the root-finding using Newton-Raphson iteration from Boost.Math.
   const T yvm =
      boost::math::tools::newton_raphson_iterate(
         boost::math::detail::bessel_zero::cyl_neumann_zero_detail::function_object_yv_and_yv_prime<T, Policy>(v, pol),
         guess_root,
         T(guess_root - delta_lo),
         T(guess_root + 0.2F),
         policies::digits<T, Policy>(),
         number_of_iterations);

   if(number_of_iterations >= policies::get_max_root_iterations<Policy>())
   {
      return policies::raise_evaluation_error<T>(function, "Unable to locate root in a reasonable time:"
         "  Current best guess is %1%", yvm, Policy());
   }

   return yvm;
}

} // namespace detail

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_j(T1 v, T2 x, const Policy& /* pol */)
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_j_imp<value_type>(v, static_cast<value_type>(x), tag_type(), forwarding_policy()), "boost::math::cyl_bessel_j<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_j(T1 v, T2 x)
{
   return cyl_bessel_j(v, x, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type sph_bessel(unsigned v, T x, const Policy& /* pol */)
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::sph_bessel_j_imp<value_type>(v, static_cast<value_type>(x), forwarding_policy()), "boost::math::sph_bessel<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_bessel(unsigned v, T x)
{
   return sph_bessel(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_i(T1 v, T2 x, const Policy& /* pol */)
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_i_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy()), "boost::math::cyl_bessel_i<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_i(T1 v, T2 x)
{
   return cyl_bessel_i(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_k(T1 v, T2 x, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag128 tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_k_imp<value_type>(v, static_cast<value_type>(x), tag_type(), forwarding_policy()), "boost::math::cyl_bessel_k<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_k(T1 v, T2 x)
{
   return cyl_bessel_k(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_neumann(T1 v, T2 x, const Policy& /* pol */)
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_neumann_imp<value_type>(v, static_cast<value_type>(x), tag_type(), forwarding_policy()), "boost::math::cyl_neumann<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_neumann(T1 v, T2 x)
{
   return cyl_neumann(v, x, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type sph_neumann(unsigned v, T x, const Policy& /* pol */)
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::sph_neumann_imp<value_type>(v, static_cast<value_type>(x), forwarding_policy()), "boost::math::sph_neumann<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_neumann(unsigned v, T x)
{
   return sph_neumann(v, x, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type cyl_bessel_j_zero(T v, int m, const Policy& /* pol */)
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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_j_zero_imp<value_type>(v, m, forwarding_policy()), "boost::math::cyl_bessel_j_zero<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_bessel_j_zero(T v, int m)
{
   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return cyl_bessel_j_zero<T, policies::policy<> >(v, m, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator cyl_bessel_j_zero(T v,
                              int start_index,
                              unsigned number_of_zeros,
                              OutputIterator out_it,
                              const Policy& pol)
{
   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   for(int i = 0; i < static_cast<int>(number_of_zeros); ++i)
   {
      *out_it = boost::math::cyl_bessel_j_zero(v, start_index + i, pol);
      ++out_it;
   }
   return out_it;
}

template <class T, class OutputIterator>
inline OutputIterator cyl_bessel_j_zero(T v,
                              int start_index,
                              unsigned number_of_zeros,
                              OutputIterator out_it)
{
   return cyl_bessel_j_zero(v, start_index, number_of_zeros, out_it, policies::policy<>());
}

template <class T, class Policy>
inline typename detail::bessel_traits<T, T, Policy>::result_type cyl_neumann_zero(T v, int m, const Policy& /* pol */)
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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_neumann_zero_imp<value_type>(v, m, forwarding_policy()), "boost::math::cyl_neumann_zero<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_neumann_zero(T v, int m)
{
   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return cyl_neumann_zero<T, policies::policy<> >(v, m, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator cyl_neumann_zero(T v,
                             int start_index,
                             unsigned number_of_zeros,
                             OutputIterator out_it,
                             const Policy& pol)
{
   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   for(int i = 0; i < static_cast<int>(number_of_zeros); ++i)
   {
      *out_it = boost::math::cyl_neumann_zero(v, start_index + i, pol);
      ++out_it;
   }
   return out_it;
}

template <class T, class OutputIterator>
inline OutputIterator cyl_neumann_zero(T v,
                             int start_index,
                             unsigned number_of_zeros,
                             OutputIterator out_it)
{
   return cyl_neumann_zero(v, start_index, number_of_zeros, out_it, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_BESSEL_HPP



/* bessel.hpp
O4T9BVi9UN7zke2dUN72gi0uCeXoLNjY80LYxfAcrUt6ovtFYSxcLlhhcQjrJ9iOOmHsD0K2d7MC2FD6RXnMkch7V5T/Q7aoLvxGwfLOCGW7DVhOKMcE+NsU0p0ML8eF/e7GN6Kcwgz0siW05Wz4GxjK9hA03g55eUywnttDGvOx+bpQp8/C896w34v4UHR/axG6j/IHr4Pv2xC2nLH1Q/29hS0fj/79P3TQJqT7Lj4e5ds3Y6NLwrFb8asnQ9in+NW2kJev4PmSKP8H3aNDuj+iv+juzW70EtWUpzpRPxnl/wQriubnAwSrGunvQMFmnRjiqylY3p9C+9YRrDj6HYTDBBsb3XM4EtiGEN/RgpVWDvEd3wm/TwWwkwTb0bNiAGsq2PxFIb7T4e/SUKfNkTfKSZ8DjcZR/g85orulhYItju7mdoLGpNBGF6HnaG7qQb+jwji6TLDC6Dc3+qLn6DcyrhIs/8kQdjX6i+rhRqCXD0Ldj4aXt6L8H/YdHt3/FSzVI/TJO5A32qdMQn8do/u/yBZ9Z+5lbFQ7Mws9R3mLOei5T5T/Q44rQj94Eh18EdJ9RrCSiO4L0Ij6vQKNplH9H/q7IqT7Jv2ahTpYjV6i2sG3kTeqg9+I7/4S+ukHwKK140fI1j+0xyf0i9ZcXyJv9NuPO/DxYSHdH4BF6/Zd+FCE7zf0ckyU/+ssG0V1SxUEK4x+A6UKsFuj3/8QrOjk0MdrCzYryq0fSr8vwn5HCDY/qo/4o2AFUU3lceCL8ruN4GVzGPtNBEtF9S9/FmzHn0NdFSBvdG+2pWD5Y0PYedDoEuX/gOVG9X+ClfwcxnRX5IjOay+Bv4fDsb3RQVT/3Eew4t+i+j/4+zWUd4hgeZH+rkHecaH+/grdajkB7Hp0EO0hboFutyj/B39RXXOxYGPbRfk/9BLte+4RrGf0zZuJH0Ry/B1YlBeYC76oZvYJ5Ijqlp6mX7TG/Af8RTnahdijRkjjVcFKt4Y6eAO9zAlhq+AvqgNYi09GdVUbkHd0SON9dHpqiK9UsKoRz9uBRevJL4AVhWO/wb6fh772PXJEvvaLYLOjf+9mLz4U/e5w1oXSS3THM1ewWdG96MqCLR4c+lB1weZnhvY4WLCSTtH9X/BFdYL1BcvbWC2A/UGw1O2hDo4VLH9plP+DRnTW1pixfaL8n2CFB4Z6PpN+0e+wnS1YaXTu3Eqw4uiuUVvo1gvpXgB/m0I/6ALdF0OeuwtWNYqPS9FftGa9kn6PRfd/4S/aSw7GblHuerhgReWi3/+FRlSDMVawVdeFvnEz9m0fjr0du9UKaUyEl59DP7gLvUT3tqcLtiO6p34/skV39R9EV38Ixz5Cv6Oi3/9F3tKQl6fgJdpvPQ/Pl4W6ehmbbw15WYJeorrwZejg+5CXlfSL/LkE33gmuv+L7qP1xiZki9YHH9Kvb+hX2wQbG+UPPkfetqFs/8TXPgt5+Q4am0IaP6O/6I7dHsZGZ7OZXSTHoKj+T7BUTkijkmA7ikL+qgk26+SQbi3B8qOcdF1o5IR6zgMW6f4owcZG5ynH0O/XMGZOFKwgqoc7RbCSv4Q8nybY4uNCec+gX2ZI4yzoRv5yLjQGRL//i7w7QhodkPf9UAcXQjca202wql+GMdMLutG38QrBivaE8vaH50tCvy+in89EDkk1qZaRqiQCqdRRVWuk8vQJOmHo5SOGkgZKNa2WhulRvfe9aTDwqtS+cZmMy6+RqrWwfKqAK3BDLus1tFcyLjtDAP6nv8zUCWd16Nigy1nNw3e0/353UfguN/P3d62icZWy9nsXjaua/fu7wmhczZz93kXjapf7/V3HaFy98vu987iia3M=
*/