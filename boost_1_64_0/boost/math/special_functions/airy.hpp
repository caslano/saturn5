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
sJNz6yNQS6nHWNjJWphozCc6TzXWSp57ZkDneqzVHOQh5wq+MBYStgQxV+TcQtBZ7JYb88jvGK8Ek/fTP6OWI3i+tYivM8e3AX7lTOBWzDdAzv+hryZy3fZCP9m3PYSY5X3tMehXmGM+jfiasn5/YWxnjuUy+uWM7P+hRhlYl7vGJsizfRx5yHvYx8hjG9f3BXzIWniLWGoyS1Ldxo7l+VIac65nls5Y+DBr8K4xr1wnsxoLTOIa5TQWr8s658XYn9iuoLGg7B8UQyx++f63Oq4lbFfeWDSBWWVjMT/XyIP43GxXCz7e8DWxvjGPm8c2MRaSd7PNYTeRtWoNO7medoDfmeyjCzQdzLn1xNierGk/5JGS2SBjDvm7MBx2qbi+Y4y5C7DdBNR8nez/IQ8v12g6NJUz70H4kNwWII92XMsvke8PSYktg48NHN93GJuP2Y9g8u59DWok5/p+Qx94kxBbj3ylRluQxyOOb4cx3zrWZQ968g/Z/8NY2TM6Cr8N5fyfsV/k+eM85pOzQjH0uJwZu4718YLnuwP9DiYQu4/cTnPM/xpz/ct1ew6dO7N+bxBzP54vcQ17ZSPXlxTGYvJuJ62xkFe+/zUWkXP1WTB2H+ucw5hP3pvmMeaQv7XvG3PJ362ixk5Mlf0/+K3IduWM+cOs3wfG3N25Nz4yFpB3wjURcyfOt14N7JnzfI2NecvL97+YT/aMWkErD9e8PWIuzqyzMc9M1q8HNEjCrK8xZxGu20DELOdUh8Fvf9Z5NOLryCwA1p81nYJ6RFiXz43F+3GNZiOPUbL/Zyx4S/7/P+jXUPb/EN87rPP/ULdz3C8rMN9YZquhSzFmv0KX86zpOjA5l7EZTM4obTem/4fQbmPRuOz/oebd2W8UTM5WnES+9ViDc6jvdO6/S/AxjOe7hnqIVreR7w7W+R9o35jZI9i147HPYFeH2WvELOdFE9W0dSnfEyeviWsn1yiNsZj8Nn56Y049/weWjefLbswh50VdxlyyX1IAfh/yfEUw3wk5/2csLO+KyiK+OdzjlYwFpZYfGovOl/N/YPI8WBfxyZ50I2gl54yaGYvIumxpLC691g7zteV8O8HvQfbRHVptYu37GAvJOQA/8pVr2FBjgY08dpQxr9zbjgeTveHJYDL2M2P+fqzpLMQX5DzmId9MnMciaDWQx36FPFZw3b7F2D6s3w/QtAvrvAr5PuNa/gK7LZzbH+iXzBzLJvgVTSPGPPNYg13Qryj3wX702gs5/4dYbnEsJ6DLXjn/h/6rwfFdhF1jju8qdJa/PbegXxKO5W/4lXo8RA/JXtBTxFye2SvE0o/nS6hlrB37TWYsPkD2/2Anzy5OYz5Zq5mMBWSf5j1jCXI/lNuY089a5TfmHcasMOxycCwljIUus6ZlwOR3FSoai57n+lY1VlBiqQ67ROy3DvwuZB8NoYGcE2wKu6esQQtosJg1aGvMI+cKfMZih7ke3TCfvIPsbSyyku0GYOwmjnkI9JPvo0bCrgnnMQ7sEM83CTVfLOf/EPM17qGZsLvMfTDXmFvWwkJo4GIfS405yvF83yDfJOz3e7D6rPNPGNuX6xY25pe/8b8jt3zsdyPyWMh225DHBK7Rn7Cryrntg1/51uOwsfCX7OM4Yr7BGpzBfFd5vgvGXCt47BXYyf/XchPzXeGx9zA2wPo9QN/P4PXxBP2yNYHYS/TuVtbAUdvs5DvDpMZ8UvNUxqIP2O4dY95anEdGYzE5253NWFx0yQW71myXz1i4HutcyJjjK9agOMZKzKWNOW+yjwrIbSrPVwV2cr9bDX7lXqW2MbfcCzSABuLDayxwkbX/BD4O8jpvg/lOsfYdMXY=
*/