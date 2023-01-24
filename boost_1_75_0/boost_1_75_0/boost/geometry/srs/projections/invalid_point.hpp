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
SRj4q61o789KPHWAujZJydmLEgApliIyVkC6FKUwUcrzRLVpJ60zR07TksLRwS9B4SKeQmWrjqfo/JyJX27+6/NiiHYsxSNLaVJwiGDObM+hg9LPW5MRmuDYbPWF7NCAZcAZ/aM21JEuttHO4hnLY55RD8nar0KJBCwZwOZUyYH3O+FDYnahRiCdhNvKPJK3xpXRVJuyslSuyyWDAFgacermNwQu7IXAgETYCJBHvw/0GgW5UhCdyr+ZCYIF551/0hIkvDw9YSCqLx4USAIVjtXxEi66Mw2uXKmuji3EmuzRlSL3528K5xoWB/xcP11N7PbRRl3LFgCiM/J/XltwSfrrvfWb6Ai9FP3uthE0NUB0DcsVrOcIyv/0kBxM1kWpMkLgTAALO05AUM/4oRkPQTIXZn3awO1lkEoRTtIWrNHLbr61CdeD/2XZTwaScWYSTplXVyp3QG4fNcVnzioQLc8Of5P9BcIkco5sNTD42dr+lxiqMAT/RJ4+8+DDvY+WkVdZkizhuf3oe14rPZZZbX2SDvGfScOPHaPXXodoVdh6R2cdbvsx8wcpEmyspZZfFyxoAkJ6BGVLVg0jD7s58gKzvaDBQG7vwWk7BP8wVs7URbQHDQNZ4CmB4OYstVw7+4NalK+h+FOXq4f7uPEpRsI8SNul2xYc2AYBlwT12cGDaw1I32BxwQegwLE+2KkHhM23sBLhk2yqPkbt
*/