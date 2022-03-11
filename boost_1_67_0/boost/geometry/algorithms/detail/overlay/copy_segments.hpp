// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_COPY_SEGMENTS_HPP


#include <vector>

#include <boost/array.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/integral_constant.hpp>

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

#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>


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
        typename SideStrategy,
        typename RobustPolicy,
        typename RangeOut
    >
    static inline void apply(Ring const& ring,
            SegmentIdentifier const& seg_id,
            signed_size_type to_index,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy,
            RangeOut& current_output)
    {
        typedef typename closeable_view
        <
            Ring const,
            closure<Ring>::value
        >::type cview_type;

        typedef typename reversible_view
        <
            cview_type const,
            Reverse ? iterate_reverse : iterate_forward
        >::type rview_type;

        typedef typename boost::range_iterator<rview_type const>::type iterator;
        typedef geometry::ever_circling_iterator<iterator> ec_iterator;


        cview_type cview(ring);
        rview_type view(cview);

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
    template <typename RangeOut, typename Point, typename SideStrategy, typename RobustPolicy>
    static inline void append_to_output(RangeOut& current_output,
                                        Point const& point,
                                        SideStrategy const& strategy,
                                        RobustPolicy const& robust_policy,
                                        boost::true_type const&)
    {
        detail::overlay::append_no_dups_or_spikes(current_output, point,
                                                  strategy,
                                                  robust_policy);
    }

    // keep spikes
    template <typename RangeOut, typename Point, typename SideStrategy, typename RobustPolicy>
    static inline void append_to_output(RangeOut& current_output,
                                        Point const& point,
                                        SideStrategy const& strategy,
                                        RobustPolicy const&,
                                        boost::false_type const&)
    {
        detail::overlay::append_no_duplicates(current_output, point, strategy.get_equals_point_point_strategy());
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
                             boost::integral_constant<bool, RemoveSpikes>());
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