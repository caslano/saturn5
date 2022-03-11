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
#include <boost/assert.hpp>

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
   
#ifdef BOOST_MSVC
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
            BOOST_ASSERT(x == 1);
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
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ACOS_INCLUDED

/* acos.hpp
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
*/