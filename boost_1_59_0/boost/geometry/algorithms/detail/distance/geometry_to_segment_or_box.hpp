// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_TO_SEGMENT_OR_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_TO_SEGMENT_OR_BOX_HPP

#include <iterator>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/geometry_to_range.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// closure of segment or box point range
template
<
    typename SegmentOrBox,
    typename Tag = typename tag<SegmentOrBox>::type
>
struct segment_or_box_point_range_closure
    : not_implemented<SegmentOrBox>
{};    

template <typename Segment>
struct segment_or_box_point_range_closure<Segment, segment_tag>
{
    static const closure_selector value = closed;
};

template <typename Box>
struct segment_or_box_point_range_closure<Box, box_tag>
{
    static const closure_selector value = open;
};



template
<
    typename Geometry,
    typename SegmentOrBox,
    typename Strategies,
    typename Tag = typename tag<Geometry>::type
>
class geometry_to_segment_or_box
{
private:
    typedef typename point_type<SegmentOrBox>::type segment_or_box_point;

    typedef distance::strategy_t<Geometry, SegmentOrBox, Strategies> strategy_type;

    typedef detail::closest_feature::point_to_point_range
        <
            typename point_type<Geometry>::type,
            std::vector<segment_or_box_point>,
            segment_or_box_point_range_closure<SegmentOrBox>::value
        > point_to_point_range;

    typedef detail::closest_feature::geometry_to_range geometry_to_range;

    typedef distance::creturn_t<Geometry, SegmentOrBox, Strategies> comparable_return_type;

    // assign the new minimum value for an iterator of the point range
    // of a segment or a box
    template
    <
        typename SegOrBox,
        typename SegOrBoxTag = typename tag<SegOrBox>::type
    >
    struct assign_new_min_iterator
        : not_implemented<SegOrBox>
    {};

    template <typename Segment>
    struct assign_new_min_iterator<Segment, segment_tag>
    {
        template <typename Iterator>
        static inline void apply(Iterator&, Iterator)
        {
        }
    };

    template <typename Box>
    struct assign_new_min_iterator<Box, box_tag>
    {
        template <typename Iterator>
        static inline void apply(Iterator& it_min, Iterator it)
        {
            it_min = it;
        }
    };


    // assign the points of a segment or a box to a range
    template
    <
        typename SegOrBox,
        typename PointRange,
        typename SegOrBoxTag = typename tag<SegOrBox>::type
    >
    struct assign_segment_or_box_points
    {};

    template <typename Segment, typename PointRange>
    struct assign_segment_or_box_points<Segment, PointRange, segment_tag>
    {
        static inline void apply(Segment const& segment, PointRange& range)
        {
            detail::assign_point_from_index<0>(segment, range[0]);
            detail::assign_point_from_index<1>(segment, range[1]);
        }
    };

    template <typename Box, typename PointRange>
    struct assign_segment_or_box_points<Box, PointRange, box_tag>
    {
        static inline void apply(Box const& box, PointRange& range)
        {
            detail::assign_box_corners_oriented<true>(box, range);
        }
    };

public:
    typedef distance::return_t<Geometry, SegmentOrBox, Strategies> return_type;

    static inline return_type apply(Geometry const& geometry,
                                    SegmentOrBox const& segment_or_box,
                                    Strategies const& strategies,
                                    bool check_intersection = true)
    {
        typedef geometry::point_iterator<Geometry const> point_iterator_type;
        typedef geometry::segment_iterator
            <
                Geometry const
            > segment_iterator_type;

        typedef typename boost::range_const_iterator
            <
                std::vector<segment_or_box_point>
            >::type seg_or_box_const_iterator;

        typedef assign_new_min_iterator<SegmentOrBox> assign_new_value;


        if (check_intersection
            && geometry::intersects(geometry, segment_or_box, strategies))
        {
            return return_type(0);
        }

        strategy_type const strategy = strategies.distance(geometry, segment_or_box);

        auto const cstrategy = strategy::distance::services::get_comparable
                                <
                                    strategy_type
                                >::apply(strategy);

        // get all points of the segment or the box
        std::vector<segment_or_box_point>
            seg_or_box_points(geometry::num_points(segment_or_box));

        assign_segment_or_box_points
            <
                SegmentOrBox, 
                std::vector<segment_or_box_point>
            >::apply(segment_or_box, seg_or_box_points);

        // consider all distances of the points in the geometry to the
        // segment or box
        comparable_return_type cd_min1(0);
        point_iterator_type pit_min;
        seg_or_box_const_iterator it_min1 = boost::const_begin(seg_or_box_points);
        seg_or_box_const_iterator it_min2 = it_min1;
        ++it_min2;
        bool first = true;

        for (point_iterator_type pit = points_begin(geometry);
             pit != points_end(geometry); ++pit, first = false)
        {
            comparable_return_type cd;
            std::pair
                <
                    seg_or_box_const_iterator, seg_or_box_const_iterator
                > it_pair
                = point_to_point_range::apply(*pit,
                                              boost::const_begin(seg_or_box_points),
                                              boost::const_end(seg_or_box_points),
                                              cstrategy,
                                              cd);

            if (first || cd < cd_min1)
            {
                cd_min1 = cd;
                pit_min = pit;
                assign_new_value::apply(it_min1, it_pair.first);
                assign_new_value::apply(it_min2, it_pair.second);
            }
        }

        // consider all distances of the points in the segment or box to the
        // segments of the geometry
        comparable_return_type cd_min2(0);
        segment_iterator_type sit_min;
        seg_or_box_const_iterator it_min;

        first = true;
        for (seg_or_box_const_iterator it = boost::const_begin(seg_or_box_points);
             it != boost::const_end(seg_or_box_points); ++it, first = false)
        {
            comparable_return_type cd;
            segment_iterator_type sit
                = geometry_to_range::apply(*it,
                                           segments_begin(geometry),
                                           segments_end(geometry),
                                           cstrategy,
                                           cd);

            if (first || cd < cd_min2)
            {
                cd_min2 = cd;
                it_min = it;
                sit_min = sit;
            }
        }

        if (BOOST_GEOMETRY_CONDITION(is_comparable<strategy_type>::value))
        {
            return (std::min)(cd_min1, cd_min2);
        }

        if (cd_min1 < cd_min2)
        {
            return strategy.apply(*pit_min, *it_min1, *it_min2);
        }
        else
        {
            return dispatch::distance
                <
                    segment_or_box_point,
                    typename std::iterator_traits
                        <
                            segment_iterator_type
                        >::value_type,
                    Strategies
                >::apply(*it_min, *sit_min, strategies);
        }
    }


