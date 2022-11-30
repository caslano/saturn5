// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP

#include <cstddef>
#include <functional>
#include <type_traits>
#include <vector>

#include <boost/core/ignore_unused.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/closest_feature/point_to_range.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

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


template <typename Segment, typename Box, typename Strategy>
inline bool intersects_segment_box(Segment const& segment, Box const& box,
                                   Strategy const& strategy)
{
    return ! detail::disjoint::disjoint_segment_box::apply(segment, box, strategy);
}

// TODO: segment_to_box_2D_generic is not used anymore. Remove?

// TODO: Furthermore this utility can potentially use different strategy than
//       the one that was passed into bg::distance() but it seems this is by design.

template
<
    typename Segment,
    typename Box,
    typename Strategies,
    bool UsePointBoxStrategy = false // use only PointSegment strategy
>
class segment_to_box_2D_generic
{
private:
    typedef typename point_type<Segment>::type segment_point;
    typedef typename point_type<Box>::type box_point;

    typedef distance::strategy_t<box_point, Segment, Strategies> ps_strategy_type;

    typedef detail::closest_feature::point_to_point_range
        <
            segment_point,
            std::vector<box_point>,
            open
        > point_to_point_range;
    
public:
    // TODO: Or should the return type be defined by sb_strategy_type?
    typedef distance::return_t<box_point, Segment, Strategies> return_type;

    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategies const& strategies,
                                    bool check_intersection = true)
    {
        if (check_intersection && intersects_segment_box(segment, box, strategies))
        {
            return return_type(0);
        }

        // get segment points
        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        // get box points
        std::vector<box_point> box_points(4);
        detail::assign_box_corners_oriented<true>(box, box_points);
 
        ps_strategy_type const strategy = strategies.distance(dummy_point(), dummy_segment());

        auto const cstrategy = strategy::distance::services::get_comparable
                                <
                                    ps_strategy_type
                                >::apply(strategy);

        distance::creturn_t<box_point, Segment, Strategies> cd[6];
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

        if (BOOST_GEOMETRY_CONDITION(is_comparable<ps_strategy_type>::value))
        {
            return cd[imin];
        }

        if (imin < 4)
        {
            return strategy.apply(box_points[imin], p[0], p[1]);
        }
        else
        {
            unsigned int bimin = imin - 4;
            return strategy.apply(p[bimin],
                                  *bit_min[bimin].first,
                                  *bit_min[bimin].second);
        }
    }
};


template
<
    typename Segment,
    typename Box,
    typename Strategies
>
class segment_to_box_2D_generic<Segment, Box, Strategies, true> // Use both PointSegment and PointBox strategies
{
private:
    typedef typename point_type<Segment>::type segment_point;
    typedef typename point_type<Box>::type box_point;

    typedef distance::strategy_t<box_point, Segment, Strategies> ps_strategy_type;
    typedef distance::strategy_t<segment_point, Box, Strategies> pb_strategy_type;

public:
    // TODO: Or should the return type be defined by sb_strategy_type?
    typedef distance::return_t<box_point, Segment, Strategies> return_type;
    
    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategies const& strategies,
                                    bool check_intersection = true)
    {
        if (check_intersection && intersects_segment_box(segment, box, strategies))
        {
            return return_type(0);
        }

        // get segment points
        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        // get box points
        std::vector<box_point> box_points(4);
        detail::assign_box_corners_oriented<true>(box, box_points);

        distance::creturn_t<box_point, Segment, Strategies> cd[6];

        ps_strategy_type ps_strategy = strategies.distance(dummy_point(), dummy_segment());
        auto const ps_cstrategy = strategy::distance::services::get_comparable
                                    <
                                        ps_strategy_type
                                    >::apply(ps_strategy);
        boost::ignore_unused(ps_strategy, ps_cstrategy);

        for (unsigned int i = 0; i < 4; ++i)
        {
            cd[i] = ps_cstrategy.apply(box_points[i], p[0], p[1]);
        }

        pb_strategy_type const pb_strategy = strategies.distance(dummy_point(), dummy_box());
        auto const pb_cstrategy = strategy::distance::services::get_comparable
                                    <
                                        pb_strategy_type
                                    >::apply(pb_strategy);
        boost::ignore_unused(pb_strategy, pb_cstrategy);

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

        if (imin < 4)
        {
            if (is_comparable<ps_strategy_type>::value)
            {
                return cd[imin];
            }

            return ps_strategy.apply(box_points[imin], p[0], p[1]);
        }
        else
        {
            if (is_comparable<pb_strategy_type>::value)
            {
                return cd[imin];
            }

            return pb_strategy.apply(p[imin - 4], box);
        }
    }
};




