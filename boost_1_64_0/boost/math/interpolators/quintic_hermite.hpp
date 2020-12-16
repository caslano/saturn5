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
2oXb6fZI6wee29xpwF2SlbSdIH1a8l0ZiQPvyPM+4nlvSfgz9XnRPjhJ3+93xP1kJ50S7e0U7hFsVJhnk6Y7JE1x5re491t697eJM2vCjKmTRnGC3sitaSVp+Zpze91LVe+ueEy7HypxPE6t9/XJ46f0w8Oln7izVmFfVJHEfl6b+oZT05g73sdtJ37Mb0naXuTLkEd/+TK86+5+i77C3CWfoL8VIkdK3/ka2G0zvycnWkny+6J+9D3SsNKeE8Re2v+/cr/jGbIOcdrwb24fcuSzBxR8+2jby6pM2hzsd/y79zu6ZA7I9/6tsJXKHDjGjC9lvCxuPNbcfd1c1w9awSawNWwH0XIGPAP2gx3gULg/PAYe4F4P0PgX+8gd5V03Z7sbwBTYAdaHHWFj2AU20OekwQtgQzgfNoLXiD+9Xy3yTQszfe5XO1jzc6jmp7vmpxccBPvAY+Hh8DjY1+RDvqX85afqGW4bDoa14RDYCg6FbeFwmAGPgt3g0XAAPEafdyw8Tv1JvTj6raHfO7dK2uSeb1Gj8VcdjoP14HhYH06B6XAqbAmnwUNhDuwNv9ByzIVHwhlwOJwJR8F8eApEyzrPqfBaeLqu95wBb4PnwHtUNsN98CL4DrwYvg8vg1/Ay+EueCX8CS6Ae+AiWI/MLYVp8HrYFN4AO8JlsCt8E/aE78NB8AM4HN4Jx8F74IlwOTwXyr2WcA28Gj4K74FPwHvhk/B++BR8Hq6DL8MX4UaVUfE6fAW+CzfCAo13J3wN/gTfgL9o+kLhNWEYC0+DiXAOTIJnwnrwLFgfngSbwdkwHS6GHeASeAB8Gh4GN8De8DE4BK6Fw+B9cDhcAUfCT+Bo+CmcAL+Ak+HrcB78DF4BP4cL1X1osM+3VPt8R68qn72+/4V9vhMecu/1JU7Wkpah16IL0NavwdpSoAIVqEAFKlCBCtS/Vf016/9jJuaxtba81v8fcN0BkKdj5KPQFdDD0C93YR7ilejaTPfDh44aMnTw4QN6G7HrLpm5mUZu9k4JM5h5w1b+a77ibpvz+LY1bnLm+Fyz5llnY9iuse9agoZVWa8mrMgIr6HPT5Dw6b5rOxreV255BQnXCbORIyt5FPm7sIq4728lk4sGpEb2eIu/KZm5+CT/sgbcSPzVZD6ygneNx19uspG7Shm6z3RruSRhV83I2zf5LSKf+1aVnd8f7aD7oUftw5zHRt/6G4/oahpTkfoz5ZcrYeL96o743OUn8/pm7WucuHXnfG6Kb915w7KeY+auZ2rZtnW5Y2vq5hpxj93rmpmnPMUca8puapE156fCHrW9R5hRj3kD/zJDErFbzne+X/kQ1nt35VjfslB/2tbMmQLfNmviNPK4yyr7PCorgDSpfF9Xm9Jnu9tToq7H/6hp+AGdTXt6udiy0fZkyifTnJ35WsJs4vx2BebEQv5y4H3aVQ0NXyBuFVUGQ8RvexNe7TzlOTNz8oxss77yurjnkb8YiaeaCdPVxKN23jZqZGn/IG6vsLrbhrm5GJOe0Kaw/XrXeZ8s89y+4jaIOWHHyMdeKHYt3O3cyJ/YtbGw70zDv9gZ/60pucYm7TXEbo17TXWm5ZIdX0HcryUOTragI2t3a8U+eofAPeHJYJ+1aAz+7cn/vfK0Jyn7Iu/a8sp6b4BN24JJsH9TnvOqtKcslqA9baqwLU1OkrZk+ph08f89c6GVfNsR8Zl2sE1+W3JyLNd6YeprKmNd6+cI8R/yfUfdcSWYdzR6r0sDca9k3y5nc6gXE+YDaw5lvJpfCdO2PPFRjkXuwKwDGxe62zd47p9N0rRniPupPK0Nrb+9+V0aKvZL5BengzXG7A/ZIfbx5i6KY8U=
*/