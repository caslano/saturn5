// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP

#include <cstddef>

#include <functional>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>
#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/util/calculation_type.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/has_nan_coordinate.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/strategies/disjoint.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// TODO: Take strategy
template <typename Segment, typename Box>
inline bool intersects_segment_box(Segment const& segment, Box const& box)
{
    typedef typename strategy::disjoint::services::default_strategy
        <
            Segment, Box
        >::type strategy_type;

    return ! detail::disjoint::disjoint_segment_box::apply(segment, box,
                                                           strategy_type());
}


template
<
    typename Segment,
    typename Box,
    typename Strategy,
    bool UsePointBoxStrategy = false
>
class segment_to_box_2D_generic
{
private:
    typedef typename point_type<Segment>::type segment_point;
    typedef typename point_type<Box>::type box_point;

    typedef typename strategy::distance::services::comparable_type
        <
            typename Strategy::distance_ps_strategy::type
        >::type comparable_strategy;

    typedef detail::closest_feature::point_to_point_range
        <
            segment_point,
            std::vector<box_point>,
            open,
            comparable_strategy
        > point_to_point_range;

    typedef typename strategy::distance::services::return_type
        <
            comparable_strategy, segment_point, box_point
        >::type comparable_return_type;
    
public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy, segment_point, box_point
        >::type return_type;

    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategy const& strategy,
                                    bool check_intersection = true)
    {
        if (check_intersection && intersects_segment_box(segment, box))
        {
            return 0;
        }

        comparable_strategy cstrategy =
            strategy::distance::services::get_comparable
                <
                    typename Strategy::distance_ps_strategy::type
                >::apply(strategy.get_distance_ps_strategy());

        // get segment points
        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        // get box points
        std::vector<box_point> box_points(4);
        detail::assign_box_corners_oriented<true>(box, box_points);
 
        comparable_return_type cd[6];
        for (unsigned int i = 0; i < 4; ++i)
        {
            cd[i] = cstrategy.apply(box_points[i], p[0], p[1]);
        }

        std::pair
            <
                typename std::vector<box_point>::const_iterator,
                typename std::vector<box_point>::const_iterator
            > bit_min[2];

        bit_min[0] = point_to_point_range::apply(p[0],
                                                 box_points.begin(),
                                                 box_points.end(),
                                                 cstrategy,
                                                 cd[4]);
        bit_min[1] = point_to_point_range::apply(p[1],
                                                 box_points.begin(),
                                                 box_points.end(),
                                                 cstrategy,
                                                 cd[5]);

        unsigned int imin = 0;
        for (unsigned int i = 1; i < 6; ++i)
        {
            if (cd[i] < cd[imin])
            {
                imin = i;
            }
        }

        if (BOOST_GEOMETRY_CONDITION(is_comparable<Strategy>::value))
        {
            return cd[imin];
        }

        if (imin < 4)
        {
            return strategy.get_distance_ps_strategy().apply(box_points[imin], p[0], p[1]);
        }
        else
        {
            unsigned int bimin = imin - 4;
            return strategy.get_distance_ps_strategy().apply(p[bimin],
                                  *bit_min[bimin].first,
                                  *bit_min[bimin].second);
        }
    }
};


template
<
    typename Segment,
    typename Box,
    typename Strategy
>
class segment_to_box_2D_generic<Segment, Box, Strategy, true>
{
private:
    typedef typename point_type<Segment>::type segment_point;
    typedef typename point_type<Box>::type box_point;

    typedef typename strategy::distance::services::comparable_type
        <
            Strategy
        >::type comparable_strategy;

    typedef typename strategy::distance::services::return_type
        <
            comparable_strategy, segment_point, box_point
        >::type comparable_return_type;

    typedef typename detail::distance::default_strategy
        <
            segment_point, Box
        >::type point_box_strategy;

