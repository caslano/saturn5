// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP


#include <cstddef>
#include <map>

#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Segment>
struct segment_as_subrange
{
    segment_as_subrange(Segment const& s)
        : m_segment(s)
    {
        geometry::set<0>(m_p1, geometry::get<0, 0>(m_segment));
        geometry::set<1>(m_p1, geometry::get<0, 1>(m_segment));
        geometry::set<0>(m_p2, geometry::get<1, 0>(m_segment));
        geometry::set<1>(m_p2, geometry::get<1, 1>(m_segment));
    }

    typedef typename geometry::point_type<Segment>::type point_type;

    point_type const& at(std::size_t index) const
    {
        return index == 0 ? m_p1 : m_p2;
    }

    static inline bool is_last_segment()
    {
        return true;
    }

    point_type m_p1, m_p2;

    Segment const& m_segment;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP

/* segment_as_subrange.hpp
DCIANkE8GpWQxkqIdGayWApfQV0COGqTSY6OI3cL53S1btyl+isqupzWYXi6gXjoqLqo2MgBvhBsTXTBSMtUwrk1LT3+FYp239KTIKWljKjrIlTOMJdo4FxUKPa5xRZX05uUk3Y2vdH0ZtNb0n44Do1j8xkmSy6y3P6L89nugd2F5VtuvYqTAolM92ZuvLdjpTwFrvnL3MLzhVvg9HKKxS1m2Aq5nS4s3+gfWMjrJt3lq/0nIT1db/q7FpbvoGunPx2rvWIxrPLgqBm/iDHwJzQf25C2saRtS+Q5RzcU4fqqLYZt9A97g36Up8GcTGn8V/HYp3AqnSvkVMpZ8lmpSNRoPxU15hbvxnjlYLwr5eXd8z326xrJ8nO6MSU+Ltnwt2YiJY9e59uvbaQ+zQZX9F5C0knM7/Fg/QZt8EBJnqY1jh3hCMwRZXJKLh/bI3AR3MulOzMwoXxxVqDQXX5NdmC0V9wpT1A98kZwa/7EAf4hqNu04M2nGyC+H4U062zNUzu+WQkmpvNVO36f/ArWZkdXuwo+tt91nZQ7vDauJ61KFC8slKt+2GBk+nFy1OKSU6P9h0/SJzwue6Uyyj4pSsnVsCtasM7+wxz4BZst9tv70jEqfJHVgPPhbviwn4ruNt9+/ah1e8wGlNaw9Jb0aF2w7otoFXwH3gNfX3jcFLdY6x5SV2mVNXadtgz/tofHmObbF+4wFIWXMnuf2m+tDa6yzLcf2QrnK0i9fr79YB2+axB7K6Mibd7AzfPtn75BB4Jef5Op5rvsby6j9CriIt7i7TYCoO+UCkTegHgb+VVBy0kI32bjl2dpEoqtLSCvJ2SZ/nEJTjrrkkF5Hk7AqXIVbLbfdRpg23MoyDN3u2/u5qKC7bcUYpVE4R2e6l3W6CqfGeZS1hUNWU/53/CYI+BSFdG85dxV0VWMgUslrB7zGo95IyZWiDV5NG+wwRh4A9fKMi6DGVb9rhWivMMz4Q0xgnoPOpI8NoS/x/ymJ25sZRhDqqTTYc/xS3nuKYo1/d9iVKcFfy3zcZs/TV5GUfO4CS6TdCk7/GVVN6VV2qRH9goL3pVRtlZhdU07zvOnu3S7oWfeqc8ZP6+T6u8HvGKf4lNAf4F2a+Vt3DSpXAzqzBcixYQhV8HIoGDmY/K0fiK3GY9cgG1Gh/5yj3kf3EWhQYpVQDsnJJWkudds7dfZkgfXHdEWIxr1nOED2beIGUmocMkLbu3lFuANjzc2HIndHPypUb9H+iM4xLQs4Ny+ljP4K7r+vS98Vv41R6Jg+3ZLZvtqvtDgSH/yUa10nRBstgbStZuQU2gsLveKsjX7tDT0qHQxjXZZB63TYZJ/bE8A6rxob8RKKEN8oUHUfDIXhgazPy7VT9vN7lB28OZsJxLDhnStTzRHzkJnBoI3lzUQQRpTdXKJsp8tXZVmcNEm3F0qNYXm6b8P8bgttEuupYnHaPmDAnbtkb5SfainPbgH0QmmQ2H+YGW7wJ3/KzkDK4EYUYS9XczAAz15eqb4uva7eHqmLQAs2gh4EB/Bm7Msgd7ItDHQFUWvwWGzNv8UpUr7fQQ6ZaBJBj7HQK8eeFnpzVnMeevwU/XwUfHEDhm4goGd9cDsWOKTZXjvWPjH/RDOlQVtgTomQ0Laz/IJ9D6fNNhIOp6ragnNubpm/2cTP7lVpFi6uvONiX5WsGrR3i+zKOzjuo/zu7iSY+VWKQAd1C/kMUq7+bVlA/bF78bYj9E+r4z6r+CIkwpQtu5eHFAnN0G/wmTK91NyuvX+hYlgrrmzL6RWVR9iPs6Qlw/13R+NjjYYRg61l/9QYVkWMxgZXYOvu/Qv10v87w5xjqCp/sLcLYW5O9zIcEk=
*/