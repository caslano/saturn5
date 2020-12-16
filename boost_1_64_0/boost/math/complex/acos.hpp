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
kfy+JGZ+qxs9G+nznOA57i7bs5HC7VLe/NVQ22h/5jN2w8vxyATSaJTjJVqOxhlKxItriZfcyxRyT8O35s0kSRRlpR7nIpfjX0Ewb+rH1ph5021dLLCk92fJm/2b/THypiAivS1JpPfCiPQSFteEZXlfoC0l+TUf+zWl2Gtr1xcF7q/cmXniXsPf2fTbe4vvyN1vyzrOE8kM3L9+50Nmft7ntKuOWJCz9Omrz1jEeRorBe5P+nHUWtN/OOyEhVvskv9531OOjLVWE3ttZ2PeU8D+dTe9+fAAb+2DS07uWCnrgY1jr5XZr0HFWuNKfq0v2bXEbMmHY6+56KUPHvd6j3p8h7n1p17NoSpbyH3/4JO+P2q7C3c5bu2dLskq7vd+rDWo5NcS7dcGk1/T6621O9H7N/pwbaNLwvT+oeX9gE6118fGXrbF3lK1t3Jc/7TPAYPj2kPUXl4Me7Oov3LWwEhPt+uB/nkpron4NxM5G1mILEbe4FkXzNoGNw+ba4W6Togb7s9E5geu4flIe0C4XgIXw2Uwc9vgWmIRnIpErin6uNeKGGuL7fy9FCms5DlyIvfq4PlwLrzPXHfkHtc3I0P4uxNOgl2wAs5C8rcLX5P0cn0frIRzkY/5+2y4DC6Ei5DI9cqPuZexfXDdchQsQTLag2uYNfw95JHotcy53J+PTN6MZ7Aapu1AXGARnAcroQ9pRW5HliDzub8QWcbfkeucRZa1zvzp+AWLYCVybAnxJR5nwzqude2TQ3i4hywJXLfjH7w9cI38ilTiJq2UeMCCGcQXqUZORBYgxprpYv5eivyKlHA9cEfCQxr4exZsQdoQY021g7+XIJFrq66diDtSjESus87k3lxkPtKO1HBvCTwxYu31c+69ATNmUkeQCqQBmYdYv63bNjO0FruYv99HItdkXTsTVzgKTkWqkc6AHTgfWcrfV9KGOpA3kGXIwLWc9yUc4xjH/H/Mipn/z/HtW//Xv/83TOf/3iY5o3nz6TuUl1ZuXrVD5bTScl0FEDtr8aKkP8rOloYVWSfYzvKtvvk26wRXBs4/nybzsoiAZLVA5mdtQ2POz3Db87UC/JU5V9i31FLs1wpa7eIoM//E1wxmNkWtGZjhttisGVxF3nTYhiuHqie9dmCEVZgaXQ5XE9bS6LC21GKQcng4Tjks/Qvl8LCWg/WMhvNT7cvBVREdRzIz4TK4OU4ZpKVFl8E15EuWTZhSBH+hDEalR6/fXEdY3gpz/Sa8zLUMFsReq8Bt4us43orE13G8FT1fx1nQg3UczSPmwtF5tMvq6BbZ59GWxtrizNVj51FlEnlUmUQeVf6FPJq5es/zyNs3eq1rIXnuqzDWuiLrUfd9qq8i8TUvX0XP17yIQ+w1L2ufnBGdxt3Js1bbNFIPEuivWpNIY+tfSOPDQ1fsup79elzy633261ax1gGTX+9rkPW+9249Y9PTd3moce7ROZXXbvzhuN5b77Nfj1v+64D/9XU9GW9pf9QVsW62qmV9rVXt9bGxN8hir0PtrdyNf0vjhLtmyB4ZHTvcNSz2ssz1xPj+edXe4G7iV2nai++fT+3ldZd/seypf35dnywcFVyfnDrK46xR9vIa5V9Zn5x6ferfskb5X1+fnLgwdbmsUTbQflqRm5EXkWVI/miPayIyCzkMaRvd83XLFTT/r9+7F/f/Fx9g7v/vsOUW4fv/O3Sz/z9sFL8VW+l+t3pg3f/vG3uMjruezyXxN2ouuUjn1jwSMxSZRvw6IuLHZ/a8xveERvPc7SI/9by6HLhY7OfZxhm/zPHko6vJ94VmN+wd+pbpInmeZTu+xK35HfVFQbc19XvXzvG7Qu5fFDv97eY=
*/