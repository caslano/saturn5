//  Copyright (c) 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_ELLINT_RG_HPP
#define BOOST_MATH_ELLINT_RG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/pow.hpp>

namespace boost { namespace math { namespace detail{

   template <typename T, typename Policy>
   T ellint_rg_imp(T x, T y, T z, const Policy& pol)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::ellint_rf<%1%>(%1%,%1%,%1%)";

      if(x < 0 || y < 0 || z < 0)
      {
         return policies::raise_domain_error<T>(function,
            "domain error, all arguments must be non-negative, "
            "only sensible result is %1%.",
            std::numeric_limits<T>::quiet_NaN(), pol);
      }
      //
      // Function is symmetric in x, y and z, but we require
      // (x - z)(y - z) >= 0 to avoid cancellation error in the result
      // which implies (for example) x >= z >= y
      //
      using std::swap;
      if(x < y)
         swap(x, y);
      if(x < z)
         swap(x, z);
      if(y > z)
         swap(y, z);
      
      BOOST_MATH_ASSERT(x >= z);
      BOOST_MATH_ASSERT(z >= y);
      //
      // Special cases from http://dlmf.nist.gov/19.20#ii
      //
      if(x == z)
      {
         if(y == z)
         {
            // x = y = z
            // This also works for x = y = z = 0 presumably.
            return sqrt(x);
         }
         else if(y == 0)
         {
            // x = y, z = 0
            return constants::pi<T>() * sqrt(x) / 4;
         }
         else
         {
            // x = z, y != 0
            swap(x, y);
            return (x == 0) ? T(sqrt(z) / 2) : T((z * ellint_rc_imp(x, z, pol) + sqrt(x)) / 2);
         }
      }
      else if(y == z)
      {
         if(x == 0)
            return constants::pi<T>() * sqrt(y) / 4;
         else
            return (y == 0) ? T(sqrt(x) / 2) : T((y * ellint_rc_imp(x, y, pol) + sqrt(x)) / 2);
      }
      else if(y == 0)
      {
         swap(y, z);
         //
         // Special handling for common case, from
         // Numerical Computation of Real or Complex Elliptic Integrals, eq.46
         //
         T xn = sqrt(x);
         T yn = sqrt(y);
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
         return ((boost::math::pow<2>((x0 + y0) / 2) - sum) * RF) / 2;
      }
      return (z * ellint_rf_imp(x, y, z, pol)
         - (x - z) * (y - z) * ellint_rd_imp(x, y, z, pol) / 3
         + sqrt(x * y / z)) / 2;
   }

} // namespace detail

template <class T1, class T2, class T3, class Policy>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rg(T1 x, T2 y, T3 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::ellint_rg_imp(
         static_cast<value_type>(x),
         static_cast<value_type>(y),
         static_cast<value_type>(z), pol), "boost::math::ellint_rf<%1%>(%1%,%1%,%1%)");
}

template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   ellint_rg(T1 x, T2 y, T3 z)
{
   return ellint_rg(x, y, z, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_RG_HPP


/* ellint_rg.hpp
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
*/