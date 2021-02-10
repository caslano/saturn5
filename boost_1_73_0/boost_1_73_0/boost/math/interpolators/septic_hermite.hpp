/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_MATH_INTERPOLATORS_SEPTIC_HERMITE_HPP
#define BOOST_MATH_INTERPOLATORS_SEPTIC_HERMITE_HPP
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <boost/math/interpolators/detail/septic_hermite_detail.hpp>

namespace boost::math::interpolators {

template<class RandomAccessContainer>
class septic_hermite
{
public:
    using Real = typename RandomAccessContainer::value_type;
    septic_hermite(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx, 
                   RandomAccessContainer && d2ydx2, RandomAccessContainer && d3ydx3)
     : impl_(std::make_shared<detail::septic_hermite_detail<RandomAccessContainer>>(std::move(x), 
     std::move(y), std::move(dydx), std::move(d2ydx2), std::move(d3ydx3)))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    inline Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const septic_hermite & m)
    {
        os << *m.impl_;
        return os;
    }

    int64_t bytes() const
    {
        return impl_->bytes() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }

private:
    std::shared_ptr<detail::septic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_septic_hermite
{
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_septic_hermite(RandomAccessContainer && y, RandomAccessContainer && dydx,
                            RandomAccessContainer && d2ydx2, RandomAccessContainer && d3ydx3, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_septic_hermite_detail<RandomAccessContainer>>(
     std::move(y), std::move(dydx), std::move(d2ydx2), std::move(d3ydx3), x0, dx))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    inline Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    int64_t bytes() const
    {
        return impl_->bytes() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }

private:
    std::shared_ptr<detail::cardinal_septic_hermite_detail<RandomAccessContainer>> impl_;
};


template<class RandomAccessContainer>
class cardinal_septic_hermite_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    cardinal_septic_hermite_aos(RandomAccessContainer && data, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_septic_hermite_detail_aos<RandomAccessContainer>>(std::move(data), x0, dx))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    inline Real double_prime(Real x) const 
    {
        return impl_->double_prime(x);
    }

    int64_t bytes() const
    {
        return impl_.size() + sizeof(impl_);
    }

    std::pair<Real, Real> domain() const
    {
        return impl_->domain();
    }

private:
    std::shared_ptr<detail::cardinal_septic_hermite_detail_aos<RandomAccessContainer>> impl_;
};

}
#endif 
/* septic_hermite.hpp
xiheftVN6H28Ooj7tBPYWxa+PKJRt1ob5snDGNcRxbfCmXmxa9FxRy45c6YV5S0K5iTvJtdLI8/yI10Y9LIeLa2l4U1f8ZIIczfzNbJwBCeVwl2eSd587y5OMllyTjsdaQLn0DrZnsl0mFJGaz8qqxHnPWL6EHeEl41ObrrRqgm3IpuJkrjBTM9j7TqZZV2xYIou36aPIRnf18HtMmRXGmNZpy4/1c10pokacRay/Wrq3cp50MTcqUjbqhy/bqdistba5/UR6IFN7S3moa4S+b5ZjMwSzqpfBonv3685TYSrSlkHC1p9rg5cOVvPnNNslTwWrZu9ZoItnMenp+/iICuaoa/nTbum1yPyMmye56RbNcS8O5aRst4WrVvPrieGlzvSyIysiK0JmW2U+DXftHVnNoWwPB7Yc8sWNB2u+TjbzscPOyO266jIJXdudvLUzev52ackX9s6NNWMZrXxCuzz5kp3U/twb14zi+aOd4Vjm3Y1yhgzZqfEk7uSAMm9qlRBLa2NP1wzXTNVkxFdXhRW3LSrRruI55zT9dVFmZjL0nDU9rbY765dI74Ie/ncuN0mPHBy5G7V4NXWy2EBp4Yqx9eSuUeHk3UenvRdKiYrRklEtRgtR8yMOjOd6IkxMSrDbKwH86yzVEPK
*/