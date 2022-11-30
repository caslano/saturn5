//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JY_DERIVATIVES_SERIES_HPP
#define BOOST_MATH_BESSEL_JY_DERIVATIVES_SERIES_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <cstdint>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
struct bessel_j_derivative_small_z_series_term
{
   typedef T result_type;

   bessel_j_derivative_small_z_series_term(T v_, T x)
      : N(0), v(v_), term(1), mult(x / 2)
   {
      mult *= -mult;
      // iterate if v == 0; otherwise result of
      // first term is 0 and tools::sum_series stops
      if (v == 0)
         iterate();
   }
   T operator()()
   {
      T r = term * (v + 2 * N);
      iterate();
      return r;
   }
private:
   void iterate()
   {
      ++N;
      term *= mult / (N * (N + v));
   }
   unsigned N;
   T v;
   T term;
   T mult;
};
//
// Series evaluation for BesselJ'(v, z) as z -> 0.
// It's derivative of http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01/0003/
// Converges rapidly for all z << v.
//
template <class T, class Policy>
inline T bessel_j_derivative_small_z_series(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T prefix;
   if (v < boost::math::max_factorial<T>::value)
   {
      prefix = pow(x / 2, v - 1) / 2 / boost::math::tgamma(v + 1, pol);
   }
   else
   {
      prefix = (v - 1) * log(x / 2) - constants::ln_two<T>() - boost::math::lgamma(v + 1, pol);
      prefix = exp(prefix);
   }
   if (0 == prefix)
      return prefix;

   bessel_j_derivative_small_z_series_term<T, Policy> s(v, x);
   std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();

   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   boost::math::policies::check_series_iterations<T>("boost::math::bessel_j_derivative_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   return prefix * result;
}

template <class T, class Policy>
struct bessel_y_derivative_small_z_series_term_a
{
   typedef T result_type;

   bessel_y_derivative_small_z_series_term_a(T v_, T x)
      : N(0), v(v_)
   {
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term * (-v + 2 * N);
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
struct bessel_y_derivative_small_z_series_term_b
{
   typedef T result_type;

   bessel_y_derivative_small_z_series_term_b(T v_, T x)
      : N(0), v(v_)
   {
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term * (v + 2 * N);
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
// Series form for BesselY' as z -> 0,
// It's derivative of http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/01/0003/
// This series is only useful when the second term is small compared to the first
// otherwise we get catastrophic cancellation errors.
//
// Approximating tgamma(v) by v^v, and assuming |tgamma(-z)| < eps we end up requiring:
// eps/2 * v^v(x/2)^-v > (x/2)^v or log(eps/2) > v log((x/2)^2/v)
//
template <class T, class Policy>
inline T bessel_y_derivative_small_z_series(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "bessel_y_derivative_small_z_series<%1%>(%1%,%1%)";
   T prefix;
   T gam;
   T p = log(x / 2);
   T scale = 1;
   bool need_logs = (v >= boost::math::max_factorial<T>::value) || (boost::math::tools::log_max_value<T>() / v < fabs(p));
   if (!need_logs)
   {
      gam = boost::math::tgamma(v, pol);
      p = pow(x / 2, v + 1) * 2;
      if (boost::math::tools::max_value<T>() * p < gam)
      {
         scale /= gam;
         gam = 1;
         if (boost::math::tools::max_value<T>() * p < gam)
         {
            // This term will overflow to -INF, when combined with the series below it becomes +INF:
            return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -gam / (boost::math::constants::pi<T>() * p);
   }
   else
   {
      gam = boost::math::lgamma(v, pol);
      p = (v + 1) * p + constants::ln_two<T>();
      prefix = gam - log(boost::math::constants::pi<T>()) - p;
      if (boost::math::tools::log_max_value<T>() < prefix)
      {
         prefix -= log(boost::math::tools::max_value<T>() / 4);
         scale /= (boost::math::tools::max_value<T>() / 4);
         if (boost::math::tools::log_max_value<T>() < prefix)
         {
            return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -exp(prefix);
   }
   bessel_y_derivative_small_z_series_term_a<T, Policy> s(v, x);
   std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();

   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   boost::math::policies::check_series_iterations<T>("boost::math::bessel_y_derivative_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   result *= prefix;

   p = pow(x / 2, v - 1) / 2;
   if (!need_logs)
   {
      prefix = boost::math::tgamma(-v, pol) * boost::math::cos_pi(v, pol) * p / boost::math::constants::pi<T>();
   }
   else
   {
      int sgn;
      prefix = boost::math::lgamma(-v, &sgn, pol) + (v - 1) * log(x / 2) - constants::ln_two<T>();
      prefix = exp(prefix) * sgn / boost::math::constants::pi<T>();
   }
   bessel_y_derivative_small_z_series_term_b<T, Policy> s2(v, x);
   max_iter = boost::math::policies::get_max_series_iterations<Policy>();

   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   result += scale * prefix * b;
   return result;
}

// Calculating of BesselY'(v,x) with small x (x < epsilon) and integer x using derivatives
// of formulas in http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/02/
// seems to lose precision. Instead using linear combination of regular Bessel is preferred.

}}} // namespaces

#endif // BOOST_MATH_BESSEL_JY_DERIVATVIES_SERIES_HPP

/* bessel_jy_derivatives_series.hpp
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
*/