// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP

#include <deque>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/order_as_direction.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/closeable_view.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/num_distinct_consecutive_points.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_valid_self_turns.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

// TEMP - with UmberllaStrategy this will be not needed
#include <boost/geometry/strategy/area.hpp>
#include <boost/geometry/strategies/area/services.hpp>
// TODO: use point_order instead of area


#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <boost/geometry/io/dsv/write.hpp>
#endif

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


// struct to check whether a ring is topologically closed
template <typename Ring, closure_selector Closure = geometry::closure<Ring>::value>
struct is_topologically_closed
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const&, VisitPolicy& visitor, Strategy const&)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};

template <typename Ring>
struct is_topologically_closed<Ring, closed>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor, Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        using geometry::detail::equals::equals_point_point;
        if (equals_point_point(range::front(ring), range::back(ring), strategy))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return visitor.template apply<failure_not_closed>();
        }
    }
};


// TODO: use calculate_point_order here
template <typename Ring, bool IsInteriorRing>
struct is_properly_oriented
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        // Check area
        auto const area = detail::area::ring_area::apply(ring, strategy);
        decltype(area) const zero = 0;

        if (IsInteriorRing ? (area < zero) : (area > zero))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return visitor.template apply<failure_wrong_orientation>();
        }
    }
};



template
<
    typename Ring,
    bool CheckSelfIntersections = true,
    bool IsInteriorRing = false
>
struct is_valid_ring
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        // return invalid if any of the following condition holds:
        // (a) the ring's point coordinates are not invalid (e.g., NaN)
        // (b) the ring's size is below the minimal one
        // (c) the ring consists of at most two distinct points
        // (d) the ring is not topologically closed
        // (e) the ring has spikes
        // (f) the ring has duplicate points (if AllowDuplicates is false)
        // (g) the boundary of the ring has self-intersections
        // (h) the order of the points is inconsistent with the defined order
        //
        // Note: no need to check if the area is zero. If this is the
        // case, then the ring must have at least two spikes, which is
        // checked by condition (d).

        if (has_invalid_coordinate<Ring>::apply(ring, visitor))
        {
            return false;
        }

        if (boost::size(ring) < detail::minimum_ring_size<Ring>::value)
        {
            return visitor.template apply<failure_few_points>();
        }

        detail::closed_view<Ring const> const view(ring);

        if (detail::num_distinct_consecutive_points
                <
                    decltype(view), 4u, true
                >::apply(view, strategy)
            < 4u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        return
            is_topologically_closed<Ring>::apply(ring, visitor, strategy)
            && ! has_duplicates<Ring>::apply(ring, visitor, strategy)
            && ! has_spikes<Ring>::apply(ring, visitor, strategy)
            && (! CheckSelfIntersections
                || has_valid_self_turns<Ring, typename Strategy::cs_tag>::apply(ring, visitor, strategy))
            && is_properly_oriented<Ring, IsInteriorRing>::apply(ring, visitor, strategy);
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A Ring is a Polygon with exterior boundary only.
// The Ring's boundary must be a LinearRing (see OGC 06-103-r4,
// 6.1.7.1, for the definition of LinearRing)
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Ring, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        Ring, ring_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_ring<Ring>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP

/* ring.hpp
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
*/