// Copyright John Maddock 2012.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_AIRY_HPP
#define BOOST_MATH_AIRY_HPP

#include <limits>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/detail/airy_ai_bi_zero.hpp>
#include <boost/math/tools/roots.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
T airy_ai_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING

   if(x < 0)
   {
      T p = (-x * sqrt(-x) * 2) / 3;
      T v = T(1) / 3;
      T j1 = boost::math::cyl_bessel_j(v, p, pol);
      T j2 = boost::math::cyl_bessel_j(-v, p, pol);
      T ai = sqrt(-x) * (j1 + j2) / 3;
      //T bi = sqrt(-x / 3) * (j2 - j1);
      return ai;
   }
   else if(fabs(x * x * x) / 6 < tools::epsilon<T>())
   {
      T tg = boost::math::tgamma(constants::twothirds<T>(), pol);
      T ai = 1 / (pow(T(3), constants::twothirds<T>()) * tg);
      //T bi = 1 / (sqrt(boost::math::cbrt(T(3))) * tg);
      return ai;
   }
   else
   {
      T p = 2 * x * sqrt(x) / 3;
      T v = T(1) / 3;
      //T j1 = boost::math::cyl_bessel_i(-v, p, pol);
      //T j2 = boost::math::cyl_bessel_i(v, p, pol);
      //
      // Note that although we can calculate ai from j1 and j2, the accuracy is horrible
      // as we're subtracting two very large values, so use the Bessel K relation instead:
      //
      T ai = cyl_bessel_k(v, p, pol) * sqrt(x / 3) / boost::math::constants::pi<T>();  //sqrt(x) * (j1 - j2) / 3;
      //T bi = sqrt(x / 3) * (j1 + j2);
      return ai;
   }
}

template <class T, class Policy>
T airy_bi_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING

   if(x < 0)
   {
      T p = (-x * sqrt(-x) * 2) / 3;
      T v = T(1) / 3;
      T j1 = boost::math::cyl_bessel_j(v, p, pol);
      T j2 = boost::math::cyl_bessel_j(-v, p, pol);
      //T ai = sqrt(-x) * (j1 + j2) / 3;
      T bi = sqrt(-x / 3) * (j2 - j1);
      return bi;
   }
   else if(fabs(x * x * x) / 6 < tools::epsilon<T>())
   {
      T tg = boost::math::tgamma(constants::twothirds<T>(), pol);
      //T ai = 1 / (pow(T(3), constants::twothirds<T>()) * tg);
      T bi = 1 / (sqrt(boost::math::cbrt(T(3), pol)) * tg);
      return bi;
   }
   else
   {
      T p = 2 * x * sqrt(x) / 3;
      T v = T(1) / 3;
      T j1 = boost::math::cyl_bessel_i(-v, p, pol);
      T j2 = boost::math::cyl_bessel_i(v, p, pol);
      T bi = sqrt(x / 3) * (j1 + j2);
      return bi;
   }
}

template <class T, class Policy>
T airy_ai_prime_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING

   if(x < 0)
   {
      T p = (-x * sqrt(-x) * 2) / 3;
      T v = T(2) / 3;
      T j1 = boost::math::cyl_bessel_j(v, p, pol);
      T j2 = boost::math::cyl_bessel_j(-v, p, pol);
      T aip = -x * (j1 - j2) / 3;
      return aip;
   }
   else if(fabs(x * x) / 2 < tools::epsilon<T>())
   {
      T tg = boost::math::tgamma(constants::third<T>(), pol);
      T aip = 1 / (boost::math::cbrt(T(3), pol) * tg);
      return -aip;
   }
   else
   {
      T p = 2 * x * sqrt(x) / 3;
      T v = T(2) / 3;
      //T j1 = boost::math::cyl_bessel_i(-v, p, pol);
      //T j2 = boost::math::cyl_bessel_i(v, p, pol);
      //
      // Note that although we can calculate ai from j1 and j2, the accuracy is horrible
      // as we're subtracting two very large values, so use the Bessel K relation instead:
      //
      T aip = -cyl_bessel_k(v, p, pol) * x / (boost::math::constants::root_three<T>() * boost::math::constants::pi<T>());
      return aip;
   }
}

