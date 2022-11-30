// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENTS_HPP


#include <type_traits>
#include <vector>

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/append_no_duplicates.hpp>
#include <boost/geometry/algorithms/detail/overlay/append_no_dups_or_spikes.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/iterators/ever_circling_iterator.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace copy_segments
{


template <bool Reverse>
struct copy_segments_ring
{
    template
    <
        typename Ring,
        typename SegmentIdentifier,
        typename Strategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(Ring const& ring,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            Strategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {
        using view_type = detail::closed_clockwise_view
            <
                Ring const,
                closure<Ring>::value,
                Reverse ? counterclockwise : clockwise
            >;

        using iterator = typename boost::range_iterator<view_type const>::type;
        using ec_iterator = geometry::ever_circling_iterator<iterator>;

        view_type view(ring);

        // The problem: sometimes we want to from "3" to "2"
        // -> end = "3" -> end == begin
        // This is not convenient with iterators.

        // So we use the ever-circling iterator and determine when to step out

        signed_size_type const from_index = seg_id.segment_index + 1;

        // Sanity check
        BOOST_GEOMETRY_ASSERT(from_index < static_cast<signed_size_type>(boost::size(view)));

        ec_iterator it(boost::begin(view), boost::end(view),
                    boost::begin(view) + from_index);

        // [2..4] -> 4 - 2 + 1 = 3 -> {2,3,4} -> OK
        // [4..2],size=6 -> 6 - 4 + 2 + 1 = 5 -> {4,5,0,1,2} -> OK
        // [1..1], travel the whole ring round
        signed_size_type const count = from_index <= to_index
            ? to_index - from_index + 1
            : static_cast<signed_size_type>(boost::size(view))
                - from_index + to_index + 1;

        for (signed_size_type i = 0; i < count; ++i, ++it)
        {
            detail::overlay::append_no_dups_or_spikes(current_output, *it, strategy, robust_policy);
        }
    }
};

template <bool Reverse, bool RemoveSpikes = true>
class copy_segments_linestring
{
private:
    // remove spikes
    template <typename RangeOut, typename Point, typename Strategy, typename RobustPolicy>
    static inline void append_to_output(RangeOut& current_output,
                                        Point const& point,
                                        Strategy const& strategy,
                                        RobustPolicy const& robust_policy,
                                        std::true_type const&)
    {
        detail::overlay::append_no_dups_or_spikes(current_output, point,
                                                  strategy,
                                                  robust_policy);
    }

    // keep spikes
    template <typename RangeOut, typename Point, typename Strategy, typename RobustPolicy>
    static inline void append_to_output(RangeOut& current_output,
                                        Point const& point,
                                        Strategy const& strategy,
                                        RobustPolicy const&,
                                        std::false_type const&)
    {
        detail::overlay::append_no_duplicates(current_output, point, strategy);
    }

public:
    template
    <
        typename LineString,
        typename SegmentIdentifier,
        typename SideStrategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(LineString const& ls,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {
        signed_size_type const from_index = seg_id.segment_index + 1;

        // Sanity check
        if ( from_index > to_index
          || from_index < 0
          || to_index >= static_cast<signed_size_type>(boost::size(ls)) )
        {
            return;
        }

        signed_size_type const count = to_index - from_index + 1;

        typename boost::range_iterator<LineString const>::type
            it = boost::begin(ls) + from_index;

        for (signed_size_type i = 0; i < count; ++i, ++it)
        {
            append_to_output(current_output, *it, strategy, robust_policy,
                             std::integral_constant<bool, RemoveSpikes>());
        }
    }
};

template <bool Reverse>
struct copy_segments_polygon
{
    template
    <
        typename Polygon,
        typename SegmentIdentifier,
        typename SideStrategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(Polygon const& polygon,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {
        // Call ring-version with the right ring
        copy_segments_ring<Reverse>::apply
            (
                seg_id.ring_index < 0
                    ? geometry::exterior_ring(polygon)
                    : range::at(geometry::interior_rings(polygon), seg_id.ring_index),
                seg_id, to_index,
                strategy,
                robust_policy,
                current_output
            );
    }
};


template <bool Reverse>
struct copy_segments_box
{
    template
    <
        typename Box,
        typename SegmentIdentifier,
        typename SideStrategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(Box const& box,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {
        signed_size_type index = seg_id.segment_index + 1;
        BOOST_GEOMETRY_ASSERT(index < 5);

        signed_size_type const count = index <= to_index
            ? to_index - index + 1
            : 5 - index + to_index + 1;

        // Create array of points, the fifth one closes it
        boost::array<typename point_type<Box>::type, 5> bp;
        assign_box_corners_oriented<Reverse>(box, bp);
        bp[4] = bp[0];

        // (possibly cyclic) copy to output
        //    (see comments in ring-version)
        for (signed_size_type i = 0; i < count; i++, index++)
        {
            detail::overlay::append_no_dups_or_spikes(current_output,
                bp[index % 5], strategy, robust_policy);

        }
    }
};


template<typename Policy>
struct copy_segments_multi
{
    template
    <
        typename MultiGeometry,
        typename SegmentIdentifier,
        typename SideStrategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(MultiGeometry const& multi_geometry,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {

        BOOST_GEOMETRY_ASSERT
            (
                seg_id.multi_index >= 0
                && static_cast<std::size_t>(seg_id.multi_index) < boost::size(multi_geometry)
            );

        // Call the single-version
        Policy::apply(range::at(multi_geometry, seg_id.multi_index),
                      seg_id, to_index,
                      strategy,
                      robust_policy,
                      current_output);
    }
};


}} // namespace detail::copy_segments
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Tag,
    bool Reverse
>
struct copy_segments : not_implemented<Tag>
{};


template <bool Reverse>
struct copy_segments<ring_tag, Reverse>
    : detail::copy_segments::copy_segments_ring<Reverse>
{};


template <bool Reverse>
struct copy_segments<linestring_tag, Reverse>
    : detail::copy_segments::copy_segments_linestring<Reverse>
{};

template <bool Reverse>
struct copy_segments<polygon_tag, Reverse>
    : detail::copy_segments::copy_segments_polygon<Reverse>
{};


template <bool Reverse>
struct copy_segments<box_tag, Reverse>
    : detail::copy_segments::copy_segments_box<Reverse>
{};


template<bool Reverse>
struct copy_segments<multi_polygon_tag, Reverse>
    : detail::copy_segments::copy_segments_multi
        <
            detail::copy_segments::copy_segments_polygon<Reverse>
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Copy segments from a geometry, starting with the specified segment (seg_id)
        until the specified index (to_index)
    \ingroup overlay
 */
template
<
    bool Reverse,
    typename Geometry,
    typename SegmentIdentifier,
    typename SideStrategy,
    typename RobustPolicy,
    typename RangeOut
>
inline void copy_segments(Geometry const& geometry,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& range_out)
{
    concepts::check<Geometry const>();

    dispatch::copy_segments
        <
            typename tag<Geometry>::type,
            Reverse
        >::apply(geometry, seg_id, to_index, strategy, robust_policy, range_out);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENTS_HPP

/* copy_segments.hpp
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
*/