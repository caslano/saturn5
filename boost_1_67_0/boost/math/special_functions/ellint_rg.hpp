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
      
      BOOST_ASSERT(x >= z);
      BOOST_ASSERT(z >= y);
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