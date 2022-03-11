// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

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
            >::apply(point, segment,
                     strategy.template get_point_in_geometry_strategy<Point, Segment>());
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
            >::apply(point, box,
                     strategy.get_disjoint_point_box_strategy());
    }
};


template
<
    typename Range,
    closure_selector Closure,
    typename SegmentOrBox
>
struct disjoint_range_segment_or_box
{
    template <typename Strategy>
    static inline bool apply(Range const& range,
                             SegmentOrBox const& segment_or_box,
                             Strategy const& strategy)
    {
        typedef typename closeable_view<Range const, Closure>::type view_type;

        typedef typename ::boost::range_value<view_type>::type point_type;
        typedef typename ::boost::range_iterator
            <
                view_type const
            >::type const_iterator;

        typedef typename ::boost::range_size<view_type>::type size_type;

        typedef typename geometry::model::referring_segment
            <
                point_type const
            > range_segment;

        view_type view(range);

        const size_type count = ::boost::size(view);

        if ( count == 0 )
        {
            return false;
        }
        else if ( count == 1 )
        {
            return disjoint_point_segment_or_box
                <
                    SegmentOrBox
                >::apply(geometry::range::front<view_type const>(view),
                         segment_or_box,
                         strategy);
        }
        else
        {
            const_iterator it0 = ::boost::begin(view);
            const_iterator it1 = ::boost::begin(view) + 1;
            const_iterator last = ::boost::end(view);

            for ( ; it1 != last ; ++it0, ++it1 )
            {
                range_segment rng_segment(*it0, *it1);
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
    : disjoint_range_segment_or_box<Linestring, closed, SegmentOrBox>
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