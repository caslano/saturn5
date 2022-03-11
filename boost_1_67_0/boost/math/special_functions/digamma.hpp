//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_DIGAMMA_HPP
#define BOOST_MATH_SF_DIGAMMA_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/series.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/math/tools/big_constant.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

namespace boost{
namespace math{
namespace detail{
//
// Begin by defining the smallest value for which it is safe to
// use the asymptotic expansion for digamma:
//
inline unsigned digamma_large_lim(const boost::integral_constant<int, 0>*)
{  return 20;  }
inline unsigned digamma_large_lim(const boost::integral_constant<int, 113>*)
{  return 20;  }
inline unsigned digamma_large_lim(const void*)
{  return 10;  }
//
// Implementations of the asymptotic expansion come next,
// the coefficients of the series have been evaluated
// in advance at high precision, and the series truncated
// at the first term that's too small to effect the result.
// Note that the series becomes divergent after a while
// so truncation is very important.
//
// This first one gives 34-digit precision for x >= 20:
//
template <class T>
inline T digamma_imp_large(T x, const boost::integral_constant<int, 113>*)
{
   BOOST_MATH_STD_USING // ADL of std functions.
   static const T P[] = {
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.0083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.003968253968253968253968253968253968253968253968254),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.0041666666666666666666666666666666666666666666666667),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.0075757575757575757575757575757575757575757575757576),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.021092796092796092796092796092796092796092796092796),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.44325980392156862745098039215686274509803921568627),
      BOOST_MATH_BIG_CONSTANT(T, 113, 3.0539543302701197438039543302701197438039543302701),
      BOOST_MATH_BIG_CONSTANT(T, 113, -26.456212121212121212121212121212121212121212121212),
      BOOST_MATH_BIG_CONSTANT(T, 113, 281.4601449275362318840579710144927536231884057971),
      BOOST_MATH_BIG_CONSTANT(T, 113, -3607.510546398046398046398046398046398046398046398),
      BOOST_MATH_BIG_CONSTANT(T, 113, 54827.583333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 113, -974936.82385057471264367816091954022988505747126437),
      BOOST_MATH_BIG_CONSTANT(T, 113, 20052695.796688078946143462272494530559046688078946),
      BOOST_MATH_BIG_CONSTANT(T, 113, -472384867.72162990196078431372549019607843137254902),
      BOOST_MATH_BIG_CONSTANT(T, 113, 12635724795.916666666666666666666666666666666666667)
   };
   x -= 1;
   T result = log(x);
   result += 1 / (2 * x);
   T z = 1 / (x*x);
   result -= z * tools::evaluate_polynomial(P, z);
   return result;
}
//
// 19-digit precision for x >= 10:
//
template <class T>
inline T digamma_imp_large(T x, const boost::integral_constant<int, 64>*)
{
   BOOST_MATH_STD_USING // ADL of std functions.
   static const T P[] = {
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.0083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.003968253968253968253968253968253968253968253968254),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.0041666666666666666666666666666666666666666666666667),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.0075757575757575757575757575757575757575757575757576),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.021092796092796092796092796092796092796092796092796),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.44325980392156862745098039215686274509803921568627),
      BOOST_MATH_BIG_CONSTANT(T, 64, 3.0539543302701197438039543302701197438039543302701),
      BOOST_MATH_BIG_CONSTANT(T, 64, -26.456212121212121212121212121212121212121212121212),
      BOOST_MATH_BIG_CONSTANT(T, 64, 281.4601449275362318840579710144927536231884057971),
   };
   x -= 1;
   T result = log(x);
   result += 1 / (2 * x);
   T z = 1 / (x*x);
   result -= z * tools::evaluate_polynomial(P, z);
   return result;
}
//
// 17-digit precision for x >= 10:
//
template <class T>
inline T digamma_imp_large(T x, const boost::integral_constant<int, 53>*)
{
   BOOST_MATH_STD_USING // ADL of std functions.
   static const T P[] = {
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.0083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.003968253968253968253968253968253968253968253968254),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.0041666666666666666666666666666666666666666666666667),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.0075757575757575757575757575757575757575757575757576),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.021092796092796092796092796092796092796092796092796),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.44325980392156862745098039215686274509803921568627)
   };
   x -= 1;
   T result = log(x);
   result += 1 / (2 * x);
   T z = 1 / (x*x);
   result -= z * tools::evaluate_polynomial(P, z);
   return result;
}
//
// 9-digit precision for x >= 10:
//
template <class T>
inline T digamma_imp_large(T x, const boost::integral_constant<int, 24>*)
{
   BOOST_MATH_STD_USING // ADL of std functions.
   static const T P[] = {
      BOOST_MATH_BIG_CONSTANT(T, 24, 0.083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 24, -0.0083333333333333333333333333333333333333333333333333),
      BOOST_MATH_BIG_CONSTANT(T, 24, 0.003968253968253968253968253968253968253968253968254)
   };
   x -= 1;
   T result = log(x);
   result += 1 / (2 * x);
   T z = 1 / (x*x);
   result -= z * tools::evaluate_polynomial(P, z);
   return result;
}
//
// Fully generic asymptotic expansion in terms of Bernoulli numbers, see:
// http://functions.wolfram.com/06.14.06.0012.01
//
template <class T>
struct digamma_series_func
{
private:
   int k;
   T xx;
   T term;
public:
   digamma_series_func(T x) : k(1), xx(x * x), term(1 / (x * x)) {}
   T operator()()
   {
      T result = term * boost::math::bernoulli_b2n<T>(k) / (2 * k);
      term /= xx;
      ++k;
      return result;
   }
   typedef T result_type;
};

