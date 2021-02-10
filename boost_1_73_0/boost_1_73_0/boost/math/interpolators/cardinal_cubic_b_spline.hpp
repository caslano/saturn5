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
kJVdJk+5V498ODfe0WOTFnbWw3jqQxP0nSw7OZnfcUYJfGK8+TbS/E42miZPR72nnhfC37B2mC6GKzY2xeyptfOm9UPdwNo6TlZ3Cjb1y6MxJkv/RZ33B4/Z46w3tvz9fC8srXZHzdqJw4KaeSwEBLvjerfp2jWBZio7jD26DBBuvzn6tT5yNXqMZ3ub8JF/MVl3Ws8rJZpMIsVYplOWvLb658rPrk+ELR8ux9c8bxd1MD7bcrhOxzdorn55Gs6vt07b89ybWb88aMFC7llHI1puD85Oaa3PebdYu93V6igvw/nAZItJosijYrL2vLp97NaKUXvLszxQ1claTdvu+HH61GMvSWKl+bHf2jiq3vfzxSjjs4fyOE3DfF5OSm2Zr5bR+WQP/UQY40LWqnCxHudn5/RYGfOXMxlFyYWP0tby9dV4eDzIL5ctW10PWS+9ddtaT9Gu7XmZ29MiOE70QTBZPon5c7qIz735KuwG05tYLQv5Nm/tNg/kVqkR2ydjvb0aTUX3ca+NXvU8WWfzgp0vY7M/SXvZMCRF9v37D4L1Q+93ev0PUEsDBAoAAAAIAC1nSlIlgIRA9QIAANQDAAA4AAkAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9z
*/