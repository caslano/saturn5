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

         BOOST_MATH_ASSERT(fabs(v) <= 0.5f);  // precondition for using this routine

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
            tolerance = 2 * policies::get_epsilon<T, Policy>();
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
         BOOST_MATH_ASSERT(fabs(x) > 1);

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
         BOOST_MATH_ASSERT(x >= 0);

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
               Yv = asymptotic_bessel_y_large_x_2(v, x, pol);
            }
            else
               Yv = std::numeric_limits<T>::quiet_NaN(); // any value will do, we're not using it.
            if(kind&need_j)
            {
               Jv = asymptotic_bessel_j_large_x_2(v, x, pol);
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
            T sv = boost::math::sin_pi(mod_v, pol);
            T cv = boost::math::cos_pi(mod_v, pol);

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