/*
 * Copyright Nick Thompson, 2017
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Use the adaptive trapezoidal rule to estimate the integral of periodic functions over a period,
 * or to integrate a function whose derivative vanishes at the endpoints.
 *
 * If your function does not satisfy these conditions, and instead is simply continuous and bounded
 * over the whole interval, then this routine will still converge, albeit slowly. However, there
 * are much more efficient methods in this case, including Romberg, Simpson, and double exponential quadrature.
 */

#ifndef BOOST_MATH_QUADRATURE_TRAPEZOIDAL_HPP
#define BOOST_MATH_QUADRATURE_TRAPEZOIDAL_HPP

#include <cmath>
#include <limits>
#include <utility>
#include <stdexcept>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

namespace boost{ namespace math{ namespace quadrature {

template<class F, class Real, class Policy>
auto trapezoidal(F f, Real a, Real b, Real tol, std::size_t max_refinements, Real* error_estimate, Real* L1, const Policy& pol)->decltype(std::declval<F>()(std::declval<Real>()))
{
    static const char* function = "boost::math::quadrature::trapezoidal<%1%>(F, %1%, %1%, %1%)";
    using std::abs;
    using boost::math::constants::half;
    // In many math texts, K represents the field of real or complex numbers.
    // Too bad we can't put blackboard bold into C++ source!
    typedef decltype(f(a)) K;
    static_assert(!std::is_integral<K>::value,
                  "The return type cannot be integral, it must be either a real or complex floating point type.");
    if (!(boost::math::isfinite)(a))
    {
       return static_cast<K>(boost::math::policies::raise_domain_error(function, "Left endpoint of integration must be finite for adaptive trapezoidal integration but got a = %1%.\n", a, pol));
    }
    if (!(boost::math::isfinite)(b))
    {
       return static_cast<K>(boost::math::policies::raise_domain_error(function, "Right endpoint of integration must be finite for adaptive trapezoidal integration but got b = %1%.\n", b, pol));
    }

    if (a == b)
    {
        return static_cast<K>(0);
    }
    if(a > b)
    {
        return -trapezoidal(f, b, a, tol, max_refinements, error_estimate, L1, pol);
    }


    K ya = f(a);
    K yb = f(b);
    Real h = (b - a)*half<Real>();
    K I0 = (ya + yb)*h;
    Real IL0 = (abs(ya) + abs(yb))*h;

    K yh = f(a + h);
    K I1;
    I1 = I0*half<Real>() + yh*h;
    Real IL1 = IL0*half<Real>() + abs(yh)*h;

    // The recursion is:
    // I_k = 1/2 I_{k-1} + 1/2^k \sum_{j=1; j odd, j < 2^k} f(a + j(b-a)/2^k)
    std::size_t k = 2;
    // We want to go through at least 5 levels so we have sampled the function at least 20 times.
    // Otherwise, we could terminate prematurely and miss essential features.
    // This is of course possible anyway, but 20 samples seems to be a reasonable compromise.
    Real error = abs(I0 - I1);
    // I take k < 5, rather than k < 4, or some other smaller minimum number,
    // because I hit a truly exceptional bug where the k = 2 and k =3 refinement were bitwise equal,
    // but the quadrature had not yet converged.
    while (k < 5 || (k < max_refinements && error > tol*IL1) )
    {
        I0 = I1;
        IL0 = IL1;

        I1 = I0*half<Real>();
        IL1 = IL0*half<Real>();
        std::size_t p = static_cast<std::size_t>(1u) << k;
        h *= half<Real>();
        K sum = 0;
        Real absum = 0;

        for(std::size_t j = 1; j < p; j += 2)
        {
            K y = f(a + j*h);
            sum += y;
            absum += abs(y);
        }

        I1 += sum*h;
        IL1 += absum*h;
        ++k;
        error = abs(I0 - I1);
    }

    if (error_estimate)
    {
        *error_estimate = error;
    }

    if (L1)
    {
        *L1 = IL1;
    }

    return static_cast<K>(I1);
}

template<class F, class Real>
auto trapezoidal(F f, Real a, Real b, Real tol = boost::math::tools::root_epsilon<Real>(), std::size_t max_refinements = 12, Real* error_estimate = nullptr, Real* L1 = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))
{
   return trapezoidal(f, a, b, tol, max_refinements, error_estimate, L1, boost::math::policies::policy<>());
}

}}}
#endif

/* trapezoidal.hpp
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
*/