template <class T, class Policy>
inline T digamma_imp_large(T x, const Policy& pol, const boost::integral_constant<int, 0>*)
{
   BOOST_MATH_STD_USING
   digamma_series_func<T> s(x);
   T result = log(x) - 1 / (2 * x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
   result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, -result);
   result = -result;
   policies::check_series_iterations<T>("boost::math::digamma<%1%>(%1%)", max_iter, pol);
   return result;
}
//
// Now follow rational approximations over the range [1,2].
//
// 35-digit precision:
//
template <class T>
T digamma_imp_1_2(T x, const boost::integral_constant<int, 113>*)
{
   //
   // Now the approximation, we use the form:
   //
   // digamma(x) = (x - root) * (Y + R(x-1))
   //
   // Where root is the location of the positive root of digamma,
   // Y is a constant, and R is optimised for low absolute error
   // compared to Y.
   //
   // Max error found at 128-bit long double precision:  5.541e-35
   // Maximum Deviation Found (approximation error):     1.965e-35
   //
   static const float Y = 0.99558162689208984375F;

   static const T root1 = T(1569415565) / 1073741824uL;
   static const T root2 = (T(381566830) / 1073741824uL) / 1073741824uL;
   static const T root3 = ((T(111616537) / 1073741824uL) / 1073741824uL) / 1073741824uL;
   static const T root4 = (((T(503992070) / 1073741824uL) / 1073741824uL) / 1073741824uL) / 1073741824uL;
   static const T root5 = BOOST_MATH_BIG_CONSTANT(T, 113, 0.52112228569249997894452490385577338504019838794544e-36);

   static const T P[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.25479851061131551526977464225335883769),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.18684290534374944114622235683619897417),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.80360876047931768958995775910991929922),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.67227342794829064330498117008564270136),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.26569010991230617151285010695543858005),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.05775672694575986971640757748003553385),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.0071432147823164975485922555833274240665),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.00048740753910766168912364555706064993274),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.16454996865214115723416538844975174761e-4),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.20327832297631728077731148515093164955e-6)
   };
   static const T Q[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 113, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 113, 2.6210924610812025425088411043163287646),
      BOOST_MATH_BIG_CONSTANT(T, 113, 2.6850757078559596612621337395886392594),
      BOOST_MATH_BIG_CONSTANT(T, 113, 1.4320913706209965531250495490639289418),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.4410872083455009362557012239501953402),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.081385727399251729505165509278152487225),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.0089478633066857163432104815183858149496),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.00055861622855066424871506755481997374154),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.1760168552357342401304462967950178554e-4),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.20585454493572473724556649516040874384e-6),
      BOOST_MATH_BIG_CONSTANT(T, 113, -0.90745971844439990284514121823069162795e-11),
      BOOST_MATH_BIG_CONSTANT(T, 113, 0.48857673606545846774761343500033283272e-13),
   };
   T g = x - root1;
   g -= root2;
   g -= root3;
   g -= root4;
   g -= root5;
   T r = tools::evaluate_polynomial(P, T(x-1)) / tools::evaluate_polynomial(Q, T(x-1));
   T result = g * Y + g * r;

   return result;
}
//
// 19-digit precision:
//
template <class T>
T digamma_imp_1_2(T x, const boost::integral_constant<int, 64>*)
{
   //
   // Now the approximation, we use the form:
   //
   // digamma(x) = (x - root) * (Y + R(x-1))
   //
   // Where root is the location of the positive root of digamma,
   // Y is a constant, and R is optimised for low absolute error
   // compared to Y.
   //
   // Max error found at 80-bit long double precision:   5.016e-20
   // Maximum Deviation Found (approximation error):     3.575e-20
   //
   static const float Y = 0.99558162689208984375F;

   static const T root1 = T(1569415565) / 1073741824uL;
   static const T root2 = (T(381566830) / 1073741824uL) / 1073741824uL;
   static const T root3 = BOOST_MATH_BIG_CONSTANT(T, 64, 0.9016312093258695918615325266959189453125e-19);

   static const T P[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.254798510611315515235),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.314628554532916496608),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.665836341559876230295),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.314767657147375752913),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.0541156266153505273939),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.00289268368333918761452)
   };
   static const T Q[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 64, 2.1195759927055347547),
      BOOST_MATH_BIG_CONSTANT(T, 64, 1.54350554664961128724),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.486986018231042975162),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.0660481487173569812846),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.00298999662592323990972),
      BOOST_MATH_BIG_CONSTANT(T, 64, -0.165079794012604905639e-5),
      BOOST_MATH_BIG_CONSTANT(T, 64, 0.317940243105952177571e-7)
   };
   T g = x - root1;
   g -= root2;
   g -= root3;
   T r = tools::evaluate_polynomial(P, T(x-1)) / tools::evaluate_polynomial(Q, T(x-1));
   T result = g * Y + g * r;

   return result;
}
//
// 18-digit precision:
//
template <class T>
T digamma_imp_1_2(T x, const boost::integral_constant<int, 53>*)
{
   //
   // Now the approximation, we use the form:
   //
   // digamma(x) = (x - root) * (Y + R(x-1))
   //
   // Where root is the location of the positive root of digamma,
   // Y is a constant, and R is optimised for low absolute error
   // compared to Y.
   //
   // Maximum Deviation Found:               1.466e-18
   // At double precision, max error found:  2.452e-17
   //
   static const float Y = 0.99558162689208984F;

   static const T root1 = T(1569415565) / 1073741824uL;
   static const T root2 = (T(381566830) / 1073741824uL) / 1073741824uL;
   static const T root3 = BOOST_MATH_BIG_CONSTANT(T, 53, 0.9016312093258695918615325266959189453125e-19);

   static const T P[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.25479851061131551),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.32555031186804491),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.65031853770896507),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.28919126444774784),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.045251321448739056),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.0020713321167745952)
   };
   static const T Q[] = {    
      BOOST_MATH_BIG_CONSTANT(T, 53, 1.0),
      BOOST_MATH_BIG_CONSTANT(T, 53, 2.0767117023730469),
      BOOST_MATH_BIG_CONSTANT(T, 53, 1.4606242909763515),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.43593529692665969),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.054151797245674225),
      BOOST_MATH_BIG_CONSTANT(T, 53, 0.0021284987017821144),
      BOOST_MATH_BIG_CONSTANT(T, 53, -0.55789841321675513e-6)
   };
   T g = x - root1;
   g -= root2;
   g -= root3;
   T r = tools::evaluate_polynomial(P, T(x-1)) / tools::evaluate_polynomial(Q, T(x-1));
   T result = g * Y + g * r;

   return result;
}
//
// 9-digit precision:
//
template <class T>
inline T digamma_imp_1_2(T x, const boost::integral_constant<int, 24>*)
{
   //
   // Now the approximation, we use the form:
   //
   // digamma(x) = (x - root) * (Y + R(x-1))
   //
   // Where root is the location of the positive root of digamma,
   // Y is a constant, and R is optimised for low absolute error
   // compared to Y.
   //
   // Maximum Deviation Found:              3.388e-010
   // At float precision, max error found:  2.008725e-008
   //
   static const float Y = 0.99558162689208984f;
   static const T root = 1532632.0f / 1048576;
   static const T root_minor = static_cast<T>(0.3700660185912626595423257213284682051735604e-6L);
   static const T P[] = {    
      0.25479851023250261e0f,
      -0.44981331915268368e0f,
      -0.43916936919946835e0f,
      -0.61041765350579073e-1f
   };
   static const T Q[] = {    
      0.1e1,
      0.15890202430554952e1f,
      0.65341249856146947e0f,
      0.63851690523355715e-1f
   };
   T g = x - root;
   g -= root_minor;
   T r = tools::evaluate_polynomial(P, T(x-1)) / tools::evaluate_polynomial(Q, T(x-1));
   T result = g * Y + g * r;

   return result;
}

