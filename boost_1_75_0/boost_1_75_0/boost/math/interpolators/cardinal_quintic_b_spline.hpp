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
PMrWSbo99eioxlDicJXzrS5Lw2X9byqslU5P3vRpAh6HeaT4oYDDVZnqmYkMngj+VLw3icM1Kgr2trs/+WM1kydyWqIf8b2QAWRjvcdPRSBH8tg+cv0wSR74ZEjjv7kMkTA8PXzV+hH9te3tssgTNwA88eA/eL62KZB3aF/kHZGZaS11UVFLlROu0MC2cCYc9Xj+XI6DC23AjuJQilzojp2IlaaDfWI347ubv10o6aoy9U+q+xDy2jJeh44aInw7ywZBj9m43KufQ0Ra7Ex/BL5wAObC8XUMJxRfqewQUnhTidgwsLLYGlh+nKWlmw/4iOYNJmSY8rXm9vp/utVlYTYASgfpnBHg8avmAJ5t5yVIe9+hbN79716WXvAs4DUDcd7y0ErYK5gMYraJpE9YRkn2DEGdHjJg2bHaKyyghW9L9SeTD8lo0ZZ5KtyiLhfDMReinpbh6fiU0vnls5X1Iv/eY/NCxTzFASTJXGYzODzYG0u+sAOUr7/DbJymIlZYqs3KGo6zb3wfaqAyuLscL41Ps8jfj0zaQndZzgrYMi12prwAh8PE/qTyH6k2OldFAmF+McKvFgeWw5W/fbwO5tVyJ2qKSe/0WMutG0x8P4h0GbSPeimOOGi6Yrpk2S0ifzLt30GK3EsMLrJZ0h0uvdNiMYs0J+gciFS88UyHNPQfqf59yKlMWQVY3U8MBl+Vb4Q041XnbTL3gIxq
*/