    typedef typename strategy::distance::services::comparable_type
        <
            point_box_strategy
        >::type point_box_comparable_strategy;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy, segment_point, box_point
        >::type return_type;

    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategy const& strategy,
                                    bool check_intersection = true)
    {
        if (check_intersection && intersects_segment_box(segment, box))
        {
            return 0;
        }

        comparable_strategy cstrategy =
            strategy::distance::services::get_comparable
                <
                    Strategy
                >::apply(strategy);
        boost::ignore_unused(cstrategy);

        // get segment points
        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        // get box points
        std::vector<box_point> box_points(4);
        detail::assign_box_corners_oriented<true>(box, box_points);
 
        comparable_return_type cd[6];
        for (unsigned int i = 0; i < 4; ++i)
        {
            cd[i] = cstrategy.apply(box_points[i], p[0], p[1]);
        }

        point_box_comparable_strategy pb_cstrategy;
        boost::ignore_unused(pb_cstrategy);
        cd[4] = pb_cstrategy.apply(p[0], box);
        cd[5] = pb_cstrategy.apply(p[1], box);

        unsigned int imin = 0;
        for (unsigned int i = 1; i < 6; ++i)
        {
            if (cd[i] < cd[imin])
            {
                imin = i;
            }
        }

        if (is_comparable<Strategy>::value)
        {
            return cd[imin];
        }

        if (imin < 4)
        {
            strategy.apply(box_points[imin], p[0], p[1]);
        }
        else
        {
            return point_box_strategy().apply(p[imin - 4], box);
        }
    }
};




template
<
    typename ReturnType,
    typename SegmentPoint,
    typename BoxPoint,
    typename SBStrategy
>
class segment_to_box_2D
{
private:
    template <typename Result>
    struct cast_to_result
    {
        template <typename T>
        static inline Result apply(T const& t)
        {
            return boost::numeric_cast<Result>(t);
        }
    };


    template <typename T, bool IsLess /* true */>
    struct compare_less_equal
    {
        typedef compare_less_equal<T, !IsLess> other;

        template <typename T1, typename T2>
        inline bool operator()(T1 const& t1, T2 const& t2) const
        {
            return std::less_equal<T>()(cast_to_result<T>::apply(t1),
                                        cast_to_result<T>::apply(t2));
        }
    };

    template <typename T>
    struct compare_less_equal<T, false>
    {
        typedef compare_less_equal<T, true> other;

        template <typename T1, typename T2>
        inline bool operator()(T1 const& t1, T2 const& t2) const
        {
            return std::greater_equal<T>()(cast_to_result<T>::apply(t1),
                                           cast_to_result<T>::apply(t2));
        }
    };


    template <typename LessEqual>
    struct other_compare
    {
        typedef typename LessEqual::other type;
    };


    // it is assumed here that p0 lies to the right of the box (so the
    // entire segment lies to the right of the box)
    template <typename LessEqual>
    struct right_of_box
    {
        static inline ReturnType apply(SegmentPoint const& p0,
                                       SegmentPoint const& p1,
                                       BoxPoint const& bottom_right,
                                       BoxPoint const& top_right,
                                       SBStrategy const& sb_strategy)
        {
            boost::ignore_unused(sb_strategy);

            // the implementation below is written for non-negative slope
            // segments
            //
            // for negative slope segments swap the roles of bottom_right
            // and top_right and use greater_equal instead of less_equal.

            typedef cast_to_result<ReturnType> cast;

            LessEqual less_equal;

            typename SBStrategy::distance_ps_strategy::type ps_strategy =
                                sb_strategy.get_distance_ps_strategy();

            if (less_equal(geometry::get<1>(bottom_right), geometry::get<1>(p0)))
            {
                //if p0 is in box's band
                if (less_equal(geometry::get<1>(p0), geometry::get<1>(top_right)))
                {
                    // segment & crosses band (TODO:merge with box-box dist)
                    if (math::equals(geometry::get<0>(p0), geometry::get<0>(p1)))
                    {
                        SegmentPoint high = geometry::get<1>(p1) > geometry::get<1>(p0) ? p1 : p0;
                        if (less_equal(geometry::get<1>(high), geometry::get<1>(top_right)))
                        {
                            return cast::apply(ps_strategy.apply(high, bottom_right, top_right));
                        }
                        return cast::apply(ps_strategy.apply(top_right, p0, p1));
                    }
                    return cast::apply(ps_strategy.apply(p0, bottom_right, top_right));
                }
                // distance is realized between the top-right
                // corner of the box and the segment
                return cast::apply(ps_strategy.apply(top_right, p0, p1));
            }
            else
            {
                // distance is realized between the bottom-right
                // corner of the box and the segment
                return cast::apply(ps_strategy.apply(bottom_right, p0, p1));
            }
        }
    };

