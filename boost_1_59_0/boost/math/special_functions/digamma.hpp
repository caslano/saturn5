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
inline unsigned digamma_large_lim(const std::integral_constant<int, 0>*)
{  return 20;  }
inline unsigned digamma_large_lim(const std::integral_constant<int, 113>*)
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
inline T digamma_imp_large(T x, const std::integral_constant<int, 113>*)
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
inline T digamma_imp_large(T x, const std::integral_constant<int, 64>*)
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
inline T digamma_imp_large(T x, const std::integral_constant<int, 53>*)
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
inline T digamma_imp_large(T x, const std::integral_constant<int, 24>*)
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
inline T digamma_imp_large(T x, const Policy& pol, const std::integral_constant<int, 0>*)
{
   BOOST_MATH_STD_USING
   digamma_series_func<T> s(x);
   T result = log(x) - 1 / (2 * x);
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
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
T digamma_imp_1_2(T x, const std::integral_constant<int, 113>*)
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
T digamma_imp_1_2(T x, const std::integral_constant<int, 64>*)
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
T digamma_imp_1_2(T x, const std::integral_constant<int, 53>*)
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
inline T digamma_imp_1_2(T x, const std::integral_constant<int, 24>*)
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
T digamma_imp(T x, const std::integral_constant<int, 0>* t, const Policy& pol)
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
         do_init(std::integral_constant<bool, precision_type::value && (precision_type::value <= 113)>());
      }
      void do_init(const std::true_type&)
      {
         boost::math::digamma(T(1.5), Policy());
         boost::math::digamma(T(500), Policy());
      }
      void do_init(const std::false_type&){}
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
   typedef std::integral_constant<int,
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