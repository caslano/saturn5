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
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
// Template argument deduction failure otherwise:
template<class F, class Real>
auto trapezoidal(F f, Real a, Real b, Real tol = 0, std::size_t max_refinements = 12, Real* error_estimate = 0, Real* L1 = 0)->decltype(std::declval<F>()(std::declval<Real>()))
#elif !defined(BOOST_NO_CXX11_NULLPTR)
template<class F, class Real>
auto trapezoidal(F f, Real a, Real b, Real tol = boost::math::tools::root_epsilon<Real>(), std::size_t max_refinements = 12, Real* error_estimate = nullptr, Real* L1 = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))
#else
template<class F, class Real>
auto trapezoidal(F f, Real a, Real b, Real tol = boost::math::tools::root_epsilon<Real>(), std::size_t max_refinements = 12, Real* error_estimate = 0, Real* L1 = 0)->decltype(std::declval<F>()(std::declval<Real>()))
#endif
{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1600)
   if (tol == 0)
      tol = boost::math::tools::root_epsilon<Real>();
#endif
   return trapezoidal(f, a, b, tol, max_refinements, error_estimate, L1, boost::math::policies::policy<>());
}

}}}
#endif

/* trapezoidal.hpp
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
*/