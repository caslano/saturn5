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
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
*/