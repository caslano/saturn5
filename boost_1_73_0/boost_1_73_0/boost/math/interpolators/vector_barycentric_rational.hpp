/*
 *  Copyright Nick Thompson, 2019
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Exactly the same as barycentric_rational.hpp, but delivers values in $\mathbb{R}^n$.
 *  In some sense this is trivial, since each component of the vector is computed in exactly the same
 *  as would be computed by barycentric_rational.hpp. But this is a bit more efficient and convenient.
 */

#ifndef BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_HPP
#define BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_HPP

#include <memory>
#include <boost/math/interpolators/detail/vector_barycentric_rational_detail.hpp>

namespace boost{ namespace math{

template<class TimeContainer, class SpaceContainer>
class vector_barycentric_rational
{
public:
    using Real = typename TimeContainer::value_type;
    using Point = typename SpaceContainer::value_type;
    vector_barycentric_rational(TimeContainer&& times, SpaceContainer&& points, size_t approximation_order = 3);

    void operator()(Point& x, Real t) const;

    // I have validated using google benchmark that returning a value is no more expensive populating it,
    // at least for Eigen vectors with known size at compile-time.
    // This is kinda a weird thing to discover since it goes against the advice of basically every high-performance computing book.
    Point operator()(Real t) const {
        Point p;
        this->operator()(p, t);
        return p;
    }

    void prime(Point& dxdt, Real t) const {
        Point x;
        m_imp->eval_with_prime(x, dxdt, t);
    }

    Point prime(Real t) const {
        Point p;
        this->prime(p, t);
        return p;
    }

    void eval_with_prime(Point& x, Point& dxdt, Real t) const {
        m_imp->eval_with_prime(x, dxdt, t);
        return;
    }

    std::pair<Point, Point> eval_with_prime(Real t) const {
        Point x;
        Point dxdt;
        m_imp->eval_with_prime(x, dxdt, t);
        return {x, dxdt};
    }

private:
    std::shared_ptr<detail::vector_barycentric_rational_imp<TimeContainer, SpaceContainer>> m_imp;
};


template <class TimeContainer, class SpaceContainer>
vector_barycentric_rational<TimeContainer, SpaceContainer>::vector_barycentric_rational(TimeContainer&& times, SpaceContainer&& points, size_t approximation_order):
 m_imp(std::make_shared<detail::vector_barycentric_rational_imp<TimeContainer, SpaceContainer>>(std::move(times), std::move(points), approximation_order))
{
    return;
}

template <class TimeContainer, class SpaceContainer>
void vector_barycentric_rational<TimeContainer, SpaceContainer>::operator()(typename SpaceContainer::value_type& p, typename TimeContainer::value_type t) const
{
    m_imp->operator()(p, t);
    return;
}

}}
#endif

/* vector_barycentric_rational.hpp
h7sVdd1ny1l6ai2GohRTkhKp8nmtofSUiWgh5Y+T+DZKFZeX9vc58ZylUCjGqmI2nj95xEOH4qVAmIbm5Zw0jiy2i8dMyG7J/lXnovgq2af8lNzu6UchLx54Ii3T53g/acKnuqQsruHXh2DCauJxP5LO8nw6VMrmokU3sbk/nkGeacWuKOXwmQY6dVGXM2J/XNJj42ZPrltnOH0tfP/lXI/F8WyWwqZOeOrkz8JSuTDceROumOXWZ5yvZGPY+udUo/1kKURgitO92vs6ws82uuPODQ3Ywd+olvn7j4l1dM+8fGA/Cj+6owHNsyLL0YwkSQLHYdkw9gUhpESK496s+t6MDZQ8wU1UWqBv7coOXgAhtHD37oo5/8cis6oeYOPHO35+37f0/cbbD7/vPf4PbcR7279rKb58aI4Gm/ujqgfKJYCe8WdUvTwLoYN8p9Yu64EaxeU9QhDd64CWB5SIaA5x0oChaGkwnm8+LFDiGnpPNNCjYDAQ3i5ghHcL1l872v8fUXzXZP3iwWD58HOwAd33wLzE5XuP3ky+ybB75X2SV9+f/lz06/4B69DgbwwFEYTe/O8fROdl+MgfFfowgR+KQj6PPArxAhJ4FMeI9hAdItlDXIhiGtEi8iO8QYH4uQaWQXGEeBor8VjE
*/