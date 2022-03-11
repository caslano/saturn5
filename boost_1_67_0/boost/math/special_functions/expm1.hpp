//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_EXPM1_INCLUDED
#define BOOST_MATH_EXPM1_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <math.h> // platform's ::expm1
#include <boost/limits.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/mpl/less_equal.hpp>

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
  // Functor expm1_series returns the next term in the Taylor series
  // x^k / k!
  // each time that operator() is invoked.
  //
  template <class T>
  struct expm1_series
  {
     typedef T result_type;

     expm1_series(T x)
        : k(0), m_x(x), m_term(1) {}

     T operator()()
     {
        ++k;
        m_term *= m_x;
        m_term /= k;
        return m_term;
     }

     int count()const
     {
        return k;
     }

  private:
     int k;
     const T m_x;
     T m_term;
     expm1_series(const expm1_series&);
     expm1_series& operator=(const expm1_series&);
  };

template <class T, class Policy, class tag>
struct expm1_initializer
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
         expm1(T(0.5));
      }
      static void do_init(const boost::integral_constant<int, 113>&)
      {
         expm1(T(0.5));
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
const typename expm1_initializer<T, Policy, tag>::init expm1_initializer<T, Policy, tag>::initializer;

//
// Algorithm expm1 is part of C99, but is not yet provided by many compilers.
//
// This version uses a Taylor series expansion for 0.5 > |x| > epsilon.
//
template <class T, class Policy>
T expm1_imp(T x, const boost::integral_constant<int, 0>&, const Policy& pol)
{
   BOOST_MATH_STD_USING

   T a = fabs(x);
   if((boost::math::isnan)(a))
   {
      return policies::raise_domain_error<T>("boost::math::expm1<%1%>(%1%)", "expm1 requires a finite argument, but got %1%", a, pol);
   }
   if(a > T(0.5f))
   {
      if(a >= tools::log_max_value<T>())
      {
         if(x > 0)
            return policies::raise_overflow_error<T>("boost::math::expm1<%1%>(%1%)", 0, pol);
         return -1;
      }
      return exp(x) - T(1);
   }
   if(a < tools::epsilon<T>())
      return x;
   detail::expm1_series<T> s(x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582)) && !BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
   T result = tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter);
#else
   T zero = 0;
   T result = tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter, zero);
#endif
   policies::check_series_iterations<T>("boost::math::expm1<%1%>(%1%)", max_iter, pol);
   return result;
}

template <class T, class P>
T expm1_imp(T x, const boost::integral_constant<int, 53>&, const P& pol)
{
   BOOST_MATH_STD_USING

   T a = fabs(x);
   if(a > T(0.5L))
   {
      if(a >= tools::log_max_value<T>())
      {
         if(x > 0)
            return policies::raise_overflow_error<T>("boost::math::expm1<%1%>(%1%)", 0, pol);
         return -1;
      }
      return exp(x) - T(1);
   }
   if(a < tools::epsilon<T>())
      return x;

   static const float Y = 0.10281276702880859e1f;
   static const T n[] = { static_cast<T>(-0.28127670288085937e-1), static_cast<T>(0.51278186299064534e0), static_cast<T>(-0.6310029069350198e-1), static_cast<T>(0.11638457975729296e-1), static_cast<T>(-0.52143390687521003e-3), static_cast<T>(0.21491399776965688e-4) };
   static const T d[] = { 1, static_cast<T>(-0.45442309511354755e0), static_cast<T>(0.90850389570911714e-1), static_cast<T>(-0.10088963629815502e-1), static_cast<T>(0.63003407478692265e-3), static_cast<T>(-0.17976570003654402e-4) };

   T result = x * Y + x * tools::evaluate_polynomial(n, x) / tools::evaluate_polynomial(d, x);
   return result;
}