    // it is assumed here that p0 lies above the box (so the
    // entire segment lies above the box)

    template <typename LessEqual>
    struct above_of_box
    {

        static inline ReturnType apply(SegmentPoint const& p0,
                                       SegmentPoint const& p1,
                                       BoxPoint const& top_left,
                                       SBStrategy const& sb_strategy)
        {
            boost::ignore_unused(sb_strategy);
            return apply(p0, p1, p0, top_left, sb_strategy);
        }

        static inline ReturnType apply(SegmentPoint const& p0,
                                       SegmentPoint const& p1,
                                       SegmentPoint const& p_max,
                                       BoxPoint const& top_left,
                                       SBStrategy const& sb_strategy)
        {
            boost::ignore_unused(sb_strategy);
            typedef cast_to_result<ReturnType> cast;
            LessEqual less_equal;

            // p0 is above the upper segment of the box (and inside its band)
            // then compute the vertical (i.e. meridian for spherical) distance
            if (less_equal(geometry::get<0>(top_left), geometry::get<0>(p_max)))
            {
                ReturnType diff =
                sb_strategy.get_distance_ps_strategy().vertical_or_meridian(
                                    geometry::get_as_radian<1>(p_max),
                                    geometry::get_as_radian<1>(top_left));

                return strategy::distance::services::result_from_distance
                    <
                        SBStrategy, SegmentPoint, BoxPoint
                    >::apply(sb_strategy, math::abs(diff));
            }

            // p0 is to the left of the box, but p1 is above the box
            // in this case the distance is realized between the
            // top-left corner of the box and the segment
            return cast::apply(sb_strategy.get_distance_ps_strategy().
                                                      apply(top_left, p0, p1));
        }
    };

    template <typename LessEqual>
    struct check_right_left_of_box
    {
        static inline bool apply(SegmentPoint const& p0,
                                 SegmentPoint const& p1,
                                 BoxPoint const& top_left,
                                 BoxPoint const& top_right,
                                 BoxPoint const& bottom_left,
                                 BoxPoint const& bottom_right,
                                 SBStrategy const& sb_strategy,
                                 ReturnType& result)
        {
            // p0 lies to the right of the box
            if (geometry::get<0>(p0) >= geometry::get<0>(top_right))
            {
                result = right_of_box
                    <
                        LessEqual
                    >::apply(p0, p1, bottom_right, top_right,
                             sb_strategy);
                return true;
            }

            // p1 lies to the left of the box
            if (geometry::get<0>(p1) <= geometry::get<0>(bottom_left))
            {
                result = right_of_box
                    <
                        typename other_compare<LessEqual>::type
                    >::apply(p1, p0, top_left, bottom_left,
                             sb_strategy);
                return true;
            }

            return false;
        }
    };

    template <typename LessEqual>
    struct check_above_below_of_box
    {
        static inline bool apply(SegmentPoint const& p0,
                                 SegmentPoint const& p1,
                                 BoxPoint const& top_left,
                                 BoxPoint const& top_right,
                                 BoxPoint const& bottom_left,
                                 BoxPoint const& bottom_right,
                                 SBStrategy const& sb_strategy,
                                 ReturnType& result)
        {
            typedef compare_less_equal<ReturnType, false> GreaterEqual;

            // the segment lies below the box
            if (geometry::get<1>(p1) < geometry::get<1>(bottom_left))
            {
                result = sb_strategy.template segment_below_of_box
                        <
                            LessEqual,
                            ReturnType
                        >(p0, p1,
                          top_left, top_right,
                          bottom_left, bottom_right);
                return true;
            }

            // the segment lies above the box
            if (geometry::get<1>(p0) > geometry::get<1>(top_right))
            {
                result = (std::min)(above_of_box
                                    <
                                        LessEqual
                                    >::apply(p0, p1, top_left, sb_strategy),
                                    above_of_box
                                    <
                                        GreaterEqual
                                    >::apply(p1, p0, top_right, sb_strategy));
                return true;
            }
            return false;
        }
    };

