// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#define BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#include <memory>
#include <boost/math/interpolators/detail/whittaker_shannon_detail.hpp>

namespace boost { namespace math { namespace interpolators {

template<class RandomAccessContainer>
class whittaker_shannon {
public:

    using Real = typename RandomAccessContainer::value_type;
    whittaker_shannon(RandomAccessContainer&& y, Real const & t0, Real const & h)
     : m_impl(std::make_shared<detail::whittaker_shannon_detail<RandomAccessContainer>>(std::move(y), t0, h))
    {}

    inline Real operator()(Real t) const
    {
        return m_impl->operator()(t);
    }

    inline Real prime(Real t) const
    {
        return m_impl->prime(t);
    }

    inline Real operator[](size_t i) const
    {
        return m_impl->operator[](i);
    }

    RandomAccessContainer&& return_data()
    {
        return m_impl->return_data();
    }


private:
    std::shared_ptr<detail::whittaker_shannon_detail<RandomAccessContainer>> m_impl;
};
}}}
#endif

/* whittaker_shannon.hpp
MIgREC8jIUAhj6gAiRzy+lf4/qkGOkCegGQGCUJvWkBUhDUEPhJDRIESGvkUYgEM+7mGEGz5KBKQRGPMoow4FkkUoiTEihgA0yOUGOT/BoMEYgGKQwQDJsSDkEIhizgGgYOBjDwJhTQKAhRRv4kDaIhRBPIRjiS4EzJ9DEOMJwpRFCOGxTEBRz7VwMQo9rEYHyOKRYKEOIibh4F5HopkJFJYg+Bj7z7VIPPIDxEfYaixhGgBeSK2CJjhO8ATwCPYDghI8LkGAMxyeCF4TUPAwXfQFveqOBRKiIIBj7cm5H6jIUABeAoRC5AgoqAPO2w9DCgfJxgGAJ6yyGd+sxcyDpEHACgcPTCHcwxMQ5WIsPsYW4gYDnv6uQbYfVAS4gDKAfYIC3s4f8IQ+w5I4DcfIP83kYQtgLSPwYUQpxaMAxYFAIDCXyIJp5MP203j5P88H8BZ2C8JpxBYj3m8oUGfinDoYg8xNAYGMuFv8kHmEBvjXOIpRMtICnsYkBuQoh7ObS7GOiErxN+czVjAJ1cESR5BdoFkCOda7E8oHBMWh9H38UbIv4kDOAgpB/rBazjgsBa2gO2rAd7EEB9tHpKKRpH3Gw1wLtgPM0Z7LS/RpUYDgQcaxuRLUxRF/yxf+693LdGPi5j36r9Nfy+w
*/