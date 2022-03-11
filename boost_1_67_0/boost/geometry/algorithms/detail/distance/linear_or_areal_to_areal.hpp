// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/algorithms/detail/distance/linear_to_linear.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear, typename Areal, typename Strategy>
struct linear_to_areal
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear>::type,
            typename point_type<Areal>::type
        >::type return_type;

    static inline return_type apply(Linear const& linear,
                                    Areal const& areal,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(linear, areal,
                                  strategy.get_relate_segment_segment_strategy()) )
        {
            return 0;
        }

        return linear_to_linear
            <
                Linear, Areal, Strategy
            >::apply(linear, areal, strategy, false);
    }


    static inline return_type apply(Areal const& areal,
                                    Linear const& linear,
                                    Strategy const& strategy)
    {
        return apply(linear, areal, strategy);
    }
};

template <typename Areal1, typename Areal2, typename Strategy>
struct areal_to_areal
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Areal1>::type,
            typename point_type<Areal2>::type
        >::type return_type;

    static inline return_type apply(Areal1 const& areal1,
                                    Areal2 const& areal2,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(areal1, areal2,
                                  strategy.get_relate_segment_segment_strategy()) )
        {
            return 0;
        }

        return linear_to_linear
            <
                Areal1, Areal2, Strategy
            >::apply(areal1, areal2, strategy, false);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear, typename Areal, typename Strategy>
struct distance
    <
        Linear, Areal, Strategy,
        linear_tag, areal_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::linear_to_areal
        <
            Linear, Areal, Strategy
        >
{};

template <typename Areal, typename Linear, typename Strategy>
struct distance
    <
        Areal, Linear, Strategy,
        areal_tag, linear_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::linear_to_areal
        <
            Linear, Areal, Strategy
        >
{};


template <typename Areal1, typename Areal2, typename Strategy>
struct distance
    <
        Areal1, Areal2, Strategy,
        areal_tag, areal_tag, 
        strategy_tag_distance_point_segment, false
    >
    : detail::distance::areal_to_areal
        <
            Areal1, Areal2, Strategy
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP

/* linear_or_areal_to_areal.hpp
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
*/