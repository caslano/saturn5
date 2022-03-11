//  Copyright (c) 2007 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is a partial header, do not include on it's own!!!
//
// Contains asymptotic expansions for Bessel J(v,x) and Y(v,x)
// functions, as x -> INF.
//
#ifndef BOOST_MATH_SF_DETAIL_BESSEL_JY_ASYM_HPP
#define BOOST_MATH_SF_DETAIL_BESSEL_JY_ASYM_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/factorials.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T>
inline T asymptotic_bessel_amplitude(T v, T x)
{
   // Calculate the amplitude of J(v, x) and Y(v, x) for large
   // x: see A&S 9.2.28.
   BOOST_MATH_STD_USING
   T s = 1;
   T mu = 4 * v * v;
   T txq = 2 * x;
   txq *= txq;

   s += (mu - 1) / (2 * txq);
   s += 3 * (mu - 1) * (mu - 9) / (txq * txq * 8);
   s += 15 * (mu - 1) * (mu - 9) * (mu - 25) / (txq * txq * txq * 8 * 6);

   return sqrt(s * 2 / (constants::pi<T>() * x));
}

template <class T>
T asymptotic_bessel_phase_mx(T v, T x)
{
   //
   // Calculate the phase of J(v, x) and Y(v, x) for large x.
   // See A&S 9.2.29.
   // Note that the result returned is the phase less (x - PI(v/2 + 1/4))
   // which we'll factor in later when we calculate the sines/cosines of the result:
   //
   T mu = 4 * v * v;
   T denom = 4 * x;
   T denom_mult = denom * denom;

   T s = 0;
   s += (mu - 1) / (2 * denom);
   denom *= denom_mult;
   s += (mu - 1) * (mu - 25) / (6 * denom);
   denom *= denom_mult;
   s += (mu - 1) * (mu * mu - 114 * mu + 1073) / (5 * denom);
   denom *= denom_mult;
   s += (mu - 1) * (5 * mu * mu * mu - 1535 * mu * mu + 54703 * mu - 375733) / (14 * denom);
   return s;
}

template <class T>
inline T asymptotic_bessel_y_large_x_2(T v, T x)
{
   // See A&S 9.2.19.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   T ampl = asymptotic_bessel_amplitude(v, x);
   T phase = asymptotic_bessel_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 + 1/4) term not added to the
   // phase when we calculated it.
   //
   T cx = cos(x);
   T sx = sin(x);
   T ci = cos_pi(v / 2 + 0.25f);
   T si = sin_pi(v / 2 + 0.25f);
   T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   return sin_phase * ampl;
}

template <class T>
inline T asymptotic_bessel_j_large_x_2(T v, T x)
{
   // See A&S 9.2.19.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   T ampl = asymptotic_bessel_amplitude(v, x);
   T phase = asymptotic_bessel_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 + 1/4) term not added to the
   // phase when we calculated it.
   //
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   T cx = cos(x);
   T sx = sin(x);
   T ci = cos_pi(v / 2 + 0.25f);
   T si = sin_pi(v / 2 + 0.25f);
   T sin_phase = cos(phase) * (cx * ci + sx * si) - sin(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_VARIABLE(sin_phase);
   return sin_phase * ampl;
}

template <class T>
inline bool asymptotic_bessel_large_x_limit(int v, const T& x)
{
   BOOST_MATH_STD_USING
      //
      // Determines if x is large enough compared to v to take the asymptotic
      // forms above.  From A&S 9.2.28 we require: 
      //    v < x * eps^1/8
      // and from A&S 9.2.29 we require:
      //    v^12/10 < 1.5 * x * eps^1/10
      // using the former seems to work OK in practice with broadly similar 
      // error rates either side of the divide for v < 10000.
      // At double precision eps^1/8 ~= 0.01.
      //
      BOOST_ASSERT(v >= 0);
      return (v ? v : 1) < x * 0.004f;
}

template <class T>
inline bool asymptotic_bessel_large_x_limit(const T& v, const T& x)
{
   BOOST_MATH_STD_USING
   //
   // Determines if x is large enough compared to v to take the asymptotic
   // forms above.  From A&S 9.2.28 we require: 
   //    v < x * eps^1/8
   // and from A&S 9.2.29 we require:
   //    v^12/10 < 1.5 * x * eps^1/10
   // using the former seems to work OK in practice with broadly similar 
   // error rates either side of the divide for v < 10000.
   // At double precision eps^1/8 ~= 0.01.
   //
   return (std::max)(T(fabs(v)), T(1)) < x * sqrt(tools::forth_root_epsilon<T>());
}

template <class T, class Policy>
void temme_asyptotic_y_small_x(T v, T x, T* Y, T* Y1, const Policy& pol)
{
   T c = 1;
   T p = (v / boost::math::sin_pi(v, pol)) * pow(x / 2, -v) / boost::math::tgamma(1 - v, pol);
   T q = (v / boost::math::sin_pi(v, pol)) * pow(x / 2, v) / boost::math::tgamma(1 + v, pol);
   T f = (p - q) / v;
   T g_prefix = boost::math::sin_pi(v / 2, pol);
   g_prefix *= g_prefix * 2 / v;
   T g = f + g_prefix * q;
   T h = p;
   T c_mult = -x * x / 4;

   T y(c * g), y1(c * h);

   for(int k = 1; k < policies::get_max_series_iterations<Policy>(); ++k)
   {
      f = (k * f + p + q) / (k*k - v*v);
      p /= k - v;
      q /= k + v;
      c *= c_mult / k;
      T c1 = pow(-x * x / 4, k) / factorial<T>(k, pol);
      g = f + g_prefix * q;
      h = -k * g + p;
      y += c * g;
      y1 += c * h;
      if(c * g / tools::epsilon<T>() < y)
         break;
   }

   *Y = -y;
   *Y1 = (-2 / x) * y1;
}

template <class T, class Policy>
T asymptotic_bessel_i_large_x(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING  // ADL of std names
   T s = 1;
   T mu = 4 * v * v;
   T ex = 8 * x;
   T num = mu - 1;
   T denom = ex;

   s -= num / denom;

   num *= mu - 9;
   denom *= ex * 2;
   s += num / denom;

   num *= mu - 25;
   denom *= ex * 3;
   s -= num / denom;

   // Try and avoid overflow to the last minute:
   T e = exp(x/2);

   s = e * (e * s / sqrt(2 * x * constants::pi<T>()));

   return (boost::math::isfinite)(s) ? 
      s : policies::raise_overflow_error<T>("boost::math::asymptotic_bessel_i_large_x<%1%>(%1%,%1%)", 0, pol);
}

}}} // namespaces

#endif


/* bessel_jy_asym.hpp
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
*/