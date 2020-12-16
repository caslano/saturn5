//  Copyright (c) 2006 Xiaogang Zhang, 2015 John Maddock.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it slightly to fit into the
//  Boost.Math conceptual framework better.
//  Updated 2015 to use Carlson's latest methods.

#ifndef BOOST_MATH_ELLINT_RD_HPP
#define BOOST_MATH_ELLINT_RD_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rc.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

// Carlson's elliptic integral of the second kind
// R_D(x, y, z) = R_J(x, y, z, z) = 1.5 * \int_{0}^{\infty} [(t+x)(t+y)]^{-1/2} (t+z)^{-3/2} dt
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T ellint_rd_imp(T x, T y, T z, const Policy& pol)
{
   BOOST_MATH_STD_USING
   using std::swap;

   static const char* function = "boost::math::ellint_rd<%1%>(%1%,%1%,%1%)";

   if(x < 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument x must be >= 0, but got %1%", x, pol);
   }
   if(y < 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument y must be >= 0, but got %1%", y, pol);
   }
   if(z <= 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument z must be > 0, but got %1%", z, pol);
   }
   if(x + y == 0)
   {
      return policies::raise_domain_error<T>(function,
         "At most one argument can be zero, but got, x + y = %1%", x + y, pol);
   }
   //
   // Special cases from http://dlmf.nist.gov/19.20#iv
   //
   using std::swap;
   if(x == z)
      swap(x, y);
   if(y == z)
   {
      if(x == y)
      {
         return 1 / (x * sqrt(x));
      }
      else if(x == 0)
      {
         return 3 * constants::pi<T>() / (4 * y * sqrt(y));
      }
      else
      {
         if((std::min)(x, y) / (std::max)(x, y) > 1.3)
            return 3 * (ellint_rc_imp(x, y, pol) - sqrt(x) / y) / (2 * (y - x));
         // Otherwise fall through to avoid cancellation in the above (RC(x,y) -> 1/x^0.5 as x -> y)
      }
   }
   if(x == y)
   {
      if((std::min)(x, z) / (std::max)(x, z) > 1.3)
         return 3 * (ellint_rc_imp(z, x, pol) - 1 / sqrt(z)) / (z - x);
      // Otherwise fall through to avoid cancellation in the above (RC(x,y) -> 1/x^0.5 as x -> y)
   }
   if(y == 0)
      swap(x, y);
   if(x == 0)
   {
      //
      // Special handling for common case, from
      // Numerical Computation of Real or Complex Elliptic Integrals, eq.47
      //
      T xn = sqrt(y);
      T yn = sqrt(z);
      T x0 = xn;
      T y0 = yn;
      T sum = 0;
      T sum_pow = 0.25f;

      while(fabs(xn - yn) >= 2.7 * tools::root_epsilon<T>() * fabs(xn))
      {
         T t = sqrt(xn * yn);
         xn = (xn + yn) / 2;
         yn = t;
         sum_pow *= 2;
         sum += sum_pow * boost::math::pow<2>(xn - yn);
      }
      T RF = constants::pi<T>() / (xn + yn);
      //
      // This following calculation suffers from serious cancellation when y ~ z
      // unless we combine terms.  We have:
      //
      // ( ((x0 + y0)/2)^2 - z ) / (z(y-z))
      //
      // Substituting y = x0^2 and z = y0^2 and simplifying we get the following:
      //
      T pt = (x0 + 3 * y0) / (4 * z * (x0 + y0));
      //
      // Since we've moved the denominator from eq.47 inside the expression, we
      // need to also scale "sum" by the same value:
      //
      pt -= sum / (z * (y - z));
      return pt * RF * 3;
   }

   T xn = x;
   T yn = y;
   T zn = z;
   T An = (x + y + 3 * z) / 5;
   T A0 = An;
   // This has an extra 1.2 fudge factor which is really only needed when x, y and z are close in magnitude:
   T Q = pow(tools::epsilon<T>() / 4, -T(1) / 8) * (std::max)((std::max)(An - x, An - y), An - z) * 1.2f;
   BOOST_MATH_INSTRUMENT_VARIABLE(Q);
   T lambda, rx, ry, rz;
   unsigned k = 0;
   T fn = 1;
   T RD_sum = 0;

   for(; k < policies::get_max_series_iterations<Policy>(); ++k)
   {
      rx = sqrt(xn);
      ry = sqrt(yn);
      rz = sqrt(zn);
      lambda = rx * ry + rx * rz + ry * rz;
      RD_sum += fn / (rz * (zn + lambda));
      An = (An + lambda) / 4;
      xn = (xn + lambda) / 4;
      yn = (yn + lambda) / 4;
      zn = (zn + lambda) / 4;
      fn /= 4;
      Q /= 4;
      BOOST_MATH_INSTRUMENT_VARIABLE(k);
      BOOST_MATH_INSTRUMENT_VARIABLE(RD_sum);
      BOOST_MATH_INSTRUMENT_VARIABLE(Q);
      if(Q < An)
         break;
   }

   policies::check_series_iterations<T, Policy>(function, k, pol);

   T X = fn * (A0 - x) / An;
   T Y = fn * (A0 - y) / An;
   T Z = -(X + Y) / 3;
   T E2 = X * Y - 6 * Z * Z;
   T E3 = (3 * X * Y - 8 * Z * Z) * Z;
   T E4 = 3 * (X * Y - Z * Z) * Z * Z;
   T E5 = X * Y * Z * Z * Z;

   T result = fn * pow(An, T(-3) / 2) *
      (1 - 3 * E2 / 14 + E3 / 6 + 9 * E2 * E2 / 88 - 3 * E4 / 22 - 9 * E2 * E3 / 52 + 3 * E5 / 26 - E2 * E2 * E2 / 16
      + 3 * E3 * E3 / 40 + 3 * E2 * E4 / 20 + 45 * E2 * E2 * E3 / 272 - 9 * (E3 * E4 + E2 * E5) / 68);
   BOOST_MATH_INSTRUMENT_VARIABLE(result);
   result += 3 * RD_sum;

   return result;
}

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rd(T1 x, T2 y, T3 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rd_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y),
         static_cast<value_type>(z), pol), "boost::math::ellint_rd<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rd(T1 x, T2 y, T3 z)
{
   return ellint_rd(x, y, z, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RD_HPP


/* ellint_rd.hpp
d9E6q/Twvasy8FniyHlJXDVF3Eq4r46jrOM8Ge9qW49PXK0urf4zP4O/spbLi+r4UnZRJ27Xq39y6Jpz9YfLIr9OC9fdkPzeaH45+DPjU4tvm+36q/WVr3Hedanq80z8+/70HcZlXjq9E9wzjo64Vn/4cDrJn1ovMi6Jg6fSVeSNSu7PVF8W9uFV1a01/HV1rJ/YYl3RZtfxd+ONb0+8q8/2hvz7fqq+k3yxRjxfyA93wFM34y1a+EM7XXJBUhe5wbrqlI3qgRJ4tJ5/35OgExWf+vCgh+qjxDr1reqaafLpKvjtS7jtGTjonUzrkfHKqdY37tSfSME/fqOe7MBrfwH3nJ70nyHX4VGu4RfeZ1Qk7g79hzgX6/DLYx08PW3Uhw/HL4EjeuTHtkny6Wy6yiL2Hj0XfWCYj5PlGbzN1AMz5FX4Gl7vwjuW4l8KIv+bG46/yOezxK9B1q28Ka8vtp74QfXRfPd5KRwxfX88ANxt3qZav79nCr/8u/gzR9x6Cu7OpI+ZzN++TKd/wYvjK6rUCa0r2elEdZ26vUkeKH0Qby+etN5uv/o88yX2cn+8vg1PlGd9brXx4veF7GCweLoarltwnjygzqi5FB8R+W1aON+n7M06/1EnphknuhO4uGAEPUEpPDYAXluS1u/X4TrxxGWhjgifJ8hbA/E/zrsj1J/h81nq1JXw/AL4B09R7X6q6ELnpuqf3+T74mEd/rBmSdiG9Vr6n+fIA+JFyWD8Mf61+3bxyDx3Hamfxq4rhou75qv+efnrj+ZzE/s9PcSD6DoXu76N+nYz4Igs9cC/1ekvyl8RfkwLxzefHfi24rfxSXBBbau6Fl/XUaF+aTE+e/UZ6HbL6azXFIufL9J9PCFexPyT3zeHcQ2f29hVinx7Q/C7sE5I/Qf35RiHRuub6xbC2e4r83dw4Mn6Ql3WET6rH/Fd/k/HMIx/Lryf39ALVYk/BS3w4yHyuToxcw77uss8safmNvwtHcyYGfwrGo/+4XyH43f49ZBD9BseoocY6TjH4YPwSjvU3XX6FeNXym/qr3bj0xHh+4wwHnnGy3WnhPo5nL9UvXFd3B/G22wTt9ZY3/MpuxNXsm9yPVf5Pd63YSy94+tw4Tzz+Q6edJ78yT466E6K/gCfVcPN9ILlDa7jGHXHxWEb9OlhG/ra+vbx+16f8Fy41a7zPvOTr148He6t9Z6mcnk1xp8jBiZ/p24sjvSzh4bxOIgO6mx82vF4vWb5bp71fOy1ZQm/X6lPHNVlaeH3Cbp4/j36E+N6S7o60Th08dPT6Anl3Qa/y1xkfRs/rCu3DugZOuaX6NOPoO85g57bPDbn4ZvOpBs4WX0h/9R9KS6G+wz/L1MXHhXFw3D+YnhhAf6pUn4Ifhu21uMVpumvvQnf/oq+50Xj9F3XO1c8wfdU05WMoXcf/gJcvcB151rPigeZcg0d1y34zXT+DH/N7cHvX+k++Fnhifr7/4v63WHbnKZ/yg8a8e3ixGrrcRKjA68UeDb81I36XPB+7iZ8sfNWPuY6/km/8h19hiV4ozv08/IHel9Icv/uo/Ask9jvRHlpHHyoX1Aa9CRhS5eX+WO6tfvch/n91PeHtPOflex3I759tro+1mv+wP0PDPtDvjB+rm/H9c5j3Idav1qeKR+fJv8f4D1cH8oPf1EXxHzban7+Njzvcw/+qInupOM49jABj7o1Wd+0HSsu+P6CXvP0Jl75Fse1jiWlzPxEeC81+IXfdz6UoD8SH+93/3iPKs8XzvX9WviuGJ8zpFcchHNaP4RTlvqe+NV7tHG7V166Irmdom4vWKJOqRGfforfvkRePAAPhn9rmAR33QsP1sJP7CQ=
*/