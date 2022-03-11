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

namespace boost::math::interpolators {

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
#endif
/* makima.hpp
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
*/