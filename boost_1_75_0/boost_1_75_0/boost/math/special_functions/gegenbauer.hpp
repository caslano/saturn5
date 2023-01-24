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
ARzBO2HfQd2ZlMSQO+UnHqLtk84F0ngEkjm9Icpdgvn90XVZFc0UzeeOt0RzYeaxodfI7E82o7WkS57ALi+2bAW1ypCxJuPcQhzpkinqBRO5OA+n3HrXzKxklDaIfe+gzLZ9xFHZyzsJ+C5kG8L5rlNn8pDGBQuG3Bz7O/I2dKUNBdyfNW7zFKfKZS4J3KJJ8tnW5ZzmuIc/ExOUSncvgtS5bdYse5MbRh/zuEd9kmbwNJ3PlBQqNstd/UepuBzKZNx6Sur06/ZW6d2YATTt1cnE2sWK5i4eEmemuFlxJwIUSNGLHW0pwtZCzAvndZONTXHZkVmESe2azKTyA5LMYs/zko3dZblh9bTjUBMOoR8UDY0qgq5COVNZCtGzqGNqkI9bcgedxcIUSlZ2l0Pu5U0q3Kk+ZRu5hFo59WgL6j6LE3ElSWYuHaaFoTxp3J1JcAZCumpC7w6eVjZsfZU7obEpEuSyP4ErvFhmsj+OtHt7W+x/1q9aNFG6imrQjAT0k0ytyVNEatN4ip/qqsQpqpjLdHLfOamv/5Urm6yirq8sLOXoIUks3sm4i4v+fbpf0vg3H8EJZmtrCzTsi31DD/L0SyucGkC16Ed1AlqYKsEinxFSYZjGKVC32slGbg8IH/VSUeaJF9uXv6NXGr3d6dFtfjKvN7CY1Aa42upj4XxImcgT4s0VH71LxGKfIsG4258prw4Y3/Eoetiq
*/