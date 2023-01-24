// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct isinf
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return boost::math::isinf(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_infinite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::isinf,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_INFINITE_COORDINATE_HPP

/* has_infinite_coordinate.hpp
FEDc3ZDDRsWuORcJkWUC2e5fP+3DT47C78YNr6qKxkpB1NqN6fGG8jn6sTeUP2VomNXroAW4qsYRnyISYmcBLh8xY0XcWr+xEZ0MuI20B6WEJZtWyvX94bD8vLxmP+GvKq/DphWmLxWurCOUdVeQQ7ytpkdfdmkwOZw4GRZl+DElkvwrbUq45g6q+mX7HD0OBmceBnEqZNLZsJjzsIfGYptV9wHw1rVApWbShsT9TZ2Ezc0RLkoKSlM41bX/8zjb8y0bHqn0jsg30hcTYqWLOu0PSSPwwdYTf7/pPmvdh2m2jpxggTo1DgUpkOB7i4vfj6KKZ06zps1LtaWTGmHxp9y1mHnhyyLs9SLSLy8kGLyXXwNrlQs0G1AopENbFE9DXu4iRaQj404wRzbh6Vc/oRy12qeJS+xtA9RR4xKfr80noqZRD4q/2eBRBHP8HDwzZTqwRWoZxNFZsBC176//fJrRZlE9YDOhTeRkJmGSqpysjGpmWL5uhejxxeTjWDXfFJjn5ntFmt2Gq0riVd0wvaI/U762gaP/UZYMP2kA41GfrlJrpIPxJBgsDq5fkKcoJ7HtY7AjKh9krJW2GazXrRo4i3lXHFfwmruSE+mRyeSlVIhH4Ea0inBVOt+5gaXaeLtVIc8vNo/JWXWjFbKv8TE+58IOAkYrHvYauFLXLmbySjwQf9xUUR3ebA1Phl0/7t0KxERp+R2bMpyt
*/