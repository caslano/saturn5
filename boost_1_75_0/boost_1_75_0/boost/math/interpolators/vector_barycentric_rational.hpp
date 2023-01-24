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
KhFzdYxKjpe4ADEytJOhbyhmCTxuTBaZ3BYj4lDhm9e07OPr2qAymUMr8C2U5/ordnxD8eZyGO6li0dGjsdF+/6Kgtu9eCoM7G4T6yfgEZs9XHGT3YtXU+aiWOCaZ2MtfukphuMClcFbE1HmsVAZXOQysvZUT4UcL+2J4tD+jVdh3P/+nVR7jIFuAtLsX4eWIM9G6OAk4TusPBZxvwXpzsZD74t9X7/Wxvfi0IdI4ddM9aYrjcvNaUYowfvL3k6rshRX0Hqy2F6zwIeHPtHLrDOoT1wS6pPaQwIi7Yk5sNd4Htf7nPFUPudRroO2TsFcCornvn5t3fpQLuLq9CYHPvfl4nUrm4q2Ha6GD0ZxmaXcZOR80ayEvL3xFgmItPj++AAyZjn8h6WNSgUV/ZDHwNcgIAG5PSKDLgZQRnBGFjcVc6HHIfgGcWUeZma3Cno48OZpGK+SEfD3Kcm1Fwv3J2brAr6M9sdgRdw8hk/1YjV2WuEKJ0/jpPNtpGLULR3SpJqKqFBl3mASPXx7PFYx8v6O5VntpTaLLAfvh6TZmOcP7m9feeDKIjHvLr4lw7GNG2KuabE2KX9z8bnBDx4BD8Y5lsKwD/qdh+0P6XR1cdx5yCZFUgzDcedRBse3zAcotoxicDgpyfKhHuo54JlF0zPd5ZkWF/dlRqCIfuThnuL+usDw9IqZWMdUzbkaLzeYAVcOBvzmr5gQwAjT
*/