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
8Zx15rPwqHBt203mCz+XtRTPBnd0v6Ke7FRHzRdvX7TNx6upH3aroxaGPmj4fL7+oesbJq/VGN8d5exjtTySS6+yI16foG/xAzzbL70XBm+eVakvVMR+4nUkdPgpsS7xf/iBH+vzDpc30+gBnpIvhosn/C1zos/RvO8XxotusBCPsawLTqcba1O3jplEf3SO+8VXFtxNtw7fZi7g5xvwSHiDPbN8dvzhJ7pO/ZCs69j3IPgGL1XZhsc5Ndkn6Tlbvr0czj7feEf61yOCn492XaudVx3a3mW84NncCnGuWn1+AV0VfJ6vniqdLI49rd8Brw3LS1jHKb/RJ5eeZBzuCXxHWC+Ad8fzF8Jv5dE4VYTj0U1tUM/Wh3kNn8eKF1f3T/qzPmbeWHXZeH3mm9izeqdmFfuBN+rCOt6wFa+rn2Tff9U/2oI3fMZ1BH4ufN4sn5/Ljwcn645RfpfDPhv4Tav6fsgH6lC87ZqXzWvEQ+SF+TYPefj8jivwYEEXGvbH+ogt/HwrHNFlfA/WT1AfjnpJ3n2bfW3SB7c+YO095h3fV7hdv4ReIfEMHYh819sfPswU3x/h58+Iezvh+6C/CPtvpsOJnp80OPwOTzF+m3oGXmywnrLkan70Q3EcH1B3LP9L6a++Vi/diAfDtxbwnyF4xKwZA/RV1Lv4kd4vw/7Am4pXPzIveIFK7yfIktcSp3gu2FsZ9JjGYZU+uO2eO+lkzpHvK/BeV6lbdqj3+E95FX1cjfxWok91u+N20Pe9E7Yhv4Rt4L3pYdLZ1YHm79fi8kB+dJ788VAmXZh+7074KlP/IuDZ8Lt4PVATXHe8ePat+LnZ/d1GB1gLh/Xo6/qcW6U+dJ6F9+GdDsRveX5/K7urWOo4F8Id/LC7CR/ArjLfwIfQ2+eksi98wdCT8Cb17HKe6z5cf26BuKUf0eF4Xfy6+HXxmv6u7mH9DPG8gj/siPQH6WG+wvnD/lPViSV4/rvpt7rlbX3q8u3iwan4r4Hq08PE4bPY9/Puq40fj1Pv8Nu86PyHB/v8hL/Ig6Pz+Mmd+J9286kuX7AQT3infhgevUYfq+Rx8W8kXox/d9Cd7f5bRr+0YOfns4957OMYuPIQ14/nWu24TafxL9c7+i75Ispb41Kj49A5N85kN3BILdyfE+J3+LwtbIPd2ooXc1PpwhfSW9DTrsHP5uK1x9zLT9vhxwTeGX6o30/csO3Up8pcLa6/ir97SbxqUb++S399OJ3UV3BEHj9mf5n6CgvoDOauNF/em9X1Wdgf+qOZ+FTzLS5lDYLLxKfR0xN0NOrZLHWCdZBZ9+Nr8WP51nOvOMzzQPH1tcZ71EOuy32Ofz5TX8x6vaAvDPvF3+zoPC3hfifCowW2F+trrYv7IXDCMeLSI/ziYf1peuK5LXS/880nfqZ5t+OFvmrYvw3/O0rfohz/Q680Gs4a4r1xJXiCFXV40wnqvp/4DGfleA76aPmzwXyu3sbP4+eeTpYHfo8XcN9lW/nDFDrhLH1v9db4a/jxAc4beKBwnP/iSekwp0bjenLwA9fRIm7lRO+f3C+M03fwf2dbn62OHq2OzpGfC3bSx5wWzVNKWOeo78V+WjroRbw3viJ+b0rwu/DZ+1g75YUW9ewK70vq+YvfHwC/HUdv3AavvO4+L9Vnn6POnMY/lorTF+Pd+pLXlVkORxa4z3PZwUHq8jPTo+9F87NP3+/vmfhh66ym8/dP+OsQ6xjodjLd76675dHN6qT99/P+C8fFH++Jn1vhfWqdf5FPb8J7X+l+32IfI/WL4PHyefqrPfCJeWk9Vp0/AY83Ez9yv/u+3Lh5j1iJ+i9TPVoxxbj/gR+w1yy8+AI=
*/