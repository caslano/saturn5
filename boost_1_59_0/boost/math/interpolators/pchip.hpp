// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_PCHIP_HPP
#define BOOST_MATH_INTERPOLATORS_PCHIP_HPP
#include <memory>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>

namespace boost {
namespace math {
namespace interpolators {

template<class RandomAccessContainer>
class pchip {
public:
    using Real = typename RandomAccessContainer::value_type;

    pchip(RandomAccessContainer && x, RandomAccessContainer && y,
          Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
          Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
    {
        using std::isnan;
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
}
}
#endif

/* pchip.hpp
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
*/