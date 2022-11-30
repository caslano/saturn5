//  Copyright (c) 2006 Xiaogang Zhang, 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to correctly
//  handle the p < 0 case.
//  Updated 2015 to use Carlson's latest methods.
//

#ifndef BOOST_MATH_ELLINT_RJ_HPP
#define BOOST_MATH_ELLINT_RJ_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/ellint_rc.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>

// Carlson's elliptic integral of the third kind
// R_J(x, y, z, p) = 1.5 * \int_{0}^{\infty} (t+p)^{-1} [(t+x)(t+y)(t+z)]^{-1/2} dt
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T ellint_rc1p_imp(T y, const Policy& pol)
{
   using namespace boost::math;
   // Calculate RC(1, 1 + x)
   BOOST_MATH_STD_USING

  static const char* function = "boost::math::ellint_rc<%1%>(%1%,%1%)";

   if(y == -1)
   {
      return policies::raise_domain_error<T>(function,
         "Argument y must not be zero but got %1%", y, pol);
   }

   // for 1 + y < 0, the integral is singular, return Cauchy principal value
   T result;
   if(y < -1)
   {
      result = sqrt(1 / -y) * detail::ellint_rc_imp(T(-y), T(-1 - y), pol);
   }
   else if(y == 0)
   {
      result = 1;
   }
   else if(y > 0)
   {
      result = atan(sqrt(y)) / sqrt(y);
   }
   else
   {
      if(y > -0.5)
      {
         T arg = sqrt(-y);
         result = (boost::math::log1p(arg, pol) - boost::math::log1p(-arg, pol)) / (2 * sqrt(-y));
      }
      else
      {
         result = log((1 + sqrt(-y)) / sqrt(1 + y)) / sqrt(-y);
      }
   }
   return result;
}

