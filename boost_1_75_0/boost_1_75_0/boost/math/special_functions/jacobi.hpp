//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_JACOBI_HPP
#define BOOST_MATH_SPECIAL_JACOBI_HPP

#include <limits>
#include <stdexcept>

namespace boost { namespace math {

template<typename Real>
Real jacobi(unsigned n, Real alpha, Real beta, Real x)
{
    static_assert(!std::is_integral<Real>::value, "Jacobi polynomials do not work with integer arguments.");

    if (n == 0) {
        return Real(1);
    }
    Real y0 = 1;
    Real y1 = (alpha+1) + (alpha+beta+2)*(x-1)/Real(2);

    Real yk = y1;
    Real k = 2;
    Real k_max = n*(1+std::numeric_limits<Real>::epsilon());
    while(k < k_max)
    {
        // Hoping for lots of common subexpression elimination by the compiler:
        Real denom = 2*k*(k+alpha+beta)*(2*k+alpha+beta-2);
        Real gamma1 = (2*k+alpha+beta-1)*( (2*k+alpha+beta)*(2*k+alpha+beta-2)*x + alpha*alpha -beta*beta);
        Real gamma0 = -2*(k+alpha-1)*(k+beta-1)*(2*k+alpha+beta);
        yk = (gamma1*y1 + gamma0*y0)/denom;
        y0 = y1;
        y1 = yk;
        k += 1;
    }
    return yk;
}

template<typename Real>
Real jacobi_derivative(unsigned n, Real alpha, Real beta, Real x, unsigned k)
{
    if (k > n) {
        return Real(0);
    }
    Real scale = 1;
    for(unsigned j = 1; j <= k; ++j) {
        scale *= (alpha + beta + n + j)/2;
    }

    return scale*jacobi<Real>(n-k, alpha + k, beta+k, x);
}

template<typename Real>
Real jacobi_prime(unsigned n, Real alpha, Real beta, Real x)
{
    return jacobi_derivative<Real>(n, alpha, beta, x, 1);
}

template<typename Real>
Real jacobi_double_prime(unsigned n, Real alpha, Real beta, Real x)
{
    return jacobi_derivative<Real>(n, alpha, beta, x, 2);
}

}}
#endif

/* jacobi.hpp
bbueKcdijxTtL/hP12iO0M6QixJkN8KaYLGssc/2RCvygM+0GZd6c1KYQ4yR1KnoVscGOFhw/7JX4oyFKhFyPNOEEJSZgzEDNdaZBUL6ZwucvMl+YySjsZA6tcwfsc0yA3MHc6lExiwKr0gO/RJ78tBBU/2KQvdpKMoKzu9tHwngwS8hAW9I4exuUHELKhhsh5O3A4vVgdZqXags16mMNGkm1IMm2Y0h93jZLdIATmmE+nKLQdRWqPjuhCsdqbRcPznFRrm1zGt7+e890zzGczOCC3twmopllEd6ZbAaQy2Ksg01JiZSbJHR5isD2vVX2Vrf8Bma7T9czgs3yKdlN/w1OYzWIM2GbpcCXAouEWvI/TQoObMWLY6CYnwk/I58J1NxZCHFqUz5zeHizkameQiT2PnQQiYDtFBzuYfxxgj1FxqRgUAUqfQXHP3Qb13KCPkY1iHl7+xe2Uovn5VTohWmhEhdl01m6L/TW3Z/syM8/04cOLSJHgpOsvokeXHf5FIOqayNm4mO+WKYQgWTNqEvYNMjgGvuR449EScdXQwNPXrvSZ3kwu7IKuCbxxh6LTeYoKOnDozp3wI5NdBRz6j4ZOfwe15iz0RgsjPlAwGxZ5L7wO9oO/wR/xJDIlgC9b62KT6BJP3Me03iiA/fX+pEKW9U8feG/nQqGSn1AP3kiGAZ8X+FIFT/2hOHWptuRorTxvjOeYY5x+s+
*/