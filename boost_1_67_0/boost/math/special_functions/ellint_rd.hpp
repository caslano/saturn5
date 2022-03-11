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