//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JN_SERIES_HPP
#define BOOST_MATH_BESSEL_JN_SERIES_HPP

#ifdef _MSC_VER
#pragma once
#endif

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
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
   *pscale = scale;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   policies::check_series_iterations<T>("boost::math::bessel_y_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   result *= prefix;

   if(!need_logs)
   {
      prefix = boost::math::tgamma(-v, pol) * boost::math::cos_pi(v) * p / constants::pi<T>();
   }
   else
   {
      int sgn;
      prefix = boost::math::lgamma(-v, &sgn, pol) + p;
      prefix = exp(prefix) * sgn / constants::pi<T>();
   }
   bessel_y_small_z_series_term_b<T, Policy> s2(v, x);
   max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
   BOOST_ASSERT(n >= 0);
   BOOST_ASSERT((z < policies::get_epsilon<T, Policy>()));

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
      T result = -((boost::math::factorial<T>(n - 1) / constants::pi<T>()));
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