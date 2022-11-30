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

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_HPP

#include <boost/math/interpolators/detail/cardinal_cubic_b_spline_detail.hpp>

namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_cubic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cardinal_cubic_b_spline(const BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                   Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                   Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());
    cardinal_cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
       Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
       Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());

    cardinal_cubic_b_spline() = default;
    Real operator()(Real x) const;

    Real prime(Real x) const;

    Real double_prime(Real x) const;

private:
    std::shared_ptr<detail::cardinal_cubic_b_spline_imp<Real>> m_imp;
};

template<class Real>
cardinal_cubic_b_spline<Real>::cardinal_cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
                                     Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cardinal_cubic_b_spline_imp<Real>>(f, f + length, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template <class Real>
template <class BidiIterator>
cardinal_cubic_b_spline<Real>::cardinal_cubic_b_spline(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
   Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cardinal_cubic_b_spline_imp<Real>>(f, end_p, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::double_prime(Real x) const
{
    return m_imp->double_prime(x);
}


}}}
#endif

/* cardinal_cubic_b_spline.hpp
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
*/