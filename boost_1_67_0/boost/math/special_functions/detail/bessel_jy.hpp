//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JY_HPP
#define BOOST_MATH_BESSEL_JY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/hypot.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/special_functions/detail/bessel_jy_asym.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <complex>

// Bessel functions of the first and second kind of fractional order

namespace boost { namespace math {

   namespace detail {

      //
      // Simultaneous calculation of A&S 9.2.9 and 9.2.10
      // for use in A&S 9.2.5 and 9.2.6.
      // This series is quick to evaluate, but divergent unless
      // x is very large, in fact it's pretty hard to figure out
      // with any degree of precision when this series actually 
      // *will* converge!!  Consequently, we may just have to
      // try it and see...
      //
      template <class T, class Policy>
      bool hankel_PQ(T v, T x, T* p, T* q, const Policy& )
      {
         BOOST_MATH_STD_USING
            T tolerance = 2 * policies::get_epsilon<T, Policy>();
         *p = 1;
         *q = 0;
         T k = 1;
         T z8 = 8 * x;
         T sq = 1;
         T mu = 4 * v * v;
         T term = 1;
         bool ok = true;
         do
         {
            term *= (mu - sq * sq) / (k * z8);
            *q += term;
            k += 1;
            sq += 2;
            T mult = (sq * sq - mu) / (k * z8);
            ok = fabs(mult) < 0.5f;
            term *= mult;
            *p += term;
            k += 1;
            sq += 2;
         }
         while((fabs(term) > tolerance * *p) && ok);
         return ok;
      }

      // Calculate Y(v, x) and Y(v+1, x) by Temme's method, see
      // Temme, Journal of Computational Physics, vol 21, 343 (1976)
      template <typename T, typename Policy>
      int temme_jy(T v, T x, T* Y, T* Y1, const Policy& pol)
      {
         T g, h, p, q, f, coef, sum, sum1, tolerance;
         T a, d, e, sigma;
         unsigned long k;

         BOOST_MATH_STD_USING
            using namespace boost::math::tools;
         using namespace boost::math::constants;

         BOOST_ASSERT(fabs(v) <= 0.5f);  // precondition for using this routine

         T gp = boost::math::tgamma1pm1(v, pol);
         T gm = boost::math::tgamma1pm1(-v, pol);
         T spv = boost::math::sin_pi(v, pol);
         T spv2 = boost::math::sin_pi(v/2, pol);
         T xp = pow(x/2, v);

         a = log(x / 2);
         sigma = -a * v;
         d = abs(sigma) < tools::epsilon<T>() ?
            T(1) : sinh(sigma) / sigma;
         e = abs(v) < tools::epsilon<T>() ? T(v*pi<T>()*pi<T>() / 2)
            : T(2 * spv2 * spv2 / v);

         T g1 = (v == 0) ? T(-euler<T>()) : T((gp - gm) / ((1 + gp) * (1 + gm) * 2 * v));
         T g2 = (2 + gp + gm) / ((1 + gp) * (1 + gm) * 2);
         T vspv = (fabs(v) < tools::epsilon<T>()) ? T(1/constants::pi<T>()) : T(v / spv);
         f = (g1 * cosh(sigma) - g2 * a * d) * 2 * vspv;

         p = vspv / (xp * (1 + gm));
         q = vspv * xp / (1 + gp);

         g = f + e * q;
         h = p;
         coef = 1;
         sum = coef * g;
         sum1 = coef * h;

         T v2 = v * v;
         T coef_mult = -x * x / 4;

         // series summation
         tolerance = policies::get_epsilon<T, Policy>();
         for (k = 1; k < policies::get_max_series_iterations<Policy>(); k++)
         {
            f = (k * f + p + q) / (k*k - v2);
            p /= k - v;
            q /= k + v;
            g = f + e * q;
            h = p - k * g;
            coef *= coef_mult / k;
            sum += coef * g;
            sum1 += coef * h;
            if (abs(coef * g) < abs(sum) * tolerance) 
            { 
               break; 
            }
         }
         policies::check_series_iterations<T>("boost::math::bessel_jy<%1%>(%1%,%1%) in temme_jy", k, pol);
         *Y = -sum;
         *Y1 = -2 * sum1 / x;

         return 0;
      }