template <class T, class Policy>
T airy_bi_prime_imp(T x, const Policy& pol)
{
   BOOST_MATH_STD_USING

   if(x < 0)
   {
      T p = (-x * sqrt(-x) * 2) / 3;
      T v = T(2) / 3;
      T j1 = boost::math::cyl_bessel_j(v, p, pol);
      T j2 = boost::math::cyl_bessel_j(-v, p, pol);
      T aip = -x * (j1 + j2) / constants::root_three<T>();
      return aip;
   }
   else if(fabs(x * x) / 2 < tools::epsilon<T>())
   {
      T tg = boost::math::tgamma(constants::third<T>(), pol);
      T bip = sqrt(boost::math::cbrt(T(3), pol)) / tg;
      return bip;
   }
   else
   {
      T p = 2 * x * sqrt(x) / 3;
      T v = T(2) / 3;
      T j1 = boost::math::cyl_bessel_i(-v, p, pol);
      T j2 = boost::math::cyl_bessel_i(v, p, pol);
      T aip = x * (j1 + j2) / boost::math::constants::root_three<T>();
      return aip;
   }
}

template <class T, class Policy>
T airy_ai_zero_imp(int m, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names, needed for log, sqrt.

   // Handle cases when a negative zero (negative rank) is requested.
   if(m < 0)
   {
      return policies::raise_domain_error<T>("boost::math::airy_ai_zero<%1%>(%1%, int)",
         "Requested the %1%'th zero, but the rank must be 1 or more !", static_cast<T>(m), pol);
   }

   // Handle case when the zero'th zero is requested.
   if(m == 0U)
   {
      return policies::raise_domain_error<T>("boost::math::airy_ai_zero<%1%>(%1%,%1%)",
        "The requested rank of the zero is %1%, but must be 1 or more !", static_cast<T>(m), pol);
   }

   // Set up the initial guess for the upcoming root-finding.
   const T guess_root = boost::math::detail::airy_zero::airy_ai_zero_detail::initial_guess<T>(m, pol);

   // Select the maximum allowed iterations based on the number
   // of decimal digits in the numeric type T, being at least 12.
   const int my_digits10 = static_cast<int>(static_cast<float>(policies::digits<T, Policy>() * 0.301F));

   const std::uintmax_t iterations_allowed = static_cast<std::uintmax_t>((std::max)(12, my_digits10 * 2));

   std::uintmax_t iterations_used = iterations_allowed;

   // Use a dynamic tolerance because the roots get closer the higher m gets.
   T tolerance;

   if     (m <=   10) { tolerance = T(0.3F); }
   else if(m <=  100) { tolerance = T(0.1F); }
   else if(m <= 1000) { tolerance = T(0.05F); }
   else               { tolerance = T(1) / sqrt(T(m)); }

   // Perform the root-finding using Newton-Raphson iteration from Boost.Math.
   const T am =
      boost::math::tools::newton_raphson_iterate(
         boost::math::detail::airy_zero::airy_ai_zero_detail::function_object_ai_and_ai_prime<T, Policy>(pol),
         guess_root,
         T(guess_root - tolerance),
         T(guess_root + tolerance),
         policies::digits<T, Policy>(),
         iterations_used);

   static_cast<void>(iterations_used);

   return am;
}

