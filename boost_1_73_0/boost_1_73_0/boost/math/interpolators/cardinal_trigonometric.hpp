//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_TRIGONOMETRIC_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_TRIGONOMETRIC_HPP
#include <memory>
#include <boost/math/interpolators/detail/cardinal_trigonometric_detail.hpp>

namespace boost { namespace math { namespace interpolators {

template<class RandomAccessContainer>
class cardinal_trigonometric
{
public:
    using Real = typename RandomAccessContainer::value_type;
    cardinal_trigonometric(RandomAccessContainer const & v, Real t0, Real h)
    {
        m_impl = std::make_shared<interpolators::detail::cardinal_trigonometric_detail<Real>>(v.data(), v.size(), t0, h);
    }

    Real operator()(Real t) const
    {
        return m_impl->operator()(t);
    }

    Real prime(Real t) const
    {
        return m_impl->prime(t);
    }

    Real double_prime(Real t) const
    {
        return m_impl->double_prime(t);
    }

    Real period() const
    {
        return m_impl->period();
    }

    Real integrate() const
    {
        return m_impl->integrate();
    }

    Real squared_l2() const
    {
        return m_impl->squared_l2();
    }

private:
    std::shared_ptr<interpolators::detail::cardinal_trigonometric_detail<Real>> m_impl;
};

}}}
#endif

/* cardinal_trigonometric.hpp
FmYeWb/8opKM1KI8Bb/8ciCdqhBSVFpcouCYl5yRX2QgJ85raGFgaWhpYG5oYmIRJc5rZGZoZGAG5RqEU+wSUQNhiEt4cvKTE3My8otL9PLyDJoYlZB9zcjKwNzEyM8AFOdiamJkZNi6ICz1v5TsLN+P4vtEjhv9C1ywWEktMucqT8nKHDWZZZPSZKfxRZ6uZWXcYCh85/azxo+Vzg0c5iV6gU3b2mv+tuv+vXDZyejkiotnHpjXP7JLnXTJ92/l2/fKVw31f7+PZ87wzKpZ9bJAOdt56t64iz/Ell99sLc+2WWJjq+JmJGg0Ln7YktusC09fcXnvOaa9INNage5/7us/7yp03CRwN+lRj9Y/LKNZFXimjttPeeYqEQJ39Xh1onZHL/vT+7tfYePOOS+CNz/8J/1Bw0nla8ZR/QYfimafLg4xT41QLJ333l2LQ7/jILybyIVrvoFt9zVAotld2+a/FC5PHeBu5/J8fV/VwY7vnpezMTMyMC4uHGeQeNsAx1gAMoKsqgaKDdxwgOxiQvONERiGxlwg1Tzs7AwMzGvAIe9rCoLjwEXG4c2GyMrKzszo4EsSJCPRYxFpODXTvXq6RUeDX+uXzecIPT2qf8EUwN5kLQyi4SBWIOI0Kld3m4sy0u7dF7whUzZ
*/