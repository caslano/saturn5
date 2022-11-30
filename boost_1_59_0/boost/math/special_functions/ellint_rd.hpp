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
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
*/