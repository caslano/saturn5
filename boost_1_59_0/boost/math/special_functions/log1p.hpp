//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_LOG1P_INCLUDED
#define BOOST_MATH_LOG1P_INCLUDED

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <cmath>
#include <cstdint>
#include <limits>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/assert.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

namespace boost{ namespace math{

namespace detail
{
  // Functor log1p_series returns the next term in the Taylor series
  //   pow(-1, k-1)*pow(x, k) / k
  // each time that operator() is invoked.
  //
  template <class T>
  struct log1p_series
  {
     typedef T result_type;

     log1p_series(T x)
        : k(0), m_mult(-x), m_prod(-1){}

     T operator()()
     {
        m_prod *= m_mult;
        return m_prod / ++k;
     }

     int count()const
     {
        return k;
     }

  private:
     int k;
     const T m_mult;
     T m_prod;
     log1p_series(const log1p_series&);
     log1p_series& operator=(const log1p_series&);
  };

// Algorithm log1p is part of C99, but is not yet provided by many compilers.
//
// This version uses a Taylor series expansion for 0.5 > x > epsilon, which may
// require up to std::numeric_limits<T>::digits+1 terms to be calculated. 
// It would be much more efficient to use the equivalence:
//   log(1+x) == (log(1+x) * x) / ((1-x) - 1)
// Unfortunately many optimizing compilers make such a mess of this, that 
// it performs no better than log(1+x): which is to say not very well at all.
//
template <class T, class Policy>
T log1p_imp(T const & x, const Policy& pol, const std::integral_constant<int, 0>&)
{ // The function returns the natural logarithm of 1 + x.
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::log1p<%1%>(%1%)";

   if((x < -1) || (boost::math::isnan)(x))
      return policies::raise_domain_error<T>(
         function, "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   result_type a = abs(result_type(x));
   if(a > result_type(0.5f))
      return log(1 + result_type(x));
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<result_type>())
      return x;
   detail::log1p_series<result_type> s(x);
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

   result_type result = tools::sum_series(s, policies::get_epsilon<result_type, Policy>(), max_iter);

   policies::check_series_iterations<T>(function, max_iter, pol);
   return result;
}

template <class T, class Policy>
T log1p_imp(T const& x, const Policy& pol, const std::integral_constant<int, 53>&)
{ // The function returns the natural logarithm of 1 + x.
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::log1p<%1%>(%1%)";

   if(x < -1)
      return policies::raise_domain_error<T>(
         function, "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   T a = fabs(x);
   if(a > 0.5f)
      return log(1 + x);
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<T>())
      return x;

   // Maximum Deviation Found:                     1.846e-017
   // Expected Error Term:                         1.843e-017
   // Maximum Relative Change in Control Points:   8.138e-004
   // Max Error found at double precision =        3.250766e-016
   static const T P[] = {    
       0.15141069795941984e-16L,
       0.35495104378055055e-15L,
       0.33333333333332835L,
       0.99249063543365859L,
       1.1143969784156509L,
       0.58052937949269651L,
       0.13703234928513215L,
       0.011294864812099712L
     };
   static const T Q[] = {    
       1L,
       3.7274719063011499L,
       5.5387948649720334L,
       4.159201143419005L,
       1.6423855110312755L,
       0.31706251443180914L,
       0.022665554431410243L,
       -0.29252538135177773e-5L
     };

   T result = 1 - x / 2 + tools::evaluate_polynomial(P, x) / tools::evaluate_polynomial(Q, x);
   result *= x;

   return result;
}

template <class T, class Policy>
T log1p_imp(T const& x, const Policy& pol, const std::integral_constant<int, 64>&)
{ // The function returns the natural logarithm of 1 + x.
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::log1p<%1%>(%1%)";

   if(x < -1)
      return policies::raise_domain_error<T>(
         function, "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   T a = fabs(x);
   if(a > 0.5f)
      return log(1 + x);
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<T>())
      return x;

   // Maximum Deviation Found:                     8.089e-20
   // Expected Error Term:                         8.088e-20
   // Maximum Relative Change in Control Points:   9.648e-05
   // Max Error found at long double precision =   2.242324e-19
   static const T P[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.807533446680736736712e-19),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.490881544804798926426e-18),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.333333333333333373941),
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.17141290782087994162),
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.62790522814926264694),
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.13156411870766876113),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.408087379932853785336),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.0706537026422828914622),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.00441709903782239229447)
   };
   static const T Q[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 64, 4.26423872346263928361),
      BOOST_MATH_BIG_CONSTANT(T, 64, 7.48189472704477708962),
      BOOST_MATH_BIG_CONSTANT(T, 64, 6.94757016732904280913),
      BOOST_MATH_BIG_CONSTANT(T, 64, 3.6493508622280767304),
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.06884863623790638317),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.158292216998514145947),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.00885295524069924328658),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.560026216133415663808e-6)
   };

   T result = 1 - x / 2 + tools::evaluate_polynomial(P, x) / tools::evaluate_polynomial(Q, x);
   result *= x;

   return result;
}

