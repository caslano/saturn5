// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#include <memory>
#include <boost/math/interpolators/detail/cardinal_quadratic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quadratic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quadratic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quadratic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quadratic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quadratic_b_spline.hpp
QHmbz7D18RZTkWgyaxsMrKR2hdlt9bbNHIq+UVjYyp7qMEt9rGVy+pNiG5TLVIcdFjDUI74v5v1/h+h5O1k9GLw74OP/B3mxjg2om8FhyO1F3unG4SqbpH8e7ob0Efmy/pKN7Z0z2Brqnc1GI2zedf0w/zcPBCbTXc429a0S35E3NAzA1UZWVhLzn/70HLRepMO3p/qSG1NoXr3F5KLKEdvyM9yBPqjPS3+oHVkOj5j4gCexc6wbSml7vcVLNAeTX45jD8Q33ZLGy/U5qS3BZGyzfK/dhzyl5cTZlpqli0cMZpJ1rc1kL62gDMXkdU/0m7ouU7/U4nIzNYCltRFmY39d2w5uiMAavP9NXpe2toxwMuAtDtdbS+0mT4WLy9vNIeiPMHc6llutIC7KU/aBDtdzNcPJKgEcvu3TjxzbxfP5cOgXfAttOPlfWtt+8Vl7pL4x9INd//2j2B7Kd6jA4Zso/cjqJ4DLdlmpAmaiexGe7yTjy1Umm6wTAU8OR/sfKjRX+hoCeNVAjOuqZ1CWVFHAG8Kg35X1ZvvTdp0D/OH+YN3elTI861S08VR/nCvMv7ptGylX8eax8g+z9tmny4t20bIl3ulJQgflWEpcFjcvk8/jf+6ifEZ3BVShE3rmxnDUw/a4FyhWUeQJ64Nzj4l5uW6Lfr2bzkQZVwO/PQJnHsMntK0n0L5x2NkfesQbE9O5ymVkPrBh0Llm
*/