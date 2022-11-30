//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_GEGENBAUER_HPP
#define BOOST_MATH_SPECIAL_GEGENBAUER_HPP

#include <limits>
#include <stdexcept>
#include <type_traits>

namespace boost { namespace math {

template<typename Real>
Real gegenbauer(unsigned n, Real lambda, Real x)
{
    static_assert(!std::is_integral<Real>::value, "Gegenbauer polynomials required floating point arguments.");
    if (lambda <= -1/Real(2)) {
        throw std::domain_error("lambda > -1/2 is required.");
    }
    // The only reason to do this is because of some instability that could be present for x < 0 that is not present for x > 0.
    // I haven't observed this, but then again, I haven't managed to test an exhaustive number of parameters.
    // In any case, the routine is distinctly faster without this test:
    //if (x < 0) {
    //    if (n&1) {
    //        return -gegenbauer(n, lambda, -x);
    //    }
    //    return gegenbauer(n, lambda, -x);
    //}

    if (n == 0) {
        return Real(1);
    }
    Real y0 = 1;
    Real y1 = 2*lambda*x;

    Real yk = y1;
    Real k = 2;
    Real k_max = n*(1+std::numeric_limits<Real>::epsilon());
    Real gamma = 2*(lambda - 1);
    while(k < k_max)
    {
        yk = ( (2 + gamma/k)*x*y1 - (1+gamma/k)*y0);
        y0 = y1;
        y1 = yk;
        k += 1;
    }
    return yk;
}


template<typename Real>
Real gegenbauer_derivative(unsigned n, Real lambda, Real x, unsigned k)
{
    if (k > n) {
        return Real(0);
    }
    Real gegen = gegenbauer<Real>(n-k, lambda + k, x);
    Real scale = 1;
    for (unsigned j = 0; j < k; ++j) {
        scale *= 2*lambda;
        lambda += 1;
    }
    return scale*gegen;
}

template<typename Real>
Real gegenbauer_prime(unsigned n, Real lambda, Real x) {
    return gegenbauer_derivative<Real>(n, lambda, x, 1);
}


}}
#endif

/* gegenbauer.hpp
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
*/