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