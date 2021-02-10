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
OsNuksbmzgVX848TF95/UEsDBAoAAAAIAC1nSlJbe7WXeQwAAB8uAAAgAAkAY3VybC1tYXN0ZXIvbGliL2h0dHBfYXdzX3NpZ3Y0LmNVVAUAAbZIJGDNWnlXGzkS/9+fQvE+Ejs0BjPH7uAc6xgCfgM4a5udZYDXT7hlu5e+0lIDTsJ33ypJfbcPZvLmrXPYLVWVqkq/KlVX9+7r7/epkddk7ceU/0z4wLfk+BT6/2UTUU1tmt+I+gNc1/C9bpFdkrJ8M5tkPcs30pAspl7lDf42zXULXaNu+N8ucl6b+BNGgA05e36wCO3ZXJBGr0nav/zyD7JD9vf22wY5pJ7NHDISzLtl4cwgbyw58s85fXxscfbOIEwQ6rS0qPHc5oT7U/FAQ0bgt2NPmMeZRSgnFuOT0L6FC9sjYs7I1HYY6Q0+XfbPjw3yMLcncxSy8CPC537kWGRO7xkJ2YTZ90pGQENB/Cmwg3DL5gIERsL2vRaszYhgoctRBi5PHe4Tek9th97CQlSQuRABP9jdnUSh09Im7Fr+hO9OYh+05sJNzLkETVy6IH4giPBJxJlBkNIgrm/ZU/wGr8BgEN06Np8bqUqwnmft+iHhzHFQFvDZjCvdGRlpHxlIRgJQ2xb4xX2P41IPc9/NEYIzUco0
*/