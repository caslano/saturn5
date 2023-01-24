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
Dk6FCbLECt2YrcLANQ3FnDk1hepY6yh8sWU9X6CByx+CfA9tM1jLLXQwy53Q+kUf1rIy75irc3ETHuaQiUoo4M6Gge9eeUTncHvkSPjSwF9kuPK5U7RtXjTjQcpMZivvP6Rr6YN+OoR0ziJLscRSFcXFnDeQ5sQQ6OOZm0Uala3StB441KEa/jbkthM5Ffb21WB8BR/XcLL28fb8AVxtOPok0a2jcoICvZs/8F7cYOiaZbdqrfY18PuIHwb9XPdTW3u70Qgc/FO7k19cVCdk7/BhCiHvPsl1LZ6mMBzrpfF1DuMTEfucExGQ8Q3mtuX69qHVYZJe9f0BWr537wY44qf1IwuXUBlGx9MhmdGN8NvGt6EGKE/dy8t1sp2rHI9veQWT118GDuWfZzrpj087ndC4jUb4eBcOw/73jgtcAhZVlNIqGVBQmt1Dt1xGyQ88nMz6gS4KBZlUvFvtFq9t7Dz8YYnjAF+7fUj4iUeyPeSJG2nZGVaLC+vlegYPh05/9TS9bD/aMAT9a3nNqdex90hmn9O+66QA5Anrh/lgaGG7Y2FAQbr9/QFfqXWW0N2LgNd76zwX/baQbpu9xm7AE+HMQKYpKe1ySTc/Hg5YyEYnTSjBmti+/+sGJzbeRl5u0nDwWuKdej/l7h2M9MdPu2TpW4ZCNpe/RuvRJi3+gsmbF2H/Y9/V7s90+kf0ftJ1J1+co8lYeUODINYq
*/