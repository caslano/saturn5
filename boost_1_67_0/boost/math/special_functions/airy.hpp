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
      T bi = 1 / (sqrt(boost::math::cbrt(T(3))) * tg);
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
      T aip = 1 / (boost::math::cbrt(T(3)) * tg);
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
      T bip = sqrt(boost::math::cbrt(T(3))) / tg;
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
   const T guess_root = boost::math::detail::airy_zero::airy_ai_zero_detail::initial_guess<T>(m);

   // Select the maximum allowed iterations based on the number
   // of decimal digits in the numeric type T, being at least 12.
   const int my_digits10 = static_cast<int>(static_cast<float>(policies::digits<T, Policy>() * 0.301F));

   const boost::uintmax_t iterations_allowed = static_cast<boost::uintmax_t>((std::max)(12, my_digits10 * 2));

   boost::uintmax_t iterations_used = iterations_allowed;

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
   const T guess_root = boost::math::detail::airy_zero::airy_bi_zero_detail::initial_guess<T>(m);

   // Select the maximum allowed iterations based on the number
   // of decimal digits in the numeric type T, being at least 12.
   const int my_digits10 = static_cast<int>(static_cast<float>(policies::digits<T, Policy>() * 0.301F));

   const boost::uintmax_t iterations_allowed = static_cast<boost::uintmax_t>((std::max)(12, my_digits10 * 2));

   boost::uintmax_t iterations_used = iterations_allowed;

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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
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

   BOOST_STATIC_ASSERT_MSG(    false == std::numeric_limits<T>::is_specialized
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