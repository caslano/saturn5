// Copyright Nick Thompson, 2020
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CUBIC_HERMITE_HPP
#define BOOST_MATH_INTERPOLATORS_CUBIC_HERMITE_HPP
#include <memory>
#include <boost/math/interpolators/detail/cubic_hermite_detail.hpp>

namespace boost {
namespace math {
namespace interpolators {

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
}
}
#endif

/* cubic_hermite.hpp
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
*/