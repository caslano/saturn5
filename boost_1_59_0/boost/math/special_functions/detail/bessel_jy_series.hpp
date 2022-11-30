//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JN_SERIES_HPP
#define BOOST_MATH_BESSEL_JN_SERIES_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <cstdint>

namespace boost { namespace math { namespace detail{

template <class T, class Policy>
struct bessel_j_small_z_series_term
{
   typedef T result_type;

   bessel_j_small_z_series_term(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};
//
// Series evaluation for BesselJ(v, z) as z -> 0.
// See http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01/0003/
// Converges rapidly for all z << v.
//
template <class T, class Policy>
inline T bessel_j_small_z_series(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T prefix;
   if(v < max_factorial<T>::value)
   {
      prefix = pow(x / 2, v) / boost::math::tgamma(v+1, pol);
   }
   else
   {
      prefix = v * log(x / 2) - boost::math::lgamma(v+1, pol);
      prefix = exp(prefix);
   }
   if(0 == prefix)
      return prefix;

   bessel_j_small_z_series_term<T, Policy> s(v, x);
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   policies::check_series_iterations<T>("boost::math::bessel_j_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   return prefix * result;
}

template <class T, class Policy>
struct bessel_y_small_z_series_term_a
{
   typedef T result_type;

   bessel_y_small_z_series_term_a(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      BOOST_MATH_STD_USING
      T r = term;
      ++N;
      term *= mult / (N * (N - v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};

template <class T, class Policy>
struct bessel_y_small_z_series_term_b
{
   typedef T result_type;

   bessel_y_small_z_series_term_b(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};
//
// Series form for BesselY as z -> 0, 
// see: http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/01/0003/
// This series is only useful when the second term is small compared to the first
// otherwise we get catastrophic cancellation errors.
//
// Approximating tgamma(v) by v^v, and assuming |tgamma(-z)| < eps we end up requiring:
// eps/2 * v^v(x/2)^-v > (x/2)^v or log(eps/2) > v log((x/2)^2/v)
//
template <class T, class Policy>
inline T bessel_y_small_z_series(T v, T x, T* pscale, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "bessel_y_small_z_series<%1%>(%1%,%1%)";
   T prefix;
   T gam;
   T p = log(x / 2);
   T scale = 1;
   bool need_logs = (v >= max_factorial<T>::value) || (tools::log_max_value<T>() / v < fabs(p));
   if(!need_logs)
   {
      gam = boost::math::tgamma(v, pol);
      p = pow(x / 2, v);
      if(tools::max_value<T>() * p < gam)
      {
         scale /= gam;
         gam = 1;
         if(tools::max_value<T>() * p < gam)
         {
            return -policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -gam / (constants::pi<T>() * p);
   }
   else
   {
      gam = boost::math::lgamma(v, pol);
      p = v * p;
      prefix = gam - log(constants::pi<T>()) - p;
      if(tools::log_max_value<T>() < prefix)
      {
         prefix -= log(tools::max_value<T>() / 4);
         scale /= (tools::max_value<T>() / 4);
         if(tools::log_max_value<T>() < prefix)
         {
            return -policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -exp(prefix);
   }
   bessel_y_small_z_series_term_a<T, Policy> s(v, x);
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
   *pscale = scale;

   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   policies::check_series_iterations<T>("boost::math::bessel_y_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   result *= prefix;

   if(!need_logs)
   {
      prefix = boost::math::tgamma(-v, pol) * boost::math::cos_pi(v, pol) * p / constants::pi<T>();
   }
   else
   {
      int sgn;
      prefix = boost::math::lgamma(-v, &sgn, pol) + p;
      prefix = exp(prefix) * sgn / constants::pi<T>();
   }
   bessel_y_small_z_series_term_b<T, Policy> s2(v, x);
   max_iter = policies::get_max_series_iterations<Policy>();

   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   result -= scale * prefix * b;
   return result;
}

template <class T, class Policy>
T bessel_yn_small_z(int n, T z, T* scale, const Policy& pol)
{
   //
   // See http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/02/
   //
   // Note that when called we assume that x < epsilon and n is a positive integer.
   //
   BOOST_MATH_STD_USING
   BOOST_MATH_ASSERT(n >= 0);
   BOOST_MATH_ASSERT((z < policies::get_epsilon<T, Policy>()));

   if(n == 0)
   {
      return (2 / constants::pi<T>()) * (log(z / 2) +  constants::euler<T>());
   }
   else if(n == 1)
   {
      return (z / constants::pi<T>()) * log(z / 2) 
         - 2 / (constants::pi<T>() * z) 
         - (z / (2 * constants::pi<T>())) * (1 - 2 * constants::euler<T>());
   }
   else if(n == 2)
   {
      return (z * z) / (4 * constants::pi<T>()) * log(z / 2) 
         - (4 / (constants::pi<T>() * z * z)) 
         - ((z * z) / (8 * constants::pi<T>())) * (T(3)/2 - 2 * constants::euler<T>());
   }
   else
   {
      T p = pow(z / 2, n);
      T result = -((boost::math::factorial<T>(n - 1, pol) / constants::pi<T>()));
      if(p * tools::max_value<T>() < result)
      {
         T div = tools::max_value<T>() / 8;
         result /= div;
         *scale /= div;
         if(p * tools::max_value<T>() < result)
         {
            return -policies::raise_overflow_error<T>("bessel_yn_small_z<%1%>(%1%,%1%)", 0, pol);
         }
      }
      return result / p;
   }
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_JN_SERIES_HPP


/* bessel_jy_series.hpp
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
*/