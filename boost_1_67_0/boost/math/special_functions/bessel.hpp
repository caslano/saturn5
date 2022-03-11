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
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
*/