/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_INTERPOLATORS_QUINTIC_HERMITE_HPP
#define BOOST_MATH_INTERPOLATORS_QUINTIC_HERMITE_HPP
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <boost/math/interpolators/detail/quintic_hermite_detail.hpp>

namespace boost::math::interpolators {

template<class RandomAccessContainer>
class quintic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;
    quintic_hermite(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2)
     : impl_(std::make_shared<detail::quintic_hermite_detail<RandomAccessContainer>>(std::move(x), std::move(y), std::move(dydx), std::move(d2ydx2)))
    {}

    Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    Real double_prime(Real x) const
    {
        return impl_->double_prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const quintic_hermite & m)
    {
        os << *m.impl_;
        return os;
    }

    void push_back(Real x, Real y, Real dydx, Real d2ydx2)
    {
        impl_->push_back(x, y, dydx, d2ydx2);
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
    std::shared_ptr<detail::quintic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_quintic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_quintic_hermite(RandomAccessContainer && y, RandomAccessContainer && dydx, RandomAccessContainer && d2ydx2, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_quintic_hermite_detail<RandomAccessContainer>>(std::move(y), std::move(dydx), std::move(d2ydx2), x0, dx))
    {}

    inline Real operator()(Real x) const {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const {
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
    std::shared_ptr<detail::cardinal_quintic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_quintic_hermite_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;
    cardinal_quintic_hermite_aos(RandomAccessContainer && data, Real x0, Real dx)
     : impl_(std::make_shared<detail::cardinal_quintic_hermite_detail_aos<RandomAccessContainer>>(std::move(data), x0, dx))
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
    std::shared_ptr<detail::cardinal_quintic_hermite_detail_aos<RandomAccessContainer>> impl_;
};


}
#endif

/* quintic_hermite.hpp
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
*/