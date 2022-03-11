//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JY_DERIVATIVES_SERIES_HPP
#define BOOST_MATH_BESSEL_JY_DERIVATIVES_SERIES_HPP

#ifdef _MSC_VER
#pragma once
#endif

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
   boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
   boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   boost::math::policies::check_series_iterations<T>("boost::math::bessel_y_derivative_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   result *= prefix;

   p = pow(x / 2, v - 1) / 2;
   if (!need_logs)
   {
      prefix = boost::math::tgamma(-v, pol) * boost::math::cos_pi(v) * p / boost::math::constants::pi<T>();
   }
   else
   {
      int sgn;
      prefix = boost::math::lgamma(-v, &sgn, pol) + (v - 1) * log(x / 2) - constants::ln_two<T>();
      prefix = exp(prefix) * sgn / boost::math::constants::pi<T>();
   }
   bessel_y_derivative_small_z_series_term_b<T, Policy> s2(v, x);
   max_iter = boost::math::policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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