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

template <class T, class Policy>
inline T asymptotic_bessel_y_large_x_2(T v, T x, const Policy& pol)
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
   T ci = boost::math::cos_pi(v / 2 + 0.25f, pol);
   T si = boost::math::sin_pi(v / 2 + 0.25f, pol);
   T sin_phase = sin(phase) * (cx * ci + sx * si) + cos(phase) * (sx * ci - cx * si);
   BOOST_MATH_INSTRUMENT_CODE(sin(phase));
   BOOST_MATH_INSTRUMENT_CODE(cos(x));
   BOOST_MATH_INSTRUMENT_CODE(cos(phase));
   BOOST_MATH_INSTRUMENT_CODE(sin(x));
   return sin_phase * ampl;
}

template <class T, class Policy>
inline T asymptotic_bessel_j_large_x_2(T v, T x, const Policy& pol)
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
   T ci = boost::math::cos_pi(v / 2 + 0.25f, pol);
   T si = boost::math::sin_pi(v / 2 + 0.25f, pol);
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
      BOOST_MATH_ASSERT(v >= 0);
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
LiMO4f2UiFsC/QPFQ6BJVt34DiqRSn98Obtw6WaW7qmh3avVe3OfCFRrFrBxp8YBfEyqD9hsIzr63jIM5g/yGyMIbW1ZULxWJy7CYXxexm4z8E1wprv8xP6FLEkdnyHnNXVKPo5aaXGl+blIqWE6nn0loaF3XaJixF3jD7XhnXX3WPhYjj9NhqvzS/5wiJsyW7CBsOiuNr9RxdNxyJuT7D4sY8yc0SzRag9Qq4WbTFJvq3A9eXJP4ySyq8pvUYA8oHr7VEXLwER95KADSMS1snAGMdHbTPlOjEX1apizOHlH52Rz82Cwomua1L2is3GkcDkp5vefoX4UTEN8dKiwpzjaAVe+MNZ9eKXkFsXEDHtA0pPjx4euK+MThQTdSB+mjfAJhbQt3svc93/3xCVoZoJ0c9GR02oRY6+V/ACj7ROIS6VNxEvZpWpJ95FTlQCsThtQFevIOa9Nr3CPJlbkfAZDMGe8zL6VTxdgajSaceSewhqKPiSAslsbEGIlX21uiog81IxHbyqYp7ZnjcnjQbSmRvooFTFUU+4MzW4ndd1swXddhesWhdzWZ8TnCDt1dXcjFeXxXQJeT5ZyshUEt/Ys02MdDRHgZX3MWmy+tNea+5dq7/yC4ySvv5XmTNMf0kWGu4JFfTbF+vXgjlmdkyk4RZa+MFk/qIorW7AaBVTuY6fJEwdLkO79o/xZN7QIHW62WVy7d55Txm1cl/r6XqVDsplX1S4ToPb4aFuSMqoAQ545EGm50bLJlqBYqAY1bfXLaleIVhcOFf3fZtlhaQZPCHt7VTl3JHIKGmz/TuUCZe2VgyvbRIEkKs6OKqpVzOQGTCBTmRRqGwzXp3ng/DG4FhcAuZRl2EUDxU4GK5l7BBhyHy8nIGwHHeL+nKIgGvkB6206LFJKVGs0eUsVlyCdkRJd06htvfN1UBB8ONBIlJV0SraN6xSMqz20RGpZHrQbhbI+79qjEGEf3rwm4viZWoVfxUtRL8rvdODoRIX0W7YE3pt7ctw/+UmYbky2lWyOomxHqVkJ/2fweixdN8W8LItDKUZQs6BC0wdI4G/5CZ2HN0zsCAKZBCfX0Guf1EbtaAIP4t6cpdv0/e0RJoWDtHuFzx6eVi8uwLy1D2b/LdV9FWvvYMhmu40OPZvyqvRKBlc1oLdkzv5odbOtA/buj9H2qWl/whWV6qxNKpQZqMK6GzXb8+OytUNzpTV0l1TitZkjiNyYs9WZqw+0QyrQz3kjKUaPdwZlZVwfnHZyoVYJl7SeHRuN5Bum+z5xSzgrsbP6H+dVEjjCuDfnbxbSiA0FXGTPEMETtGMPECPmEgjEeC3CJ0bGQrwsLZM1wocv4frtV+Q1r7WtzjFQMYcMpH+XqBNqwoLwT0cQTBy5wa5+7GS632MT7qtX2iqNXp6uanWtiwys63WsjdGTJaFf15cFwS1oyfdYuz6vi+Ih847Wi1lCz2+HFcu/6VXoiVEZXeAqiq41YiuOcIZMhJ0qwT4xc9BjzSCcFS9g7VbzDwA9DdIfzkc92kHJPCvMY24PtyXjs51JCrpnNq3rGfUjuESEw9m68bW3gNJqN9FcxEMyUHUSMo19ImdkE/cPx3a+dM6F/8kvQK6KTa6QBRI7dHbUAEdoIoEcEty5NGpI3hwU3v/w9UaMbaMwIfKwuIQKS904QuPlWLeJ4jxmjXQ8OcifHaTvOMsD2OtCGIOm5vgVNxCscgfDCt8gLEy6Yq+VmAdRN/1wrGhdem6yU9nhxmiep5eGu/nJQdS0wcxWVkW8TH7G4aDNUpiH32gqiZ8J3aKW9KuG4OCboVCJWEsLaJcbjqiDwROwuwOFgQ+O1q5vermwMBr5GMkm0WPfOOYA9wa7EYnovO94FcYst76wcK6dV83Yjv77OdOz7WrKLUaD4Rym90FtWe9HJuufp4VOobEKdeauHPYyEPPHKVCmhkMrhTOL7qvk5o6NSmx5MEg5SZZcWhqLo0TO1BihGMo3sXPKnHNK4nKBTL4ETRjPALuI/JiGxHVem/Bz6dCjXCfwq9anKmDT62JHbLLsQG/ZgfJ8jNnXDWfKkXrYQFdChEZ1dUF+PVT6uNm+aTgmcLTFOsOLb0bCYSTgMiCXm8efZkBFeo2Q0zH1cl3Z5ebCM2hY4hC+FZr9l6nuTuOPd9IA3Ck5EPgBrXZaAoFXzNvSmH3NGneRg0qm8d98U9LEyry74b6YSI2+cEEbb6tgOEJE1kN5nRSlBe8ILuFr70ePbb1fYkTMolTdS39ZxPi4TYBH0bL7FFqS+6jPNboTFqJMRbsBPSRExOBBKvEXQCgW6vbkowXpHmkYK5VPMyqgWLtx9O1RtIzrbo6YjJqguh27Mpn5r3PrPEJ+bje2ACHC9bjk/GcrMfUJd4tl6PkCM+8MdmXZa5OclTHLAShxScF1dNHZziv/ZwCWe61Ct87xWwnb5/sa+WjqS8AZRwpDxhLjNiAo8dTo4YEynl7h8jWfpuQvaQN+gBz1k0NP8mM8HEA8jpDbhZ4vE1vhHI5MfJco4EvQkVbTeWMs2Xd68huCYtHka1j0XIKiqoB4kwwpHA+zfpZGrqVXKBBVdqT7l8tGMXk2AGXOiJeiZ0TPhmArSWqBbUN0jV6YFN2O9wCwx97JcW2HmWYhH4kQvZRChm0K+38zRjp9bsNNszqZZJ/dgwXpWp1d9E8Not7o8Mn9gsCIaykX3+TIzdxnAmYLMUQ0xNU3Izs5PTqz5yWro0oXk6Fhds7OsTGNsBONwdhSbtgXweam+/bwEYiYekMyvX6E2JlAKFtDZnQ/26za/e/Jv9mvbwi0EHOv6TUhy6WPQng0wGJy6jEFN8cuJH5FC3k2S/PwBmKZZqf/pWO5Gnv4BMy5oCCMpDyj0l537spDa940dAbM2iAegJLx1yVWPAmc6BMI3PRzcVt3anK7z293XcWrIzi0Hx4YjngT+pHUi0PhQRnlBDQgKAhq+drCzyWoSLOYaq7N76Wtcij/1uVXOtK5cPDrNw3MqOu36jL33OIGecl6NkFdb76c5CJslXVFul+DSaR47ZW2crIymmOijy81sQ3ZwhuMHUwr1Xl4BS60gBCMSbK5lU3JYkh+jHx/qT1mDfS9gDt7VZXtmtSq+YNaqxqO/DJA96UAlD/DYWd/ye8QZf4bgqTE1tmL1cTa5khb0jugBLfaTw7DQTRovtkB2YkbyuQ8eSJ1JiKo+JCbBCt5VpSpRRZ50qHViTtrynsuZlIRr4wmgmk5CizO9UjyOU1R9U4BwkzJQEz9PWR3nOURm89v4hbkEIz9mnesZ1K5qr2uWRzJ3EulngIHiY+jyIzoOY4Z5KL5fPqiHtlcrvbq7lcG53DVwQdQb1ppQXAvacvxP8r0mNzF9NbTwqP3vMJZzRnnxG21C5Xt7K5y0h3k9XTRcONWCMoo8ml5sZH3RdhB51yWj+ciCLs3j/tHZJllHB4Dp3osNPblcGXK8MsVY243QrPqcarC63t1aMhRQjZFxgrWCIVt8uXSOop9OY6Z9aLfeQldl/FMIqwOpLLVBTuLJSeVOoRvglL4MuZeKUm1MEpuu/9+700Kn5tTPJbgUe0VohP4ynibZZn1tSNlCsebno0DmUhf0OiyeZYG5lx4/z2a4SVFMqkfcVCZVlb2OJFNGQy1HAMmE6woblX9UjHFW8AAz7sV+aiqGUWXA+tbUm9WcAvSXfs71c53IWAR1jv4mVDO5i1xn2merhkhdRS8NDOr2mG72SMktojLZkAqC4+NwBG6Bc4y5CtJLPG6zanQJy9GdpyN2AZO0UfRqMMMevQjJ0psA8p5kK8owaORo1g697Gg+YnYF43W1z1wMD2JMRv73XI+X6Mzr5Gs7hoBoRo8EJN4QATlWHwqXY4QWYhlQy//fbl5utdQ/6l/tUa99FpxjfVTUFeCgELLJ8hYBRlwNeHVWS7Qwlwyqsp21iBt4VDZCgFWRuXWyVk18/1j55QeapnoBPsBXwMHfoObmfRLUTnhaMgTsQW0ZbMI+TOVVDXsYOtmR36L5Lq0DCkIwiSXw/KSnW10H2Fe6Lz2EM1Icl3iuiIgfAKz2/HuWx/MVjskrvrNolL1429DRZUGnGVheA7EEgfUUwwAaJJzs20XfZxMB+56vr1BzrlNDFHWfwDhjqV1KWbFw7o0CeREpVBQfIDrewP2kbCzwzS7WKLAzTgfonGzoyrkUqOSufBe6XvdX/NwX8gkL1pmgbhpNGDz6sTST66EdJSxq/PiXvUBCclXE5nkntfljOEoK9ZdxUPNPe3p1TGH/+Bb/KtCyQDTgeqXUyy7kh1pPmd7hFyWQP8gVsp2oYwRXIn6m8Fa4XHi3hUATx7iDpln4rW1F5iSz82jcah8M1XNAGJQ2j+8G7cwqZbBqhHewsx7l1/5wIhRvTUoVNzx8eAz1lPkBmtqTFB+FESEv8RM6JHUUvyEG6LYuFTtQIA6Gr8yzom/BXr+PXkbKVKFlH4P5Tr3OShZKjlUAvNoZnPWh+guLb3C3Wdh+gnbCB0BFK7G1Nz7/Z9bbffL1nFxMKX95vF3rVGp4Pf1LbqtC05ycpcn2MroCRv6oqx/4amquS8ruu0QutU/gblc0e9OaZ2+nx7wU/d3uCxk8IFw3R90stdwO9/7D9/tvd671F9osbe3j8feF75fz1Wr1I7d99LXXxedupYft8udrtZbuC8I+NBe1w+Xx+rfmZ+x3W3a1pvpzNedJw8vsp/u/75+fnZo3R6wRwJufmu6k/bWO3CK0ozctrxnkAtzjZdO4TwPVhJ2rl2/zU2tLb1t/X2DApJC0lKyMuZzXS6SVdBWqvnr6OrpGxgaGVlZ2VrZ2xyD3d08Pby9fH3ebgkIeL3NyREdDuZBjYk9JkWkpzKisjJzsosKebGDk3hYbERq3AZ61kfNTNxcvDz8fPpuwkmiI9ViyIiS9/NTiwsfSpeXVleO1iJ/d3V+Z7ryvuHn/H67ix8+xh/JfBcr9Pu6O65iHm5+YiFP5R56Y+0FkKS/LntycsvNQtXxNtxfu3/felv3v738PPBqYA+b/WjP745U3co+6+geZscBnz7sfsJfHNDF+Yx+Eb/zHfNdZQwbGWwNPpFohrnz2L9RAr8m+EiRYTapy/caBNDgKi4vZWMN+lJamSSI8ig/iJTqiAn9c7pWafcDwpNF1huXz4fypF1ndMCJWSGKrIwjDWzvxNzrvXbZeipErYRcZTfhw07V9A0sE1fPIIdAtvSHQxDAyZ9iIr88th0rS6qyGDSRfBt/8Jg10GZtIORTL2M/UaJ9A0cxcFYj+iI9Npy4+7qfQhv5KSHPtjYvDSsrS6lfwdUW8I6wNvQkybuQSI6n6najekkC+JjX2WanQmpOFRTukuxDufeeCPOHvnnfmJTvV0YkXss6MqeSNAIhI7p8Mkh4Vsv9V24EMKxHSZhXWwG2rWErgvIRc2oelHREQhQLg3Mqy8eKN5T1WY80h7YwiY2NiZDrmpMuQtedaofcRunULFqgL011J5LF/ivFiwnYE3OlKZuAwe5LtQ00M6JNL88JTBCLXIfSmH1QeEtz/dZRoBkSuv13NeWVFBuTyu+7BCMOHUIMhvhKPZNDCwpGEcXZXL+n5psj+zFAi1K/76ym47lQhArgz7C5cRF7k5qWbuEPbZRq9jPcn/x+JVWEE0CJacCe3UJKaN0RHscCqFp6h+eQ0qcIvyZsszvanJKWzxV1en5DL354TWbM7cnl6dSxp3wRXnkkJTvHXhhTbPSDBShlvXH2A7AbD9Uxo8wTV6Tl+AplPgBmB46JBYoEHd6pMyF1wsnxaaeKz3jUao2WtTi6P3YHebq2zsPKoYZ0pa60ohB0R7+e1pIuxqSoCDusDrwriiMbvR58NiHG+QVtDfIPv2qn2I8GzYZaevCTjQyxXXB92yoHnYIy44DzgR0okaw6sZmTa6mcQNeVqpwD+JQUwBRGrHVpqcTx1/fFjf9fswg+0ktmQi+d/JU/AT5QouxNs5aKkWMW96xZMtMQt8ozDayQjraKs6kbfJhpn9xw4zKV2NpcJci6r8hQUyfnuHJvx8bWt2oN+vftGOVloLUvaV12tRyw46x2RyFs6HQ1rF2IwXzlWzALZWqL30+oWLKbvR+xbHyjIKqaPV7778roovpq2/di8gCpmQB8B3kznKXiHhyaSdPOudhO3YkO2SmZDYgjLki1n0Vlm/XhZTJmMc2/pKv3XcSCn19H+djW3v9+5/oCDguLRjqlENYDr90aB7XJWu8uz0mzAHFd61eZZaX6TXOH58irtIeL9Bop2RmoPKiLM6tQtTpoNSaKCH53N7VaD2b383JIXOn6uiAXhQ5p/ht2bR0Jpm9s6T9ASGSHf/P3c072ZinaXyHXMzPXEIRc77Tr3o39zyW084Mj+oS7Vy3e5La+N+841xiDwag+L+I/EaOibPl23pHFiG3v/skZhEBxNgtOQ8lpYO0Z/3mq/gc1LGvjlNvhRh42oK3/hhpgQBEjPZbx44/d25KfdFsntBHI/GN9lKwu/cjcRzyUzg8WKYM/HbZtzXq307XGdbosm8XGJ5cYiuPiw0KJw40Rly2+WFjZZ1gr06a9pvJLh6bIkYEidXIPDbFvUZvL4i0Y172QKyuSEN81zO9PYay3k0t1O9Qk9H4VMIq0uyvY0sT5MJlPhgfr/4Fc8lLBalRcMR74vDJGpY1ec9flRWslsm2knvhbmyFqFjYqjMD2UlzyuBQLB5p8uGofKSU6W+x0a0tEx26EZ/dOW3RMuyLXhk3a3sSeB92iG94OHASaE0b5fT7G1xvYm6MyEOgNwjjqmcrblyGYI2AXD402FodhzSinga+zs9LwO/gqNOja4uweBEpSqupsG82ISRextCnFRJhNOfXxxbkU7OsTpH8ok1lQ3Ho4K4pKHyqid93Ex8bsUG4Vbm1JG1EeuMhISSvNx1cqvz1nZ/bJsuVKvaf0hk3BGydIjR46u3Msr3Po78+FFGW1usmAJD5Gp1CfJFNuWeqrDaM801tHSG1Xor/y4boiVwWMYhqjTWSjAjc03CVOgZyG5b4sT8mliSlyTXsiBvEFy5fRfmpfySCXczqh9lAftFd7K8UBfuQ76M/Yk13hnkJ6xM+Vw1eN+Di4wAmN8sntfoH7A/gLSQEC+P/6JRJ6YndYRgTk2c1EIyesdf1z/3xUuebYs/ZkEgK7uGrQ7fEIqHZYuOTgq9Zxjk8O5HSPPZSXh5KYtq99vimtwTGUeOWJ9yWqWQy/HvjNlsG3bedijty5KButbsemCyq2rvkFV9Av+W/Yoql0TwgZOTsr3PoaFNNeO9uLOU79MVZDZy+xIhhPKWJpV/cFJLYdx6LQcK+te96A81PVzKJ0lD4ENp3YncOdOfkt7YiOcdtiUFEMkItqqIxBSr5HTAYz1n7YTBchBGpUWm2TCOAnytru97Bz3wHb2RQ61G1ewOo6pc2H6Vz0eyO5J86wcS/bjtNG3sjjSM6xONPExEBM3+mD17yXsNKC7JCdYx4jSHhTVhjNuSfniyU8SdvK9eLwtrfzIbWV5Bhcl/n3cf7x08i9EeebzoK3qcGOqVGJIkBm/FHB8fL+6kEkAx8HdstljHT1kMfGVLvkFktvpB45voGmvslN
*/