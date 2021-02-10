// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This implements the compactly supported cubic b spline algorithm described in
// Kress, Rainer. "Numerical analysis, volume 181 of Graduate Texts in Mathematics." (1998).
// Splines of compact support are faster to evaluate and are better conditioned than classical cubic splines.

// Let f be the function we are trying to interpolate, and s be the interpolating spline.
// The routine constructs the interpolant in O(N) time, and evaluating s at a point takes constant time.
// The order of accuracy depends on the regularity of the f, however, assuming f is
// four-times continuously differentiable, the error is of O(h^4).
// In addition, we can differentiate the spline and obtain a good interpolant for f'.
// The main restriction of this method is that the samples of f must be evenly spaced.
// Look for barycentric rational interpolation for non-evenly sampled data.
// Properties:
// - s(x_j) = f(x_j)
// - All cubic polynomials interpolated exactly

#ifndef BOOST_MATH_INTERPOLATORS_CUBIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CUBIC_B_SPLINE_HPP

#include <boost/math/interpolators/detail/cubic_b_spline_detail.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");

namespace boost{ namespace math{

template <class Real>
class cubic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cubic_b_spline(const BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                   Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                   Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());
    cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
       Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
       Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());

    cubic_b_spline() = default;
    Real operator()(Real x) const;

    Real prime(Real x) const;

    Real double_prime(Real x) const;

private:
    std::shared_ptr<detail::cubic_b_spline_imp<Real>> m_imp;
};

template<class Real>
cubic_b_spline<Real>::cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
                                     Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cubic_b_spline_imp<Real>>(f, f + length, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template <class Real>
template <class BidiIterator>
cubic_b_spline<Real>::cubic_b_spline(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
   Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cubic_b_spline_imp<Real>>(f, end_p, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template<class Real>
Real cubic_b_spline<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real cubic_b_spline<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}

template<class Real>
Real cubic_b_spline<Real>::double_prime(Real x) const
{
    return m_imp->double_prime(x);
}


}}
#endif

/* cubic_b_spline.hpp
4vTMDvCTS3LOweCOnJONSU9/z2591arRfDOS/vnnr3hJ0ew/fsD9cX0t5kLpjyGl/xr/QJamScup8RxnCJwncXvGv941k6nv1Wb8Cpat4kZGpVlubXq9nlhUgzUX0mJd9Ul9pw70KnaW95TT8t0CwBnPJKPYcA1eCqTffDK1doFq1riHotp9Z73/OBxewxr8fptBWGMkRFdMj4XSAcNszYFWz+Z7oxKuz1AnPmLah/lsxiqBrYEtrcJl23x6S77p4Fc2AC4boZv1reeevm9GEfSvZCJocDC0oVuZ5iFZdMOc72SPVuoyJXYhps+iN7xatzS57zcx7Ro6jmsHNC1eEr9TsoIQNUEzQivobrxcAsHBnYQythK5IPaUFMDPWWyCxC6FWgNZbWXIxMXMv99+cQH6u7qthpf7IpWObVUHko2hV33m4tREzuN4bvkLW6S+k+aG2N4Ar4lySELB5hCwRCcCe3indgbIT6+DjOy19LC0jrA+5UdydF7fKPIQEB7V+jp6AxEEJHdONaS5R7uaTK5VLDonCC5p2WrqYJxzgQ8NmmJ5W0ZinhTopzS62MQV5dpe91bqJCq5zwax8+875/Xl6CaOYc9nMy56kyISQXP2SHfhBS+0y6KratAxZ+n1k4SAGfVqnXH/BZwX
*/