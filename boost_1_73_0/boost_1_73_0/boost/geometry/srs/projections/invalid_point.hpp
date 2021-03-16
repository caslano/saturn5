// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP
#define BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP


#include <cmath>

#include <boost/geometry/core/access.hpp>


namespace boost { namespace geometry { namespace projections
{

// Originally in pj_transform()
template <typename Point>
inline void set_invalid_point(Point & point)
{
    geometry::set<0>(point, HUGE_VAL);
    geometry::set<1>(point, HUGE_VAL);
}

template <typename Point>
inline bool is_invalid_point(Point const& point)
{
    return geometry::get<0>(point) == HUGE_VAL;
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_INVALID_POINT_HPP

/* invalid_point.hpp
NdonszwWV91ORFQtsHnSf3GtpRtW6PeOgQQqu0AbX9qi5EJXnZvYiRbX2h4xYnp/9VhqTQKJnrSFY111JXZS6uSqu4SfdA509IRn/uQTZewLh6hgjneDRGCeezs1GfA6JLwO81rwVvYgpyetwOlxZRY4s+v2+Ye6zs+IrDep0+PdqtOr5nR1bbFZMnnlYE058U0FTndoZ1Pgi+y0rrVt9+TQehFrWH2mqUmdMpaWAGn2NLSdgre51tCYxxdWeb0=
*/