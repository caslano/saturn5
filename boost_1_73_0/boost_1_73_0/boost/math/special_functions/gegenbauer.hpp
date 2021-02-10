//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_GEGENBAUER_HPP
#define BOOST_MATH_SPECIAL_GEGENBAUER_HPP

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
DXUD1PQYWQioNWjyB1LIRHQVUgCxgAtgAt4A1QNz/toP6h4ZuAJGEyBTMAdiDOABMQZqhj2gtcDLDLipITVR+chokCQYJUQdeRcIG1foOHSwRiohqZAaqJEEmG/kGucF6f3+Rvq1AEsIGYIfpBMCgfqBOLIQCVm3MC+AWcgFyKj0Pn6oOaKCocBDzhQF44ehClQB9uPEoCIRw01gIhYgqfH7+oPgGAwJG3oWBi70UEadh/iBhoGPjWbkgZ4Fi3A+ZEp9nz8YQsxGT8E9ACzMUYA2SD5oNGSENwMYCFwAGFcQozBsfJj3wKuwOURr9AOcB0eg4DCRgMSCXb2xC2mHNIHOSQznnnf7m7kGfbYwzyiDEKGCDQMVBW+hwNxE/CJAI9Rn7X39QH0AEpJJLLH1F1621/XHguPNFn7Hd+jCa962Rr7v3heOQ4tuQmvfponfdePydL92+YiKXWf+2p37oeJOPdupl3TUTW7OG+3byXhl082iRQ/aZLTw6mG9cVfT6cB1dp1td3XxvbEUnepkuu7vWfe4973jJeytDsF6Vfqd/jGSV7voNM5bsPASKqvDaL6p+7Qx4rq2NAmVvhh0V/cwteGe5dt1/+h3Zne2Hou+16k28u4a7SlvdWrxNnGpNloc6vGbJ44W/QDe
*/