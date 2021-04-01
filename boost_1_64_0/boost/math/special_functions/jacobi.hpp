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
DGpLPiJ/INtVXhsiGVd0o/yWvb4/zCB3HmTaqPRZoBO7Yfp2q3efXBnnZu6USHvrpFvGqsXvBIXoftu3tznaPieYa4/fL+qSVpOPg5gVvcgxooVbGQvvDpzdWwmCvrUAztzyh11+xgtSGTqGxdp/SrwRSeaYapBCexFVL7NRF3i8DkJO0+VCE/G0DoRnfZ/XYwoSzMZFesUMTuiPbzkAem9c1Qiv8ev7ZGKZoD8B5ReDabKzA8URw7nKq108/UqhSi3nhZ4E9C1LkPRPR9b8ZK2pYuUrGxJFwAnAO2ZnVTO+qZEk1FFqIJrOaJ8M0cqJV3Ri2R+kzX2kHQz1+5ox4T/mNqymhWfIdiOKGgeGpIX8nqo9U2OoA60UXmpBoG3pPLRgRN3+fNeFWlF8jkxxaqAYS47shal0QNjk80YxqRAyRsLv+pK4+RqJ9mCHba/cpV1gzjMHmle/ct7zhwsh3y518VB3m3HWm7A9F7GM9tyqRSKx3tBZm/d74sqCoHDCxjJOcQgUr3xd4C+F5NAmMeyZ5hk4OqC8iDJIaGxVzJrWM6F7ORHNsuRTfQ==
*/