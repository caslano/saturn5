// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// See: https://blogs.mathworks.com/cleve/2019/04/29/makima-piecewise-cubic-interpolation/
// And: https://doi.org/10.1145/321607.321609

#ifndef BOOST_MATH_INTERPOLATORS_MAKIMA_HPP
#define BOOST_MATH_INTERPOLATORS_MAKIMA_HPP
#include <memory>
#include <cmath>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>

namespace boost {
namespace math {
namespace interpolators {

template<class RandomAccessContainer>
class makima {
public:
    using Real = typename RandomAccessContainer::value_type;

    makima(RandomAccessContainer && x, RandomAccessContainer && y,
           Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
           Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
    {
        using std::isnan;
        using std::abs;
        if (x.size() < 4)
        {
            throw std::domain_error("Must be at least four data points.");
        }
        RandomAccessContainer s(x.size(), std::numeric_limits<Real>::quiet_NaN());
        Real m2 = (y[3]-y[2])/(x[3]-x[2]);
        Real m1 = (y[2]-y[1])/(x[2]-x[1]);
        Real m0 = (y[1]-y[0])/(x[1]-x[0]);
        // Quadratic extrapolation: m_{-1} = 2m_0 - m_1:
        Real mm1 = 2*m0 - m1;
        // Quadratic extrapolation: m_{-2} = 2*m_{-1}-m_0:
        Real mm2 = 2*mm1 - m0;
        Real w1 = abs(m1-m0) + abs(m1+m0)/2;
        Real w2 = abs(mm1-mm2) + abs(mm1+mm2)/2;
        if (isnan(left_endpoint_derivative))
        {
            s[0] = (w1*mm1 + w2*m0)/(w1+w2);
            if (isnan(s[0]))
            {
                s[0] = 0;
            }
        }
        else
        {
            s[0] = left_endpoint_derivative;
        }

        w1 = abs(m2-m1) + abs(m2+m1)/2;
        w2 = abs(m0-mm1) + abs(m0+mm1)/2;
        s[1] = (w1*m0 + w2*m1)/(w1+w2);
        if (isnan(s[1])) {
            s[1] = 0;
        }

        for (decltype(s.size()) i = 2; i < s.size()-2; ++i) {
            Real mim2 = (y[i-1]-y[i-2])/(x[i-1]-x[i-2]);
            Real mim1 = (y[i  ]-y[i-1])/(x[i  ]-x[i-1]);
            Real mi   = (y[i+1]-y[i  ])/(x[i+1]-x[i  ]);
            Real mip1 = (y[i+2]-y[i+1])/(x[i+2]-x[i+1]);
            w1 = abs(mip1-mi) + abs(mip1+mi)/2;
            w2 = abs(mim1-mim2) + abs(mim1+mim2)/2;
            s[i] = (w1*mim1 + w2*mi)/(w1+w2);
            if (isnan(s[i])) {
                s[i] = 0;
            }
        }
        // Quadratic extrapolation at the other end:
        
        decltype(s.size()) n = s.size();
        Real mnm4 = (y[n-3]-y[n-4])/(x[n-3]-x[n-4]);
        Real mnm3 = (y[n-2]-y[n-3])/(x[n-2]-x[n-3]);
        Real mnm2 = (y[n-1]-y[n-2])/(x[n-1]-x[n-2]);
        Real mnm1 = 2*mnm2 - mnm3;
        Real mn = 2*mnm1 - mnm2;
        w1 = abs(mnm1 - mnm2) + abs(mnm1+mnm2)/2;
        w2 = abs(mnm3 - mnm4) + abs(mnm3+mnm4)/2;

        s[n-2] = (w1*mnm3 + w2*mnm2)/(w1 + w2);
        if (isnan(s[n-2])) {
            s[n-2] = 0;
        }

        w1 = abs(mn - mnm1) + abs(mn+mnm1)/2;
        w2 = abs(mnm2 - mnm3) + abs(mnm2+mnm3)/2;


        if (isnan(right_endpoint_derivative))
        {
            s[n-1] = (w1*mnm2 + w2*mnm1)/(w1+w2);
            if (isnan(s[n-1])) {
                s[n-1] = 0;
            }
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

    friend std::ostream& operator<<(std::ostream & os, const makima & m)
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
        // dydx_[n-2] was computed by extrapolation. Now dydx_[n-2] -> dydx_[n-3], and it can be computed by the same formula.
        decltype(impl_->size()) n = impl_->size();
        auto i = n - 3;
        Real mim2 = (impl_->y_[i-1]-impl_->y_[i-2])/(impl_->x_[i-1]-impl_->x_[i-2]);
        Real mim1 = (impl_->y_[i  ]-impl_->y_[i-1])/(impl_->x_[i  ]-impl_->x_[i-1]);
        Real mi   = (impl_->y_[i+1]-impl_->y_[i  ])/(impl_->x_[i+1]-impl_->x_[i  ]);
        Real mip1 = (impl_->y_[i+2]-impl_->y_[i+1])/(impl_->x_[i+2]-impl_->x_[i+1]);
        Real w1 = abs(mip1-mi) + abs(mip1+mi)/2;
        Real w2 = abs(mim1-mim2) + abs(mim1+mim2)/2;
        impl_->dydx_[i] = (w1*mim1 + w2*mi)/(w1+w2);
        if (isnan(impl_->dydx_[i])) {
            impl_->dydx_[i] = 0;
        }

        Real mnm4 = (impl_->y_[n-3]-impl_->y_[n-4])/(impl_->x_[n-3]-impl_->x_[n-4]);
        Real mnm3 = (impl_->y_[n-2]-impl_->y_[n-3])/(impl_->x_[n-2]-impl_->x_[n-3]);
        Real mnm2 = (impl_->y_[n-1]-impl_->y_[n-2])/(impl_->x_[n-1]-impl_->x_[n-2]);
        Real mnm1 = 2*mnm2 - mnm3;
        Real mn = 2*mnm1 - mnm2;
        w1 = abs(mnm1 - mnm2) + abs(mnm1+mnm2)/2;
        w2 = abs(mnm3 - mnm4) + abs(mnm3+mnm4)/2;

        impl_->dydx_[n-2] = (w1*mnm3 + w2*mnm2)/(w1 + w2);
        if (isnan(impl_->dydx_[n-2])) {
            impl_->dydx_[n-2] = 0;
        }

        w1 = abs(mn - mnm1) + abs(mn+mnm1)/2;
        w2 = abs(mnm2 - mnm3) + abs(mnm2+mnm3)/2;

        impl_->dydx_[n-1] = (w1*mnm2 + w2*mnm1)/(w1+w2);
        if (isnan(impl_->dydx_[n-1])) {
            impl_->dydx_[n-1] = 0;
        }
    }

private:
    std::shared_ptr<detail::cubic_hermite_detail<RandomAccessContainer>> impl_;
};

}
}
}
#endif

/* makima.hpp
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
*/