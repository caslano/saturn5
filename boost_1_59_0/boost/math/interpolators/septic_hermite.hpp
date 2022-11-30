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

namespace boost {
namespace math {
namespace interpolators {

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
}
}
#endif

/* septic_hermite.hpp
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
*/