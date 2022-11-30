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
#include <boost/math/tools/assert.hpp>

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
            BOOST_MATH_ASSERT(x == 1);
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
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ASIN_INCLUDED

/* asin.hpp
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
*/