//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_MATH_TOOLS_MINIMA_HPP
#define BOOST_MATH_TOOLS_MINIMA_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <utility>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/cstdint.hpp>

namespace boost{ namespace math{ namespace tools{

template <class F, class T>
std::pair<T, T> brent_find_minima(F f, T min, T max, int bits, boost::uintmax_t& max_iter)
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
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
   BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && noexcept(std::declval<F>()(std::declval<T>())))
{
   boost::uintmax_t m = (std::numeric_limits<boost::uintmax_t>::max)();
   return brent_find_minima(f, min, max, digits, m);
}

}}} // namespaces

#endif





/* minima.hpp
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
*/