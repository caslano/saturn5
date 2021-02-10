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
2rxMu7zJ4ujPEqfgL2Kg7k/N/q6viH77DTLRZD7N8QR4ALv/LPzm9HrdtYlYlefHmxuwDzwJq65s64f9Qfd3E7+rbyKDl0zeDOyqbiHHJTz08G/8+3slf978cxf/rMG2iapO/TJ/+i2U+qMtMLJ4J/Cy9PuHPe9UfxnoUXweqF19Hsh12ObhwDyfuyjvisE6bmK/DrOBeq66CHwris9s/hQgFvlq9Yf8x1Cw9Hv0DQjin01VxG0Gef4X8V8DJ4sxCuAJMjQI4xpjI/TbGN5gwUGUXfzaL4h/4I+ij017sN7Ig+XadGVHH8x077VCWKapX2RTkeWZKq90WVK42DEfkzItWYo2pcWyjQt6Gsg570qrapu2q8lokTzPjbUZ16cTMbytlYQ57JYe9TA3l+mTWquqF+7kS95fw/2YHE3TOmgzg59fbUcPGaEpRxeGk0bSNczUI7GebIXW4ejxKEovx8nMoc1FUtCH0mR7LxEZrhmvD6tHVtG6IjD78EjNwt3zbNi75Wwo1hERnSo1tjb9fPHMHzZblpLP8c8yrjaLA7Xb7ePFVFSN3f7krXvJPMq7w/MhLrkw3OejrGI3xKnaJkbMOOmoP2+Xm7FiUUzcP3yev10e5MK7K1zHtGZRenz2sKXlpfBHM6ftAJqb
*/