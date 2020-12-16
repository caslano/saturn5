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
#include <boost/assert.hpp>

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

#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ATANH_INCLUDED

/* atanh.hpp
E7ZFGGPT5VHkuUkhbVGupC2qpcjGkMeNQTO3RZz6ckFGKM3OZqI88vEkUuWfD4oDtYP2yYL+99DHM08tf6gflI/cvroTGP/Rygb43RZ0oHAeCYVL5aGAhcOyS1TuwKu3dw5mYxq1tRPZ81olAxJVgkTljw8jIVGz0YnKm8arnl3wPPL4VaTxGpSLF8ZHbjfHhdRz6IezZxewe0xWnf2SyaSVQaRRtd8xiSZTPiVtqO35zVwB6FCUhx5RPtUdhWH9sLwS5kcPp58GZsOEX75d2MO4XSC/2pyTQ1Gmj4Wn+SbabJmukA7cQzp0ZTVnI+YfqRl0m4Ke2xU/g3bZxvzmuiE9UF9Tl27clsOfJnv/+ME5EUKbrI53XCQ7vc5+e5qJOqn2EUhvUB+aLpAuNr+Ba7uAZPfW6WeGLVw/H6BjsYv0M2tQP78WGuvHbkE/dgv6sQ9DP78WRq+fHDyEQ/0esu8/jfLjHNRPc34jX34ivws4OZl/Ha/N6xHP1dHJ7LUgM9IQIjPiovkyofIlbRwuXyJeZj0i+Sj/75fI57Egn2cY8t0fQb4fgd444zWNYru+kV3ceF7ClXOC9989s/HCm9N/uG/1hNkfrlzw2A6QeyAO9zf8rG1OeWb5M785X9rK1VdXbt0uLl6bamx3F6/RNZ5/IJ5XYTS/wfr8gO/Z/nr0DUbvQx0g2oOQuXRu370U4isiPm3fPbJ3s/d7YBqwBphJdu0c4KHA7YG1wEl0rcbvoXDHCeLfjOPzSvg25ezlPuIrJj7eXl5Idt4iYDLNQ0gBTgZm0HyELYElwG2AZcBtad7BDkAnMJ/b57BsKH14fzTW43iej9I3RiLHCvX9BTif+Gg/S+FaXDvJsytwDHArYDpwInBz4NYkTzZwR+LLBeYAdwVuDywB7gh0AncCVgB3BrqAu9D8gHxgLfk/FJgHPIrut7P7ZG9X3yfoHadDZ2+fQfmwN6XXBSwA7qfpifpdQKaxnsAHkvBlcnxO4kuLEJ7HiI/CWxAPWXaDHRaU8mDQ3h95nbFm/9etM+Zt/6tAtLaYX1dMtn75OuLXLkxQVoPU9cSrgeo64j7QACi4brhTsF54EUhdJ+z/LlFJviiB2f5LQHb8p7XCtE5Ytf3L1wbngsrhV7QuuBb31wATae0vrfslW7/xul9+ze+iYNjgbQMJ1v7ya35pvS+/1le/zlds9xev6YVfYD9w2UUJptbx8mt4lYNC1uvSWl1coyzNBS0ELQWtBK0GJRainIHKQY2gBaAloKcKY3MAYi7mYi7mYi7mYi7mYi7m/qluNNb/t+O3bn57y0is/w/a74/k1vJXkd3VT9/Dj4E+xGCJr5CNRQbjr2s8uq6+cbbJ9VOFQ2ORv6UFedtpHSDtF8ietyo2Zn0HH4YYkzR/6VpYdE+3FrJ1fguEOFY0Xq2L+6RNFbj69tkt4CG7e0ZR8Pk0xLIjC3PQ1jwPim9ohylRs88HWDjxmu3zC3a9gZbWB9j1rdC5at9vZnGw8WwWx94Yx9mO7sFqGryH6y3pzMpPmBGZqVSzkT3CwrxWGY94rwapukb6Dm9phAyUFj/4EBayP57uhYZPNh6UEMxLAXlTItvDxijrjR0MQ4Fy5WvUkKe4R3nK28e4vEkjXqaPEP3uPvY+ln6c75I+eL2Wrj8tDt3zoZNsucuoXN4O+hw8XUUh5RJG2SNNlUv409koj24DaGXjefZ8urKJsoNo3Bz+hesCtXWml7HnYyH7VOiE+JH6aRhhO1PZZqicCtJC+1Fqadlid2bLQx3ZWAvvDebncIQ2hs3sYGtWWa4yFWj16wnGN18pxu9UEEsfcPLuXJyJzF/Qm1ZuH2P+3FiXtQM=
*/