template <class T, class Tag, class Policy>
T digamma_imp(T x, const Tag* t, const Policy& pol)
{
   //
   // This handles reflection of negative arguments, and all our
   // error handling, then forwards to the T-specific approximation.
   //
   BOOST_MATH_STD_USING // ADL of std functions.

   T result = 0;
   //
   // Check for negative arguments and use reflection:
   //
   if(x <= -1)
   {
      // Reflect:
      x = 1 - x;
      // Argument reduction for tan:
      T remainder = x - floor(x);
      // Shift to negative if > 0.5:
      if(remainder > 0.5)
      {
         remainder -= 1;
      }
      //
      // check for evaluation at a negative pole:
      //
      if(remainder == 0)
      {
         return policies::raise_pole_error<T>("boost::math::digamma<%1%>(%1%)", 0, (1-x), pol);
      }
      result = constants::pi<T>() / tan(constants::pi<T>() * remainder);
   }
   if(x == 0)
      return policies::raise_pole_error<T>("boost::math::digamma<%1%>(%1%)", 0, x, pol);
   //
   // If we're above the lower-limit for the
   // asymptotic expansion then use it:
   //
   if(x >= digamma_large_lim(t))
   {
      result += digamma_imp_large(x, t);
   }
   else
   {
      //
      // If x > 2 reduce to the interval [1,2]:
      //
      while(x > 2)
      {
         x -= 1;
         result += 1/x;
      }
      //
      // If x < 1 use recurrence to shift to > 1:
      //
      while(x < 1)
      {
         result -= 1/x;
         x += 1;
      }
      result += digamma_imp_1_2(x, t);
   }
   return result;
}

