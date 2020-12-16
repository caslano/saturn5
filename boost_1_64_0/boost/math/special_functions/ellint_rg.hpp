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
fFvOLn6bltDvk6+24Ivgg9Z2eg1xckyj/iidWQmdWcd66zOeFjfG6hfW0y3J97V46bKM0L8N/Wk4EX/Tfrpxz8UTHYqvPBvvvx5f0kqPuYJdwGP5t6tXNsKR+vtFdLJTytnVH9Xz/HvoEnwanVreSPP0LX+9Ur17ozh8tj7zaH2DcL3h+DenwyXynvhSWSyPyH855qf6wyiOhu+n68dUiLfqkQ2xTrRKXflXec77abrVIZ305XnstJUddxwJ1we9W/je6/AdfmHIULxU/P7188SrD9Qr+NgNdDVdwQ/DNsf8LKb3GBvjNNe1x/XCTUPFs9HqhZRy8WuaPskP8Bx48zZ80aiB9A7D7N8prjXDXX+Ha9apH/AEuer4Xnh+/N1wxsns33g1HYb3eYqfzje/19MP48WLVvo8yzq8Cfp47KP4d3Sq4mMZu6v/q/xfBtfLw3lZ9C2xbuTwdH0aefBDvO4vXU/gdcN51Yllr5jH55P2k3iVzuoocfoOegTjUfstv/rY/jPpjo6B+5bA60FvFs5jfjrVky3stst26FX6qlezn7lhG+IdnJGDV34Pf9YlX7r+3XjANjxAC/ze+ArcdCkea1G0Df+P36N0Cx4TDiuN+1GVGfySn50X9RPDeW7jn8Few+8/Na4vqBfVO8WT8ex/Ua/CaxWL9LmDH4fPVXDnNfrS830ehm+/2/VfID6F+jLsP4DuId88XIFPwff31MAzL7LTXnat7s2HN1Ja5aF8cTgL/2NcBn8Pb39N+H/Qj+CD4/d13Ab3wXG9V6Un13llDEjqcS9mh+LY6uZU+Fr/LuC9sL1MvyDF+D3geOfRIeEn6sfDM/jF6nfUAd6TXvoRO6DjKY6eY3FOmL9bE3gHfG6T8wV9Qth/o3WCpwRcH13/MvlyHrt8nD19krBuw/Hh5pxH99cP4pf0z7W/CH3QwGfKX/vzf7rx4XiBNX/T74iu9+ww7uxjRbif8PmggXQ8jiNuV3ouQIo4v3YK3usE9fx56tKP8ThhvMNx9+K5voBb/4Hvy7K+JF6ffoHx2u69kcahDS/S7PkKpeJEw+vqlRPwp+rBqkuMi9+VhfWHYSsu1wyM13/JP+qW0dfJG1Ed978wnofgS25OTdrXueLu+WEb+q7J8c75D77qSnxQMX87U7xdBs8Psz6Rjjofni88yHW9pb7Pw59Uwi1rMpJ4o5c9d9PlNOBFt4gPH7Kr3rANehc47wX9vajvsygl6PUz8Bvm+356L35Svk2dEOsdf6cO3d98vQ2X3AuvBZ41bJ+Dq1PT6BSN6xPqum1wGT+dW4Kn6YU7npTv5d8GeL56nj7/8fQ/V4qj2+EzcXuDenTZNerxh8X7D+E8OrIWzyFbIO7WLjfu0+mX5Iluflrq/vfgTTLh5vwt+qmr1EHqmDHBbsLxxddmeqq2sXDC75PHzf5YPL2DHnwyftJ7Whusgy9+A78TvRfulPA79tr4O/79SKyTh0fL5asLrbuCjwvi93jQm8xlXxUTYz29unuzOD4HDlksLx7Pn1+gP1A3tF3GXjz/oWWGuP8JXrKGX3SK81PcP71c613q9pfh+L3+PyCd3gtOMb/NV6i7f2cb6sOwZXed6szhN/Ln38L3cX3s+RnVH6gfbo3iebj+p/Cq7L9jBzzzEv7mNHrMc9nNSHXyNPye/teojfDO9P3pc8S/Zvn7b3RInms617raqYeG9ZfhfcTyYtw/h5fzDne/cG3FAc7zG/2PI+XjWXjin7PbgmS/d2GD3+FNC72/ocbxGiap68XnYfqwuzcmkscdCg/OpZ8aoa4pUv/G72WoxjPe5rr18xIJPMuJ6t6bva9wlbzerA6dLU/hZQefJ/8=
*/