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
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
*/