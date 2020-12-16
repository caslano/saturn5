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
5vuFc0tnzDlMvv81FpTnt6zGwqs5j5zG4vfk/J+xmPzdL2jMlYT9FsN86WT/z5hD/gaUx3zy3qUycsvG9fUY847getRCbvKOpT587GC7JtDlW7ZrjpglltbG3Bk4tw7GIgfZrgtibsi17In5pvKa6Wcsmlj2/5DHZh47HPHll+9/kds+jmUC6pGe7T6F3984t+mI7zCPDRrzJ+V1tAB9sIJj+RIsyHksgwYPZP8PNTrN7EfoJ9/ZrEF8wn5DLHK/sR4xp+T5tsBO9lB2QJcMzPZAv43s4yD6QPweRXwR7tNT0FTuO88bC8jfmRjslrDO1//Lg33cQd/LM/t9aFCJY/4XvSH3p8/BGsv3v4hlHc+XOLvltp1ZCmORv+X3P4yFXvI6z2AsUDSBWBZjQdmXygE7OZ+Tx5hzPtu9b8xXgfMoaiy+nuNzG4tu5dzKIY8CbPeBMXc17t2PMPZ39lvTmOuLJMTqIZZycv7PWEzO53wMu7s8tpWx8BUe2x5j3+OYOyMWOaPUA9pnYbu+mO8lr6OByFf2D4ZBU9l7GA0N7rNdAPM95PimYL65vI4+B4ux39kYu5HZfOT2knVZDFaG/X6NsXn4Wvw/9Et2rscK5LGf51ttzC/v2n6FVpfZbh3m+4Ln2wy/SXltbUd8c+X7X/iNyv6fMU+Q54sa8z5gu5PQWe5VzqHvfWx3Cf0izzPX4PcFXztvY70d5Nz+QZ8W4Ro9Qo3Wyf4fxiaw3Wv02ly2S5TDtCrDuiQ3FpE95DRgct4svTGf5JY5B/bw2Ed2Y67pzFzGYnKNKADmle9/Md8ZOf+HWCTfssZChXlsJWN+ye1DY85KrGkN2EksdY05asv+H7QSv82MRZdzj7fEfFLfdshD6tsJdsK6GwvIN/h94EP2Y/2Ybx+zobCTPh1lzP0Hs/HGPLJ/NdlY5aG8Lj9D3eQsxCzUSM5iz4NdUb5eLUJucp71K9g15np8i5jlLOcPyE2eEVdh7M+y/wcf2zm+P5BbF76ubYKdfEsWgQ/5tm8X+tnL8e3HWHcCsSPoDblvP4GenME6n8VYL6+Zi9BP3pddxdhMzG4Zm/o51+Nv5CbvFh9iPrnmPP1PA87jFdhdzjchp/Vad2bJjPnle/vUxlyyPpzGomKXCWOLcs3fM+Z4zRrkNhaR7xbzGwtGWYPCxuLyzF7CWDgla1AGY5txLBWNucfx2KqY718eWx2x7ON+qWPM45Dzf8ac8znmptCgJufWAvku4vnagsm3vj74/YHj64b5rrKP3sZCcsZhAOrhZjYEdtl4DY6E34Nc33HIrQ7HPAmazuNYpqE3vmMfMxHfeGZzYSfXnIWIJSX7WGrs5kDu52+M+eS69j1yK8d5/IT5EvHYMPLYzjr/jljkfmMj6ibPW9uMeeX96p/QwM9a7YPdLGaHwSSW44hZnrvPgDnZ7wX4kO8qr6BG8s7mJnSRtXAPGjh57ANjscJs9wT5Hk1N7CXsZD5HLvMhNUpqzDOdfaQy5t3BOr9jzC91y2jMJSwbmOwn5jIWe8Za5TPmkH2kQmABZsUxdhPnURrxNWFWwVhQviepglieyPe/GLuM61vbWESunQ0w35p0xLxgd5l98p+msv8Hrd7wfB3hQ/72dEW+hznmXojvOfvobywuZ1wHY7532McIY84W7GMs7ORaMhG6yHeLUxFLMr5ezUButblf5hgL7+WxXyDmxMyWGAvJ/lXImHsDx7ccuR3isSuNRfcz+xl9+pDZWmOB1qzBBtjJmYStiE+ej3ZCF/kN6b2IWb7NPYT+k2fiY4h5CedxGn7lfuMv+JBnq8vQdA/X/AZ0+YhjvgtWkWOJo//kWegxYpHnnhfoP3k=
*/