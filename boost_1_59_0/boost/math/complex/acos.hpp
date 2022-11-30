//  (C) Copyright John Maddock 2005.
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ACOS_INCLUDED
#define BOOST_MATH_COMPLEX_ACOS_INCLUDED

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
std::complex<T> acos(const std::complex<T>& z)
{
   //
   // This implementation is a transcription of the pseudo-code in:
   //
   // "Implementing the Complex Arcsine and Arccosine Functions using Exception Handling."
   // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
   // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
   //

   //
   // These static constants should really be in a maths constants library,
   // note that we have tweaked a_crossover as per: https://svn.boost.org/trac/boost/ticket/7290
   //
   static const T one = static_cast<T>(1);
   //static const T two = static_cast<T>(2);
   static const T half = static_cast<T>(0.5L);
   static const T a_crossover = static_cast<T>(10);
   static const T b_crossover = static_cast<T>(0.6417L);
   static const T s_pi = boost::math::constants::pi<T>();
   static const T half_pi = s_pi / 2;
   static const T log_two = boost::math::constants::ln_two<T>();
   static const T quarter_pi = s_pi / 4;
   
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif
   //
   // Get real and imaginary parts, discard the signs as we can 
   // figure out the sign of the result later:
   //
   T x = std::fabs(z.real());
   T y = std::fabs(z.imag());

   T real, imag; // these hold our result

   // 
   // Handle special cases specified by the C99 standard,
   // many of these special cases aren't really needed here,
   // but doing it this way prevents overflow/underflow arithmetic
   // in the main body of the logic, which may trip up some machines:
   //
   if((boost::math::isinf)(x))
   {
      if((boost::math::isinf)(y))
      {
         real = quarter_pi;
         imag = std::numeric_limits<T>::infinity();
      }
      else if((boost::math::isnan)(y))
      {
         return std::complex<T>(y, -std::numeric_limits<T>::infinity());
      }
      else
      {
         // y is not infinity or nan:
         real = 0;
         imag = std::numeric_limits<T>::infinity();
      }
   }
   else if((boost::math::isnan)(x))
   {
      if((boost::math::isinf)(y))
         return std::complex<T>(x, ((boost::math::signbit)(z.imag())) ? std::numeric_limits<T>::infinity() :  -std::numeric_limits<T>::infinity());
      return std::complex<T>(x, x);
   }
   else if((boost::math::isinf)(y))
   {
      real = half_pi;
      imag = std::numeric_limits<T>::infinity();
   }
   else if((boost::math::isnan)(y))
   {
      return std::complex<T>((x == 0) ? half_pi : y, y);
   }
   else
   {
      //
      // What follows is the regular Hull et al code,
      // begin with the special case for real numbers:
      //
      if((y == 0) && (x <= one))
         return std::complex<T>((x == 0) ? half_pi : std::acos(z.real()), (boost::math::changesign)(z.imag()));
      //
      // Figure out if our input is within the "safe area" identified by Hull et al.
      // This would be more efficient with portable floating point exception handling;
      // fortunately the quantities M and u identified by Hull et al (figure 3), 
      // match with the max and min methods of numeric_limits<T>.
      //
      T safe_max = detail::safe_max(static_cast<T>(8));
      T safe_min = detail::safe_min(static_cast<T>(4));

      T xp1 = one + x;
      T xm1 = x - one;

      if((x < safe_max) && (x > safe_min) && (y < safe_max) && (y > safe_min))
      {
         T yy = y * y;
         T r = std::sqrt(xp1*xp1 + yy);
         T s = std::sqrt(xm1*xm1 + yy);
         T a = half * (r + s);
         T b = x / a;

         if(b <= b_crossover)
         {
            real = std::acos(b);
         }
         else
         {
            T apx = a + x;
            if(x <= one)
            {
               real = std::atan(std::sqrt(half * apx * (yy /(r + xp1) + (s-xm1)))/x);
            }
            else
            {
               real = std::atan((y * std::sqrt(half * (apx/(r + xp1) + apx/(s+xm1))))/x);
            }
         }

         if(a <= a_crossover)
         {
            T am1;
            if(x < one)
            {
               am1 = half * (yy/(r + xp1) + yy/(s - xm1));
            }
            else
            {
               am1 = half * (yy/(r + xp1) + (s + xm1));
            }
            imag = boost::math::log1p(am1 + std::sqrt(am1 * (a + one)));
         }
         else
         {
            imag = std::log(a + std::sqrt(a*a - one));
         }
      }
      else
      {
         //
         // This is the Hull et al exception handling code from Fig 6 of their paper:
         //
         if(y <= (std::numeric_limits<T>::epsilon() * std::fabs(xm1)))
         {
            if(x < one)
            {
               real = std::acos(x);
               imag = y / std::sqrt(xp1*(one-x));
            }
            else
            {
               // This deviates from Hull et al's paper as per https://svn.boost.org/trac/boost/ticket/7290
               if(((std::numeric_limits<T>::max)() / xp1) > xm1)
               {
                  // xp1 * xm1 won't overflow:
                  real = y / std::sqrt(xm1*xp1);
                  imag = boost::math::log1p(xm1 + std::sqrt(xp1*xm1));
               }
               else
               {
                  real = y / x;
                  imag = log_two + std::log(x);
               }
            }
         }
         else if(y <= safe_min)
         {
            // There is an assumption in Hull et al's analysis that
            // if we get here then x == 1.  This is true for all "good"
            // machines where :
            // 
            // E^2 > 8*sqrt(u); with:
            //
            // E =  std::numeric_limits<T>::epsilon()
            // u = (std::numeric_limits<T>::min)()
            //
            // Hull et al provide alternative code for "bad" machines
            // but we have no way to test that here, so for now just assert
            // on the assumption:
            //
            BOOST_MATH_ASSERT(x == 1);
            real = std::sqrt(y);
            imag = std::sqrt(y);
         }
         else if(std::numeric_limits<T>::epsilon() * y - one >= x)
         {
            real = half_pi;
            imag = log_two + std::log(y);
         }
         else if(x > one)
         {
            real = std::atan(y/x);
            T xoy = x/y;
            imag = log_two + std::log(y) + half * boost::math::log1p(xoy*xoy);
         }
         else
         {
            real = half_pi;
            T a = std::sqrt(one + y*y);
            imag = half * boost::math::log1p(static_cast<T>(2)*y*(y+a));
         }
      }
   }

   //
   // Finish off by working out the sign of the result:
   //
   if((boost::math::signbit)(z.real()))
      real = s_pi - real;
   if(!(boost::math::signbit)(z.imag()))
      imag = (boost::math::changesign)(imag);

   return std::complex<T>(real, imag);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ACOS_INCLUDED

/* acos.hpp
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
*/