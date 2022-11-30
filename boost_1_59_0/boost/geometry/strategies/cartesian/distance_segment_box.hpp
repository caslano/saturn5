// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_SEGMENT_BOX_HPP

#include <boost/geometry/algorithms/detail/distance/segment_to_box.hpp>

#include <boost/geometry/strategies/cartesian/distance_projected_point.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras_point_box.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace distance
{

template
<
    typename CalculationType = void,
    typename Strategy = pythagoras<CalculationType>
>
struct cartesian_segment_box
{
    template <typename PointOfSegment, typename PointOfBox>
    struct calculation_type
        : promote_floating_point
          <
              typename strategy::distance::services::return_type
                  <
                      Strategy,
                      PointOfSegment,
                      PointOfBox
                  >::type
          >
    {};

    typedef cartesian_tag cs_tag;

    template
    <
        typename LessEqual, typename ReturnType,
        typename SegmentPoint, typename BoxPoint,
        typename Strategies
    >
    inline ReturnType segment_below_of_box(SegmentPoint const& p0,
                                           SegmentPoint const& p1,
                                           BoxPoint const&,
                                           BoxPoint const&,
                                           BoxPoint const&,
                                           BoxPoint const& bottom_right,
                                           Strategies const& strategies) const
    {
        // TODO: The strategy should not call the algorithm like that
        return geometry::detail::distance::segment_to_box_2D
            <
                ReturnType,
                SegmentPoint,
                BoxPoint,
                Strategies
            >::template call_above_of_box
                <
                    typename LessEqual::other
                >(p1, p0, bottom_right, strategies);
    }

    template <typename SPoint, typename BPoint>
    static void mirror(SPoint&,
                       SPoint&,
                       BPoint&,
                       BPoint&,
                       BPoint&,
                       BPoint&)
    {}
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<cartesian_segment_box<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_segment_box type;
};

template <typename CalculationType, typename Strategy, typename PS, typename PB>
struct return_type<cartesian_segment_box<CalculationType, Strategy>, PS, PB>
    : cartesian_segment_box<CalculationType, Strategy>::template calculation_type<PS, PB>
{};

template <typename CalculationType, typename Strategy>
struct comparable_type<cartesian_segment_box<CalculationType, Strategy> >
{
    // Define a cartesian_segment_box strategy with its underlying point-point
    // strategy being comparable
    typedef cartesian_segment_box
        <
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<cartesian_segment_box<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            cartesian_segment_box<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(cartesian_segment_box<CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};

template <typename CalculationType, typename Strategy, typename PS, typename PB>
struct result_from_distance<cartesian_segment_box<CalculationType, Strategy>, PS, PB>
{
private :
    typedef typename return_type<
                                    cartesian_segment_box
                                    <
                                        CalculationType,
                                        Strategy
                                    >,
                                    PS,
                                    PB
                                 >::type return_type;
public :
    template <typename T>
    static inline return_type apply(cartesian_segment_box<CalculationType,
                                                          Strategy> const& ,
                                    T const& value)
    {
        Strategy s;
        return result_from_distance<Strategy, PS, PB>::apply(s, value);
    }
};

template <typename Segment, typename Box>
struct default_strategy
    <
        segment_tag, box_tag, Segment, Box,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_segment_box<> type;
};

template <typename Box, typename Segment>
struct default_strategy
    <
        box_tag, segment_tag, Box, Segment,
        cartesian_tag, cartesian_tag
    >
{
    typedef typename default_strategy
        <
            segment_tag, box_tag, Segment, Box,
            cartesian_tag, cartesian_tag
        >::type type;
};

}
#endif

}} // namespace strategy::distance

}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_SEGMENT_BOX_HPP

/* distance_segment_box.hpp
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
*/