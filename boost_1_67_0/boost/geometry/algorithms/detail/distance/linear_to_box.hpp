// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/intersects.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{

template <typename Linear, typename Box, typename Strategy>
struct linear_to_box
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear>::type,
            typename point_type<Box>::type
        >::type return_type;

    template <typename Iterator>
    static inline return_type apply(Box const& box,
                                    Iterator begin,
                                    Iterator end,
                                    Strategy const& strategy)
    {
        bool first = true;
        return_type d_min(0);
        for (Iterator it = begin; it != end; ++it, first = false)
        {
            typedef typename std::iterator_traits<Iterator>::value_type
                    Segment;

            return_type d = dispatch::distance<Segment, Box, Strategy>
                                    ::apply(*it, box, strategy);

            if ( first || d < d_min )
            {
                d_min = d;
            }
        }
        return d_min;
    }

    static inline return_type apply(Linear const& linear,
                                    Box const& box,
                                    Strategy const& strategy)
    {
        if ( geometry::intersects(linear, box) )
        {
            return 0;
        }

        return apply(box,
                     geometry::segments_begin(linear),
                     geometry::segments_end(linear),
                     strategy);
    }


    static inline return_type apply(Box const& box,
                                    Linear const& linear,
                                    Strategy const& strategy)
    {
        return apply(linear, box, strategy);
    }
};

}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear, typename Box, typename Strategy>
struct distance
    <
        Linear, Box, Strategy,
        linear_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
    : detail::distance::linear_to_box
        <
            Linear, Box, Strategy
        >
{};


template <typename Areal, typename Box, typename Strategy>
struct distance
    <
        Areal, Box, Strategy,
        areal_tag, box_tag,
        strategy_tag_distance_segment_box, false
    >
    : detail::distance::linear_to_box
        <
            Areal, Box, Strategy
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP

/* linear_to_box.hpp
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
*/