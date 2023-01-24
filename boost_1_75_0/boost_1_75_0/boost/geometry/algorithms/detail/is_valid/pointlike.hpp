// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A point is always simple
template <typename Point>
struct is_valid<Point, point_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Point const& point, VisitPolicy& visitor, Strategy const&)
    {
        boost::ignore_unused(visitor);
        return ! detail::is_valid::has_invalid_coordinate
            <
                Point
            >::apply(point, visitor);
    }
};



// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint, bool AllowEmptyMultiGeometries>
struct is_valid<MultiPoint, multi_point_tag, AllowEmptyMultiGeometries>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiPoint const& multipoint,
                             VisitPolicy& visitor,
                             Strategy const&)
    {
        boost::ignore_unused(multipoint, visitor);

        if (BOOST_GEOMETRY_CONDITION(
                AllowEmptyMultiGeometries || !boost::empty(multipoint)))
        {
            // we allow empty multi-geometries, so an empty multipoint
            // is considered valid
            return ! detail::is_valid::has_invalid_coordinate
                <
                    MultiPoint
                >::apply(multipoint, visitor);
        }
        else
        {
            // we do not allow an empty multipoint
            return visitor.template apply<failure_few_points>();
        }
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

/* pointlike.hpp
GdmrFaD1RyJ7bmTE1yWr0bJiBHfznwN6czL8/cc5Qm9+Bv1Cr1VMHi0AHgvjKHcUjVdN4t0Ify3gBMuYQ06UPQ3+xDaUj6FMlJ6N3L+l0Pu3qP0Xmv5v09C95LsPMQai3nhf4EMkyYk5aegR8t6PCjGKq1NymqTzFvydI+VUcjrtqE5oRkX0/JvoRpQwed2v4XWd6V2Ikwf9JiN34yhYs5OQuyrCYaDpeSFK/iT4KwU3+12y1uSQGZ+TP+tReJ1N/oj4XQVJKrm7A6pKhEnQBuE5XAFIMuHpmUZJxM6NPtYqcQ6zw8hlsmPv/36X84xm/iAN7YXAH8CRhe0QQCSIR1hev37fgR7BGmr+lYnIg4ifCJ+ZkQvzO8tHAw4OdFUgGTn7qMbqAEn/ay39xPcy0DhwU98jciCSZR/prWfJ3x/hb+1mAUuy/z16uefk9yJ57jcb8zyTIH8gLJXSZSfLN44txrb3OE93MXhWv6fzdIkVq6Bch1cImbgKBWkfTVTQ+K4xaHyjHY0PpKDxp3SOD13/3+N2Oo6A5+/vaXSqxtNkiIFOm3YbdqT10+hxTz9FFpm6cF3pWtwm9Ii7gZBJFdxSvnxKupVcPZQNzieVKVstl4FatStesVCttc6x2VWvkIo9aImVMstkK0XJEddh42O19n0Yg/Xw1/I+kcWgGYlZyE51nmP2hrXvc77PPeDZ977OR9JLz3dVdSGu
*/