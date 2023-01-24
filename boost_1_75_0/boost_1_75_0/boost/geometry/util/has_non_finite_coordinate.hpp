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
w2SdpqukDCMKyaNUFrjEQp0YC7YFQRwcgDRLEuqvo8wQn9QkkJrLvmIR59ZjB1jkPBKUKKzoRZv9enAcYsaIrKho1N5D05B8pFCSGEc2m+xmNGhB6pnvMpb6W34ElpTtUNS5pbjm19sVJ+MS9qgBeYA7ilRB+SrlLzOzUlYfB7GE9+RAeOOGB0s4K69cTGKERRsVDUW548PR/4Vveyr1iDdXujl1PHBu/ze+bXStzq3VBQP/PPQ472+pesoYgGMYOgKjfbXMsC+pYWK73DTa3Dy4Eb5aEvLFNPObTI9QBgVQHjhpjqAFkM1KVZK4pi6cXCshxyS7RLJHzmimap7ckXFFXoG52lx3BXnTqgI5JmCjYo1kJnMqohWColIpn9idG5CJDimcFs4Letr3Zu5bZH1odEHfsKcoDXYDU2eZclybAfe4jkNzRT/fgz9FzzCLWqj5suMV10Pfi0nhgt/BRYF4RlBROJ0YS+HtMGRRbnCXJtXRPaJqxh5sCXGGSpNJGifjc8sOGBdL5EukOp67m1XAIqLkjRNrDylQgW+eNv/QPV9ob9Ai9M8fNjGGEXU0XZtXzSm7lhIHD/sgqu5noWHO7gfEAGJqkcQSaJeYeIwpyg3J+hPu+0zPyQ6/wtyR8e1Q0C9fL7OdW7DKbLRdYXSMaQobhH4gg7Ln96aeflmv+b14p1HILz9pyvdTqVLV2TrWylCPSHROcoXs
*/