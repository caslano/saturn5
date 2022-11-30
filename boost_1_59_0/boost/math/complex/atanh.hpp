//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#define BOOST_MATH_COMPLEX_ATANH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_LOG1P_INCLUDED
#  include <boost/math/special_functions/log1p.hpp>
#endif
#include <boost/math/tools/assert.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::sqrt; using ::fabs; using ::acos; using ::asin; using ::atan; using ::atan2; }
#endif

namespace boost{ namespace math{

template<class T> 
std::complex<T> atanh(const std::complex<T>& z)
{
   //
   // References:
   //
   // Eric W. Weisstein. "Inverse Hyperbolic Tangent." 
   // From MathWorld--A Wolfram Web Resource. 
   // http://mathworld.wolfram.com/InverseHyperbolicTangent.html
   //
   // Also: The Wolfram Functions Site,
   // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/
   //
   // Also "Abramowitz and Stegun. Handbook of Mathematical Functions."
   // at : http://jove.prohosting.com/~skripty/toc.htm
   //
   // See also: https://svn.boost.org/trac/boost/ticket/7291
   //
   
   static const T pi = boost::math::constants::pi<T>();
   static const T half_pi = pi / 2;
   static const T one = static_cast<T>(1.0L);
   static const T two = static_cast<T>(2.0L);
   static const T four = static_cast<T>(4.0L);
   static const T zero = static_cast<T>(0);
   static const T log_two = boost::math::constants::ln_two<T>();

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif

   T x = std::fabs(z.real());
   T y = std::fabs(z.imag());

   T real, imag;  // our results

   T safe_upper = detail::safe_max(two);
   T safe_lower = detail::safe_min(static_cast<T>(2));

   //
   // Begin by handling the special cases specified in C99:
   //
   if((boost::math::isnan)(x))
   {
      if((boost::math::isnan)(y))
         return std::complex<T>(x, x);
      else if((boost::math::isinf)(y))
         return std::complex<T>(0, ((boost::math::signbit)(z.imag()) ? -half_pi : half_pi));
      else
         return std::complex<T>(x, x);
   }
   else if((boost::math::isnan)(y))
   {
      if(x == 0)
         return std::complex<T>(x, y);
      if((boost::math::isinf)(x))
         return std::complex<T>(0, y);
      else
         return std::complex<T>(y, y);
   }
   else if((x > safe_lower) && (x < safe_upper) && (y > safe_lower) && (y < safe_upper))
   {

      T yy = y*y;
      T mxm1 = one - x;
      ///
      // The real part is given by:
      // 
      // real(atanh(z)) == log1p(4*x / ((x-1)*(x-1) + y^2))
      // 
      real = boost::math::log1p(four * x / (mxm1*mxm1 + yy));
      real /= four;
      if((boost::math::signbit)(z.real()))
         real = (boost::math::changesign)(real);

      imag = std::atan2((y * two), (mxm1*(one+x) - yy));
      imag /= two;
      if(z.imag() < 0)
         imag = (boost::math::changesign)(imag);
   }
   else
   {
      //
      // This section handles exception cases that would normally cause
      // underflow or overflow in the main formulas.
      //
      // Begin by working out the real part, we need to approximate
      //    real = boost::math::log1p(4x / ((x-1)^2 + y^2))
      // without either overflow or underflow in the squared terms.
      //
      T mxm1 = one - x;
      if(x >= safe_upper)
      {
         // x-1 = x to machine precision:
         if((boost::math::isinf)(x) || (boost::math::isinf)(y))
         {
            real = 0;
         }
         else if(y >= safe_upper)
         {
            // Big x and y: divide through by x*y:
            real = boost::math::log1p((four/y) / (x/y + y/x));
         }
         else if(y > one)
         {
            // Big x: divide through by x:
            real = boost::math::log1p(four / (x + y*y/x));
         }
         else
         {
            // Big x small y, as above but neglect y^2/x:
            real = boost::math::log1p(four/x);
         }
      }
      else if(y >= safe_upper)
      {
         if(x > one)
         {
            // Big y, medium x, divide through by y:
            real = boost::math::log1p((four*x/y) / (y + mxm1*mxm1/y));
         }
         else
         {
            // Small or medium x, large y:
            real = four*x/y/y;
         }
      }
      else if (x != one)
      {
         // y is small, calculate divisor carefully:
         T div = mxm1*mxm1;
         if(y > safe_lower)
            div += y*y;
         real = boost::math::log1p(four*x/div);
      }
      else
         real = boost::math::changesign(two * (std::log(y) - log_two));

      real /= four;
      if((boost::math::signbit)(z.real()))
         real = (boost::math::changesign)(real);

      //
      // Now handle imaginary part, this is much easier,
      // if x or y are large, then the formula:
      //    atan2(2y, (1-x)*(1+x) - y^2)
      // evaluates to +-(PI - theta) where theta is negligible compared to PI.
      //
      if((x >= safe_upper) || (y >= safe_upper))
      {
         imag = pi;
      }
      else if(x <= safe_lower)
      {
         //
         // If both x and y are small then atan(2y),
         // otherwise just x^2 is negligible in the divisor:
         //
         if(y <= safe_lower)
            imag = std::atan2(two*y, one);
         else
         {
            if((y == zero) && (x == zero))
               imag = 0;
            else
               imag = std::atan2(two*y, one - y*y);
         }
      }
      else
      {
         //
         // y^2 is negligible:
         //
         if((y == zero) && (x == one))
            imag = 0;
         else
            imag = std::atan2(two*y, mxm1*(one+x));
      }
      imag /= two;
      if((boost::math::signbit)(z.imag()))
         imag = (boost::math::changesign)(imag);
   }
   return std::complex<T>(real, imag);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ATANH_INCLUDED

/* atanh.hpp
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
*/