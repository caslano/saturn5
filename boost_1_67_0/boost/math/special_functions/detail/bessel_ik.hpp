//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_IK_HPP
#define BOOST_MATH_BESSEL_IK_HPP

#ifdef _MSC_VER
#pragma once
#endif

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
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
    BOOST_ASSERT(abs(x) <= 2);
    BOOST_ASSERT(abs(v) <= 0.5f);

    T gp = boost::math::tgamma1pm1(v, pol);
    T gm = boost::math::tgamma1pm1(-v, pol);

    a = log(x / 2);
    b = exp(v * a);
    sigma = -a * v;
    c = abs(v) < tools::epsilon<T>() ?
       T(1) : T(boost::math::sin_pi(v) / (v * pi<T>()));
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

    BOOST_ASSERT(abs(x) > 1);

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
        T fact = (2 / pi<T>()) * (boost::math::sin_pi(z) * Kv);
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
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
*/