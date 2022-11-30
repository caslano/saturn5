// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP


#include <cstddef>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{
// Note: this is moved to namespace detail because the names and parameter orders
// are not yet 100% clear.

/*!
\brief Assign the four points of a 2D box
\ingroup assign
\note The order is crucial. Most logical is LOWER, UPPER and sub-order LEFT, RIGHT
    so this is how it is implemented.
\tparam Box \tparam_box
\tparam Point \tparam_point
\param box \param_box
\param lower_left point being assigned to lower left coordinates of the box
\param lower_right point being assigned to lower right coordinates of the box
\param upper_left point being assigned to upper left coordinates of the box
\param upper_right point being assigned to upper right coordinates of the box

\qbk{
[heading Example]
[assign_box_corners] [assign_box_corners_output]
}
*/
template <typename Box, typename Point>
inline void assign_box_corners(Box const& box,
        Point& lower_left, Point& lower_right,
        Point& upper_left, Point& upper_right)
{
    concepts::check<Box const>();
    concepts::check<Point>();

    detail::assign::assign_box_2d_corner
            <min_corner, min_corner>(box, lower_left);
    detail::assign::assign_box_2d_corner
            <max_corner, min_corner>(box, lower_right);
    detail::assign::assign_box_2d_corner
            <min_corner, max_corner>(box, upper_left);
    detail::assign::assign_box_2d_corner
            <max_corner, max_corner>(box, upper_right);
}

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


template <bool Reverse, typename Box, typename Range>
inline void assign_box_corners_oriented(Box const& box, Range& corners)
{
    if (Reverse)
    {
        // make counterclockwise ll,lr,ur,ul
        assign_box_corners(box,
                           range::at(corners, 0), range::at(corners, 1),
                           range::at(corners, 3), range::at(corners, 2));
    }
    else
    {
        // make clockwise ll,ul,ur,lr
        assign_box_corners(box,
                           range::at(corners, 0), range::at(corners, 3),
                           range::at(corners, 1), range::at(corners, 2));
    }
}
#if defined(_MSC_VER)
#pragma warning(pop)
#endif


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_BOX_CORNERS_HPP

/* assign_box_corners.hpp
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
*/