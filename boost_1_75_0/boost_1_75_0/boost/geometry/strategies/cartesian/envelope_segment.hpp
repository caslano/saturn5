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
sXBqy2bjz55gp4Edo0fR/NrgJ1HTIIR3fm37mjq5WNAEPYBSyHvR55V+f3tFpPc+UO2wQOSuTu9CoDAlHdMze+zKTUTiO/m0JU9/hAzODf1NdoaHnS1yTvZzhZXrYe7cKzmF9ZeGLX5EwQtFARPfkywhVE2jOr7Ju3n61Ag5GZv5KIh9drxb7+HwqQ67ls1ZdCbsiLNe6qSN/tjC5qXUvFtjQqnX2giA+oNvbnT3b/GZGsYMzVBDxjCbKp0LsQh7Ov7CCMu2bsp4MbwPcxB7qmE19tcZYcDcGQEpwONW5aZxbvT91ypOZs2lRAnqlLmpmwdPhKcBBGhD7fXyItFpsJZgcWFBTS8gsnXfSWZKbM7bzrBbD4crQM1cTPenUI2CfBfxe/eNb+VCKZtVUTMBCz3UnaKfXUYn5JnM5OQJmnxOgcs9HmcGEld7/fHGjksRE1E8mT/kX8CkppFuaLqFSw2mV87f31oVUZvSW3QE38ZlA4yB7l/uJwVqurIXZvb2AAFyUzqPNso0THW5fME6PPZlmntTfsLnM18D+KHZ2klcJUHB3bwhhTH48NQuI7OYNgmP3j1JC9qQAV/j976iG8r4j+z5Jefin3QrtmNwW1KjWzw+bRq9BdQovcsDQNmasnAC2JMMWVIiRVi2zsbCOV+2JaHx8ZoNHyFEP0EtdQTV1uSwevLZA2/8uzdZxotnC9dUySoGDieMEuQq
*/