      // Evaluate continued fraction fv = J_(v+1) / J_v, see
      // Abramowitz and Stegun, Handbook of Mathematical Functions, 1972, 9.1.73
      template <typename T, typename Policy>
      int CF1_jy(T v, T x, T* fv, int* sign, const Policy& pol)
      {
         T C, D, f, a, b, delta, tiny, tolerance;
         unsigned long k;
         int s = 1;

         BOOST_MATH_STD_USING

            // |x| <= |v|, CF1_jy converges rapidly
            // |x| > |v|, CF1_jy needs O(|x|) iterations to converge

            // modified Lentz's method, see
            // Lentz, Applied Optics, vol 15, 668 (1976)
            tolerance = 2 * policies::get_epsilon<T, Policy>();;
         tiny = sqrt(tools::min_value<T>());
         C = f = tiny;                           // b0 = 0, replace with tiny
         D = 0;
         for (k = 1; k < policies::get_max_series_iterations<Policy>() * 100; k++)
         {
            a = -1;
            b = 2 * (v + k) / x;
            C = b + a / C;
            D = b + a * D;
            if (C == 0) { C = tiny; }
            if (D == 0) { D = tiny; }
            D = 1 / D;
            delta = C * D;
            f *= delta;
            if (D < 0) { s = -s; }
            if (abs(delta - 1) < tolerance) 
            { break; }
         }
         policies::check_series_iterations<T>("boost::math::bessel_jy<%1%>(%1%,%1%) in CF1_jy", k / 100, pol);
         *fv = -f;
         *sign = s;                              // sign of denominator

         return 0;
      }
      //
      // This algorithm was originally written by Xiaogang Zhang
      // using std::complex to perform the complex arithmetic.
      // However, that turns out to 10x or more slower than using
      // all real-valued arithmetic, so it's been rewritten using
      // real values only.
      //
      template <typename T, typename Policy>
      int CF2_jy(T v, T x, T* p, T* q, const Policy& pol)
      {
         BOOST_MATH_STD_USING

            T Cr, Ci, Dr, Di, fr, fi, a, br, bi, delta_r, delta_i, temp;
         T tiny;
         unsigned long k;

         // |x| >= |v|, CF2_jy converges rapidly
         // |x| -> 0, CF2_jy fails to converge
         BOOST_ASSERT(fabs(x) > 1);

         // modified Lentz's method, complex numbers involved, see
         // Lentz, Applied Optics, vol 15, 668 (1976)
         T tolerance = 2 * policies::get_epsilon<T, Policy>();
         tiny = sqrt(tools::min_value<T>());
         Cr = fr = -0.5f / x;
         Ci = fi = 1;
         //Dr = Di = 0;
         T v2 = v * v;
         a = (0.25f - v2) / x; // Note complex this one time only!
         br = 2 * x;
         bi = 2;
         temp = Cr * Cr + 1;
         Ci = bi + a * Cr / temp;
         Cr = br + a / temp;
         Dr = br;
         Di = bi;
         if (fabs(Cr) + fabs(Ci) < tiny) { Cr = tiny; }
         if (fabs(Dr) + fabs(Di) < tiny) { Dr = tiny; }
         temp = Dr * Dr + Di * Di;
         Dr = Dr / temp;
         Di = -Di / temp;
         delta_r = Cr * Dr - Ci * Di;
         delta_i = Ci * Dr + Cr * Di;
         temp = fr;
         fr = temp * delta_r - fi * delta_i;
         fi = temp * delta_i + fi * delta_r;
         for (k = 2; k < policies::get_max_series_iterations<Policy>(); k++)
         {
            a = k - 0.5f;
            a *= a;
            a -= v2;
            bi += 2;
            temp = Cr * Cr + Ci * Ci;
            Cr = br + a * Cr / temp;
            Ci = bi - a * Ci / temp;
            Dr = br + a * Dr;
            Di = bi + a * Di;
            if (fabs(Cr) + fabs(Ci) < tiny) { Cr = tiny; }
            if (fabs(Dr) + fabs(Di) < tiny) { Dr = tiny; }
            temp = Dr * Dr + Di * Di;
            Dr = Dr / temp;
            Di = -Di / temp;
            delta_r = Cr * Dr - Ci * Di;
            delta_i = Ci * Dr + Cr * Di;
            temp = fr;
            fr = temp * delta_r - fi * delta_i;
            fi = temp * delta_i + fi * delta_r;
            if (fabs(delta_r - 1) + fabs(delta_i) < tolerance)
               break;
         }
         policies::check_series_iterations<T>("boost::math::bessel_jy<%1%>(%1%,%1%) in CF2_jy", k, pol);
         *p = fr;
         *q = fi;

         return 0;
      }

