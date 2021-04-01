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
8tQUpBpvqwM2fblGLZtBn84EPUGh+Nv2PZQuJvTAlUsgV/JmTBoWU7r4b+IgzJsGI9FBZfRUrFtJWleepRf93/Qe+4SZbqDYN7Z0B4AoAzM6vojjnygOOtt6ztH+ZNZLCRZYVdVNicyXNJndjCV4WWyE1ZfxCSN3VCuIzodqCW2TWg6H0K+gkj5ngIJg28teU11p9PsTZP4dGGHtIDIUAOskKFgiy+aHW3Omqvjl0dMmRGkvrY+PiKeeIeFTfJq6BKPrsnC9T/NP7s1SdMAkz+cgZ9BoteqUZtxArK36szGo4WaSQxw5RiEkGN840ojm3OndFY6lZ1FBVFFigSuMtfYk4btbVOO7H0PKvBqYvJs7KahqHdLLnmgERCqrMU07Sg3AGWvVRmyA+1JC/x206z3V09LlehkO59MtZmxNm5aq94GRtkucU9GHa8pjdRORFru5WZfzb2tEdVAbSCKn4UCc++lJoLgOe3MH2i19cOo1/doKY1IpEOehq5DjyJdmjVLykk1yzeh/4e4oFfjbY2s76RJ+X+G5XwwvaGFZuqc3lHZP+/uY+71+sQ==
*/