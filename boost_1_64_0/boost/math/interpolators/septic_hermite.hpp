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
/JJpp+57OCpJudTRsMwZi9/Y38WVoPm8RMzXWCOKykkx7X6QuL/G/Ht70+4XiF1rc8/tsIToObgHSnmvZnitUeLx3FVDOyny+0ndY5a617YJXX2du22eotNwz+iDNqD7NCU3UiZzJ2Zk+bdN7edMmeWJ/zukvEmThr/KtAG1M23gR0/7TIJ7xL2jX3vUsP53qMZD5/XCsPWxiaShoti1d9+Jaup8mcTXx6xT7xZzFVf84e/N6D2w54j7RDVH/HcrKh9J39Ma8tzmlt9epjpwjoRdVeZ+J1K/P5r6dcmg/xet++6XKHJuVnaaOfLsmm3u7DRp6uSkOVf9e9Z9/WXW/3fXg3fI+qGOH+BRup5ZWdYrUSoDHsj6WBx8Hu4HX4AHwpdgP/gKHAA3woHwaThMzbq+rN/KlJvP+vJy/DlwBawJ74fpcKU+50HYC66CfeAD8lzMGn965JsSVtD4HXRK5B3UfMQb2fT6XQR/VP9J6DXq/yJNz3xYD14Nu8MFsDe8S9OxEPbXdcyRcDEcC6+Dp8Kl8HR4PVwEb4BoCX8jXKbrpjfBdfBmuAHeAp+Ft8HN8Hb4GbwDfgvvhD9IPCob3tbfYv0euRU2RjexLVGDdH39KFgfHg0bwWNgEzgCtoYjtbwzYTc4RvOXpfU7Fg6B2Vq/k+AIOBlmwalwEpwG58AceCY8EZ4Lz9T8nwVvh2fDFbqO/BCcB1fDPPgknAFfhzPhFjhLZavnww/gyVoep8BfdJ06RmWHx8I5sIrKNo+Hp8MkOE/LrZOtv0H6W3mrytNvqeVWW9vNPjAW1oVVYH9YHabAmjAV1oINtL2kwVTYEKbBxnBf2Ai2gc1gB9gcdoItYGe4L+wB99N21lLLvRUcDFvDY2EbeBxsq+2tHZwAM+A02B7mwg5wNtwfngMP0no4WPdPdIUL4aFwCewBr4eHwZtgL13f7wMfh33hOs3/2DKsHwdy2MtXbtQfXUv+J8phz2HteD56DboAHbunqtVyT7CeHKhABSpQgQpUoAIVqED9FerPlv+fnRvWo2ZNz8wpl/v/VzW1zLlMhiCiGmleGqIvYaB9qa79HzZk1Iyp4SePmpR9klV4PnBJm7CbmP3vAfCu8cv6lO/5QPx6ZbFNm5Fn+ayF+sfLNIqP3DaP3xlWoV9moX3ltqlfs8a6MWXva6yRc07hsqitZVFk/V7znFBEBj95U7u4iD/Ng5GrZmGnaXWfvf855F9Pa6P1FKmlUtXR2jLU0doy1NHaMtTR2jLU0VpPHd1S959TRzsxpzvFzd+XfX59lKwP1Bi3+bETfjzlhuvvbjXsuGd3HFDcfH/Z58X91xOKW8co+/x9Wdcf/NcNym89x389ofh1Hv91m/JdT2gb6Xf0ne6Ddt9RmuyaT20I68FIuLUlhIvXcAkarha81S7d/KPfmZVF6FVonVP0zifqPKLfeZSS5w7XoLeifeYL9dxJ8XOEeegLDyn9nOCln8Z45gUJkxpr5gaZEzRzgN3QrjMknvk+vzk+v/m90s/rReb0BjF/lxPM4QUqUIEKVKAC9a9Rf9H4f9q4MeHh/x/f+/9wU8vsf1um4/9mmpem6I1d2IMSHVfy3HYZnUZlT5X04O4Z2/nvFfcdM/qPL9WvykjRvZbj8yZYfmNMT9yXm3GuzxjTLx2M+bKzfOS3e/zmid+pM6ZovMkuv8nq1z0eTa5T+vGod0wZ6xl76p5/HWeasjBj0ss949nESHjNG3aS3jyxkzyYcWpyOLyMLxtefe/ZzR545+lPxh+YtOGKUH0dl5i8aZvwjC/c+4OaQhUnI9/YfFPLN++FwXdsoAIVqEAFKlCBClSgAhWo/6j6i8b/UybmZpU=
*/