// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2018-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_BOX_HPP

#include <iterator>

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/core/point_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{

template <typename Linear, typename Box, typename Strategies>
struct linear_to_box
{
    typedef distance::return_t<Linear, Box, Strategies> return_type;

    template <typename Iterator>
    static inline return_type apply(Box const& box,
                                    Iterator begin,
                                    Iterator end,
                                    Strategies const& strategies)
    {
        bool first = true;
        return_type d_min(0);
        for (Iterator it = begin; it != end; ++it, first = false)
        {
            typedef typename std::iterator_traits<Iterator>::value_type
                    Segment;

            return_type d = dispatch::distance<Segment, Box, Strategies>
                                    ::apply(*it, box, strategies);

            if ( first || d < d_min )
            {
                d_min = d;
            }
        }
        return d_min;
    }

    static inline return_type apply(Linear const& linear,
                                    Box const& box,
                                    Strategies const& strategies)
    {
        if ( geometry::intersects(linear, box) )
        {
            return return_type(0);
        }

        return apply(box,
                     geometry::segments_begin(linear),
                     geometry::segments_end(linear),
                     strategies);
    }


    static inline return_type apply(Box const& box,
                                    Linear const& linear,
                                    Strategies const& strategies)
    {
        return apply(linear, box, strategies);
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