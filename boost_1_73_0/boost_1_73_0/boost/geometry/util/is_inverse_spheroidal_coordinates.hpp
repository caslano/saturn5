// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

template<class CT>
struct bounds
{
  static CT lowest  () { return boost::numeric::bounds<CT>::lowest(); }
  static CT highest () { return boost::numeric::bounds<CT>::highest(); }
};

template <typename Box>
bool is_inverse_spheroidal_coordinates(Box const& box)
{
    typedef typename point_type<Box>::type point_type;
    typedef typename coordinate_type<point_type>::type bound_type;

    bound_type high = bounds<bound_type>::highest();
    bound_type low = bounds<bound_type>::lowest();

    return (geometry::get<0, 0>(box) == high) &&
           (geometry::get<0, 1>(box) == high) &&
           (geometry::get<1, 0>(box) == low) &&
           (geometry::get<1, 1>(box) == low);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

/* is_inverse_spheroidal_coordinates.hpp
U6zFnY616QYwlzArjG0iVW2JJE0/DzVIVVohm93pLYHPzNadWFJqEwb7fgv6kELWaYNyDAtD6wRao0SQNBUhv25plQpKNJbRAdf2gZmg5kp1wZMolrgUbFqQGotLnNmcU+9k4JJXWxPckjkWK7yObOUqq1hcyMZ2FTCqUBB0f9c2Lab0CLc4b/dzZFui/X0dU2ESrLHqBgOJtG+NQsYIQWq7HU3JEBMnYhHyLveNNbU4hAwTZ+NEAKnJYcfCYrvZDeqh2oOZcPAOoOcVF8byvdrV2ZSxdmvwmtKTNJDNepF4bDuWlu+fpdL25DbyWyoX4CJvev0+XW2CLR7wkqKsy7B+K6N7TFPsfWkJTS5EPhMQVuM5mWMYf9Gq5JbURYnJdlLeXA+43ITafbq6T7TbDJPS6e5t29wOOlP2cMVJiEUMwskd6jpUHNqpYy191kxj4hnicjZHBKXmAGkAqjal3HEvj2mUiJ+M7B7OVv+JraFrSssWlPQiojibUimAi3h67chXUWYaC5kuznoTuKl46IIn8A8abS5UgUZuWmX96mIzwaqS0E4Hd/94uVwGp5AQ8mGLDd2NVO9ySzubpflot6HAtGg5bBGvIYM0mD7yUJKMTOfr1v8FUEsDBAoAAAAIAC1nSlIZifH+mQQA
*/