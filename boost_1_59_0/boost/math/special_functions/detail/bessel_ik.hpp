//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_IK_HPP
#define BOOST_MATH_BESSEL_IK_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <cstdint>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/config.hpp>

// Modified Bessel functions of the first and second kind of fractional order

namespace boost { namespace math {

namespace detail {

template <class T, class Policy>
struct cyl_bessel_i_small_z
{
   typedef T result_type;

   cyl_bessel_i_small_z(T v_, T z_) : k(0), v(v_), mult(z_*z_/4) 
   {
      BOOST_MATH_STD_USING
      term = 1;
   }

   T operator()()
   {
      T result = term;
      ++k;
      term *= mult / k;
      term /= k + v;
      return result;
   }
private:
   unsigned k;
   T v;
   T term;
   T mult;
};

template <class T, class Policy>
inline T bessel_i_small_z_series(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T prefix;
   if(v < max_factorial<T>::value)
   {
      prefix = pow(x / 2, v) / boost::math::tgamma(v + 1, pol);
   }
   else
   {
      prefix = v * log(x / 2) - boost::math::lgamma(v + 1, pol);
      prefix = exp(prefix);
   }
   if(prefix == 0)
      return prefix;

   cyl_bessel_i_small_z<T, Policy> s(v, x);
   std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
   
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

   policies::check_series_iterations<T>("boost::math::bessel_j_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   return prefix * result;
}

// Calculate K(v, x) and K(v+1, x) by method analogous to
// Temme, Journal of Computational Physics, vol 21, 343 (1976)
template <typename T, typename Policy>
int temme_ik(T v, T x, T* K, T* K1, const Policy& pol)
{
    T f, h, p, q, coef, sum, sum1, tolerance;
    T a, b, c, d, sigma, gamma1, gamma2;
    unsigned long k;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;


    // |x| <= 2, Temme series converge rapidly
    // |x| > 2, the larger the |x|, the slower the convergence
    BOOST_MATH_ASSERT(abs(x) <= 2);
    BOOST_MATH_ASSERT(abs(v) <= 0.5f);

    T gp = boost::math::tgamma1pm1(v, pol);
    T gm = boost::math::tgamma1pm1(-v, pol);

    a = log(x / 2);
    b = exp(v * a);
    sigma = -a * v;
    c = abs(v) < tools::epsilon<T>() ?
       T(1) : T(boost::math::sin_pi(v, pol) / (v * pi<T>()));
    d = abs(sigma) < tools::epsilon<T>() ?
        T(1) : T(sinh(sigma) / sigma);
    gamma1 = abs(v) < tools::epsilon<T>() ?
        T(-euler<T>()) : T((0.5f / v) * (gp - gm) * c);
    gamma2 = (2 + gp + gm) * c / 2;

    // initial values
    p = (gp + 1) / (2 * b);
    q = (1 + gm) * b / 2;
    f = (cosh(sigma) * gamma1 + d * (-a) * gamma2) / c;
    h = p;
    coef = 1;
    sum = coef * f;
    sum1 = coef * h;

    BOOST_MATH_INSTRUMENT_VARIABLE(p);
    BOOST_MATH_INSTRUMENT_VARIABLE(q);
    BOOST_MATH_INSTRUMENT_VARIABLE(f);
    BOOST_MATH_INSTRUMENT_VARIABLE(sigma);
    BOOST_MATH_INSTRUMENT_CODE(sinh(sigma));
    BOOST_MATH_INSTRUMENT_VARIABLE(gamma1);
    BOOST_MATH_INSTRUMENT_VARIABLE(gamma2);
    BOOST_MATH_INSTRUMENT_VARIABLE(c);
    BOOST_MATH_INSTRUMENT_VARIABLE(d);
    BOOST_MATH_INSTRUMENT_VARIABLE(a);

    // series summation
    tolerance = tools::epsilon<T>();
    for (k = 1; k < policies::get_max_series_iterations<Policy>(); k++)
    {
        f = (k * f + p + q) / (k*k - v*v);
        p /= k - v;
        q /= k + v;
        h = p - k * f;
        coef *= x * x / (4 * k);
        sum += coef * f;
        sum1 += coef * h;
        if (abs(coef * f) < abs(sum) * tolerance) 
        { 
           break; 
        }
    }
    policies::check_series_iterations<T>("boost::math::bessel_ik<%1%>(%1%,%1%) in temme_ik", k, pol);

    *K = sum;
    *K1 = 2 * sum1 / x;

    return 0;
}

// Evaluate continued fraction fv = I_(v+1) / I_v, derived from
// Abramowitz and Stegun, Handbook of Mathematical Functions, 1972, 9.1.73
template <typename T, typename Policy>
int CF1_ik(T v, T x, T* fv, const Policy& pol)
{
    T C, D, f, a, b, delta, tiny, tolerance;
    unsigned long k;

    BOOST_MATH_STD_USING

    // |x| <= |v|, CF1_ik converges rapidly
    // |x| > |v|, CF1_ik needs O(|x|) iterations to converge

    // modified Lentz's method, see
    // Lentz, Applied Optics, vol 15, 668 (1976)
    tolerance = 2 * tools::epsilon<T>();
    BOOST_MATH_INSTRUMENT_VARIABLE(tolerance);
    tiny = sqrt(tools::min_value<T>());
    BOOST_MATH_INSTRUMENT_VARIABLE(tiny);
    C = f = tiny;                           // b0 = 0, replace with tiny
    D = 0;
    for (k = 1; k < policies::get_max_series_iterations<Policy>(); k++)
    {
        a = 1;
        b = 2 * (v + k) / x;
        C = b + a / C;
        D = b + a * D;
        if (C == 0) { C = tiny; }
        if (D == 0) { D = tiny; }
        D = 1 / D;
        delta = C * D;
        f *= delta;
        BOOST_MATH_INSTRUMENT_VARIABLE(delta-1);
        if (abs(delta - 1) <= tolerance) 
        { 
           break; 
        }
    }
    BOOST_MATH_INSTRUMENT_VARIABLE(k);
    policies::check_series_iterations<T>("boost::math::bessel_ik<%1%>(%1%,%1%) in CF1_ik", k, pol);

    *fv = f;

    return 0;
}

// Calculate K(v, x) and K(v+1, x) by evaluating continued fraction
// z1 / z0 = U(v+1.5, 2v+1, 2x) / U(v+0.5, 2v+1, 2x), see
// Thompson and Barnett, Computer Physics Communications, vol 47, 245 (1987)
template <typename T, typename Policy>
int CF2_ik(T v, T x, T* Kv, T* Kv1, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::constants;

    T S, C, Q, D, f, a, b, q, delta, tolerance, current, prev;
    unsigned long k;

    // |x| >= |v|, CF2_ik converges rapidly
    // |x| -> 0, CF2_ik fails to converge

    BOOST_MATH_ASSERT(abs(x) > 1);

    // Steed's algorithm, see Thompson and Barnett,
    // Journal of Computational Physics, vol 64, 490 (1986)
    tolerance = tools::epsilon<T>();
    a = v * v - 0.25f;
    b = 2 * (x + 1);                              // b1
    D = 1 / b;                                    // D1 = 1 / b1
    f = delta = D;                                // f1 = delta1 = D1, coincidence
    prev = 0;                                     // q0
    current = 1;                                  // q1
    Q = C = -a;                                   // Q1 = C1 because q1 = 1
    S = 1 + Q * delta;                            // S1
    BOOST_MATH_INSTRUMENT_VARIABLE(tolerance);
    BOOST_MATH_INSTRUMENT_VARIABLE(a);
    BOOST_MATH_INSTRUMENT_VARIABLE(b);
    BOOST_MATH_INSTRUMENT_VARIABLE(D);
    BOOST_MATH_INSTRUMENT_VARIABLE(f);

    for (k = 2; k < policies::get_max_series_iterations<Policy>(); k++)     // starting from 2
    {
        // continued fraction f = z1 / z0
        a -= 2 * (k - 1);
        b += 2;
        D = 1 / (b + a * D);
        delta *= b * D - 1;
        f += delta;

        // series summation S = 1 + \sum_{n=1}^{\infty} C_n * z_n / z_0
        q = (prev - (b - 2) * current) / a;
        prev = current;
        current = q;                        // forward recurrence for q
        C *= -a / k;
        Q += C * q;
        S += Q * delta;
        //
        // Under some circumstances q can grow very small and C very
        // large, leading to under/overflow.  This is particularly an
        // issue for types which have many digits precision but a narrow
        // exponent range.  A typical example being a "double double" type.
        // To avoid this situation we can normalise q (and related prev/current)
        // and C.  All other variables remain unchanged in value.  A typical
        // test case occurs when x is close to 2, for example cyl_bessel_k(9.125, 2.125).
        //
        if(q < tools::epsilon<T>())
        {
           C *= q;
           prev /= q;
           current /= q;
           q = 1;
        }

        // S converges slower than f
        BOOST_MATH_INSTRUMENT_VARIABLE(Q * delta);
        BOOST_MATH_INSTRUMENT_VARIABLE(abs(S) * tolerance);
        BOOST_MATH_INSTRUMENT_VARIABLE(S);
        if (abs(Q * delta) < abs(S) * tolerance) 
        { 
           break; 
        }
    }
    policies::check_series_iterations<T>("boost::math::bessel_ik<%1%>(%1%,%1%) in CF2_ik", k, pol);

    if(x >= tools::log_max_value<T>())
       *Kv = exp(0.5f * log(pi<T>() / (2 * x)) - x - log(S));
    else
      *Kv = sqrt(pi<T>() / (2 * x)) * exp(-x) / S;
    *Kv1 = *Kv * (0.5f + v + x + (v * v - 0.25f) * f) / x;
    BOOST_MATH_INSTRUMENT_VARIABLE(*Kv);
    BOOST_MATH_INSTRUMENT_VARIABLE(*Kv1);

    return 0;
}

enum{
   need_i = 1,
   need_k = 2
};

// Compute I(v, x) and K(v, x) simultaneously by Temme's method, see
// Temme, Journal of Computational Physics, vol 19, 324 (1975)
template <typename T, typename Policy>
int bessel_ik(T v, T x, T* I, T* K, int kind, const Policy& pol)
{
    // Kv1 = K_(v+1), fv = I_(v+1) / I_v
    // Ku1 = K_(u+1), fu = I_(u+1) / I_u
    T u, Iv, Kv, Kv1, Ku, Ku1, fv;
    T W, current, prev, next;
    bool reflect = false;
    unsigned n, k;
    int org_kind = kind;
    BOOST_MATH_INSTRUMENT_VARIABLE(v);
    BOOST_MATH_INSTRUMENT_VARIABLE(x);
    BOOST_MATH_INSTRUMENT_VARIABLE(kind);

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    static const char* function = "boost::math::bessel_ik<%1%>(%1%,%1%)";

    if (v < 0)
    {
        reflect = true;
        v = -v;                             // v is non-negative from here
        kind |= need_k;
    }
    n = iround(v, pol);
    u = v - n;                              // -1/2 <= u < 1/2
    BOOST_MATH_INSTRUMENT_VARIABLE(n);
    BOOST_MATH_INSTRUMENT_VARIABLE(u);

    if (x < 0)
    {
       *I = *K = policies::raise_domain_error<T>(function,
            "Got x = %1% but real argument x must be non-negative, complex number result not supported.", x, pol);
        return 1;
    }
    if (x == 0)
    {
       Iv = (v == 0) ? static_cast<T>(1) : static_cast<T>(0);
       if(kind & need_k)
       {
         Kv = policies::raise_overflow_error<T>(function, 0, pol);
       }
       else
       {
          Kv = std::numeric_limits<T>::quiet_NaN(); // any value will do
       }

       if(reflect && (kind & need_i))
       {
           T z = (u + n % 2);
           Iv = boost::math::sin_pi(z, pol) == 0 ? 
               Iv : 
               policies::raise_overflow_error<T>(function, 0, pol);   // reflection formula
       }

       *I = Iv;
       *K = Kv;
       return 0;
    }

    // x is positive until reflection
    W = 1 / x;                                 // Wronskian
    if (x <= 2)                                // x in (0, 2]
    {
        temme_ik(u, x, &Ku, &Ku1, pol);             // Temme series
    }
    else                                       // x in (2, \infty)
    {
        CF2_ik(u, x, &Ku, &Ku1, pol);               // continued fraction CF2_ik
    }
    BOOST_MATH_INSTRUMENT_VARIABLE(Ku);
    BOOST_MATH_INSTRUMENT_VARIABLE(Ku1);
    prev = Ku;
    current = Ku1;
    T scale = 1;
    T scale_sign = 1;
    for (k = 1; k <= n; k++)                   // forward recurrence for K
    {
        T fact = 2 * (u + k) / x;
        if((tools::max_value<T>() - fabs(prev)) / fact < fabs(current))
        {
           prev /= current;
           scale /= current;
           scale_sign *= boost::math::sign(current);
           current = 1;
        }
        next = fact * current + prev;
        prev = current;
        current = next;
    }
    Kv = prev;
    Kv1 = current;
    BOOST_MATH_INSTRUMENT_VARIABLE(Kv);
    BOOST_MATH_INSTRUMENT_VARIABLE(Kv1);
    if(kind & need_i)
    {
       T lim = (4 * v * v + 10) / (8 * x);
       lim *= lim;
       lim *= lim;
       lim /= 24;
       if((lim < tools::epsilon<T>() * 10) && (x > 100))
       {
          // x is huge compared to v, CF1 may be very slow
          // to converge so use asymptotic expansion for large
          // x case instead.  Note that the asymptotic expansion
          // isn't very accurate - so it's deliberately very hard 
          // to get here - probably we're going to overflow:
          Iv = asymptotic_bessel_i_large_x(v, x, pol);
       }
       else if((v > 0) && (x / v < 0.25))
       {
          Iv = bessel_i_small_z_series(v, x, pol);
       }
       else
       {
          CF1_ik(v, x, &fv, pol);                         // continued fraction CF1_ik
          Iv = scale * W / (Kv * fv + Kv1);                  // Wronskian relation
       }
    }
    else
       Iv = std::numeric_limits<T>::quiet_NaN(); // any value will do

    if (reflect)
    {
        T z = (u + n % 2);
        T fact = (2 / pi<T>()) * (boost::math::sin_pi(z, pol) * Kv);
        if(fact == 0)
           *I = Iv;
        else if(tools::max_value<T>() * scale < fact)
           *I = (org_kind & need_i) ? T(sign(fact) * scale_sign * policies::raise_overflow_error<T>(function, 0, pol)) : T(0);
        else
         *I = Iv + fact / scale;   // reflection formula
    }
    else
    {
        *I = Iv;
    }
    if(tools::max_value<T>() * scale < Kv)
       *K = (org_kind & need_k) ? T(sign(Kv) * scale_sign * policies::raise_overflow_error<T>(function, 0, pol)) : T(0);
    else
      *K = Kv / scale;
    BOOST_MATH_INSTRUMENT_VARIABLE(*I);
    BOOST_MATH_INSTRUMENT_VARIABLE(*K);
    return 0;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_IK_HPP


/* bessel_ik.hpp
+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
*/