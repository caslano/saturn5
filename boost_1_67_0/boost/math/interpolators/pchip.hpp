// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_PCHIP_HPP
#define BOOST_MATH_INTERPOLATORS_PCHIP_HPP
#include <memory>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>

namespace boost::math::interpolators {

template<class RandomAccessContainer>
class pchip {
public:
    using Real = typename RandomAccessContainer::value_type;

    pchip(RandomAccessContainer && x, RandomAccessContainer && y,
          Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
          Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
    {
        if (x.size() < 4)
        {
            throw std::domain_error("Must be at least four data points.");
        }
        RandomAccessContainer s(x.size(), std::numeric_limits<Real>::quiet_NaN());
        if (isnan(left_endpoint_derivative))
        {
            // O(h) finite difference derivative:
            // This, I believe, is the only derivative guaranteed to be monotonic:
            s[0] = (y[1]-y[0])/(x[1]-x[0]);
        }
        else
        {
            s[0] = left_endpoint_derivative;
        }

        for (decltype(s.size()) k = 1; k < s.size()-1; ++k) {
            Real hkm1 = x[k] - x[k-1];
            Real dkm1 = (y[k] - y[k-1])/hkm1;

            Real hk = x[k+1] - x[k];
            Real dk = (y[k+1] - y[k])/hk;
            Real w1 = 2*hk + hkm1;
            Real w2 = hk + 2*hkm1;
            if ( (dk > 0 && dkm1 < 0) || (dk < 0 && dkm1 > 0) || dk == 0 || dkm1 == 0)
            {
                s[k] = 0;
            }
            else
            {
                s[k] = (w1+w2)/(w1/dkm1 + w2/dk);
            }

        }
        // Quadratic extrapolation at the other end:
        auto n = s.size();
        if (isnan(right_endpoint_derivative))
        {
            s[n-1] = (y[n-1]-y[n-2])/(x[n-1] - x[n-2]);
        }
        else
        {
            s[n-1] = right_endpoint_derivative;
        }
        impl_ = std::make_shared<detail::cubic_hermite_detail<RandomAccessContainer>>(std::move(x), std::move(y), std::move(s));
    }

    Real operator()(Real x) const {
        return impl_->operator()(x);
    }

    Real prime(Real x) const {
        return impl_->prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const pchip & m)
    {
        os << *m.impl_;
        return os;
    }

    void push_back(Real x, Real y) {
        using std::abs;
        using std::isnan;
        if (x <= impl_->x_.back()) {
             throw std::domain_error("Calling push_back must preserve the monotonicity of the x's");
        }
        impl_->x_.push_back(x);
        impl_->y_.push_back(y);
        impl_->dydx_.push_back(std::numeric_limits<Real>::quiet_NaN());
        auto n = impl_->size();
        impl_->dydx_[n-1] = (impl_->y_[n-1]-impl_->y_[n-2])/(impl_->x_[n-1] - impl_->x_[n-2]);
        // Now fix s_[n-2]:
        auto k = n-2;
        Real hkm1 = impl_->x_[k] - impl_->x_[k-1];
        Real dkm1 = (impl_->y_[k] - impl_->y_[k-1])/hkm1;

        Real hk = impl_->x_[k+1] - impl_->x_[k];
        Real dk = (impl_->y_[k+1] - impl_->y_[k])/hk;
        Real w1 = 2*hk + hkm1;
        Real w2 = hk + 2*hkm1;
        if ( (dk > 0 && dkm1 < 0) || (dk < 0 && dkm1 > 0) || dk == 0 || dkm1 == 0)
        {
            impl_->dydx_[k] = 0;
        }
        else
        {
            impl_->dydx_[k] = (w1+w2)/(w1/dkm1 + w2/dk);
        }
    }

private:
    std::shared_ptr<detail::cubic_hermite_detail<RandomAccessContainer>> impl_;
};

}
#endif
/* pchip.hpp
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
*/