// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

#include <boost/type_traits/is_floating_point.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace geometry
{
    
#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct is_not_finite
{
    template <typename T>
    static inline bool apply(T const& t)
    {
        return ! boost::math::isfinite(t);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point>
bool has_non_finite_coordinate(Point const& point)
{
    return detail::has_coordinate_with_property
        <
            Point,
            detail::is_not_finite,
            boost::is_floating_point
                <
                    typename coordinate_type<Point>::type
                >::value
        >::apply(point);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_HAS_NON_FINITE_COORDINATE_HPP

/* has_non_finite_coordinate.hpp
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
*/