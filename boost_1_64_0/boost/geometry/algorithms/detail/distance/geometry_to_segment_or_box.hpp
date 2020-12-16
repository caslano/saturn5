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
PjE/ZYSj5uAQPyfVRU5TNtIH+XFTNB0+Es7xSV+JXza9O5KW61cGntcTKzE6XUOtfwlfJqhvXl3NcTxGnFE6wF/JrR7V1yA9VcL8O9je/shjvmjt7EudzM7Jc8W52X7D/W30gj08zO77i2B+DZ7Uf+QAF6fsxFNxdlrsC/h/K4j/4Tpmh7Tq7N6H8r5CXYljrhvq7yJ/a58apS3+0s/DXTtPfzMajdLnv9aCl2bRwd99S+Px+AbhvONreC3Wk7QcvRBlDyfhsnWtxRFlYW+n38xseZ0j39dvrdQVjh4QbIYZSUNZwyN9PYtX0nqRdeLMbTzdyOV8naa0x6/qBF/chaP9YNgt/Toa/iXrZiam57bKcwr5WfSDdeqf6IKwgEcUTR9mTgWTssARtbWLrvyhFD1lv82rqeUbtGpSHlg1XuYw54EwZS2fvgCdR37StTwPmnoV/f4fr6tfyDw8XZ3Wwf3OUy/F4n3K72U9E6HeesfF2xqnq7jMkK/8Rehq+PbKvWc7W173u168z7tUIznhzRnXWfonna4n0oXS8D/jsL1y9gh3b+VluXby+M7e5PKmnDWz/hl0TE86Kc8V3I8LupcQ5+Vib6ZuEQfP/gznttO0pWCQWj78jb7/je41ewebF3LQ5UkL8LIT44sJzj94s1XqmXtoqQLmnec8oqApnu/ka76BCVl/kzM40HegHomZ+4ubV9V7+5VimlkfVdWTfcxo0/WB++53zjZ9qLluGa3eQXzOef902jdJwO8zpi8HqyvPALTkcw+lvy4eULNn+GrOpps04B9ZU7VMtFFuX58V5OfZzeZh8PCdWVYv1BWv3WbkSrlx72L6w2uPjTInFeFnbnXWXEP9Z7LWyfYs3mEd1Mq1YNeiiV7T7PjY73f33Jj8wM3lD2gUODNJv3X5HgZaX/ve4gtXUsDSAansAT71FsMnZWAczVGwLIz8j/nlG7kqwduTy6O0QqKtzlTOieV2a57PY7PncWa6MvDshtjX1ytD+TBV+vLDcVlb+PdZbFoQ1x2Su1pNYc0yvUeHlpxPNy1Xs9YWfy1eKIJH7tHsPM6OHfln5o+GJ+B4mJzJ120cn8ost6azWFbBSYv1Xl+8MBHHrrJP+vkTuLyVno3coqZxWYMCanUyjw3HHMQZNWrCwiswAjYnUMthY+39KLzPoZ/06O+PPaf1AsfQFiGV9eVrOiAezs4k/vd4t3RpbNr1T7nsj4+LwoD33eTgjtmL5s5Sm14oTrs942umcZ0QmgG/lhvHQ1I7O8ZY0zrfeyEecvsQ7o2P1gd6q1l2/JYfNuf3XM5JWBUf3ol7Gpojwz0YClMKm/340IGNF+zd3FRqkpkVJu/5UT1OVLfue0scmx6kp72m3kW9dU4fTTQT1uOP2usGnmjFgs7QosUsM60Aa4MHOJf/xOdeF7sL/xRGptyHt4/DjyheCS7JfFhv7FI7tO4ys2K472XCK+FJxXuH2MHC7rHwKn1w5g4dnpDHN5peg/cNc6ihhz74QKsm4OgM1tMRziWlmYfDzaf0It0aDybE9zPKcdTMh0c8dxoGL2/A2m/0F6/rr39482VosfjijW8rVDaDBfOgrO0+b7YFDXNeD3c7b+6jD2JXpVl70/JlxDkSrrRyn4vm+ZTmDj2VQo8eNQfWG6dWP8e7TfDeBNdWR00fmtvVcRnxyzKDhvsSP0Thxx/gCmxd/xn9OA9eXoe5z/g4PJpjYpDpsRqshPvz0UbNSFQ5m5IFpxRz5kqX1Sov33CjXTH8Upfu6ULDLJHXnvApC10nj4N2wyZ9vKgW7R6jvflRHfPAVXhXHBcNrkAfpRYTWPbbHLothb4yt5Q3tz3I7F4wqWw=
*/