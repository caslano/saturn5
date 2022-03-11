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
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
*/