template <class T, class Policy>
T digamma_imp(T x, const boost::integral_constant<int, 0>* t, const Policy& pol)
{
   //
   // This handles reflection of negative arguments, and all our
   // error handling, then forwards to the T-specific approximation.
   //
   BOOST_MATH_STD_USING // ADL of std functions.

   T result = 0;
   //
   // Check for negative arguments and use reflection:
   //
   if(x <= -1)
   {
      // Reflect:
      x = 1 - x;
      // Argument reduction for tan:
      T remainder = x - floor(x);
      // Shift to negative if > 0.5:
      if(remainder > 0.5)
      {
         remainder -= 1;
      }
      //
      // check for evaluation at a negative pole:
      //
      if(remainder == 0)
      {
         return policies::raise_pole_error<T>("boost::math::digamma<%1%>(%1%)", 0, (1 - x), pol);
      }
      result = constants::pi<T>() / tan(constants::pi<T>() * remainder);
   }
   if(x == 0)
      return policies::raise_pole_error<T>("boost::math::digamma<%1%>(%1%)", 0, x, pol);
   //
   // If we're above the lower-limit for the
   // asymptotic expansion then use it, the
   // limit is a linear interpolation with
   // limit = 10 at 50 bit precision and
   // limit = 250 at 1000 bit precision.
   //
   int lim = 10 + ((tools::digits<T>() - 50) * 240L) / 950;
   T two_x = ldexp(x, 1);
   if(x >= lim)
   {
      result += digamma_imp_large(x, pol, t);
   }
   else if(floor(x) == x)
   {
      //
      // Special case for integer arguments, see
      // http://functions.wolfram.com/06.14.03.0001.01
      //
      result = -constants::euler<T, Policy>();
      T val = 1;
      while(val < x)
      {
         result += 1 / val;
         val += 1;
      }
   }
   else if(floor(two_x) == two_x)
   {
      //
      // Special case for half integer arguments, see:
      // http://functions.wolfram.com/06.14.03.0007.01
      //
      result = -2 * constants::ln_two<T, Policy>() - constants::euler<T, Policy>();
      int n = itrunc(x);
      if(n)
      {
         for(int k = 1; k < n; ++k)
            result += 1 / T(k);
         for(int k = n; k <= 2 * n - 1; ++k)
            result += 2 / T(k);
      }
   }
   else
   {
      //
      // Rescale so we can use the asymptotic expansion:
      //
      while(x < lim)
      {
         result -= 1 / x;
         x += 1;
      }
      result += digamma_imp_large(x, pol, t);
   }
   return result;
}
//
// Initializer: ensure all our constants are initialized prior to the first call of main:
//
template <class T, class Policy>
struct digamma_initializer
{
   struct init
   {
      init()
      {
         typedef typename policies::precision<T, Policy>::type precision_type;
         do_init(boost::integral_constant<bool, precision_type::value && (precision_type::value <= 113)>());
      }
      void do_init(const boost::true_type&)
      {
         boost::math::digamma(T(1.5), Policy());
         boost::math::digamma(T(500), Policy());
      }
      void do_init(const false_type&){}
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy>
const typename digamma_initializer<T, Policy>::init digamma_initializer<T, Policy>::initializer;

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   digamma(T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::precision<T, Policy>::type precision_type;
   typedef boost::integral_constant<int,
      (precision_type::value <= 0) || (precision_type::value > 113) ? 0 :
      precision_type::value <= 24 ? 24 :
      precision_type::value <= 53 ? 53 :
      precision_type::value <= 64 ? 64 :
      precision_type::value <= 113 ? 113 : 0 > tag_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   // Force initialization of constants:
   detail::digamma_initializer<value_type, forwarding_policy>::force_instantiate();

   return policies::checked_narrowing_cast<result_type, Policy>(detail::digamma_imp(
      static_cast<value_type>(x),
      static_cast<const tag_type*>(0), forwarding_policy()), "boost::math::digamma<%1%>(%1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   digamma(T x)
{
   return digamma(x, policies::policy<>());
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif


/* digamma.hpp
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
*/