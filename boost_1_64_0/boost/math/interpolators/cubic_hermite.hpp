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
D66FJ8J1cDC8GA7R7/T94U1wANwKh+n3+uFwl/qr61Hab5JulvWoJtgL7znR/SiwG2yh+4Dawl6wFRwGW8OJsI2uR2TAmWrvMNwY6R/gDv29xqh1KEe/4zeCZ8DecCYcBGfpOsds9bdM02UeXAgLYDksgpVwIbwCFsINsBheBRdpeiyG22GZSQdty+BcSzqM1nQYr+kwQeM/EWbDk2EfOBnm6DoFypmq4cyDc9TeuHqsR0TvHvviaw774gNfet3hv23N4ckPWUNAHUE1PxL9/v9NPF+P/P8F7KdfEpr+f+m5/z1ZjpG1OFDluY/30WbDPnAEjfP+16vGlWNHT0HI4qTxM0ePmjZ+8uj8guJFrjNZFbaxJe69MnkqXeNJY27GmunmHAfnIELSVIoL1vBqzsuc9IacybHuu1e/xI9Utx8VJUVuWXIjxY9k6z30+GHGrf9h70zgbKrCAH7vfYOxz4wxJsYY+yjrUFRICCFkaUExxliyTWYwaaFV+6qSkEr7pqgUlRbRXlS0T7tKJUla9X/ffO+8O7c7Y+bXtN9Tx3/Oes92z7tn+04L+bIcm5mXaYnfLe7xu+vO/+MkvlsZJSa6zi/mTcnJjd61/6PEG1d4zlG/cytKuDq2g11lfN6EDofPaCzhc93nMjuI363WTOq4mTVcyupIHMZThxPQkfmCDOwWwfn6bZzuNz7xPSNSIf7a98yZQc/ZtlyPHJ088uA6M+KpK9y0XHHz1AHf3lKOlC1uUrZF5Ot/pO2wJlrqDL0u/JFRUHw7zJqQnTXJct9HMdavLRJH0TN+08sgd5d4w+ktktZXdSx+P5HVgffCI/ljaQlpzZmuZ77NOHtMjv+4TOORutF80abc7fhucW8iZ35jI/5JzSx2e7nfMY3HNSYea+Lo9b6caTNzYwPF/JnL7wTj9zj1GzmnPU7MGy0/eeUb5ZmpakaazwfS/l1+c43fm13xbiPeJyXs5XYN43fcKE61mPdttbjPt2fYsVb0fRxn3pUHxH2hfbLtnqOLnr+pEXmellsdMXe1o3HNNPIaVuqzku3J5kzeR+K/myvuI8wcQlNx20Psm8xZxdZi19yO+p9i0pLnSst2/J4q5tWuuCebcfFDkpYr7Zl2ZSsi7/N+mZMobMeJezkTTB145LfoPIS2wQS3XDfamlce70qde9hHI05GzwrLcfug+PbOq7/X3wjCe38j/OeZ8Od+f49NLOsZ3d/1Y5K/XhF5wyrb/jQtv9noTvTF20vOn5E85MqnqbMDPwybG8kvll/eidu84/HSHxCbSx7GHnGfZA3Cdxba9wykq/xS47EjX24Zo46kIV7CbtdzjqsqUZ4EbsnmvmoxzavZsdWcULXYiq6+0Vf+VlwpZGloWZv2RL4wk69CP5IG0inl7+5Pd4cj1PM/VZV5tK9LP3TLip2aPT1z8sTZ2WP5qMkOS3+Shqq/m9pHRs8Ur5Owe+yadkWrKf3FW2ifetBn2O7fEFOH14lbAr/RjvYZEf/pJg618/Sz04zclpXiFuek8vyO9Euf21Xcc5ymP2j8kfYH+r1z4MeYGR0mqfyVz8V9Nd98jRjD53n7Xglzi/hJtZK0D1svz/7FLrAmsw86VeVNIoVG/BXQNjmBiW4jXyCEMW4fMl49o0hflKp97N0SZ5LTlLx0Jk8D7MXWN9Iv4W7SGS2vVeK/mhPtYzPNd9C94lbLac6X0CHob+2YqMwF/X5wnzH/WeI+Gz/uZ93D027zhJs4Xs5CarnsFH8NKN3qahcJ21HKM0H760K7R6nTZNPXTCjVuetqgDkCqTOeS587R+KymvQf0D7DUrvZUbt2EbsZUbu2EbscY5dxYMTuhKhdp4g=
*/