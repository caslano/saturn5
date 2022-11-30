//  Copyright (c) 2006 Xiaogang Zhang, 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to handle
//  types longer than 80-bit reals.
//  Updated 2015 to use Carlson's latest methods.
//
#ifndef BOOST_MATH_ELLINT_RF_HPP
#define BOOST_MATH_ELLINT_RF_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/ellint_rc.hpp>

// Carlson's elliptic integral of the first kind
// R_F(x, y, z) = 0.5 * \int_{0}^{\infty} [(t+x)(t+y)(t+z)]^{-1/2} dt
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { namespace detail{

   template <typename T, typename Policy>
   T ellint_rf_imp(T x, T y, T z, const Policy& pol)
   {
      BOOST_MATH_STD_USING
      using namespace boost::math;
      using std::swap;

      static const char* function = "boost::math::ellint_rf<%1%>(%1%,%1%,%1%)";

      if(x < 0 || y < 0 || z < 0)
      {
         return policies::raise_domain_error<T>(function,
            "domain error, all arguments must be non-negative, "
            "only sensible result is %1%.",
            std::numeric_limits<T>::quiet_NaN(), pol);
      }
      if(x + y == 0 || y + z == 0 || z + x == 0)
      {
         return policies::raise_domain_error<T>(function,
            "domain error, at most one argument can be zero, "
            "only sensible result is %1%.",
            std::numeric_limits<T>::quiet_NaN(), pol);
      }
      //
      // Special cases from http://dlmf.nist.gov/19.20#i
      //
      if(x == y)
      {
         if(x == z)
         {
            // x, y, z equal:
            return 1 / sqrt(x);
         }
         else
         {
            // 2 equal, x and y:
            if(z == 0)
               return constants::pi<T>() / (2 * sqrt(x));
            else
               return ellint_rc_imp(z, x, pol);
         }
      }
      if(x == z)
      {
         if(y == 0)
            return constants::pi<T>() / (2 * sqrt(x));
         else
            return ellint_rc_imp(y, x, pol);
      }
      if(y == z)
      {
         if(x == 0)
            return constants::pi<T>() / (2 * sqrt(y));
         else
            return ellint_rc_imp(x, y, pol);
      }
      if(x == 0)
         swap(x, z);
      else if(y == 0)
         swap(y, z);
      if(z == 0)
      {
         //
         // Special case for one value zero:
         //
         T xn = sqrt(x);
         T yn = sqrt(y);

         while(fabs(xn - yn) >= 2.7 * tools::root_epsilon<T>() * fabs(xn))
         {
            T t = sqrt(xn * yn);
            xn = (xn + yn) / 2;
            yn = t;
         }
         return constants::pi<T>() / (xn + yn);
      }

      T xn = x;
      T yn = y;
      T zn = z;
      T An = (x + y + z) / 3;
      T A0 = An;
      T Q = pow(3 * boost::math::tools::epsilon<T>(), T(-1) / 8) * (std::max)((std::max)(fabs(An - xn), fabs(An - yn)), fabs(An - zn));
      T fn = 1;


      // duplication
      unsigned k = 1;
      for(; k < boost::math::policies::get_max_series_iterations<Policy>(); ++k)
      {
         T root_x = sqrt(xn);
         T root_y = sqrt(yn);
         T root_z = sqrt(zn);
         T lambda = root_x * root_y + root_x * root_z + root_y * root_z;
         An = (An + lambda) / 4;
         xn = (xn + lambda) / 4;
         yn = (yn + lambda) / 4;
         zn = (zn + lambda) / 4;
         Q /= 4;
         fn *= 4;
         if(Q < fabs(An))
            break;
      }
      // Check to see if we gave up too soon:
      policies::check_series_iterations<T>(function, k, pol);
      BOOST_MATH_INSTRUMENT_VARIABLE(k);

      T X = (A0 - x) / (An * fn);
      T Y = (A0 - y) / (An * fn);
      T Z = -X - Y;

      // Taylor series expansion to the 7th order
      T E2 = X * Y - Z * Z;
      T E3 = X * Y * Z;
      return (1 + E3 * (T(1) / 14 + 3 * E3 / 104) + E2 * (T(-1) / 10 + E2 / 24 - (3 * E3) / 44 - 5 * E2 * E2 / 208 + E2 * E3 / 16)) / sqrt(An);
   }

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rf(T1 x, T2 y, T3 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rf_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y),
         static_cast<value_type>(z), pol), "boost::math::ellint_rf<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rf(T1 x, T2 y, T3 z)
{
   return ellint_rf(x, y, z, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RF_HPP


/* ellint_rf.hpp
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
*/