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
XIYWrC8qVqIBY17XU8+4fOty+Ck/xCKsbT6PDq4yRmUfMg2xNq1vvDXBX74kCZSCRM5OGtTYVA8/ET3fAMIOQGZlNy00to+wmnClcO7mzTeE1D0KGh9BtbQkGtd2D7N+CmHy4vqgpZ2j3h/xPhaqJpUBly05JGNNzmOUln3u3lyZV2lFYweJuwPqo6A7C/EP6cXLG4OQDrFObOWLgoPPxpF7x4UcTl/OSazULEcmrmtG21zbgZ9WGgpelPT82vbCm4jydvlN3Jes/FDrJklGuZEaT8JZSnMjXpXMrPWvA2AXJVrSEOA/gvS9yxybfhFQwfFFyHIaWxRuKbdjabyKO2yu/mMNNUxBLnoNJ4qYaRGIfK4QloP40OUGjDdzwOGzuZZ9m2z64QppfctiRiEAMZX9pvFXf1UWNv/dyzENi+bj3DCcIzymzcdbQkj9OI+/YNt8laCMiLtmw75cqoO9bUg48cG7o3xwb/St0ICWm98tgWafpLz9luyoJiipM4s/DBNhX24F0gzTs83hCgsHronQPPzZNIcUvEgNLT4BfPkn5ocHlY7jBUsb0w==
*/