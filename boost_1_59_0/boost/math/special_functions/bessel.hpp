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
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

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
   if((policies::digits<T, Policy>() <= 113) && (std::numeric_limits<T>::digits <= 113) && (std::numeric_limits<T>::radix == 2))
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
   std::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

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
   std::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

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

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_bessel_j_zero_imp<value_type>(v, m, forwarding_policy()), "boost::math::cyl_bessel_j_zero<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_bessel_j_zero(T v, int m)
{
   static_assert(    false == std::numeric_limits<T>::is_specialized
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
   static_assert(    false == std::numeric_limits<T>::is_specialized
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

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Order must be a floating-point type.");

   return policies::checked_narrowing_cast<result_type, Policy>(detail::cyl_neumann_zero_imp<value_type>(v, m, forwarding_policy()), "boost::math::cyl_neumann_zero<%1%>(%1%,%1%)");
}

template <class T>
inline typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_neumann_zero(T v, int m)
{
   static_assert(    false == std::numeric_limits<T>::is_specialized
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
   static_assert(    false == std::numeric_limits<T>::is_specialized
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