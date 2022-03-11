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

#include <boost/config/no_tr1/cmath.hpp>
#include <math.h> // platform's ::log1p
#include <boost/limits.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  include <boost/static_assert.hpp>
#else
#  include <boost/assert.hpp>
#endif

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
T log1p_imp(T const & x, const Policy& pol, const boost::integral_constant<int, 0>&)
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
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582)) && !BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
   result_type result = tools::sum_series(s, policies::get_epsilon<result_type, Policy>(), max_iter);
#else
   result_type zero = 0;
   result_type result = tools::sum_series(s, policies::get_epsilon<result_type, Policy>(), max_iter, zero);
#endif
   policies::check_series_iterations<T>(function, max_iter, pol);
   return result;
}

template <class T, class Policy>
T log1p_imp(T const& x, const Policy& pol, const boost::integral_constant<int, 53>&)
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
T log1p_imp(T const& x, const Policy& pol, const boost::integral_constant<int, 64>&)
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
T log1p_imp(T const& x, const Policy& pol, const boost::integral_constant<int, 24>&)
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
      static void do_init(const boost::integral_constant<int, N>&){}
      static void do_init(const boost::integral_constant<int, 64>&)
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

   typedef boost::integral_constant<int,
      precision_type::value <= 0 ? 0 :
      precision_type::value <= 53 ? 53 :
      precision_type::value <= 64 ? 64 : 0
   > tag_type;

   detail::log1p_initializer<value_type, forwarding_policy, tag_type>::force_instantiate();

   return policies::checked_narrowing_cast<result_type, forwarding_policy>(
      detail::log1p_imp(static_cast<value_type>(x), forwarding_policy(), tag_type()), "boost::math::log1p<%1%>(%1%)");
}

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// These overloads work around a type deduction bug:
inline float log1p(float z)
{
   return log1p<float>(z);
}
inline double log1p(double z)
{
   return log1p<double>(z);
}
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline long double log1p(long double z)
{
   return log1p<long double>(z);
}
#endif
#endif

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
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
JNchi8XT9MPsSqp8DhdVn49rMGxzAdhUYGcT9dAWyRjCSz6O+oRxLnt6rhvosByP23KC3yRngiLfm8h5R9q1ZoluP/6IbksTlDtKcHPMAciAz94tB3hWVvyRGVQqGXYwo3ImZRw8a73FE/GaL74bqd0qCyNs/JORA+P0x/JqhBEjw2ihugcX1jlB0deAYIF5MnssNQiGBDzvIaZobFkqnFSuSVT62jt5jBRd4L0s2TnIG0l8fDzZKlzKOqJK51tKoO5ijlnqUb6OAbe3uJRyzsN+yetv3b/zw2vk+i74qTmec43LVRpLQoFzSZu0y8Byy75rGNeCiuSW8rmZxuk0q5+12SH4WJoqradwsv2LKGuADRzKV2Df2ZUKVN5gkyQ9tMON4QmDR3NSBeBSO7qcqrsHkA1XKpxgMcW/2+LC71mrAENmkJwnkzwpRn5gWqZrE/qSnn1oYvgxwi6oUjZ4LKjBV3eOO95W0pdHhcT+phnNQchAMBkMOY3I3gjC4WYWS05qOAolCfFDmETPcVRgkRwLJOsYYhq0x4QiinxQBBY+wYnLsQPriMSUgfR6c0GJnLl5besc4zbJlvs3Y6dZDTeJEnhZ+GrH3vtbeULMhCNn5nqHb6cWlCn1YbaPA1Hsf9aZ5pZPUNpMesL6svKZ1XoiHW0q4x/NAbXQtnQ1w/vzE4nNUTmxo3ZB3iYTv0YlYgvlKkh+grfFcnW6VOO8/CoaQximwra6RGWYSSPPjCKF/S+QDeodwoRs9b+VMIyFN9Xd1SrtySIzfwwnW5HObyLkdI/AsDakDnkI9a/hFP/KqKGoXVeM+T5kMj+0H3aTGov5ZbNxg+6v0AOEoHiot0J+X9yIeRWSzJP0/339UrMTWfLziGEYlHmNKSg1RbAYtCuPKoKE3HQmBlH4+aFQ5Fv8JN1WUCtsX2PZF87iFvpnVrAK3gwHCn95umAXduFZuMellKDH6loAn5kKmmVZfFkHWdKsI8iZVukQZ5d1bjglkMdbk58mbh3qZFnD40gsqIO6Sh4ASv4giyomlQHAGeDqO6/9dg+xJAQ7ZVKyvn7+AeIuM1KqxDLhgvKZpgzDnDIMW5GC4LQ8y2kxOH3RsAinpTz4heY5de+GNwIryHKk9kDQ4Th0uMAR1WsLeMH4U2rJ4a8MMCVwG2SRwT7B/rGtoJ+cj1YDV8iJmAcPHIKZ3BZ8dDKiZ2pS6bQRu0myRtXrTL6aKGZiqh8RKIdaBTfmbHV1TaaElnDr2aE6/lfmLp0sJuNB6aAnA8+bSPezEMUsYeFiR3ysbmnqrnJr8rhBGrpJWsEjYhNZp8P99UbL26dCOyca7C33qo78A1TUunJadL7qCXZkltPOZK2SD4trM4+e2oGxXuOJ4HxGxSnJpT0FfJYZ7lg2qHL88JAacY7no+42B7LDEidDS29ujMGkoyLoB+IEXu1w5vsQWV+J5A/Hk+NVdvBIXDUODF2N14x+zChvC7C+MPFDqQGnY4UQD/xXB9E4313qWxSNzXoiTqnT5dszjB2tjPpZ4RuLissqyLK401OUfvO78kpBXfTjIpSrB1V1bqgvAFFnepIYEZhHO5shpFJaNpi0grJAa8F2JLOG9bhb17SEVVG/igsFS5w6AK0U/NtmxINpiJxSw67iNOZEEwrAFkf1x0jXwaEhlz6kpD4KWz14Ofv+kXoF3Ql7qtqiE7eIYIt9YPeg0LbStPtOd470fmENEzZ09gzWVVopb9Q+PfMbsaqOXWNdU6AAJL+K8+5Hkqm0zGIivDTPjiOFyDOcsBId9egrzH4tGOlsQa13jXcUvE4KkiEpJZK5yB6bQtQKAlg8Zm3ArlkibLLcaB7Q1fg+XADmdDFO17k6/25TCsk9VYay5JZpa2NZbqQ1UFySAowQjj8nXxQDq9C3e7v2XGiEAEUaI/302tAEdrzVBKUxt/8jS22pnvbUe7AsIqHyOQkkAwaIMTZR0Yz6abzKwsr+6iE+CMlKnu59nxyjRjG1Fhw8Q4fldpVUBrLj1xYqOJ7zPFUSyso5iCGSKpeDdECHbZNKW3ZuNOCcymqVICdGQAtpSctGkHMpJF4PBR8LKecDoYdneph1Z2VJO63M0RnnAReXipFsdkOttgI1rXkgzMQKDVy3FRZIWfQkNN1Yyj6Irr9efOgyDmHumVEtWJikqWd+NxKbvDg73tQ8IBebPKufKsCzh8tQq4YQ1RczkKgKi3GYqQDr0Pvxobh21+6HHD6jyNQxsyTZbSU2XQokNv9RrXcaGWB7Tad5pkyWF1WRxmaCkIqmjfd+IKqdNNIuzJEJuuHrNQXpDKFpaKu9+sAF4l3g8LffLsIo41zh1dPrNHYxhkDpBUVllrPJwocrnq0XCbmKErPUd1Ag19c3KJScJzNQTHj9zNJyDFWuy8T1c957Y98r4XYJ1rTfe2nbbK6cPTSIkrPXZMACuvzdibzwhRk5rYgt0MXFUgDyFRybtFa2wXWDSBLOP1Zeu3ALsP71xckBCZRW3+DwUSUUMBZYbDE4sFrzw3gdWFjoSCyoyRQURRl5U2vjj8ZppD6LtIB0W4gm3JJpEJSUwj95iNt8V9GmeoK2Mdgievl0PCeU99dxiW7d4HgLF7OecKpeV6E4pbHu/ZbZFy8gNHjsGxD5U2ssWH4N/inU4qBfn+ljNAp34SeTGvyu15vNpAwIQ9j4/6ZQi6BcUf4N9rJZJBxk+eAOWxUPlYOVz8OLA6deJJp6dkvKMaZGShCFD4SVizzWXVqFib736w/SoMrl+iFQp92yzVHqNJR74FehajGcPGU9Z+cG5bSIcftd7Db0tLDpoNyIp8iBBKlUmhx1qpzq8uv2UJ6Nl4JlkJX81b3Ys/GsmUhyyN8w3YsAzQyPqjoPu/nLRpkojbUWx0CpYvVm1+XiMgwZ3BrFOLA8EXN0tmRXm1nD3lGTuEf2lBMXpFjtDOLwUgiKfLfGNpwtwsbHLCFanoucxQ6lgGacyMqfWcAAIOVXjWIraOPzES9oydeLatqza4KXyAHyZs9eCmnIyju6eGe+ABS+xQT2RzpDvurBQ+pBjJJpNAY8DoztfoDTG+NfukLhqDqvz0gB6CEh43UqrkY/HBiZKnkuMvT79W3qydWlPdV5rDq6n+M/HnFFCJq0C40kl8nXc5y0Tdt/TO+D5ES7WxJPveGuxnD03Nw2Nxf8LvjIKSAwrdwWXALlTiWzFV9Rc7i6tzZXq5A+i4b88UiUdRXBOsPgJhq21VFarAxpUB4G7td0x9w4KpmZcSUeMOUvy/iExSiFyIk8NA0fcvMj+GiCQTZuA33Ryy16Xtno6AqJAv5wPFJM9ULMiPMT2uvDaK0+zm62lkWIiwNI6ovBZ+aerD5wJNVk2Yd5iohb5sbRpf0U0AStt2ySvh7FwrH6ASgLWoTR9QE4w0LmAyKT14tiqdbiGRlOEl42XDsk8dh5f3Q+1zZbY8FScerIOYAuwsRuAZWPIyCRlz9POphQghNJDs9Icmrs2KVmQlmKsw+TKOyN2foXOyQvWw4l7+C6YtJThXay+qOi4aTbF5RBnx8eYleaqW+HvuB4iiqFG2mtNUZwusEEj5xjv03WUaTLzemxAQu22icgZM1WgmTDqJBjoxTwmRt5fPENlTWhiUfUKh0ZwgaL7Zqs7B90tODLEI+qAJrrLQAPlhbDgoT6naJ0Zv2MOMhsTR3E5wg4V0KQ0G8BOD/sOlZTLVuRGasQM/AoZdvjdP5QWpayLGiGM7EJApaHI3Xvk6r+62Ky5ua4GVJio1L+WEhTZcBtIJdaV5pyD4BfJiXu2DsI2gPBPQfZ9ztTS+rtgf94RBMNsSmoj81U4n+asLuY1JBpNfTrgE6y55O2flocJPxnzkd2PnshlAmhxkgMRZoFFBJ5g/l3VI5nZKsoStDkr88fFg6J8wu0Qgyd8GOlxs5uOP3J6odVMCgnIuI7VDmyrGnZBkZTM/5ChTbjYDc4FnSiPh8FojokFb/Zw/W1d0MQYbVzOZh9LzjTScVFRAU6lo0zt3upFy1zjLBBtCB3PlRLNdKsXPCqh3U1xYOPrSU63S9UqOUslhAsKR58fpW+vnqq88bK1yC51La28ExN39Kx/HBA0IuQ9GVsPY6nrkhAZM6+hxkAq201M9s8oaGeUAmHikmFyVUr7smDCI1Ei7IeiTy/XipCfxGhv5AGYjgT0eq5UsPfrsmojaRKrmUJJOeUvPw3ha4NPg9X/aOdEYedmHLleF1UajMxeglVk91OGo9jyWq93y48Te4VrCixamicRnzD6PI62zcmMAPkZVkLsokd/iPQjlX6rWKFZHYH8VdO4qA7S0net2i3sxq5ywczR5NxBnxCwM0rrslvRvm5Nw+CcV64Sbbrip0OaHZUF9UjGnAwAdjCTJ7Y82EV525efEQU8mtWGOscKVu+eCnIO9gzhdS8UFk6OMTXxcS4/KyF/pU0HbgnsJQywTbVzo70A/x9d1hlHqZUnYHZTlOJr6Ql4Vb2LCkreQRE03NiKLTOYhEvjlnh+wXRXhGdPj4r6z5xPEPhxes6RnYisiXikStGl0sgTAZ0KSPrf/oMjLjBd+N2jOqU1HKIbpaFHDr2Hmb4jHbSo38CuHS7AYjcmULLY6q+KrmmS5kZltnHa6w9VhCdtrAPIymcvXTQmT8iG3dpfIYXCu+Qlfmips+dAZGDrgnBY9N7F6xT3kbyiDVRJEU8AcJ3ntkpemblMp1GSigi4BORaJ3Z4T+RRilizlymZ0oXTBqN18eRurGcT5cjMPFo4wVetf/ecd1cuE3BZ9+gO0BYmlMNlOqHoegSsRRJ+6udB8KZ/RsGuDAo95DCUMop0D/LErlKlSfT3Ag5f6OKg6yumvcqArroD/5Yk3cZyC9X1rFUFSnDg98CYYvdTY6XRfOv2/xpKCASoHiMaKyCtph8ZyLOpNmRT6pBT2GC5IExNV0GIsPSAZ8QynAUnzCqq7miCZZrw34JlTGdTEzOa5S6KIMM79l4V/6+r0XCda2WmI3uk9zZvOTRRpcj5+XPFjpPmXThZZmXpZnNcq2aUL88OgiO0tCw7bVGvNCmGaT0DiRb9unRkaPDhjL67hcJkqEFXaizYQQp/6RewmBHqwXfKdGdDiby6VSaF90+gD/wTNDV7kF1NXvpRsneXr4fNgCcmIwCQr9c/hNdwtdLz5+VBvC4ggOU/LI/1IS80C/I9pLyEpGdYQZqsi+wU1CMVBPklqFRfWwRyvaum8ws9ELhX4fUoniIde7xZ7o7BtLeGfn2UwnLoVvawbwfL63VzbR6VYJMS7VLXx0hbteMw2bEpFiMPFs4fbKUa0ZhIk3Yb8Ct9XmP10HuVuolgFR/Hosi4huumgos03M7q0E4Li8QKpCQcTNjyPTVrQx8jLicLC1gIjGiOZyE4mpl7bMibgw1SZZ+RJv3Z+qot+neJRunIZPyx6clMaiHCuCjUgY5ufu5HMRs0RNSsDYQGLA9JgAl5iimy+jkg1iSi9n+MLKpbzzZTD0HBQXdhIjY1+FfnLDVTFTyziorKv2bY0Xerb8WlS6RCaElnoWW9rxOLdkMCq0P5/sYa8Cte42PiavgXKzYWgrXlnoSMJqqjmj+TOl4A75TpC8Fnm/1e3eEcUjeQoVRVc5CDQttobujYkYi6cXD68TQtG9+VQpYAERe4DKk2JDi1rBMceYfvyfXyO9naN8RE7NTHOc9firvsILaSjix4ThLJaPQbJ+tBGMDVH1WHWtthBU/Jvo7PU7j7SWMjAwrv/QcjD5mkK9CHKwQW2VOpi27LBjpPM35wr93BnthwC/bHl5H74Bsh1hebnx8Ggp6z1nYzOmTlMplPa9DAzy7R18BwE6OjkC21Rk3no3ul1FX6Rj3q7KpeFpNaySKA/B21tWUdp/FKRJOvOzwnDVRmqo0aaNKYRLmpsWcvE9ALrynXb1umToaZXILVAvXStpbydUr2WPLtURuX2rg+XxBU5rfMmrTtHHxaqKki7Z2fo2P5RauJWRKGwLOsJgztgYvnL6qGtZCSLYvLaCCSo4UV3ybSBaQokYylua0/ThYlHBX5fwjl1gxy+nd/Jf60p2AzMRd8faS87j9AmgIkpmKD4sNYbRMTdXG6MZK9RkG9UG+S58JBBbn8CLp3Isoakw8R+gPCLmzhTwG6fX2lZvMaf/Qt15gce9XU+uNvwL/suZMWr/rcyFV9A2IBOHXQ5Xl+CaNW7UWYlRB20hOevv/zEZ0cs3qgG1d1nNhulSCcxRu4EpHjbEki9waX8CgyOClrVfFhEieoqaASvoxPdmxpQjkavrYUInyqD+TNKZIMxMdBJibyXJjdik7eIxWar22u/iyrSGU0VTOG64JAA0vSjpTMrrg7lUnM7LIH7POKlJoGeGm3Uh18tCre8vPYkSnhJOyiX5Sjmh2qn7kCsUhgGmm+TYWMU6hmdy0i7RfRx6AaxsoSoooycvoi4LxhksUqb6iJt0sz9I5QUIO3Hit8vmTRs4OY/syJ57iPKVdsaOVhTDSVVtbuifzRD8rn94RDT02QwM+3E0mRWYS7F7P3QOrXROJga/p0BVjlgv2dIWIv0iPAUKXSCL3xNui5l6LnxRU4hg5hx2lYJb/03gjAuNpSi/+e2OyNRsBM2QGXj66jtO2nIHNinfB2LZcf3Jezv0CQVq0wDtOTJdp5eu7v7a3pdgfR5ee5PP2PJjD6yr9IFI0szE3M1eCcJmht1Vr8kIj3/9aGbGWGbsW6F610eDi6cuFUjeseZXdeV9j4oy0pmyjgd/txy8FpShykCpJKiVhAbVwQWVARUYKowYtCQmK+mKulFtPXHZbyOpdf7FlfHBGvgNsp3IS10K5nkoyTsJc8nE0d3XLSKJPAECgdHh+hkAVU9/SS68fDj7MezFvLGBkIbG31CMaHvwNpq6yigZdKvn+0z6RI9wid9GOQCm+u+fXcqYkX/3tt2JXF64GJMKalS9e5puKbnb5g9Ft6a3CGoUO6vmVwsJC639oNKxbWC11BHCqZp4O4yMaAIo3IPlHKn2tqDYeQYcSSOrvKFtaKkBcoHaNEP0NBO83cZOWeEgaDDvNBnGtPgtFNc/7ABeAcnvSmwqOKn7ILhyO0I26nAY5OcdDLag98viJOMGtnVuotOVzMnzn+3ZapNTWhtWLICVimaAmqcDikb3QJ+aqnkcScinrhRc9nlqjvtqNsgqVZ9GhSEWHOEp9HtSzIAGJpQaJFnQmdn2VfvETtPV1Wz3m4zAkX/mrMhJOI4vDK83t1NjAETovws69dvPyyTMdZIAVULi/oQ9K6fWWYXqWoW+sHWMmdMFDc5nQMB4KBfCAstLJhD/308l1TTum5obGZhjJoVCkI+PTHpcS9BrzqD7NJHo8bnBdD2vJ4EQAOI5UV5qhj2ZpUxzAEdDKlva4yISQ1coM6ow1J/tJuGlqXFnuLWNsv4RskQtPR3hfaIMPWCGajDtrWhLsiLVO1lNG5bVte8yBBVmjLj31AvOTF/S5j9aN3DWSY9aYN3Zzh/8Fz9AFKG+Ho2nDu3RL5n00F5yP4zJvpwqeadD3hcyozq4IigY3JmW7HhRGiCDt12TQQREGOV+N/d4cltRaaEzSDIASqMXQT/h4k/aAzm7FEDjNwgK7ioMp10tXVeXeDvSjFNH8H6fDpd1IeU4JI5+gJ0d7+3GRtwGs0cd2kSg7trUhq/gpiALFz1IkikXMhrP246Oa3JeVe1gyrmsUxoMY5xq89ad/aOwHs8FmuX+CPEUaN6sgh1ew8wdUBIFQf6DJkG13/ctiqiHCLcbpqfpvDylV/i6i+AqEpEE7nSn/cyODoT7Wlv7YtFzqwmWrmfEkBMSevYXPaGeU8ZpdXRs9N60mzrMVGo1w+kaCOOdlXdvoK2uGsdh0K0rNptJBlJecnTEsICWpa+6VnVFhT3tKqMGi/EzV5JpnmF1CWFE4e1gYKhM5+Bfep+UMbCoZII0JaHe0b08loPHFhHzEP9tiWhEZ3FTH7klW4Gc8ucfjDnV4WpdCxSg8iqSsXCZz+GhAxG9qZT5MXg/k9lb+mKstpenYWm9PTe7tO0+lm3emrwwqNq7TOBTROlfC0uwbr8BtlJMG835AFefn00N4gXZ80iFEXDWmEm+YjI2gj5osiP+3cQF9Z8oRu3Oc646ffw/+OcvNptlvoInTSIJag5cqkDscq0Q68CzJw31ije/UgVvd94pOcSt3aYLxUrqiIom/vHjkwAUudHC8/uqF6wpWvOX2UlbhmXq4laf05fkBykSHzLRVWcG19X2FsVNgVB4sBClIQARqnZKKikK1P2HJkhVMC77nMgfbYkXpEPYCBYunOA6Owkj25KjRhBSmLng0YlnFfk6yzPJhArmGtJ2nPteD0aw2ozWYDcharf1e00XsGtfLrQEdoxF9rmhSveGW0uPlD3L3Gq4X2rgvrTGaoSEF8UhEzEnx7JAAD2dUZ3zMnZ0d3EfOZCETpDtvOoAOO35Pxp0Uv+IRXLXDiCnc8sRPo0WVGoPcY/Lo2oNmWrIg3E8jzmRpl/0OOCFxK4sdGkpiHHKX/npDadHEs/4MgPMVCS0ry1sbePlnIJ1O9vEPVwHEGKgMF4YH5JMQREI5yVyyVASNXyeEXO086aCO9JRqIAI3nB9lptCVKa1vixBrYmT2dyYlvk//tk8leSA3qw4sBFHZeR4kCLVyRuSz79UoJzRfkpuzgmE74XNSoHC5hMNDvAjs1NCTG1LkLhjDi4nQiJYZdIog/mvI5yAPotZtoKyEA1/jk3R9PeQxHxpvl83DTIEcSlSqQ/Ja9eSAHZRr1wXWm5BWLZLN3BkJR4vXh/CHjnCtV61igZXUZLXckcdtA/IdkQ+bb6f2z4MP7PWHz5XSfEE3vlU6QZmZUUtanA4nOCICPxRYJ5/oUbhR0qXb0/OJ9QE90PNtLz7fYQTVdE57rATahZ2KKX9dEKo8SmICp4hviNcfmcxDuuTAUZldGZJL7yDcbBWWaMfYOlnBZEKkklLh05cWUrJEqS+uHDpMyoSodjpmHlxOekLpAvrCQ5wg3gme0C7SvCs6i7l7LQK1Yg3cpfOtTERuLTWaTZkED63+7mMv5itTo1a+zc3iCyEImT4PsP1BmkY7KYAyd80BuuOz7UuE2ahk1rIV7LbwyVADQ7L8CG0QKtw=
*/