    struct check_generic_position
    {
        static inline bool apply(SegmentPoint const& p0,
                                 SegmentPoint const& p1,
                                 BoxPoint const& corner1,
                                 BoxPoint const& corner2,
                                 SBStrategy const& sb_strategy,
                                 ReturnType& result)
        {
            typename SBStrategy::side_strategy_type
                side_strategy = sb_strategy.get_side_strategy();

            typedef cast_to_result<ReturnType> cast;
            ReturnType diff1 = cast::apply(geometry::get<1>(p1))
                               - cast::apply(geometry::get<1>(p0));

            typename SBStrategy::distance_ps_strategy::type ps_strategy =
                                sb_strategy.get_distance_ps_strategy();

            int sign = diff1 < 0 ? -1 : 1;
            if (side_strategy.apply(p0, p1, corner1) * sign < 0)
            {
                result = cast::apply(ps_strategy.apply(corner1, p0, p1));
                return true;
            }
            if (side_strategy.apply(p0, p1, corner2) * sign > 0)
            {
                result = cast::apply(ps_strategy.apply(corner2, p0, p1));
                return true;
            }
            return false;
        }
    };

    static inline ReturnType
    non_negative_slope_segment(SegmentPoint const& p0,
                               SegmentPoint const& p1,
                               BoxPoint const& top_left,
                               BoxPoint const& top_right,
                               BoxPoint const& bottom_left,
                               BoxPoint const& bottom_right,
                               SBStrategy const& sb_strategy)
    {
        typedef compare_less_equal<ReturnType, true> less_equal;

        // assert that the segment has non-negative slope
        BOOST_GEOMETRY_ASSERT( ( math::equals(geometry::get<0>(p0), geometry::get<0>(p1))
                              && geometry::get<1>(p0) < geometry::get<1>(p1))
                            ||
                               ( geometry::get<0>(p0) < geometry::get<0>(p1)
                              && geometry::get<1>(p0) <= geometry::get<1>(p1) )
                            || geometry::has_nan_coordinate(p0)
                            || geometry::has_nan_coordinate(p1));

        ReturnType result(0);

        if (check_right_left_of_box
                <
                    less_equal
                >::apply(p0, p1,
                         top_left, top_right, bottom_left, bottom_right,
                         sb_strategy, result))
        {
            return result;
        }

        if (check_above_below_of_box
                <
                    less_equal
                >::apply(p0, p1,
                         top_left, top_right, bottom_left, bottom_right,
                         sb_strategy, result))
        {
            return result;
        }

        if (check_generic_position::apply(p0, p1,
                                          top_left, bottom_right,
                                          sb_strategy, result))
        {
            return result;
        }

        // in all other cases the box and segment intersect, so return 0
        return result;
    }


    static inline ReturnType
    negative_slope_segment(SegmentPoint const& p0,
                           SegmentPoint const& p1,
                           BoxPoint const& top_left,
                           BoxPoint const& top_right,
                           BoxPoint const& bottom_left,
                           BoxPoint const& bottom_right,
                           SBStrategy const& sb_strategy)
    {
        typedef compare_less_equal<ReturnType, false> greater_equal;

        // assert that the segment has negative slope
        BOOST_GEOMETRY_ASSERT( ( geometry::get<0>(p0) < geometry::get<0>(p1)
                              && geometry::get<1>(p0) > geometry::get<1>(p1) )
                            || geometry::has_nan_coordinate(p0)
                            || geometry::has_nan_coordinate(p1) );

        ReturnType result(0);

        if (check_right_left_of_box
                <
                    greater_equal
                >::apply(p0, p1,
                         bottom_left, bottom_right, top_left, top_right,
                         sb_strategy, result))
        {
            return result;
        }

        if (check_above_below_of_box
                <
                    greater_equal
                >::apply(p1, p0,
                         top_right, top_left, bottom_right, bottom_left,
                         sb_strategy, result))
        {
            return result;
        }

        if (check_generic_position::apply(p0, p1,
                                          bottom_left, top_right,
                                          sb_strategy, result))
        {
            return result;
        }

        // in all other cases the box and segment intersect, so return 0
        return result;
    }

public:
    static inline ReturnType apply(SegmentPoint const& p0,
                                   SegmentPoint const& p1,
                                   BoxPoint const& top_left,
                                   BoxPoint const& top_right,
                                   BoxPoint const& bottom_left,
                                   BoxPoint const& bottom_right,
                                   SBStrategy const& sb_strategy)
    {
        BOOST_GEOMETRY_ASSERT( (geometry::less<SegmentPoint, -1, typename SBStrategy::cs_tag>()(p0, p1))
                            || geometry::has_nan_coordinate(p0)
                            || geometry::has_nan_coordinate(p1) );

        if (geometry::get<0>(p0) < geometry::get<0>(p1)
            && geometry::get<1>(p0) > geometry::get<1>(p1))
        {
            return negative_slope_segment(p0, p1,
                                          top_left, top_right,
                                          bottom_left, bottom_right,
                                          sb_strategy);
        }

        return non_negative_slope_segment(p0, p1,
                                          top_left, top_right,
                                          bottom_left, bottom_right,
                                          sb_strategy);
    }