template <class T, class P>
T expm1_imp(T x, const boost::integral_constant<int, 64>&, const P& pol)
{
   BOOST_MATH_STD_USING

   T a = fabs(x);
   if(a > T(0.5L))
   {
      if(a >= tools::log_max_value<T>())
      {
         if(x > 0)
            return policies::raise_overflow_error<T>("boost::math::expm1<%1%>(%1%)", 0, pol);
         return -1;
      }
      return exp(x) - T(1);
   }
   if(a < tools::epsilon<T>())
      return x;

   static const float Y = 0.10281276702880859375e1f;
   static const T n[] = { 
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.281276702880859375e-1), 
       BOOST_MATH_BIG_CONSTANT(T, 64, 0.512980290285154286358e0), 
       BOOST_MATH_BIG_CONSTANT(T, 64, -0.667758794592881019644e-1),
       BOOST_MATH_BIG_CONSTANT(T, 64, 0.131432469658444745835e-1),
       BOOST_MATH_BIG_CONSTANT(T, 64, -0.72303795326880286965e-3),
       BOOST_MATH_BIG_CONSTANT(T, 64, 0.447441185192951335042e-4),
       BOOST_MATH_BIG_CONSTANT(T, 64, -0.714539134024984593011e-6)
   };
   static const T d[] = { 
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.461477618025562520389e0),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.961237488025708540713e-1),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.116483957658204450739e-1),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.873308008461557544458e-3),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.387922804997682392562e-4),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.807473180049193557294e-6)
   };

   T result = x * Y + x * tools::evaluate_polynomial(n, x) / tools::evaluate_polynomial(d, x);
   return result;
}

template <class T, class P>
T expm1_imp(T x, const boost::integral_constant<int, 113>&, const P& pol)
{
   BOOST_MATH_STD_USING

   T a = fabs(x);
   if(a > T(0.5L))
   {
      if(a >= tools::log_max_value<T>())
      {
         if(x > 0)
            return policies::raise_overflow_error<T>("boost::math::expm1<%1%>(%1%)", 0, pol);
         return -1;
      }
      return exp(x) - T(1);
   }
   if(a < tools::epsilon<T>())
      return x;

   static const float Y = 0.10281276702880859375e1f;
   static const T n[] = { 
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.28127670288085937499999999999999999854e-1),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.51278156911210477556524452177540792214e0),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.63263178520747096729500254678819588223e-1),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.14703285606874250425508446801230572252e-1),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.8675686051689527802425310407898459386e-3),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.88126359618291165384647080266133492399e-4),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.25963087867706310844432390015463138953e-5),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.14226691087800461778631773363204081194e-6),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.15995603306536496772374181066765665596e-8),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.45261820069007790520447958280473183582e-10)
   };
   static const T d[] = { 
      BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.45441264709074310514348137469214538853e0),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.96827131936192217313133611655555298106e-1),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.12745248725908178612540554584374876219e-1),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.11473613871583259821612766907781095472e-2),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.73704168477258911962046591907690764416e-4),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.34087499397791555759285503797256103259e-5),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.11114024704296196166272091230695179724e-6),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.23987051614110848595909588343223896577e-8),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.29477341859111589208776402638429026517e-10),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.13222065991022301420255904060628100924e-12)
   };

   T result = x * Y + x * tools::evaluate_polynomial(n, x) / tools::evaluate_polynomial(d, x);
   return result;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type expm1(T x, const Policy& /* pol */)
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
      precision_type::value <= 64 ? 64 :
      precision_type::value <= 113 ? 113 : 0
   > tag_type;

   detail::expm1_initializer<value_type, forwarding_policy, tag_type>::force_instantiate();
   
   return policies::checked_narrowing_cast<result_type, forwarding_policy>(detail::expm1_imp(
      static_cast<value_type>(x),
      tag_type(), forwarding_policy()), "boost::math::expm1<%1%>(%1%)");
}

#ifdef expm1
#  ifndef BOOST_HAS_expm1
#     define BOOST_HAS_expm1
#  endif
#  undef expm1
#endif

#if defined(BOOST_HAS_EXPM1) && !(defined(__osf__) && defined(__DECCXX_VER))
#  ifdef BOOST_MATH_USE_C99
inline float expm1(float x, const policies::policy<>&){ return ::expm1f(x); }
#     ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline long double expm1(long double x, const policies::policy<>&){ return ::expm1l(x); }
#     endif
#  else
inline float expm1(float x, const policies::policy<>&){ return static_cast<float>(::expm1(x)); }
#  endif
inline double expm1(double x, const policies::policy<>&){ return ::expm1(x); }
#endif

template <class T>
inline typename tools::promote_args<T>::type expm1(T x)
{
   return expm1(x, policies::policy<>());
}

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
inline float expm1(float z)
{
   return expm1<float>(z);
}
inline double expm1(double z)
{
   return expm1<double>(z);
}
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline long double expm1(long double z)
{
   return expm1<long double>(z);
}
#endif
#endif

} // namespace math
} // namespace boost

#endif // BOOST_MATH_HYPOT_INCLUDED





/* expm1.hpp
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
*/