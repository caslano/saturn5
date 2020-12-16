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

template <class T>
inline T asymptotic_bessel_y_derivative_large_x_2(T v, T x)
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
   const T ci = cos_pi(vd2shifted);
   const T si = sin_pi(vd2shifted);
   const T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   return sin_phase * ampl;
}

template <class T>
inline T asymptotic_bessel_j_derivative_large_x_2(T v, T x)
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
   const T ci = cos_pi(vd2shifted);
   const T si = sin_pi(vd2shifted);
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
1yt3+pvrlA9vw+vLI+Gl3N5vrihtbeOzcsZlPZTs5df/9PejbX7aKSj1O7qnkr1xUPL3T5uVePfSNv7m1Vcevlw95bhRzUq4Ztmn/OTVbf19rkkJ93fTSjx7Myjp+/dt/DvZ9crPnRSUeNAVlOwcv43fn7heee9f1Avse1AZ9N9Gf+WFD6WV/PO+MmjnZLgoH7jU9cp93/E50PNLGSV/zaKf8shX9a/c76ag5L8bt/ntAMeVJ/1LGejbx/XK8wYog+tzQen4qm18bN+G+5eUgb3D1VMe+mSzUrx00ld539Xb8Jinf+Xe9yiDflc3KZ1frj/lw39xXNk0y3HlI6O1q3z5vWal8vPKoP2JaSX+zG1WsmePtBJOr6SUPi/cxq/t6aN8IqcM7FuUUmq/l8/Kg/srlZ/7ZkbJ/7/dZufHQYmXb23j++HNSp/Pb1LC9/CgVG6vVH4yd1s729NX+diH+lfeMVy7ytcu6KXEn52dV1oSUPL3H7bxZpjjypPWuk55ySD1lefYD0lpiya4KHfrbFJq/9+UXQd0W0sRXSD5P4UiegfROyhOCKE7iR0wJI6wHSA0SbZkW0S2XiQ5hWp6B9E7iN5B9A6idzC9g+gdBBwOvdwnzZuZLU/AP+f//da9b8vszOxseft+T/7xBuR3rk92Rn79DQWkSF/yYqQGcv4T+cf91L+X3Y4U9vFVGhd2UH+SPf/iUhcihbyfQPb2HZLzdvIH16F27Lo4Usj5lxciRX43wO8G5e3ejhTteAPkh/S5h9EepCefug0p5Ps6qsezkS/S+94Mfxv0N40jl5gg//eSbeRvDVKkTwLPQA6LBin0q7obKfT4CtuRol5b+Bvpaz6D8pA+mH4//buLIUW59Pw/Lw25IH3Yy2g8uxn+NuB/AbiBnD5zAVLIbxW/I33mJ3cjhX5cDLgBn+T/g2shNfj9GduRoh7vIP+8cgFS1P9d25Ai3y6eR/rXa21Div4iPfvmxw1S6MXPaNw9chGk+P1+F0OK/n3PLqSQ3+Q2pPj9XRcghT4P249/37sdKeR4nYsghXx7Bin83SuQP9LtzzFIUa+XUzuXwDPQn9OkV1TuVzPoJ6Q7y6gn0ku8iPzy56kdd96BFHK/I8nxmeAb5PsF8Azy+NN2pOj3d16AFHp0g4sghV438TfSS5y4GFL0SxN8A7153IVI4VdoHPoc+fvp7IVI8Tfpx7v/jtRAnwekn7izACnGbfxuUN9z25Ei/dcOpGj3RS6KFHpxVbLv3gVI8fs/DVLo17NonHv9bqTQ8zuS/t2exqfNiyAF/w4GKZ4nuWJrAynk8MxtSFGfm5Aff9AFSKH/+YsjRT+/ifzfrw1SyPlW+B3pUy+J1KD8T1wEKeT3M7QTaWWF/GnJIMXvVzckF4qfLnZxpOifz9E4+y0q9+FkL8ukV/Pk759F/XlfGpd+hhTppa9C8eFDtiOF/l3xQqSQb3sHUtSX9PSF1yf/eYjye/FFkCK97EWRor43J724HenPY3chBb6H2vuc3UhR720k56uS38rR+HonpEh/MLULKdpxbxqnf039QOP9zEOQIn37AfJz2y6OFO2Y2Y4Ufx/fjRTP/YPs79LbkULOE6QXN92GFHZI7X7FuZ1Ikd6U7OOzZC8nCX/HLqSQ+7kdSKHXr6C44qBBivGK7PAS55EP0p98aDtS8P+C35G++TkGKdIpPIf0WnNIkT7spaS/T6Px7ZXbkEJ+ZJ/v/il+R7oxe3Gk6N8+2oX0uS+jePmyFEceuhAp+mUOPKRf/An1y07wkJ6+DlID+T0Ovxs89wjkg/Rzt6G/b43UQJ8vQfW+E9qB9P0dss8i2oH0bv+mer+b9JH691E=
*/