    template <typename LessEqual>
    static inline ReturnType call_above_of_box(SegmentPoint const& p0,
                                               SegmentPoint const& p1,
                                               SegmentPoint const& p_max,
                                               BoxPoint const& top_left,
                                               SBStrategy const& sb_strategy)
    {
        return above_of_box<LessEqual>::apply(p0, p1, p_max, top_left, sb_strategy);
    }

    template <typename LessEqual>
    static inline ReturnType call_above_of_box(SegmentPoint const& p0,
                                               SegmentPoint const& p1,
                                               BoxPoint const& top_left,
                                               SBStrategy const& sb_strategy)
    {
        return above_of_box<LessEqual>::apply(p0, p1, top_left, sb_strategy);
    }
};

//=========================================================================

template
<
    typename Segment,
    typename Box,
    typename std::size_t Dimension,
    typename SBStrategy
>
class segment_to_box
    : not_implemented<Segment, Box>
{};


template
<
    typename Segment,
    typename Box,
    typename SBStrategy
>
class segment_to_box<Segment, Box, 2, SBStrategy>
{
private:
    typedef typename point_type<Segment>::type segment_point;
    typedef typename point_type<Box>::type box_point;

    typedef typename strategy::distance::services::comparable_type
        <
            SBStrategy
        >::type ps_comparable_strategy;

    typedef typename strategy::distance::services::return_type
        <
            ps_comparable_strategy, segment_point, box_point
        >::type comparable_return_type;
public:
    typedef typename strategy::distance::services::return_type
        <
            SBStrategy, segment_point, box_point
        >::type return_type;

    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    SBStrategy const& sb_strategy)
    {
        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        if (detail::equals::equals_point_point(p[0], p[1],
                sb_strategy.get_equals_point_point_strategy()))
        {
            typedef typename boost::mpl::if_
                <
                    boost::is_same
                        <
                            ps_comparable_strategy,
                            SBStrategy
                        >,
                    typename strategy::distance::services::comparable_type
                        <
                            typename SBStrategy::distance_pb_strategy::type
                        >::type,
                    typename SBStrategy::distance_pb_strategy::type
                >::type point_box_strategy_type;

            return dispatch::distance
                <
                    segment_point,
                    Box,
                    point_box_strategy_type
                >::apply(p[0], box, point_box_strategy_type());
        }

        box_point top_left, top_right, bottom_left, bottom_right;
        detail::assign_box_corners(box, bottom_left, bottom_right,
                                   top_left, top_right);

        SBStrategy::mirror(p[0], p[1],
                           bottom_left, bottom_right,
                           top_left, top_right);

        typedef geometry::less<segment_point, -1, typename SBStrategy::cs_tag> less_type;
        if (less_type()(p[0], p[1]))
        {
            return segment_to_box_2D
                <
                    return_type,
                    segment_point,
                    box_point,
                    SBStrategy
                >::apply(p[0], p[1],
                         top_left, top_right, bottom_left, bottom_right,
                         sb_strategy);
        }
        else
        {
            return segment_to_box_2D
                <
                    return_type,
                    segment_point,
                    box_point,
                    SBStrategy
                >::apply(p[1], p[0],
                         top_left, top_right, bottom_left, bottom_right,
                         sb_strategy);
        }
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename Box, typename Strategy>
struct distance
    <
        Segment, Box, Strategy, segment_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Segment>::type,
            typename point_type<Box>::type
        >::type return_type;


    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategy const& strategy)
    {
        assert_dimension_equal<Segment, Box>();

        return detail::distance::segment_to_box
            <
                Segment,
                Box,
                dimension<Segment>::value,
                Strategy
            >::apply(segment, box, strategy);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP

/* segment_to_box.hpp
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
*/