      static const int need_j = 1;
      static const int need_y = 2;

      // Compute J(v, x) and Y(v, x) simultaneously by Steed's method, see
      // Barnett et al, Computer Physics Communications, vol 8, 377 (1974)
      template <typename T, typename Policy>
      int bessel_jy(T v, T x, T* J, T* Y, int kind, const Policy& pol)
      {
         BOOST_ASSERT(x >= 0);

         T u, Jv, Ju, Yv, Yv1, Yu, Yu1(0), fv, fu;
         T W, p, q, gamma, current, prev, next;
         bool reflect = false;
         unsigned n, k;
         int s;
         int org_kind = kind;
         T cp = 0;
         T sp = 0;

         static const char* function = "boost::math::bessel_jy<%1%>(%1%,%1%)";

         BOOST_MATH_STD_USING
            using namespace boost::math::tools;
         using namespace boost::math::constants;

         if (v < 0)
         {
            reflect = true;
            v = -v;                             // v is non-negative from here
         }
         if (v > static_cast<T>((std::numeric_limits<int>::max)()))
         {
            *J = *Y = policies::raise_evaluation_error<T>(function, "Order of Bessel function is too large to evaluate: got %1%", v, pol);
            return 1;
         }
         n = iround(v, pol);
         u = v - n;                              // -1/2 <= u < 1/2

         if(reflect)
         {
            T z = (u + n % 2);
            cp = boost::math::cos_pi(z, pol);
            sp = boost::math::sin_pi(z, pol);
            if(u != 0)
               kind = need_j|need_y;               // need both for reflection formula
         }

         if(x == 0)
         {
            if(v == 0)
               *J = 1;
            else if((u == 0) || !reflect)
               *J = 0;
            else if(kind & need_j)
               *J = policies::raise_domain_error<T>(function, "Value of Bessel J_v(x) is complex-infinity at %1%", x, pol); // complex infinity
            else
               *J = std::numeric_limits<T>::quiet_NaN();  // any value will do, not using J.

            if((kind & need_y) == 0)
               *Y = std::numeric_limits<T>::quiet_NaN();  // any value will do, not using Y.
            else if(v == 0)
               *Y = -policies::raise_overflow_error<T>(function, 0, pol);
            else
               *Y = policies::raise_domain_error<T>(function, "Value of Bessel Y_v(x) is complex-infinity at %1%", x, pol); // complex infinity
            return 1;
         }

         // x is positive until reflection
         W = T(2) / (x * pi<T>());               // Wronskian
         T Yv_scale = 1;
         if(((kind & need_y) == 0) && ((x < 1) || (v > x * x / 4) || (x < 5)))
         {
            //
            // This series will actually converge rapidly for all small
            // x - say up to x < 20 - but the first few terms are large
            // and divergent which leads to large errors :-(
            //
            Jv = bessel_j_small_z_series(v, x, pol);
            Yv = std::numeric_limits<T>::quiet_NaN();
         }
         else if((x < 1) && (u != 0) && (log(policies::get_epsilon<T, Policy>() / 2) > v * log((x/2) * (x/2) / v)))
         {
            // Evaluate using series representations.
            // This is particularly important for x << v as in this
            // area temme_jy may be slow to converge, if it converges at all.
            // Requires x is not an integer.
            if(kind&need_j)
               Jv = bessel_j_small_z_series(v, x, pol);
            else
               Jv = std::numeric_limits<T>::quiet_NaN();
            if((org_kind&need_y && (!reflect || (cp != 0))) 
               || (org_kind & need_j && (reflect && (sp != 0))))
            {
               // Only calculate if we need it, and if the reflection formula will actually use it:
               Yv = bessel_y_small_z_series(v, x, &Yv_scale, pol);
            }
            else
               Yv = std::numeric_limits<T>::quiet_NaN();
         }
         else if((u == 0) && (x < policies::get_epsilon<T, Policy>()))
         {
            // Truncated series evaluation for small x and v an integer,
            // much quicker in this area than temme_jy below.
            if(kind&need_j)
               Jv = bessel_j_small_z_series(v, x, pol);
            else
               Jv = std::numeric_limits<T>::quiet_NaN();
            if((org_kind&need_y && (!reflect || (cp != 0))) 
               || (org_kind & need_j && (reflect && (sp != 0))))
            {
               // Only calculate if we need it, and if the reflection formula will actually use it:
               Yv = bessel_yn_small_z(n, x, &Yv_scale, pol);
            }
            else
               Yv = std::numeric_limits<T>::quiet_NaN();
         }
         else if(asymptotic_bessel_large_x_limit(v, x))
         {
            if(kind&need_y)
            {
               Yv = asymptotic_bessel_y_large_x_2(v, x);
            }
            else
               Yv = std::numeric_limits<T>::quiet_NaN(); // any value will do, we're not using it.
            if(kind&need_j)
            {
               Jv = asymptotic_bessel_j_large_x_2(v, x);
            }
            else
               Jv = std::numeric_limits<T>::quiet_NaN(); // any value will do, we're not using it.
         }
         else if((x > 8) && hankel_PQ(v, x, &p, &q, pol))
         {
            //
            // Hankel approximation: note that this method works best when x 
            // is large, but in that case we end up calculating sines and cosines
            // of large values, with horrendous resulting accuracy.  It is fast though
            // when it works....
            //
            // Normally we calculate sin/cos(chi) where:
            //
            // chi = x - fmod(T(v / 2 + 0.25f), T(2)) * boost::math::constants::pi<T>();
            //
            // But this introduces large errors, so use sin/cos addition formulae to
            // improve accuracy:
            //
            T mod_v = fmod(T(v / 2 + 0.25f), T(2));
            T sx = sin(x);
            T cx = cos(x);
            T sv = sin_pi(mod_v);
            T cv = cos_pi(mod_v);

            T sc = sx * cv - sv * cx; // == sin(chi);
            T cc = cx * cv + sx * sv; // == cos(chi);
            T chi = boost::math::constants::root_two<T>() / (boost::math::constants::root_pi<T>() * sqrt(x)); //sqrt(2 / (boost::math::constants::pi<T>() * x));
            Yv = chi * (p * sc + q * cc);
            Jv = chi * (p * cc - q * sc);
         }
         else if (x <= 2)                           // x in (0, 2]
         {
            if(temme_jy(u, x, &Yu, &Yu1, pol))             // Temme series
            {
               // domain error:
               *J = *Y = Yu;
               return 1;
            }
            prev = Yu;
            current = Yu1;
            T scale = 1;
            policies::check_series_iterations<T>(function, n, pol);
            for (k = 1; k <= n; k++)            // forward recurrence for Y
            {
               T fact = 2 * (u + k) / x;
               if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
               {
                  scale /= current;
                  prev /= current;
                  current = 1;
               }
               next = fact * current - prev;
               prev = current;
               current = next;
            }
            Yv = prev;
            Yv1 = current;
            if(kind&need_j)
            {
               CF1_jy(v, x, &fv, &s, pol);                 // continued fraction CF1_jy
               Jv = scale * W / (Yv * fv - Yv1);           // Wronskian relation
            }
            else
               Jv = std::numeric_limits<T>::quiet_NaN(); // any value will do, we're not using it.
            Yv_scale = scale;
         }
         else                                    // x in (2, \infty)
         {
            // Get Y(u, x):

            T ratio;
            CF1_jy(v, x, &fv, &s, pol);
            // tiny initial value to prevent overflow
            T init = sqrt(tools::min_value<T>());
            BOOST_MATH_INSTRUMENT_VARIABLE(init);
            prev = fv * s * init;
            current = s * init;
            if(v < max_factorial<T>::value)
            {
               policies::check_series_iterations<T>(function, n, pol);
               for (k = n; k > 0; k--)             // backward recurrence for J
               {
                  next = 2 * (u + k) * current / x - prev;
                  prev = current;
                  current = next;
               }
               ratio = (s * init) / current;     // scaling ratio
               // can also call CF1_jy() to get fu, not much difference in precision
               fu = prev / current;
            }
            else
            {
               //
               // When v is large we may get overflow in this calculation
               // leading to NaN's and other nasty surprises:
               //
               policies::check_series_iterations<T>(function, n, pol);
               bool over = false;
               for (k = n; k > 0; k--)             // backward recurrence for J
               {
                  T t = 2 * (u + k) / x;
                  if((t > 1) && (tools::max_value<T>() / t < current))
                  {
                     over = true;
                     break;
                  }
                  next = t * current - prev;
                  prev = current;
                  current = next;
               }
               if(!over)
               {
                  ratio = (s * init) / current;     // scaling ratio
                  // can also call CF1_jy() to get fu, not much difference in precision
                  fu = prev / current;
               }
               else
               {
                  ratio = 0;
                  fu = 1;
               }
            }
            CF2_jy(u, x, &p, &q, pol);                  // continued fraction CF2_jy
            T t = u / x - fu;                   // t = J'/J
            gamma = (p - t) / q;
            //
            // We can't allow gamma to cancel out to zero completely as it messes up
            // the subsequent logic.  So pretend that one bit didn't cancel out
            // and set to a suitably small value.  The only test case we've been able to
            // find for this, is when v = 8.5 and x = 4*PI.
            //
            if(gamma == 0)
            {
               gamma = u * tools::epsilon<T>() / x;
            }
            BOOST_MATH_INSTRUMENT_VARIABLE(current);
            BOOST_MATH_INSTRUMENT_VARIABLE(W);
            BOOST_MATH_INSTRUMENT_VARIABLE(q);
            BOOST_MATH_INSTRUMENT_VARIABLE(gamma);
            BOOST_MATH_INSTRUMENT_VARIABLE(p);
            BOOST_MATH_INSTRUMENT_VARIABLE(t);
            Ju = sign(current) * sqrt(W / (q + gamma * (p - t)));
            BOOST_MATH_INSTRUMENT_VARIABLE(Ju);

            Jv = Ju * ratio;                    // normalization

            Yu = gamma * Ju;
            Yu1 = Yu * (u/x - p - q/gamma);

            if(kind&need_y)
            {
               // compute Y:
               prev = Yu;
               current = Yu1;
               policies::check_series_iterations<T>(function, n, pol);
               for (k = 1; k <= n; k++)            // forward recurrence for Y
               {
                  T fact = 2 * (u + k) / x;
                  if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
                  {
                     prev /= current;
                     Yv_scale /= current;
                     current = 1;
                  }
                  next = fact * current - prev;
                  prev = current;
                  current = next;
               }
               Yv = prev;
            }
            else
               Yv = std::numeric_limits<T>::quiet_NaN(); // any value will do, we're not using it.
         }

         if (reflect)
         {
            if((sp != 0) && (tools::max_value<T>() * fabs(Yv_scale) < fabs(sp * Yv)))
               *J = org_kind & need_j ? T(-sign(sp) * sign(Yv) * (Yv_scale != 0 ? sign(Yv_scale) : 1) * policies::raise_overflow_error<T>(function, 0, pol)) : T(0);
            else
               *J = cp * Jv - (sp == 0 ? T(0) : T((sp * Yv) / Yv_scale));     // reflection formula
            if((cp != 0) && (tools::max_value<T>() * fabs(Yv_scale) < fabs(cp * Yv)))
               *Y = org_kind & need_y ? T(-sign(cp) * sign(Yv) * (Yv_scale != 0 ? sign(Yv_scale) : 1) * policies::raise_overflow_error<T>(function, 0, pol)) : T(0);
            else
               *Y = (sp != 0 ? sp * Jv : T(0)) + (cp == 0 ? T(0) : T((cp * Yv) / Yv_scale));
         }
         else
         {
            *J = Jv;
            if(tools::max_value<T>() * fabs(Yv_scale) < fabs(Yv))
               *Y = org_kind & need_y ? T(sign(Yv) * sign(Yv_scale) * policies::raise_overflow_error<T>(function, 0, pol)) : T(0);
            else
               *Y = Yv / Yv_scale;
         }

         return 0;
      }

   } // namespace detail

}} // namespaces

#endif // BOOST_MATH_BESSEL_JY_HPP


/* bessel_jy.hpp
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
*/