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
#include <boost/math/tools/header_deprecated.hpp>

BOOST_MATH_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");

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
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
*/