template <class T, class Policy>
T airy_bi_zero_imp(int m, const Policy& pol)
{
   BOOST_MATH_STD_USING // ADL of std names, needed for log, sqrt.

   // Handle cases when a negative zero (negative rank) is requested.
   if(m < 0)
   {
      return policies::raise_domain_error<T>("boost::math::airy_bi_zero<%1%>(%1%, int)",
         "Requested the %1%'th zero, but the rank must 1 or more !", static_cast<T>(m), pol);
   }

   // Handle case when the zero'th zero is requested.
   if(m == 0U)
   {
      return policies::raise_domain_error<T>("boost::math::airy_bi_zero<%1%>(%1%,%1%)",
        "The requested rank of the zero is %1%, but must be 1 or more !", static_cast<T>(m), pol);
   }
   // Set up the initial guess for the upcoming root-finding.
   const T guess_root = boost::math::detail::airy_zero::airy_bi_zero_detail::initial_guess<T>(m, pol);

   // Select the maximum allowed iterations based on the number
   // of decimal digits in the numeric type T, being at least 12.
   const int my_digits10 = static_cast<int>(static_cast<float>(policies::digits<T, Policy>() * 0.301F));

   const std::uintmax_t iterations_allowed = static_cast<std::uintmax_t>((std::max)(12, my_digits10 * 2));

   std::uintmax_t iterations_used = iterations_allowed;

   // Use a dynamic tolerance because the roots get closer the higher m gets.
   T tolerance;

   if     (m <=   10) { tolerance = T(0.3F); }
   else if(m <=  100) { tolerance = T(0.1F); }
   else if(m <= 1000) { tolerance = T(0.05F); }
   else               { tolerance = T(1) / sqrt(T(m)); }

   // Perform the root-finding using Newton-Raphson iteration from Boost.Math.
   const T bm =
      boost::math::tools::newton_raphson_iterate(
         boost::math::detail::airy_zero::airy_bi_zero_detail::function_object_bi_and_bi_prime<T, Policy>(pol),
         guess_root,
         T(guess_root - tolerance),
         T(guess_root + tolerance),
         policies::digits<T, Policy>(),
         iterations_used);

   static_cast<void>(iterations_used);

   return bm;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type airy_ai(T x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::airy_ai_imp<value_type>(static_cast<value_type>(x), forwarding_policy()), "boost::math::airy<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type airy_ai(T x)
{
   return airy_ai(x, policies::policy<>());
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type airy_bi(T x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::airy_bi_imp<value_type>(static_cast<value_type>(x), forwarding_policy()), "boost::math::airy<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type airy_bi(T x)
{
   return airy_bi(x, policies::policy<>());
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type airy_ai_prime(T x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::airy_ai_prime_imp<value_type>(static_cast<value_type>(x), forwarding_policy()), "boost::math::airy<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type airy_ai_prime(T x)
{
   return airy_ai_prime(x, policies::policy<>());
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type airy_bi_prime(T x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::airy_bi_prime_imp<value_type>(static_cast<value_type>(x), forwarding_policy()), "boost::math::airy<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type airy_bi_prime(T x)
{
   return airy_bi_prime(x, policies::policy<>());
}

template <class T, class Policy>
inline T airy_ai_zero(int m, const Policy& /*pol*/)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename policies::evaluation<T, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Airy value type must be a floating-point type.");

   return policies::checked_narrowing_cast<T, Policy>(detail::airy_ai_zero_imp<value_type>(m, forwarding_policy()), "boost::math::airy_ai_zero<%1%>(unsigned)");
}

template <class T>
inline T airy_ai_zero(int m)
{
   return airy_ai_zero<T>(m, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator airy_ai_zero(
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it,
                         const Policy& pol)
{
   typedef T result_type;

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Airy value type must be a floating-point type.");

   for(unsigned i = 0; i < number_of_zeros; ++i)
   {
      *out_it = boost::math::airy_ai_zero<result_type>(start_index + i, pol);
      ++out_it;
   }
   return out_it;
}

template <class T, class OutputIterator>
inline OutputIterator airy_ai_zero(
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it)
{
   return airy_ai_zero<T>(start_index, number_of_zeros, out_it, policies::policy<>());
}

template <class T, class Policy>
inline T airy_bi_zero(int m, const Policy& /*pol*/)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename policies::evaluation<T, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Airy value type must be a floating-point type.");

   return policies::checked_narrowing_cast<T, Policy>(detail::airy_bi_zero_imp<value_type>(m, forwarding_policy()), "boost::math::airy_bi_zero<%1%>(unsigned)");
}

template <typename T>
inline T airy_bi_zero(int m)
{
   return airy_bi_zero<T>(m, policies::policy<>());
}

template <class T, class OutputIterator, class Policy>
inline OutputIterator airy_bi_zero(
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it,
                         const Policy& pol)
{
   typedef T result_type;

   static_assert(    false == std::numeric_limits<T>::is_specialized
                           || (   true  == std::numeric_limits<T>::is_specialized
                               && false == std::numeric_limits<T>::is_integer),
                           "Airy value type must be a floating-point type.");

   for(unsigned i = 0; i < number_of_zeros; ++i)
   {
      *out_it = boost::math::airy_bi_zero<result_type>(start_index + i, pol);
      ++out_it;
   }
   return out_it;
}

template <class T, class OutputIterator>
inline OutputIterator airy_bi_zero(
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it)
{
   return airy_bi_zero<T>(start_index, number_of_zeros, out_it, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_AIRY_HPP

/* airy.hpp
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
*/