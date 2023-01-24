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
jLeZDvVvLYe7jVjXT4+Gf1DonHVuc7bNkukuTanweBx2htsJe5iiJZniyouyFzPY/nE4TymWYKmqrNQ0+AgB1zAV5zE/PMVwqpTsHENOmiFnmWZhVnZOmkhzKQE+VXfnsjTL0vRZ2bwI4Gqn4Xx5ULwPx/PgO8cRCnMLg7MifXl2U5oDFWSSlEel1UpFGhETRDsOtlzd7d720Tkrmsjwx6fjrJv8gvzmIipc6D4K8AzKy2GKfXEcrmdqLuBho5H+zd853FBmdZlZ+sZxSN/8sCjHUeHylOFsxzMddr4RWV76wh8cODNsMoqt/ZDHmpXNrKqA66LQx09tYfDUHI1Bk8r8sBhuOvroh10MtyQ3LWcZh4eNB/2sMQxuVOVkabIWAn56HM4Yk4IZXJOVni34NW4seORYmr7MUSn5QDGbBttv/niNwerx+uAkx2EP8O1j2JwxfZDpFhWxMh3By9ORM4BzXSXKlLqa4QqvgmwdVS3EZpskbH80FXVq/UMgWE8BfjgRZa59m2qyzEVCZbMwvQDtSGI+kUeb0A7UB7AD8ZD9K+YIXZRpASkmF9tbAo9vpQ8he2ra4ducNW9kc3yYSWsqgtsrh7F99yvPq8oxpXCyyq3ubO80FOlzR4sjaCZf6ieg3lf3hj+ITITwNiWgTyN+BwhpIwYj7ZxjqSY7muI9qwNOPRryM/KIHAE4vsceRnrn8TWMkwBcm4j0
*/