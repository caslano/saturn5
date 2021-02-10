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
9uiIAuoprtO4sTwq0B6hizqK5nNtzpsGieFo2v81Q2VgM3EwGUEPlMaIsCSAyqDf72PWB9ButZ402tU6UVnYGBiZYsU2lSoGRfqUfrDmNtKUtZgslOI+w29DHIZIGkRcybJGuBD4RqMBMOGGyWXler1uRDGXiyRCP6Jk0YxkKCTHDFPNVuv05PTZk9PTplOpmrkhJnNRlIFpDpXJ4HN/dO713o0vvNH5uTeFl5CdXYyGr6ulBwBiHvA5vOm+73uT6Xg6urigU8AqnaNOcMA5B+glDxW3RKjE0gUV73LS8973x1V4+BDyJ3h5Bu0nrVZ2OhhO+6/H3QvvsvvR+30wndD7k6dVK21X3gTJUMJkMBpWS9vu2lty/9pLMMaJxKbcG08Hl1fYQIXUJ0/x2w+4H4JnMTl5WintdEBvIL2vHsZHKg3+kiVQ8yaY/nJR3yMcpdrDokcVrzDicy+OlDashqnm9WVwpZO6kYhR1uCNWSA21Y7zxaBUsPs+Q++36eeffcMO2iSxZ7mH/QjnpliCbZRz0qvx4H13miUKJhS0M1InNvvhWA/nEL43ZJSjlHv7Uqk+YczkgrqZ0goLSMKMUzkFMMfuwsJ4yWS6Qvk+NmG5oLwh95mP7U+Zpk9och9Hwg03KIbi2hRjd9Ib
*/