template
<
    typename ReturnType,
    typename SegmentPoint,
    typename BoxPoint,
    typename Strategies
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
                                       Strategies const& strategies)
        {
            // the implementation below is written for non-negative slope
            // segments
            //
            // for negative slope segments swap the roles of bottom_right
            // and top_right and use greater_equal instead of less_equal.

            typedef cast_to_result<ReturnType> cast;

            LessEqual less_equal;

            auto const ps_strategy = strategies.distance(dummy_point(), dummy_segment());

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
                                       Strategies const& strategies)
        {
            return apply(p0, p1, p0, top_left, strategies);
        }

        static inline ReturnType apply(SegmentPoint const& p0,
                                       SegmentPoint const& p1,
                                       SegmentPoint const& p_max,
                                       BoxPoint const& top_left,
                                       Strategies const& strategies)
        {
            auto const ps_strategy = strategies.distance(dummy_point(), dummy_segment());

            typedef cast_to_result<ReturnType> cast;
            LessEqual less_equal;

            // p0 is above the upper segment of the box (and inside its band)
            // then compute the vertical (i.e. meridian for spherical) distance
            if (less_equal(geometry::get<0>(top_left), geometry::get<0>(p_max)))
            {
                ReturnType diff = ps_strategy.vertical_or_meridian(
                                    geometry::get_as_radian<1>(p_max),
                                    geometry::get_as_radian<1>(top_left));

                return strategy::distance::services::result_from_distance
                    <
                        std::remove_const_t<decltype(ps_strategy)>,
                        SegmentPoint, BoxPoint
                    >::apply(ps_strategy, math::abs(diff));
            }

            // p0 is to the left of the box, but p1 is above the box
            // in this case the distance is realized between the
            // top-left corner of the box and the segment
            return cast::apply(ps_strategy.apply(top_left, p0, p1));
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
                                 Strategies const& strategies,
                                 ReturnType& result)
        {
            // p0 lies to the right of the box
            if (geometry::get<0>(p0) >= geometry::get<0>(top_right))
            {
                result = right_of_box
                    <
                        LessEqual
                    >::apply(p0, p1, bottom_right, top_right,
                             strategies);
                return true;
            }

            // p1 lies to the left of the box
            if (geometry::get<0>(p1) <= geometry::get<0>(bottom_left))
            {
                result = right_of_box
                    <
                        typename other_compare<LessEqual>::type
                    >::apply(p1, p0, top_left, bottom_left,
                             strategies);
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
                                 Strategies const& strategies,
                                 ReturnType& result)
        {
            typedef compare_less_equal<ReturnType, false> GreaterEqual;

            // the segment lies below the box
            if (geometry::get<1>(p1) < geometry::get<1>(bottom_left))
            {
                auto const sb_strategy = strategies.distance(dummy_segment(), dummy_box());

                // TODO: this strategy calls this algorithm's again, specifically:
                //       geometry::detail::distance::segment_to_box_2D<>::call_above_of_box
                //       If possible rewrite them to avoid this.
                //       For now just pass umbrella strategy.
                result = sb_strategy.template segment_below_of_box
                        <
                            LessEqual,
                            ReturnType
                        >(p0, p1,
                          top_left, top_right,
                          bottom_left, bottom_right,
                          strategies);
                return true;
            }

            // the segment lies above the box
            if (geometry::get<1>(p0) > geometry::get<1>(top_right))
            {
                result = (std::min)(above_of_box
                                    <
                                        LessEqual
                                    >::apply(p0, p1, top_left, strategies),
                                    above_of_box
                                    <
                                        GreaterEqual
                                    >::apply(p1, p0, top_right, strategies));
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
                                 Strategies const& strategies,
                                 ReturnType& result)
        {
            auto const side_strategy = strategies.side();
            auto const ps_strategy = strategies.distance(dummy_point(), dummy_segment());

            typedef cast_to_result<ReturnType> cast;
            ReturnType diff1 = cast::apply(geometry::get<1>(p1))
                               - cast::apply(geometry::get<1>(p0));

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
                               Strategies const& strategies)
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
                         strategies, result))
        {
            return result;
        }

        if (check_above_below_of_box
                <
                    less_equal
                >::apply(p0, p1,
                         top_left, top_right, bottom_left, bottom_right,
                         strategies, result))
        {
            return result;
        }

        if (check_generic_position::apply(p0, p1,
                                          top_left, bottom_right,
                                          strategies, result))
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
                           Strategies const& strategies)
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
                         strategies, result))
        {
            return result;
        }

        if (check_above_below_of_box
                <
                    greater_equal
                >::apply(p1, p0,
                         top_right, top_left, bottom_right, bottom_left,
                         strategies, result))
        {
            return result;
        }

        if (check_generic_position::apply(p0, p1,
                                          bottom_left, top_right,
                                          strategies, result))
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
                                   Strategies const& strategies)
    {
        BOOST_GEOMETRY_ASSERT( (geometry::less<SegmentPoint, -1, typename Strategies::cs_tag>()(p0, p1))
                            || geometry::has_nan_coordinate(p0)
                            || geometry::has_nan_coordinate(p1) );

        if (geometry::get<0>(p0) < geometry::get<0>(p1)
            && geometry::get<1>(p0) > geometry::get<1>(p1))
        {
            return negative_slope_segment(p0, p1,
                                          top_left, top_right,
                                          bottom_left, bottom_right,
                                          strategies);
        }

        return non_negative_slope_segment(p0, p1,
                                          top_left, top_right,
                                          bottom_left, bottom_right,
                                          strategies);
    }

    template <typename LessEqual>
    static inline ReturnType call_above_of_box(SegmentPoint const& p0,
                                               SegmentPoint const& p1,
                                               SegmentPoint const& p_max,
                                               BoxPoint const& top_left,
                                               Strategies const& strategies)
    {
        return above_of_box<LessEqual>::apply(p0, p1, p_max, top_left, strategies);
    }

    template <typename LessEqual>
    static inline ReturnType call_above_of_box(SegmentPoint const& p0,
                                               SegmentPoint const& p1,
                                               BoxPoint const& top_left,
                                               Strategies const& strategies)
    {
        return above_of_box<LessEqual>::apply(p0, p1, top_left, strategies);
    }
};

