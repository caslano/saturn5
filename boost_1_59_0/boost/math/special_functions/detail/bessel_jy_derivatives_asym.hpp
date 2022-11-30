//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is a partial header, do not include on it's own!!!
//
// Contains asymptotic expansions for derivatives of Bessel J(v,x) and Y(v,x)
// functions, as x -> INF.
#ifndef BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP
#define BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math{ namespace detail{

template <class T>
inline T asymptotic_bessel_derivative_amplitude(T v, T x)
{
   // Calculate the amplitude for J'(v,x) and I'(v,x)
   // for large x: see A&S 9.2.30.
   BOOST_MATH_STD_USING
   T s = 1;
   const T mu = 4 * v * v;
   T txq = 2 * x;
   txq *= txq;

   s -= (mu - 3) / (2 * txq);
   s -= ((mu - 1) * (mu - 45)) / (txq * txq * 8);

   return sqrt(s * 2 / (boost::math::constants::pi<T>() * x));
}

template <class T>
inline T asymptotic_bessel_derivative_phase_mx(T v, T x)
{
   // Calculate the phase of J'(v, x) and Y'(v, x) for large x.
   // See A&S 9.2.31.
   // Note that the result returned is the phase less (x - PI(v/2 - 1/4))
   // which we'll factor in later when we calculate the sines/cosines of the result:
   const T mu = 4 * v * v;
   const T mu2 = mu * mu;
   const T mu3 = mu2 * mu;
   T denom = 4 * x;
   T denom_mult = denom * denom;

   T s = 0;
   s += (mu + 3) / (2 * denom);
   denom *= denom_mult;
   s += (mu2 + (46 * mu) - 63) / (6 * denom);
   denom *= denom_mult;
   s += (mu3 + (185 * mu2) - (2053 * mu) + 1899) / (5 * denom);
   return s;
}

template <class T, class Policy>
inline T asymptotic_bessel_y_derivative_large_x_2(T v, T x, const Policy& pol)
{
   // See A&S 9.2.20.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   const T ampl = asymptotic_bessel_derivative_amplitude(v, x);
   const T phase = asymptotic_bessel_derivative_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 - 1/4) term not added to the
   // phase when we calculated it.
   //
   const T cx = cos(x);
   const T sx = sin(x);
   const T vd2shifted = (v / 2) - 0.25f;
   const T ci = cos_pi(vd2shifted, pol);
   const T si = sin_pi(vd2shifted, pol);
   const T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   return sin_phase * ampl;
}

template <class T, class Policy>
inline T asymptotic_bessel_j_derivative_large_x_2(T v, T x, const Policy& pol)
{
   // See A&S 9.2.20.
   BOOST_MATH_STD_USING
   // Get the phase and amplitude:
   const T ampl = asymptotic_bessel_derivative_amplitude(v, x);
   const T phase = asymptotic_bessel_derivative_phase_mx(v, x);
   BOOST_MATH_INSTRUMENT_VARIABLE(ampl);
   BOOST_MATH_INSTRUMENT_VARIABLE(phase);
   //
   // Calculate the sine of the phase, using
   // sine/cosine addition rules to factor in
   // the x - PI(v/2 - 1/4) term not added to the
   // phase when we calculated it.
   //
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   const T cx = cos(x);
   const T sx = sin(x);
   const T vd2shifted = (v / 2) - 0.25f;
   const T ci = cos_pi(vd2shifted, pol);
   const T si = sin_pi(vd2shifted, pol);
   const T sin_phase = cos(phase) * (cx * ci + sx * si) - sin(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_VARIABLE(sin_phase);
   return sin_phase * ampl;
}

template <class T>
inline bool asymptotic_bessel_derivative_large_x_limit(const T& v, const T& x)
{
   BOOST_MATH_STD_USING
   //
   // This function is the copy of math::asymptotic_bessel_large_x_limit
   // It means that we use the same rules for determining how x is large
   // compared to v.
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
   return (std::max)(T(fabs(v)), T(1)) < x * sqrt(boost::math::tools::forth_root_epsilon<T>());
}

}}} // namespaces

#endif // BOOST_MATH_SF_DETAIL_BESSEL_JY_DERIVATIVES_ASYM_HPP

/* bessel_jy_derivatives_asym.hpp
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
*/