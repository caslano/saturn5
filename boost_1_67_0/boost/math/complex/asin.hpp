//  (C) Copyright John Maddock 2005.
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ASIN_INCLUDED
#define BOOST_MATH_COMPLEX_ASIN_INCLUDED

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
inline std::complex<T> asin(const std::complex<T>& z)
{
   //
   // This implementation is a transcription of the pseudo-code in:
   //
   // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
   // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
   // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
   //

   //
   // These static constants should really be in a maths constants library,
   // note that we have tweaked the value of a_crossover as per https://svn.boost.org/trac/boost/ticket/7290:
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
   T real, imag;  // our results

   //
   // Begin by handling the special cases for infinities and nan's
   // specified in C99, most of this is handled by the regular logic
   // below, but handling it as a special case prevents overflow/underflow
   // arithmetic which may trip up some machines:
   //
   if((boost::math::isnan)(x))
   {
      if((boost::math::isnan)(y))
         return std::complex<T>(x, x);
      if((boost::math::isinf)(y))
      {
         real = x;
         imag = std::numeric_limits<T>::infinity();
      }
      else
         return std::complex<T>(x, x);
   }
   else if((boost::math::isnan)(y))
   {
      if(x == 0)
      {
         real = 0;
         imag = y;
      }
      else if((boost::math::isinf)(x))
      {
         real = y;
         imag = std::numeric_limits<T>::infinity();
      }
      else
         return std::complex<T>(y, y);
   }
   else if((boost::math::isinf)(x))
   {
      if((boost::math::isinf)(y))
      {
         real = quarter_pi;
         imag = std::numeric_limits<T>::infinity();
      }
      else
      {
         real = half_pi;
         imag = std::numeric_limits<T>::infinity();
      }
   }
   else if((boost::math::isinf)(y))
   {
      real = 0;
      imag = std::numeric_limits<T>::infinity();
   }
   else
   {
      //
      // special case for real numbers:
      //
      if((y == 0) && (x <= one))
         return std::complex<T>(std::asin(z.real()), z.imag());
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
            real = std::asin(b);
         }
         else
         {
            T apx = a + x;
            if(x <= one)
            {
               real = std::atan(x/std::sqrt(half * apx * (yy /(r + xp1) + (s-xm1))));
            }
            else
            {
               real = std::atan(x/(y * std::sqrt(half * (apx/(r + xp1) + apx/(s+xm1)))));
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
         // This is the Hull et al exception handling code from Fig 3 of their paper:
         //
         if(y <= (std::numeric_limits<T>::epsilon() * std::fabs(xm1)))
         {
            if(x < one)
            {
               real = std::asin(x);
               imag = y / std::sqrt(-xp1*xm1);
            }
            else
            {
               real = half_pi;
               if(((std::numeric_limits<T>::max)() / xp1) > xm1)
               {
                  // xp1 * xm1 won't overflow:
                  imag = boost::math::log1p(xm1 + std::sqrt(xp1*xm1));
               }
               else
               {
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
            real = half_pi - std::sqrt(y);
            imag = std::sqrt(y);
         }
         else if(std::numeric_limits<T>::epsilon() * y - one >= x)
         {
            real = x/y; // This can underflow!
            imag = log_two + std::log(y);
         }
         else if(x > one)
         {
            real = std::atan(x/y);
            T xoy = x/y;
            imag = log_two + std::log(y) + half * boost::math::log1p(xoy*xoy);
         }
         else
         {
            T a = std::sqrt(one + y*y);
            real = x/a; // This can underflow!
            imag = half * boost::math::log1p(static_cast<T>(2)*y*(y+a));
         }
      }
   }

   //
   // Finish off by working out the sign of the result:
   //
   if((boost::math::signbit)(z.real()))
      real = (boost::math::changesign)(real);
   if((boost::math::signbit)(z.imag()))
      imag = (boost::math::changesign)(imag);

   return std::complex<T>(real, imag);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ASIN_INCLUDED

/* asin.hpp
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
*/