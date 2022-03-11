// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

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

#include <boost/geometry/strategies/area.hpp>

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <boost/geometry/io/dsv/write.hpp>
#endif

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


// struct to check whether a ring is topologically closed
template <typename Ring, closure_selector Closure /* open */>
struct is_topologically_closed
{
    template <typename VisitPolicy, typename EqPPStrategy>
    static inline bool apply(Ring const&, VisitPolicy& visitor, EqPPStrategy const&)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};

template <typename Ring>
struct is_topologically_closed<Ring, closed>
{
    template <typename VisitPolicy, typename EqPPStrategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor, EqPPStrategy const&)
    {
        boost::ignore_unused(visitor);

        if (geometry::detail::equals::equals_point_point(range::front(ring),
                                                         range::back(ring),
                                                         EqPPStrategy()))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return visitor.template apply<failure_not_closed>();
        }
    }
};



template <typename ResultType, bool IsInteriorRing /* false */>
struct ring_area_predicate
{
    typedef std::greater<ResultType> type;
};

template <typename ResultType>
struct ring_area_predicate<ResultType, true>
{
    typedef std::less<ResultType> type;
};



template <typename Ring, bool IsInteriorRing>
struct is_properly_oriented
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        typedef detail::area::ring_area
            <
                order_as_direction<geometry::point_order<Ring>::value>::value,
                geometry::closure<Ring>::value
            > ring_area_type;

        typedef typename Strategy::template area_strategy
            <
                Ring
            >::type::template result_type<Ring>::type area_result_type;

        typename ring_area_predicate
            <
                area_result_type, IsInteriorRing
            >::type predicate;

        // Check area
        area_result_type const zero = 0;
        area_result_type const area
            = ring_area_type::apply(ring,
                                    strategy.template get_area_strategy<Ring>());
        if (predicate(area, zero))
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
        typedef typename Strategy::cs_tag cs_tag;

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

        closure_selector const closure = geometry::closure<Ring>::value;
        typedef typename closeable_view<Ring const, closure>::type view_type;

        if (boost::size(ring)
            < core_detail::closure::minimum_ring_size<closure>::value)
        {
            return visitor.template apply<failure_few_points>();
        }

        view_type const view(ring);
        if (detail::num_distinct_consecutive_points
                <
                    view_type, 4u, true,
                    not_equal_to
                        <
                            typename point_type<Ring>::type,
                            typename Strategy::equals_point_point_strategy_type
                        >
                >::apply(view)
            < 4u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        return
            is_topologically_closed<Ring, closure>::apply(ring, visitor, strategy.get_equals_point_point_strategy())
            && ! has_duplicates<Ring, closure, cs_tag>::apply(ring, visitor)
            && ! has_spikes<Ring, closure>::apply(ring, visitor, strategy.get_side_strategy())
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