//=========================================================================

template
<
    typename Segment,
    typename Box,
    typename std::size_t Dimension,
    typename Strategies
>
class segment_to_box
    : not_implemented<Segment, Box>
{};


template
<
    typename Segment,
    typename Box,
    typename Strategies
>
class segment_to_box<Segment, Box, 2, Strategies>
{
    typedef distance::strategy_t<Segment, Box, Strategies> strategy_type;

public:
    typedef distance::return_t<Segment, Box, Strategies> return_type;

    static inline return_type apply(Segment const& segment,
                                    Box const& box,
                                    Strategies const& strategies)
    {
        typedef typename point_type<Segment>::type segment_point;
        typedef typename point_type<Box>::type box_point;

        segment_point p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        if (detail::equals::equals_point_point(p[0], p[1], strategies))
        {
            return dispatch::distance
                <
                    segment_point,
                    Box,
                    Strategies
                >::apply(p[0], box, strategies);
        }

        box_point top_left, top_right, bottom_left, bottom_right;
        detail::assign_box_corners(box, bottom_left, bottom_right,
                                   top_left, top_right);

        strategy_type::mirror(p[0], p[1],
                              bottom_left, bottom_right,
                              top_left, top_right);

        typedef geometry::less<segment_point, -1, typename Strategies::cs_tag> less_type;
        if (less_type()(p[0], p[1]))
        {
            return segment_to_box_2D
                <
                    return_type,
                    segment_point,
                    box_point,
                    Strategies
                >::apply(p[0], p[1],
                         top_left, top_right, bottom_left, bottom_right,
                         strategies);
        }
        else
        {
            return segment_to_box_2D
                <
                    return_type,
                    segment_point,
                    box_point,
                    Strategies
                >::apply(p[1], p[0],
                         top_left, top_right, bottom_left, bottom_right,
                         strategies);
        }
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename Box, typename Strategies>
struct distance
    <
        Segment, Box, Strategies, segment_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
{
    static inline auto apply(Segment const& segment, Box const& box,
                             Strategies const& strategies)
    {
        assert_dimension_equal<Segment, Box>();

        return detail::distance::segment_to_box
            <
                Segment,
                Box,
                dimension<Segment>::value,
                Strategies
            >::apply(segment, box, strategies);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_SEGMENT_TO_BOX_HPP

/* segment_to_box.hpp
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
*/