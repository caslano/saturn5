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
WSbWLQQ4e8ickMQoW+6H/0XM0yo/1cGZyP9GbVmKjbB9Nxyn1yyJ3UsNPPYLcSfi2ZyDun2p3bq51oYUKCWuiiz2azu01a7WqcbA+UQpxmtY3W+7Hbuv4Z2YTnCjlw08+y5ZEFA1NqUnYz3+bopVGxqeTFRBXztVHIguKnlzJdXeNBBrZQHvQTLlFn6MZj3rUcVVsWDHgjyfa905s+QFl8Cj7G/fN2uUpsR5fhzPW6PEn4gSQISUQwje8TImwvkq45pSsqIJ8mJYIgSmd1SQxi7m03JrA2YholKLr9Pi9f1ZfnGCNCLn5LrnQlFErxO0mkUnwJQu4i/CkKd1P7V2h65wPTdj20KLxKDBa8dKkiB6nmUnQAEZTvs1383I0qQHJKWT07UlbmvXAPmI0dSM6V6gJ0tHNar1IeSa7f6XqZHcJwjNokfhr99uFRP57/FFWlgArCYShBXMsakdAOJd6PcuFR6GE0a1yQB/P6bWy+RfHY3/vtv2mH8jPmzPq2jZ2dgdW9ftHG7Wi1lsRSqsAxisnvgucQNqVfJVvHZWZm8kxphecJRuMoyKDw==
*/