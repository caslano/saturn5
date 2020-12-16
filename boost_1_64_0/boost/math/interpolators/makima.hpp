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
XXbUrmPEbnjU7gBL+3/Jl6f/553Rvt4r15P2T36e4f1bQyoda8pEytLYFRTaZeYXOVda9jk//7nPss+xPS5zn7VDA1/oNazG2QvubF6n8vx+55bfnOKfPVfqf060uDnIP39O2n8Otexz0mWdcy1urnqXed8Kf7Py4QVoOfsRGbfp+DXfc/bjNj7968HlsAG8F6bDFXBfuBK2hvfDDLgF9oAPwqPhKjgCroaT4Bo4G66Fp8LH4TnwCbgIPgmX6l7/1fA1+JiexdoAN8MX9TnvwMgZgA3wO90z3oB8vAj3gy/BDIh/3XuuYxkdJ+V79p6fj3OYF8Aarj3YW81YgLz6lFOBnoHbCuPhZ7Ax/AK21DNcbeHXWk7bYW81HwF3wFlwJ7wYfgcXwO/hPXA3fBr+oPn+Gf4If4E1bdoirAttfuzrQwc2giF4MIyBPWEVOB/GwwWwJrwDxsF71V7LSb8Z+Wb1KacbtJxuhMlwmZbTUvNNxXuj4eLR8zXcJXrW7grYHF4J94PzYRs1t1X3DDV3UHMnNfeEV2m5XQ1HwSUwC14DJ8Nr4XS1nwUXw9lq3gHTHP3m0G+lfHgoOtHRu3w0nfVgbZii+ZwHU2B9mArRsubQQN+LprAdbA47wnR9D1rDEyBuZq3hPF1ruAR21HZ/EHwYdoaPwi7wWV1b2AS7wddgd7gF9tCzMofBd2EvWAD7wA/h4Xp2ph/cCvvDz+EA+CUcCL+GR8JvNN2/wH0hbUnWTirB4bA6HAET4PGwJRwF28FMuD/Mhp3hONgFngX7wHmwLxwPB8O5/H8cPAeOVvcxcAKcCCfCyfAEOBdOhmfCKfBiOA1eBk+Ei2EuvBPmwUfhTPgEnAXXw3z4EjwJvgpnw/fgKXArPA1WdgrTmwjnwQmwpLWEZQVVdc2hdOcc/qw1Bs44/OnrDMH5hvJZa2jyE2cb0PnoZejn0T//FKw5BCpQgQpUoAIVqP+f+mvW/7k1uZzu/7+nKWO6yL3Ijs4doKuqfI/tyYwv34muffDkUu3hJoxZ0/iKOGwLcca++0nFr3c/qZH5e524TSF/jtVD55KrmTBpJp5qnmfmxHj3m+JH5oeqYTbyejPccnz99hMvlzh7M1/cxSO7k3QY9xOMm3sP6xPiNowxdUjlkps1+uje4VLsW/XbK06ZYidl6t23auR1qgxe8hj1497ff+c7Rff3f+Ux/6pmnlVk//F8TfRcdBWdH3myHmP6dz37j2ksPnvPzRruaPE/hHMEjm8bIj5vuzBrJAPELVXXFiJ+W5rwamfaQ8inPawQ96oSf4Kn3ieLW2srjZjc8p31eeo+1FvvEk+OuB3AXEusaVsqn9zsIZ8D/dpATCn2LuscfaS+jVnr27t3/F+5j7l+LQf7l5euv6L1JbtrDhvx7a8H9+n4arCP+Z+wj/lS09fyW+GzTzfcxKvCOrAWTIZJsBncB9aFabAe3B+mwANhfTgApsLB6n8obAjHwMZwOmwCz4JN4bnqbwfMN+88FpquaujJmq4MrKvATpqOnjAFHgxbws6wI+wCB8Kumo6emo5D4TjYHZ4Me8DT1L3n/2jf7obYULB3t5zn0/J/rmpd+nMwfxaoQAUqUP9W9dec/x87cXx2bl55nf+/13X+f7fDP65vp5vRz4XvW3vbjO306aU7y004MwbLqhP+W67/850HUL9m/G7r3nC/s6XGr5ENMIUk+Nz54PE7I8bcA+C7998br+Xai1kHdhT306xGjOmzi55BNvcA7it+LrTaMvLKRfvJAPCe8T8/PB4sh3kByhg7KWNzJwBlafbZmzsBxI4y07CJcIbYSdn4ygNo9HbR+YGJxuy50yecMZUDW0X30D4=
*/