// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_OR_AREAL_TO_AREAL_HPP

#include <boost/geometry/algorithms/detail/distance/linear_to_linear.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear, typename Areal, typename Strategies>
struct linear_to_areal
{
    typedef distance::return_t<Linear, Areal, Strategies> return_type;

    static inline return_type apply(Linear const& linear,
                                    Areal const& areal,
                                    Strategies const& strategies)
    {
        if ( geometry::intersects(linear, areal, strategies) )
        {
            return return_type(0);
        }

        return linear_to_linear
            <
                Linear, Areal, Strategies
            >::apply(linear, areal, strategies, false);
    }


    static inline return_type apply(Areal const& areal,
                                    Linear const& linear,
                                    Strategies const& strategies)
    {
        return apply(linear, areal, strategies);
    }
};

template <typename Areal1, typename Areal2, typename Strategies>
struct areal_to_areal
{
    typedef distance::return_t<Areal1, Areal2, Strategies> return_type;

    static inline return_type apply(Areal1 const& areal1,
                                    Areal2 const& areal2,
                                    Strategies const& strategies)
    {
        if ( geometry::intersects(areal1, areal2, strategies) )
        {
            return return_type(0);
        }

        return linear_to_linear
            <
                Areal1, Areal2, Strategies
            >::apply(areal1, areal2, strategies, false);
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