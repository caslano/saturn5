// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

#include <iterator>
#include <utility>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/iterators/has_one_element.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/closest_feature/range_to_range.hpp>
#include <boost/geometry/algorithms/detail/distance/is_comparable.hpp>
#include <boost/geometry/algorithms/detail/distance/iterator_selector.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template
<
    typename PointOrSegmentIterator,
    typename Geometry,
    typename Strategy
>
class point_or_segment_range_to_geometry_rtree
{
private:
    typedef typename std::iterator_traits
        <
            PointOrSegmentIterator
        >::value_type point_or_segment_type;

    typedef iterator_selector<Geometry const> selector_type;

    typedef detail::closest_feature::range_to_range_rtree range_to_range;

public:
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<point_or_segment_type>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(PointOrSegmentIterator first,
                                    PointOrSegmentIterator last,
                                    Geometry const& geometry,
                                    Strategy const& strategy)
    {
        namespace sds = strategy::distance::services;

        BOOST_GEOMETRY_ASSERT( first != last );

        if ( geometry::has_one_element(first, last) )
        {
            return dispatch::distance
                <
                    point_or_segment_type, Geometry, Strategy
                >::apply(*first, geometry, strategy);
        }

        typename sds::return_type
            <
                typename sds::comparable_type<Strategy>::type,
                typename point_type<point_or_segment_type>::type,
                typename point_type<Geometry>::type
            >::type cd_min;

        std::pair
            <
                point_or_segment_type,
                typename selector_type::iterator_type
            > closest_features
            = range_to_range::apply(first,
                                    last,
                                    selector_type::begin(geometry),
                                    selector_type::end(geometry),
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
                    point_or_segment_type,                    
                    typename std::iterator_traits
                        <
                            typename selector_type::iterator_type
                        >::value_type,
                    Strategy
                >::apply(closest_features.first,
                         *closest_features.second,
                         strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_RANGE_TO_GEOMETRY_RTREE_HPP

/* range_to_geometry_rtree.hpp
UH/V3I9uLvGGfsgAb7eIZYsQs0uw+U+/76bvzU0n6Y5y8PCE5xsieF7+bo0zIV7Aa3puPXzVE51wedny/GdaozNN1/YpzL0Om9PxysbAm5H4d5jriU/PjLzLrHA/kkaPOTOt4Ov/Y++8w+MorgB+lg023b1hHOMYhxIbSy4YMI5VTrZsNSTZ2I7hcjqdpMOS7nx3ki0ILZAQWgi9dwKhJvQaOoEQakLAEEIPLUAA0wk4v7nZ3ZndmZN15PvyF/rQYb33pr335rWZ3duKmha2MPYwvnI5NX5s9xnU9MZ8gL4Sr16N3HdDr35FX/v3YCtbxbk//hM7tB5+7ky8Npf4aedazqn25r7sKOz5es4Uv6Bm+BP8IvO5tQT/exh29HNszDJ8YRV77ef4y6+QGz73ucXU/YhZ3j4NPST+f+VdbEgZscbN2LxdqXUU4YOHsMePJ77/F3HWJ+R6+JkVxEGTsSOfriE24D74Nr/kPOtFbPE9xCPjiOG5i1CEn/tbFTq8I2t8kjiKuHPwdPT8OeLkW6jdPwmPsCEPXAyf0ZdZPyXfeBpfO4R10m/Djfjm3fDrRciDmHZ9KfMbx5qxA4tmcZdtJDYEO/La9dS2niVPfIKYgT0wgdx0+H/wtYeRo5zGHhtAnIQf7GKstx5nj6BrQ/DfT6LDI0+gRtNAvIKd25ta0X6vEmt0YVfJX1MfsueJG06fRn2bvXr0Q/h58tfN0JfQjcToJxFHsxd+WURceBu2ZWfs3mx4jU+ftBO+5zr84RB0+hFy5keJAaEfcwD5PXZ7d3T6+b3QReqNfxhDfvII+/5iZPMyuXGKOshG5Lkja+rAf6EvH1NDuQQ5PUef56PXq5/F53PuNepTYrijiAmgffxI6tLcCT/lT+Rn2Oc/XEM+9n1k2wyP/sEeQtf/NIpcfhlzYt8+mcAHPsde5hzw773Uqi9nP1HDIjUPTRvL/tgf39vLnf2rqIdvyZxa8I/M754V5I09+Cvs5B4fwvtOZM46TmGdF2Gvto5RY6vgfgUx91/PRfbY6s9vpc44HLu4FTIG33Qda9kPPnGH6F580EHsxTuRF2FFaC66t4fIxafic95hL93JfvkBesL58R2t6B38mID9+uFuxCMvcndkEvYauznuJ9xXJQ54pZY5tMFb9GkgtvEoZDnuOc64F7KmxcgUfX3qevR6Cf7lEXLsC+EV/mXfYtY+hf33Y+wkvq56KXua/L6VmKdkPn73SfKnOdizE7ETW5OPxIjtbsev34p/Q98POQzZEMtefgxyWUZ8eDxx+FhifuS70yTiyt9x/sXemr8vvuN2YrGprJ/4aF90r+R1YsC9yA1egdf40XnI8K5S5oddPfUOYssBxBEiXyEGXb6IsdGxC5H1/ejHxMXsn8noy66o5QHIYn/y5P/gpz4JUYvEfsyjDvw+tfMzyXsuwybNJUeaT92UO24HYH8/v45a0aHICf1+DXt7Hf7pHWCXbU9OxjiPPgbPzkVG92B7qW/ssxX6xl779yL2wjHoyIPkM/Di6z2wc9jbo0exx8lZfvoSPqsevmDTT8H2X3Av59zo+WR4cdHJ7BPs+/cOoj5PTDEAmzKGPfok+6zoCfiEH9/hCH6Jxw4ajz6xx9Ioxw5V1EyoNW0owqedTo3gPPbqP7D7k4nXnsEeHQc/fs16tyCW2RZbeA+2Djn8iTn8GR+7yyT2yUXUQ4hDh2aoCd8I3+n3ItbQdCe2Ch7tyHM+rTtS58ZOJgehp0cTJxDPTD8AvWOBr3GWfARxfxvy/sUfiRnwx7dspDb0PHsD2/DFJNaJHxnwJbE49umwJ+AdNvoJ4uFybNOiv2FbsLVzsOsttzFmNTb3TXw=
*/