// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/envelope_point.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>
#include <boost/geometry/strategies/envelope.hpp>

namespace boost { namespace geometry { namespace strategy { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_segment
{
    template<typename Point, typename Box>
    static inline void apply(Point const& p1,
                             Point const& p2,
                             Box& mbr)
    {
        geometry::detail::envelope::envelope_one_point
            <
                Dimension, DimensionCount
            >::apply(p1, mbr);

        strategy::expand::detail::point_loop
            <
                Dimension, DimensionCount
            >::apply(mbr, p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class cartesian_segment
{
public:
    template <typename Point, typename Box>
    static inline void apply(Point const& point1, Point const& point2, Box& box)
    {
        strategy::envelope::detail::envelope_one_segment
            <
                0,
                dimension<Point>::value
            >::apply(point1, point2, box);        
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_segment<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
KY0FOSzgvQ/3nYrLQBIa2zPviuuEy2mH463C3H3UGJEPUX9doHgfdX4oe0jqsCeul87ZQzrPPUeScz2n/D+EvEw893htuVDzg5l5v85dHy+e1y87e917hOp1AMuEvEXg+WLTDQ3DhtyvqX1aFxuiocv7j+uP580ghNUHkUDk2zSuzRjJdeGxC9nnx+M0Y1rm4Z2arjdzyMoA3FuCrMLN7Il9ch7UfIayPegq9v9/gPMSi3j/
*/