template <typename T, typename Policy>
T ellint_rj_imp(T x, T y, T z, T p, const Policy& pol)
{
   BOOST_MATH_STD_USING

   static const char* function = "boost::math::ellint_rj<%1%>(%1%,%1%,%1%)";

   if(x < 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument x must be non-negative, but got x = %1%", x, pol);
   }
   if(y < 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument y must be non-negative, but got y = %1%", y, pol);
   }
   if(z < 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument z must be non-negative, but got z = %1%", z, pol);
   }
   if(p == 0)
   {
      return policies::raise_domain_error<T>(function,
         "Argument p must not be zero, but got p = %1%", p, pol);
   }
   if(x + y == 0 || y + z == 0 || z + x == 0)
   {
      return policies::raise_domain_error<T>(function,
         "At most one argument can be zero, "
         "only possible result is %1%.", std::numeric_limits<T>::quiet_NaN(), pol);
   }

   // for p < 0, the integral is singular, return Cauchy principal value
   if(p < 0)
   {
      //
      // We must ensure that x < y < z.
      // Since the integral is symmetrical in x, y and z
      // we can just permute the values:
      //
      if(x > y)
         std::swap(x, y);
      if(y > z)
         std::swap(y, z);
      if(x > y)
         std::swap(x, y);

      BOOST_MATH_ASSERT(x <= y);
      BOOST_MATH_ASSERT(y <= z);

      T q = -p;
      p = (z * (x + y + q) - x * y) / (z + q);

      BOOST_MATH_ASSERT(p >= 0);

      T value = (p - z) * ellint_rj_imp(x, y, z, p, pol);
      value -= 3 * ellint_rf_imp(x, y, z, pol);
      value += 3 * sqrt((x * y * z) / (x * y + p * q)) * ellint_rc_imp(T(x * y + p * q), T(p * q), pol);
      value /= (z + q);
      return value;
   }

   //
   // Special cases from http://dlmf.nist.gov/19.20#iii
   //
   if(x == y)
   {
      if(x == z)
      {
         if(x == p)
         {
            // All values equal:
            return 1 / (x * sqrt(x));
         }
         else
         {
            // x = y = z:
            return 3 * (ellint_rc_imp(x, p, pol) - 1 / sqrt(x)) / (x - p);
         }
      }
      else
      {
         // x = y only, permute so y = z:
         using std::swap;
         swap(x, z);
         if(y == p)
         {
            return ellint_rd_imp(x, y, y, pol);
         }
         else if((std::max)(y, p) / (std::min)(y, p) > 1.2)
         {
            return 3 * (ellint_rc_imp(x, y, pol) - ellint_rc_imp(x, p, pol)) / (p - y);
         }
         // Otherwise fall through to normal method, special case above will suffer too much cancellation...
      }
   }
   if(y == z)
   {
      if(y == p)
      {
         // y = z = p:
         return ellint_rd_imp(x, y, y, pol);
      }
      else if((std::max)(y, p) / (std::min)(y, p) > 1.2)
      {
         // y = z:
         return 3 * (ellint_rc_imp(x, y, pol) - ellint_rc_imp(x, p, pol)) / (p - y);
      }
      // Otherwise fall through to normal method, special case above will suffer too much cancellation...
   }
   if(z == p)
   {
      return ellint_rd_imp(x, y, z, pol);
   }

   T xn = x;
   T yn = y;
   T zn = z;
   T pn = p;
   T An = (x + y + z + 2 * p) / 5;
   T A0 = An;
   T delta = (p - x) * (p - y) * (p - z);
   T Q = pow(tools::epsilon<T>() / 5, -T(1) / 8) * (std::max)((std::max)(fabs(An - x), fabs(An - y)), (std::max)(fabs(An - z), fabs(An - p)));

   unsigned n;
   T lambda;
   T Dn;
   T En;
   T rx, ry, rz, rp;
   T fmn = 1; // 4^-n
   T RC_sum = 0;

   for(n = 0; n < policies::get_max_series_iterations<Policy>(); ++n)
   {
      rx = sqrt(xn);
      ry = sqrt(yn);
      rz = sqrt(zn);
      rp = sqrt(pn);
      Dn = (rp + rx) * (rp + ry) * (rp + rz);
      En = delta / Dn;
      En /= Dn;
      if((En < -0.5) && (En > -1.5))
      {
         //
         // Occasionally En ~ -1, we then have no means of calculating
         // RC(1, 1+En) without terrible cancellation error, so we
         // need to get to 1+En directly.  By substitution we have
         //
         // 1+E_0 = 1 + (p-x)*(p-y)*(p-z)/((sqrt(p) + sqrt(x))*(sqrt(p)+sqrt(y))*(sqrt(p)+sqrt(z)))^2
         //       = 2*sqrt(p)*(p+sqrt(x) * (sqrt(y)+sqrt(z)) + sqrt(y)*sqrt(z)) / ((sqrt(p) + sqrt(x))*(sqrt(p) + sqrt(y)*(sqrt(p)+sqrt(z))))
         //
         // And since this is just an application of the duplication formula for RJ, the same
         // expression works for 1+En if we use x,y,z,p_n etc.
         // This branch is taken only once or twice at the start of iteration,
         // after than En reverts to it's usual very small values.
         //
         T b = 2 * rp * (pn + rx * (ry + rz) + ry * rz) / Dn;
         RC_sum += fmn / Dn * detail::ellint_rc_imp(T(1), b, pol);
      }
      else
      {
         RC_sum += fmn / Dn * ellint_rc1p_imp(En, pol);
      }
      lambda = rx * ry + rx * rz + ry * rz;

      // From here on we move to n+1:
      An = (An + lambda) / 4;
      fmn /= 4;

      if(fmn * Q < An)
         break;

      xn = (xn + lambda) / 4;
      yn = (yn + lambda) / 4;
      zn = (zn + lambda) / 4;
      pn = (pn + lambda) / 4;
      delta /= 64;
   }

   T X = fmn * (A0 - x) / An;
   T Y = fmn * (A0 - y) / An;
   T Z = fmn * (A0 - z) / An;
   T P = (-X - Y - Z) / 2;
   T E2 = X * Y + X * Z + Y * Z - 3 * P * P;
   T E3 = X * Y * Z + 2 * E2 * P + 4 * P * P * P;
   T E4 = (2 * X * Y * Z + E2 * P + 3 * P * P * P) * P;
   T E5 = X * Y * Z * P * P;
   T result = fmn * pow(An, T(-3) / 2) *
      (1 - 3 * E2 / 14 + E3 / 6 + 9 * E2 * E2 / 88 - 3 * E4 / 22 - 9 * E2 * E3 / 52 + 3 * E5 / 26 - E2 * E2 * E2 / 16
      + 3 * E3 * E3 / 40 + 3 * E2 * E4 / 20 + 45 * E2 * E2 * E3 / 272 - 9 * (E3 * E4 + E2 * E5) / 68);

   result += 6 * RC_sum;
   return result;
}

} // namespace detail

template <class T1, class T2, class T3, class T4, class Policy>
inline typename tools::promote_args<T1, T2, T3, T4>::type 
   ellint_rj(T1 x, T2 y, T3 z, T4 p, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3, T4>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rj_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y),
         static_cast<value_type>(z),
         static_cast<value_type>(p),
         pol), "boost::math::ellint_rj<%1%>(%1%,%1%,%1%,%1%)");
}

template <class T1, class T2, class T3, class T4>
inline typename tools::promote_args<T1, T2, T3, T4>::type 
   ellint_rj(T1 x, T2 y, T3 z, T4 p)
{
   return ellint_rj(x, y, z, p, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RJ_HPP


/* ellint_rj.hpp
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
*/