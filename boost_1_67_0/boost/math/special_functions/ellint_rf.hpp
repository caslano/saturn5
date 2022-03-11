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