template <class T, class Policy>
T log1p_imp(T const& x, const Policy& pol, const std::integral_constant<int, 24>&)
{ // The function returns the natural logarithm of 1 + x.
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::log1p<%1%>(%1%)";

   if(x < -1)
      return policies::raise_domain_error<T>(
         function, "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   T a = fabs(x);
   if(a > 0.5f)
      return log(1 + x);
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<T>())
      return x;

   // Maximum Deviation Found:                     6.910e-08
   // Expected Error Term:                         6.910e-08
   // Maximum Relative Change in Control Points:   2.509e-04
   // Max Error found at double precision =        6.910422e-08
   // Max Error found at float precision =         8.357242e-08
   static const T P[] = {    
      -0.671192866803148236519e-7L,
      0.119670999140731844725e-6L,
      0.333339469182083148598L,
      0.237827183019664122066L
   };
   static const T Q[] = {    
      1L,
      1.46348272586988539733L,
      0.497859871350117338894L,
      -0.00471666268910169651936L
   };

   T result = 1 - x / 2 + tools::evaluate_polynomial(P, x) / tools::evaluate_polynomial(Q, x);
   result *= x;

   return result;
}

template <class T, class Policy, class tag>
struct log1p_initializer
{
   struct init
   {
      init()
      {
         do_init(tag());
      }
      template <int N>
      static void do_init(const std::integral_constant<int, N>&){}
      static void do_init(const std::integral_constant<int, 64>&)
      {
         boost::math::log1p(static_cast<T>(0.25), Policy());
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy, class tag>
const typename log1p_initializer<T, Policy, tag>::init log1p_initializer<T, Policy, tag>::initializer;


} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type log1p(T x, const Policy&)
{ 
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::precision<result_type, Policy>::type precision_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   typedef std::integral_constant<int,
      precision_type::value <= 0 ? 0 :
      precision_type::value <= 53 ? 53 :
      precision_type::value <= 64 ? 64 : 0
   > tag_type;

   detail::log1p_initializer<value_type, forwarding_policy, tag_type>::force_instantiate();

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::log1p_imp(static_cast<value_type>(x), forwarding_policy(), tag_type()), "boost::math::log1p<%1%>(%1%)");
}

#ifdef log1p
#  ifndef BOOST_HAS_LOG1P
#     define BOOST_HAS_LOG1P
#  endif
#  undef log1p
#endif

#if defined(BOOST_HAS_LOG1P) && !(defined(__osf__) && defined(__DECCXX_VER))
#  ifdef BOOST_MATH_USE_C99
template <class Policy>
inline float log1p(float x, const Policy& pol)
{ 
   if(x < -1)
      return policies::raise_domain_error<float>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<float>(
         "log1p<%1%>(%1%)", 0, pol);
   return ::log1pf(x); 
}
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
template <class Policy>
inline long double log1p(long double x, const Policy& pol)
{ 
   if(x < -1)
      return policies::raise_domain_error<long double>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<long double>(
         "log1p<%1%>(%1%)", 0, pol);
   return ::log1pl(x); 
}
#endif
#else
template <class Policy>
inline float log1p(float x, const Policy& pol)
{ 
   if(x < -1)
      return policies::raise_domain_error<float>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<float>(
         "log1p<%1%>(%1%)", 0, pol);
   return ::log1p(x); 
}
#endif
template <class Policy>
inline double log1p(double x, const Policy& pol)
{ 
   if(x < -1)
      return policies::raise_domain_error<double>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<double>(
         "log1p<%1%>(%1%)", 0, pol);
   return ::log1p(x); 
}
#elif defined(_MSC_VER) && (BOOST_MSVC >= 1400)
//
// You should only enable this branch if you are absolutely sure
// that your compilers optimizer won't mess this code up!!
// Currently tested with VC8 and Intel 9.1.
//
template <class Policy>
inline double log1p(double x, const Policy& pol)
{
   if(x < -1)
      return policies::raise_domain_error<double>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<double>(
         "log1p<%1%>(%1%)", 0, pol);
   double u = 1+x;
   if(u == 1.0) 
      return x; 
   else
      return ::log(u)*(x/(u-1.0));
}
template <class Policy>
inline float log1p(float x, const Policy& pol)
{
   return static_cast<float>(boost::math::log1p(static_cast<double>(x), pol));
}
#ifndef _WIN32_WCE
//
// For some reason this fails to compile under WinCE...
// Needs more investigation.
//
template <class Policy>
inline long double log1p(long double x, const Policy& pol)
{
   if(x < -1)
      return policies::raise_domain_error<long double>(
         "log1p<%1%>(%1%)", "log1p(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<long double>(
         "log1p<%1%>(%1%)", 0, pol);
   long double u = 1+x;
   if(u == 1.0) 
      return x; 
   else
      return ::logl(u)*(x/(u-1.0));
}
#endif
#endif

template <class T>
inline typename tools::promote_args<T>::type log1p(T x)
{
   return boost::math::log1p(x, policies::policy<>());
}
//
// Compute log(1+x)-x:
//
template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   log1pmx(T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::log1pmx<%1%>(%1%)";

   if(x < -1)
      return policies::raise_domain_error<T>(
         function, "log1pmx(x) requires x > -1, but got x = %1%.", x, pol);
   if(x == -1)
      return -policies::raise_overflow_error<T>(
         function, 0, pol);

   result_type a = abs(result_type(x));
   if(a > result_type(0.95f))
      return log(1 + result_type(x)) - result_type(x);
   // Note that without numeric_limits specialisation support, 
   // epsilon just returns zero, and our "optimisation" will always fail:
   if(a < tools::epsilon<result_type>())
      return -x * x / 2;
   boost::math::detail::log1p_series<T> s(x);
   s();
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

   T result = boost::math::tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter);

   policies::check_series_iterations<T>(function, max_iter, pol);
   return result;
}

template <class T>
inline typename tools::promote_args<T>::type log1pmx(T x)
{
   return log1pmx(x, policies::policy<>());
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_LOG1P_INCLUDED




/* log1p.hpp
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
*/