    static inline return_type apply(SegmentOrBox const& segment_or_box, Geometry const& geometry, 
                                    Strategies const& strategies, bool check_intersection = true)
    {
        return apply(geometry, segment_or_box, strategies, check_intersection);
    }
};



template <typename MultiPoint, typename SegmentOrBox, typename Strategies>
class geometry_to_segment_or_box
    <
        MultiPoint, SegmentOrBox, Strategies, multi_point_tag
    >
{
private:
    typedef detail::closest_feature::geometry_to_range base_type;

    typedef typename boost::range_iterator
        <
            MultiPoint const
        >::type iterator_type;

    typedef detail::closest_feature::geometry_to_range geometry_to_range;

    typedef distance::strategy_t<MultiPoint, SegmentOrBox, Strategies> strategy_type;

public:
    typedef distance::return_t<MultiPoint, SegmentOrBox, Strategies> return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    SegmentOrBox const& segment_or_box,
                                    Strategies const& strategies)
    {
        distance::creturn_t<MultiPoint, SegmentOrBox, Strategies> cd_min;

        iterator_type it_min
            = geometry_to_range::apply(segment_or_box,
                                       boost::begin(multipoint),
                                       boost::end(multipoint),
                                       strategy::distance::services::get_comparable
                                           <
                                               strategy_type
                                           >::apply(strategies.distance(multipoint, segment_or_box)),
                                       cd_min);

        return
            is_comparable<strategy_type>::value
            ?
            cd_min
            :
            dispatch::distance
                <
                    typename point_type<MultiPoint>::type,
                    SegmentOrBox,
                    Strategies
                >::apply(*it_min, segment_or_box, strategies);
    }
};



}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Linear, typename Segment, typename Strategy>
struct distance
    <
        Linear, Segment, Strategy, linear_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box<Linear, Segment, Strategy>
{};


template <typename Areal, typename Segment, typename Strategy>
struct distance
    <
        Areal, Segment, Strategy, areal_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box<Areal, Segment, Strategy>
{};


template <typename Segment, typename Areal, typename Strategy>
struct distance
    <
        Segment, Areal, Strategy, segment_tag, areal_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box<Areal, Segment, Strategy>
{};


template <typename Linear, typename Box, typename Strategy>
struct distance
    <
        Linear, Box, Strategy, linear_tag, box_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box
        <
            Linear, Box, Strategy
        >
{};


template <typename Areal, typename Box, typename Strategy>
struct distance
    <
        Areal, Box, Strategy, areal_tag, box_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box<Areal, Box, Strategy>
{};


template <typename MultiPoint, typename Segment, typename Strategy>
struct distance
    <
        MultiPoint, Segment, Strategy,
        multi_point_tag, segment_tag,
        strategy_tag_distance_point_segment, false
    > : detail::distance::geometry_to_segment_or_box
        <
            MultiPoint, Segment, Strategy
        >
{};


template <typename MultiPoint, typename Box, typename Strategy>
struct distance
    <
        MultiPoint, Box, Strategy,
        multi_point_tag, box_tag,
        strategy_tag_distance_point_box, false
    > : detail::distance::geometry_to_segment_or_box
        <
            MultiPoint, Box, Strategy
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_TO_SEGMENT_OR_BOX_HPP

/* geometry_to_segment_or_box.hpp
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
*/