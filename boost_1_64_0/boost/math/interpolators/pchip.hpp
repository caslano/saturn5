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
z8f99re98wPSkEp1Pnl7GdqR8WvmDXhtLP92tL0M7Wh7GdrRdv92ZPZnJsv4KcW0B7/984niJ83snx8gZtd9rPEltxurFHMJvu3GPZ8kZVf6dpNQpN2QZ9fewHMdZElXpyztzt+nNx+665R5d/Yenryt0gVzyj6+Lq89gwNknuHVZusO6/7movi7W5wyfGtGh5nlN34v67xEgpTPWbdc+9rH69u2PX39kPyJF928rezzFf+3PYO9pdzy6p733elHLhx+9r5HL4nrUPmj4ueLRH51pL/X37tL3fKrdV5C5kxhEmwIW8NGsBdsDPvC1rA/bAaPg+nwJNgCngf3hRepv0tgS3gdbAVvFns9ZxzpNzQNl3rOGXdwzV80gQfCNrAz7Ae7wONhVzgadodjYDc4Ax4KZ6t921CJe4LMXEanIxi/or3zFtth3AD/+Ytj9jKHsRtWG1g4l9FyYOnmM1bxdwG6ySDc0ediNwEugPnQO8exXOc5Xoad4XYYme9IPrL4OY98z7zHnfAptN9+otjBhfMf6bAb2n8ehDixW4TueQhusLg5kRydF1mJ3uKaH9k9pOQ5kuShxBW2g4PQkfmSCUPNnAkTWNih3XMnKzG750/ShpU8h1LgmkdJPCo6lzISzkUvRbvnVbaUcW7lGOzy0YvQq9DFzbVsOzo639IE3V/nXS70zL0sPSY6/7KBvz9Ce+dhrGNJK0yHfdCjdU5mLlyELuhBnpmXSf4lmJsJVKACpervHf9nTCxH+X8rXOP/t3X8P1LHR8egv2bslvN6dOzG0438v5tk3JY/NXuW77iNcKXfB4Bfj/wxjhv5j9uMX1mbFb/5fmM2/JW8BnyJuB9o1ni9cvpkQO+6g3WB+G9j7hqW88me+3wT4ELxl6JmTuuJuaI5s7uSMr+9lsrz8x/r942c2ZWwnjNb4XKvLeXuuydAx3B6tlfLsYaO4SivIjLGXOvGkifyjHmMjPHve73IHgDTTjroGH+x7hW5Bv1teIzvaSeIHytVO9lehnbi9luQWHI72V7KdqL+vLLIpI3Ebg67nW41IKWpnJstcGgHJPoD8hTqV9EJ1a46qWrjijHVKtbx1q9vu0uG/STOzqVqd2TRGir+O5TY7uLhIPFXy8wZzBBzRTnHq3NOXjlqRoZabCnuoSxtu6Neim93tKvJm027KiLbMFnPl2dqGo5D/0y7WrvZM3fE48oi25DwPn2Lb/vCb+nk2+GvxL7lPXHvWqo6DreJraWo4wT4ufhraPqWuC1Sx2aPEW2P/SV77V+MTADCa/9SGnmFWqdmjqh0fYl7fvDCWI/8Qr34u9uW39dxaeUXEtanT/CtX/yWrn7xV+J+ssu2FC+/cMCWvcsv/Ljc5Bf614m8V3pX71nVLVFL6Jyqw4XwxS604S3mXL0U9/TsTCMz1POu+L9XrjJ6nvhs7of2LXePX8kE8bKfwsgSiX8j7H6EU9y9/tG7dGdlIkDFyEdIfzMcbqfsEbzQ6m767QYS3zP2IG5Mi9zn3+6tsF0LrcOIOb3IPH5d7Uv7S/jVdm1uxOprZ1jn22lWqvark8TtDU67v83ZR+4Ut+tb/e2zXO/6iZLubaQ7wcRt7sk3/YBrbcCsH0yXuM+yL+T7YTX/peoZ98Ly6eU4nMasbC/kfqKh3MXIeXuzfy1XOgrSL+bPxH8fezxfce9ZRyBzoJrKf/D0P5rfk6Qc+Y3Tcv1oS2F9NMauJ6lJcJpZPZ0Yy1OWUn9biXOr+J/pROspexqZlfTUgk9KeqbaFyGZrwJl2d5uwLNwM3lr76TRX57NbPAQ+yRrs324xF1A3Jsl7nmO3x3Z8XCdhHesfbXuXxL/Y5yOVgVyPsQ=
*/