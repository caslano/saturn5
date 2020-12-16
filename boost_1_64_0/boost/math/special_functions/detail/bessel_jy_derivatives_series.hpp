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
10aK9Be5nUhR/p8o/ro0+c2bIjXQwyfsRor+u+MOpKhP+WJIIccu8kN6orkDKfTkweTHPr0TKeR1f7KrS1B/P5765+1IkV79ztuQovznGaSQ13vJ/y8CNyj/iigH6T9/SX7nyhciRb92kRr8fkODFHrxY4rf7gy+gb7cmfzuTS6OFO05g/og/ebDdyCFnBapPlNk55ckv31DpEgv8YsdSJHvIdLbW9H86jsGKfK/Efntn+xGivZTfPDCgxdHivwfR/V6zQVI0Y9r1E93IH17KfmzO+JvpJWb0rh9e7I/iit/kyc7oHH0m4+k+dvUDqTQk4uRnlwdqYE+3fziSCH3a1CcftsLkaLfP0X+5RSN33chv5ehuPhmF0cKeb6H7OLD1M7fkN+6GenTmw1S6MPzSb6fpzjiH1Te5civLtA85Emkf5mLI0V6H7IXss/3/203UvT723aR/iFF+vvfU3vfQnFldidStPsjVO7nKB74HMXBt8XfBtgPKZ7+0AVI0c5dNJ5dk+p3swuRQq5v3IEUclrfhhR+q0/+9V3k5yapX8guT3/0AqQov0bxbY3G3W0GKdIaxY+bZA/TFLfR+Pr2pYshhT70aJwokb/6KMnrYXge6aWhJ4WVSqtQiqJCudQCzVzbXBLWaEwWsQzQg/OzewrzhxfuOeQt10orTdNKOLkQp9qqrBnTuj5xJkMcUKJaqVUBfg3i5V3eeuWsQdOTfDou3gzXO59TvOm7nZiePTxdODh7EvXisooBjsYjC19IHjdJXYo4d8n4wtzM7J0KCwcPHZ0ulMplg39uTLx+Gm+pVimtb0QGLiHJM3PjFC7kZVClhDdY9nhxbo3CcqMCeUbchhWftxaZRoJnVn28Hp0XGfh4LGnGNwM4WmQ4/6qHxzVkGUY+jpbmku6MEhl2fbnEGlSuLJc2aq3CWql5ivt+08+zVllfaa3C5JNy22mcWKGgb0n9Oz4PGql0/1IeHjWq68jCVBLO1pXCnELlnOH+TOcUliOpz8CvDypsWgneu38Iz3E5PcjRxwuL5wuzM1NoN8kbZzp9nivvmyfy/u/cQqm5xP2TubLHb9ULJxaOHDAbSTvMKZ9zPqpIHmE87hzRA2W/C/v3aPVjTjvIgZUrX9IJclCS8ltdzTl0/PjR6YOz2pdkb3ERwWeOxT7i/gY6kuCTOQdfWq0snTJihy5eri4vq+ejPTZOzTRXSdrp4LpuHRdD04xqW8/BScPFxidsHL1vyS8XwAvNFjJZER/pcKARMPD1SqNUqz6gUm5V1ypc3tY+xT2Zh6zg0ZQseugLhZMsBM/d0nkensQAT/Q50/NwjGewxfpSq9Kiimv/7vNd7kpSdt+tG2Rt1DiZd+sWlZZOQWCnNyrrSxXJx+x3eJCplkE+gO9RbSx+yMXHt3HL4/ttTLjZWzncjXW7FcJFkCXyODE7c/fpufmDR7Wlgstj4xgu1LmS8LJjeBA3+61s5iKpPKgfN4xlKu2CtzrMZkx6joDPx8mMC1y3AAfqW4gVvNAyTbYZtMHlkTzEZ/gcyEHpgI9b/jF7G68uZNqSR/+2Pgddz+OJuV0QJ+FJe4q6LvD0uosTThTmoElGfHqYg2ZJXNZWnLvPzM8gfNLFNTmWTOWhSCO8bioPxRppY/fFIguEgIV6tVxYq5c3ahXRzc7LLA7kVFqsVYiGvNhH/UB4i+vULSouyf5I4RvLRJA4OZLxcaSDMO7l6jqi8kJlvWyaN0/qrHn19WYrxFbjSPQ1w/zyRLWwWK0zNnAwxC2MZb6jsOpKpYnKXiHpr+8KhuBRxt05rhuNBajPOmq5bKqs4/MBzpm9bLMDad/ILS/ev7LUknoVfyplVyc=
*/