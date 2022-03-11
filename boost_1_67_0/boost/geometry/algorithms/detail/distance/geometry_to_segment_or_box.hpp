// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_TO_SEGMENT_OR_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_GEOMETRY_TO_SEGMENT_OR_BOX_HPP

#include <iterator>

#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/num_points.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/geometry_to_range.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>

#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>

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
    typename Strategy,
    typename Tag = typename tag<Geometry>::type
>
class geometry_to_segment_or_box
{
private:
    typedef typename point_type<SegmentOrBox>::type segment_or_box_point;

    typedef typename strategy::distance::services::comparable_type
       <
           Strategy
       >::type comparable_strategy;

    typedef detail::closest_feature::point_to_point_range
        <
            typename point_type<Geometry>::type,
            std::vector<segment_or_box_point>,
            segment_or_box_point_range_closure<SegmentOrBox>::value,
            comparable_strategy
        > point_to_point_range;

    typedef detail::closest_feature::geometry_to_range geometry_to_range;

    typedef typename strategy::distance::services::return_type
        <
            comparable_strategy,
            typename point_type<Geometry>::type,
            segment_or_box_point
        >::type comparable_return_type;


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

    template
    <
        typename SegOrBox,
        typename SegOrBoxTag = typename tag<SegOrBox>::type
    >
    struct intersects
    {
        static inline bool apply(Geometry const& g1, SegOrBox const& g2, Strategy const&)
        {
            return geometry::intersects(g1, g2);
        }
    };

    template <typename SegOrBox>
    struct intersects<SegOrBox, segment_tag>
    {
        static inline bool apply(Geometry const& g1, SegOrBox const& g2, Strategy const& s)
        {
            return geometry::intersects(g1, g2, s.get_relate_segment_segment_strategy());
        }
    };

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Geometry>::type,
            segment_or_box_point
        >::type return_type;

    static inline return_type apply(Geometry const& geometry,
                                    SegmentOrBox const& segment_or_box,
                                    Strategy const& strategy,
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
            && intersects<SegmentOrBox>::apply(geometry, segment_or_box, strategy))
        {
            return 0;
        }

        comparable_strategy cstrategy =
            strategy::distance::services::get_comparable
                <
                    Strategy
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

        if (BOOST_GEOMETRY_CONDITION(is_comparable<Strategy>::value))
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
                    Strategy
                >::apply(*it_min, *sit_min, strategy);
        }
    }


    static inline return_type
    apply(SegmentOrBox const& segment_or_box, Geometry const& geometry, 
          Strategy const& strategy, bool check_intersection = true)
    {
        return apply(geometry, segment_or_box, strategy, check_intersection);
    }
};



template <typename MultiPoint, typename SegmentOrBox, typename Strategy>
class geometry_to_segment_or_box
    <
        MultiPoint, SegmentOrBox, Strategy, multi_point_tag
    >
{
private:
    typedef detail::closest_feature::geometry_to_range base_type;

    typedef typename boost::range_iterator
        <
            MultiPoint const
        >::type iterator_type;

    typedef detail::closest_feature::geometry_to_range geometry_to_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<SegmentOrBox>::type,
            typename point_type<MultiPoint>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    SegmentOrBox const& segment_or_box,
                                    Strategy const& strategy)
    {
        namespace sds = strategy::distance::services;

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                typename point_type<SegmentOrBox>::type,
                typename point_type<MultiPoint>::type
            >::type cd_min;

        iterator_type it_min
            = geometry_to_range::apply(segment_or_box,
                                       boost::begin(multipoint),
                                       boost::end(multipoint),
                                       sds::get_comparable
                                           <
                                               Strategy
                                           >::apply(strategy),
                                       cd_min);

        return
            is_comparable<Strategy>::value
            ?
            cd_min
            :
            dispatch::distance
                <
                    typename point_type<MultiPoint>::type,
                    SegmentOrBox,
                    Strategy
                >::apply(*it_min, segment_or_box, strategy);
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