//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_MATH_TOOLS_MINIMA_HPP
#define BOOST_MATH_TOOLS_MINIMA_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdint>
#include <cmath>
#include <utility>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/policy.hpp>

namespace boost{ namespace math{ namespace tools{

template <class F, class T>
std::pair<T, T> brent_find_minima(F f, T min, T max, int bits, std::uintmax_t& max_iter)
   noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   BOOST_MATH_STD_USING
   bits = (std::min)(policies::digits<T, policies::policy<> >() / 2, bits);
   T tolerance = static_cast<T>(ldexp(1.0, 1-bits));
   T x;  // minima so far
   T w;  // second best point
   T v;  // previous value of w
   T u;  // most recent evaluation point
   T delta;  // The distance moved in the last step
   T delta2; // The distance moved in the step before last
   T fu, fv, fw, fx;  // function evaluations at u, v, w, x
   T mid; // midpoint of min and max
   T fract1, fract2;  // minimal relative movement in x

   static const T golden = 0.3819660f;  // golden ratio, don't need too much precision here!

   x = w = v = max;
   fw = fv = fx = f(x);
   delta2 = delta = 0;

   uintmax_t count = max_iter;

   do{
      // get midpoint
      mid = (min + max) / 2;
      // work out if we're done already:
      fract1 = tolerance * fabs(x) + tolerance / 4;
      fract2 = 2 * fract1;
      if(fabs(x - mid) <= (fract2 - (max - min) / 2))
         break;

      if(fabs(delta2) > fract1)
      {
         // try and construct a parabolic fit:
         T r = (x - w) * (fx - fv);
         T q = (x - v) * (fx - fw);
         T p = (x - v) * q - (x - w) * r;
         q = 2 * (q - r);
         if(q > 0)
            p = -p;
         q = fabs(q);
         T td = delta2;
         delta2 = delta;
         // determine whether a parabolic step is acceptable or not:
         if((fabs(p) >= fabs(q * td / 2)) || (p <= q * (min - x)) || (p >= q * (max - x)))
         {
            // nope, try golden section instead
            delta2 = (x >= mid) ? min - x : max - x;
            delta = golden * delta2;
         }
         else
         {
            // whew, parabolic fit:
            delta = p / q;
            u = x + delta;
            if(((u - min) < fract2) || ((max- u) < fract2))
               delta = (mid - x) < 0 ? (T)-fabs(fract1) : (T)fabs(fract1);
         }
      }
      else
      {
         // golden section:
         delta2 = (x >= mid) ? min - x : max - x;
         delta = golden * delta2;
      }
      // update current position:
      u = (fabs(delta) >= fract1) ? T(x + delta) : (delta > 0 ? T(x + fabs(fract1)) : T(x - fabs(fract1)));
      fu = f(u);
      if(fu <= fx)
      {
         // good new point is an improvement!
         // update brackets:
         if(u >= x)
            min = x;
         else
            max = x;
         // update control points:
         v = w;
         w = x;
         x = u;
         fv = fw;
         fw = fx;
         fx = fu;
      }
      else
      {
         // Oh dear, point u is worse than what we have already,
         // even so it *must* be better than one of our endpoints:
         if(u < x)
            min = u;
         else
            max = u;
         if((fu <= fw) || (w == x))
         {
            // however it is at least second best:
            v = w;
            w = u;
            fv = fw;
            fw = fu;
         }
         else if((fu <= fv) || (v == x) || (v == w))
         {
            // third best:
            v = u;
            fv = fu;
         }
      }

   }while(--count);

   max_iter -= count;

   return std::make_pair(x, fx);
}

template <class F, class T>
inline std::pair<T, T> brent_find_minima(F f, T min, T max, int digits)
   noexcept(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   std::uintmax_t m = (std::numeric_limits<std::uintmax_t>::max)();
   return brent_find_minima(f, min, max, digits, m);
}

}}} // namespaces

#endif





/* minima.hpp
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
*/