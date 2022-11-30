//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_EXPM1_INCLUDED
#define BOOST_MATH_EXPM1_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <cstdint>
#include <limits>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/assert.hpp>

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
      static void do_init(const std::integral_constant<int, N>&){}
      static void do_init(const std::integral_constant<int, 64>&)
      {
         expm1(T(0.5));
      }
      static void do_init(const std::integral_constant<int, 113>&)
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
T expm1_imp(T x, const std::integral_constant<int, 0>&, const Policy& pol)
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
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

   T result = tools::sum_series(s, policies::get_epsilon<T, Policy>(), max_iter);

   policies::check_series_iterations<T>("boost::math::expm1<%1%>(%1%)", max_iter, pol);
   return result;
}

template <class T, class P>
T expm1_imp(T x, const std::integral_constant<int, 53>&, const P& pol)
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
T expm1_imp(T x, const std::integral_constant<int, 64>&, const P& pol)
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
T expm1_imp(T x, const std::integral_constant<int, 113>&, const P& pol)
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

   typedef std::integral_constant<int,
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

} // namespace math
} // namespace boost

#endif // BOOST_MATH_HYPOT_INCLUDED





/* expm1.hpp
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
*/