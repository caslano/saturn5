// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range/empty.hpp>

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
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
*/