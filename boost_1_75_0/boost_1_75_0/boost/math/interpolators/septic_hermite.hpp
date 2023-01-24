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
zSY5UcCbmVywDBVnnKw/EAcngfL6UOVebXs5KMSYG2lqr0KffvcIXfUK2jt2svZPgW6x4T0/bp+MhiEB+d/NKvWTn8XimcF0q1pm6+X1wzmYkQWMBG3ldKYPYPk3uKgY5zKQ4RuYbmfq3h6HesWHoC9enO/UwDCOC0i8/xOwrpGPHCVMYAs7/iyk/ei2Ep4fR7JGxP3Bhd8Ipfs20NeaPB5ad+ZkDtxuBWTqE7eg3tL9qMMRgNUOqLBxT0Ump6eDT80b2J6GJkTeaCb/B18j8jJBzfbY05B2zYN0r8RgiDF0nupLQ5Q9VzBvGH4cmuuyqdzQT0xUviPNzpmYX89/RNdO2Ympym6m+ydmA5kJHr2xyb0BNeVtPjUZtJ55ktWLpkMcgt3jsHbO/oHTgtbV5tjaiDQ6Bcoae3N2JfdZASxhFnjguyZ/Z9GIe9Q8E3rdv+v9livT65A2fgb0+W+Tua6a6TDTDazE+8xeNQ19rOwtymH0T05C+7U46+xQBeCTx6Ot87dTPKs2YFEzMebDJmGwrZ4y1jGIvdCUAB+Ekff7rauoJ9IlJmJOvVmTbfedsLM1OJ7Zuz6XNB6kPT8Le6h5C9u3B7hLM9iej5YjP+U3GhH/6fgM+AolK2V18coH4KOxxhAPadNuMb6tY9C+r41yBPIcYeeH8RkL2+UB7uIktld6jNkcZVjEnML3tQcoR37MvbKsbfxqEIMi
*/