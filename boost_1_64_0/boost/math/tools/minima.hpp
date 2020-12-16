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
+G7yvw/p7gaLNQ7/+du2zc0yGMUiGQgd/Y/2Mgh/ycZLtUyIEy+vNENvQc3OnTnHd7hv1KzK8gwAfOuE81xj85QiyL0klIUnrKl/dz5h89wYN1Ua134kaLbuxP+ftPHTdR1BCpGPJ59ObJCDbJwo/cJLIynaC0h87J2xsTeEMPIGMvVxx2UINdibbexjk0jKzA8TYe/CGuxxJrfMgyaWscSx1JG7xrBNE0a5l0c4jjq+xE86dV3lflLmtb01jBwk/zabZyqQQRT6TaxP3Dr+uS5w+bWfN1Ankb006cj/Iq/DPEujMs7Q9ZUTF+abPC9ZmZRlmQjcx+N5+YGNrUSutofLUIruHhLVz++4/sZq5y+rfMFvpTpzeKdOmyT0yjoS3eU+lXnsoq2PeVnkZd2kwjqKoDJvt7GPzWuvTCppdgb42uuai86Zow/6kDal6DjjdGLoXOTnjYGvliKJYC5/3DsBfO2SprLIqiAS1jM0LArN+WZsnoMya5KqSTyBAynNKc0cmqeRhE1TRXWDHZ3V7d62DtYuOn78ElnmMgmF6+zMuQP3GmcNmOdVXGZhc0fXgA+ENeu1MF8483WQ1737+nyIcKbXvA+4N8zpEKPMBdI0/0N3Qzm+oWnUM1sA/KMwKrbMRcSY3kUYI+fCNxFjabCdj+shHxPfAoy5mz134qQa87AcexiN5D8E6c/R9I6CIZLq42OIM9oxQtZfEMMbCoHWPHbnJkiXyQLP9Bb9dpeux2EaS5vNLp37LP0m0emg0r6XO4F0p8yQC7rPPhrTmd+8dMtoHOSI5qijMSpXNF/cCphu3UGWSM72baMwfB50+0iMzg75qtk+EgPZIcw7NWbUgal1T/AqwNg67rTjv126045n7uzQnXbcscOhO+04QLrVR7HGCLP7Ll0MZoPmbqMwi9CX6f51h+7GkzmnMWgLdB6IdtNdiYZpU0w+iwZpGp50J31307pAtMMNJmb44JdofP76Z0aDxCy+mV0WzannLyDNtkFuPd989y7Greexa7oYu55PjqLrrJBO/BkxRh0dnXvNPRy6o3N77+nQHZ07Y9EpA0Qfu5eiwwV9+8G2/VZhN9Gd/m4w6b0Jw/sgpbN0nxZj6b+Vzqn7Et3WS3t9efue0Ri87ktvI+63Ae7YGsWyvJYwSiftOjt7f05D+Yb3pddxui335gcw2uHGknvygQ7Nvaf8IJcOgu0YbHuJbuuUnfebH2ww1Oa2D7OHjKDrfBDmOQ8dgdF5oXTC6xVmcf/CBnqz92FE30hvdjycMBvpzSWDGa03P3kE0TfSm88/kjCX05uzj3JxXb15zaMJ4+rNcx5DtFF6IyY53ZZ73T6iuXrzH6KN1Jvf7Sf6KL354gGib6Q356YIM0pvbp126V29WbgBMV29If+fj1WYQV8f3qNPIOP/80aLxn04UuxSO76zjm4a4IOMw8M9SjFlsD+xsbI394JeB2vO0H5hY7MVgMGGxotdBm9l4fDa4kqg3jyJg7avpF/Z/KF6E9ZNDCArbd5+58a9PrG+DvfrZo6r2BrZglKVqWvbu942dmap76lwV4B4YLuP4tBB3FPVXhGkONdi/uJgDiMGSjHXpvNXBxOv90AG+d1+ztftNUkhorDMQz+/8ngqUDiBPqA2gy2TGehIBGGGnz6MsbIFvjWHZuRscCibyQJPgsEIZtSrpTDyn5LoOAbbNsKgH2kVBzo49PRmpp6dSVU841lZA0rRNK9suoyj+cCcYV53Ea2uggj0i+Klzjlc6E0Ddry4L8pT4x2svps1p9b+C7S3+5xNXZx+IjjUD8CSzF+NxnbT3tzFwS1FBBLutokuTm2W45SDfDpuGY3DqYXBjW0=
*/