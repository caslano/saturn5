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
uIntZvjHHH7Kyri0euB3OPxZcDs/OIH6U115/WAxfNWk71eL8wvhDQ5fvUqcXwg/2+HPhdvzC+HLPN+v3rEgGcz11N8D8JkeftDyCuerwE/0PH8nnMuK+98/CV8kuGtf+Bx8ge/7wPAHPetLD8N/7vCzl8fzg0fgP3P4MNyEP/+kZPAewd3zh0+HP0dy9/xh+IRnf8f98KJnf8cP4WOCu+cj/Aye9+zv2HFKkm9rCe6c7zgA
*/