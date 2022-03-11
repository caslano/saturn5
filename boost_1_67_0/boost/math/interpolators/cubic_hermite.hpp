// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CUBIC_HERMITE_HPP
#define BOOST_MATH_INTERPOLATORS_CUBIC_HERMITE_HPP
#include <memory>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>

namespace boost::math::interpolators {

template<class RandomAccessContainer>
class cubic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;

    cubic_hermite(RandomAccessContainer && x, RandomAccessContainer && y, RandomAccessContainer && dydx) 
    : impl_(std::make_shared<detail::cubic_hermite_detail<RandomAccessContainer>>(std::move(x), std::move(y), std::move(dydx)))
    {}

    inline Real operator()(Real x) const {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const {
        return impl_->prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const cubic_hermite & m)
    {
        os << *m.impl_;
        return os;
    }

    void push_back(Real x, Real y, Real dydx)
    {
        impl_->push_back(x, y, dydx);
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
    std::shared_ptr<detail::cubic_hermite_detail<RandomAccessContainer>> impl_;
};

template<class RandomAccessContainer>
class cardinal_cubic_hermite {
public:
    using Real = typename RandomAccessContainer::value_type;

    cardinal_cubic_hermite(RandomAccessContainer && y, RandomAccessContainer && dydx, Real x0, Real dx) 
    : impl_(std::make_shared<detail::cardinal_cubic_hermite_detail<RandomAccessContainer>>(std::move(y), std::move(dydx), x0, dx))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const cardinal_cubic_hermite & m)
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
    std::shared_ptr<detail::cardinal_cubic_hermite_detail<RandomAccessContainer>> impl_;
};


template<class RandomAccessContainer>
class cardinal_cubic_hermite_aos {
public:
    using Point = typename RandomAccessContainer::value_type;
    using Real = typename Point::value_type;

    cardinal_cubic_hermite_aos(RandomAccessContainer && data, Real x0, Real dx) 
    : impl_(std::make_shared<detail::cardinal_cubic_hermite_detail_aos<RandomAccessContainer>>(std::move(data), x0, dx))
    {}

    inline Real operator()(Real x) const
    {
        return impl_->operator()(x);
    }

    inline Real prime(Real x) const
    {
        return impl_->prime(x);
    }

    friend std::ostream& operator<<(std::ostream & os, const cardinal_cubic_hermite_aos & m)
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
    std::shared_ptr<detail::cardinal_cubic_hermite_detail_aos<RandomAccessContainer>> impl_;
};


}
#endif
/* cubic_hermite.hpp
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
*/