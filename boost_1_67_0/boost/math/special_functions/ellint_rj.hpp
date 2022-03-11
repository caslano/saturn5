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
         result = (boost::math::log1p(arg) - boost::math::log1p(-arg)) / (2 * sqrt(-y));
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

      BOOST_ASSERT(x <= y);
      BOOST_ASSERT(y <= z);

      T q = -p;
      p = (z * (x + y + q) - x * y) / (z + q);

      BOOST_ASSERT(p >= 0);

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