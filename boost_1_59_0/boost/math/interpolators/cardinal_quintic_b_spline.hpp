// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#include <memory>
#include <limits>
#include <boost/math/interpolators/detail/cardinal_quintic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quintic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quintic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quintic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real double_prime(Real t) const {
        return impl_->double_prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quintic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quintic_b_spline.hpp
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
*/