// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP


#include <boost/geometry/algorithms/detail/disjoint/multirange_geometry.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/views/closeable_view.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template
<
    typename SegmentOrBox,
    typename Tag = typename tag<SegmentOrBox>::type
>
struct disjoint_point_segment_or_box
    : not_implemented<Tag>
{};

template <typename Segment>
struct disjoint_point_segment_or_box<Segment, segment_tag>
{
    template <typename Point, typename Strategy>
    static inline bool apply(Point const& point, Segment const& segment, Strategy const& strategy)
    {
        return dispatch::disjoint
            <
                Point, Segment
            >::apply(point, segment, strategy);
    }
};

template <typename Box>
struct disjoint_point_segment_or_box<Box, box_tag>
{
    template <typename Point, typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        return dispatch::disjoint
            <
                Point, Box
            >::apply(point, box, strategy);
    }
};


template <typename Range, typename SegmentOrBox>
struct disjoint_range_segment_or_box
{
    template <typename Strategy>
    static inline bool apply(Range const& range,
                             SegmentOrBox const& segment_or_box,
                             Strategy const& strategy)
    {
        using point_type = typename point_type<Range>::type;
        using range_segment = typename geometry::model::referring_segment<point_type const>;

        detail::closed_view<Range const> const view(range);

        auto const count = ::boost::size(view);

        if ( count == 0 )
        {
            return false;
        }
        else if ( count == 1 )
        {
            return disjoint_point_segment_or_box
                <
                    SegmentOrBox
                >::apply(range::front(view), segment_or_box, strategy);
        }
        else
        {
            auto it0 = ::boost::begin(view);
            auto it1 = ::boost::begin(view) + 1;
            auto const last = ::boost::end(view);

            for ( ; it1 != last ; ++it0, ++it1 )
            {
                point_type const& p0 = *it0;
                point_type const& p1 = *it1;
                range_segment rng_segment(p0, p1);
                if ( !dispatch::disjoint
                         <
                             range_segment, SegmentOrBox
                         >::apply(rng_segment, segment_or_box, strategy) )
                {
                    return false;
                }
            }
            return true;
        }
    }
};




template
<
    typename Linear,
    typename SegmentOrBox,
    typename Tag = typename tag<Linear>::type
>
struct disjoint_linear_segment_or_box
    : not_implemented<Linear, SegmentOrBox>
{};


template <typename Linestring, typename SegmentOrBox>
struct disjoint_linear_segment_or_box<Linestring, SegmentOrBox, linestring_tag>
    : disjoint_range_segment_or_box<Linestring, SegmentOrBox>
{};


template <typename MultiLinestring, typename SegmentOrBox>
struct disjoint_linear_segment_or_box
    <
        MultiLinestring, SegmentOrBox, multi_linestring_tag
    > : multirange_constant_size_geometry<MultiLinestring, SegmentOrBox>
{};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear, typename Segment>
struct disjoint<Linear, Segment, 2, linear_tag, segment_tag, false>
    : detail::disjoint::disjoint_linear_segment_or_box<Linear, Segment>
{};


template <typename Linear, typename Box, std::size_t DimensionCount>
struct disjoint<Linear, Box, DimensionCount, linear_tag, box_tag, false>
    : detail::disjoint::disjoint_linear_segment_or_box<Linear, Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_LINEAR_SEGMENT_OR_BOX_HPP

/* linear_segment_or_box.hpp
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
*/