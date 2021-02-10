// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/envelope.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_segment
{
public:
    typedef Spheroid model_type;

    inline geographic_segment()
        : m_spheroid()
    {}

    explicit inline geographic_segment(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    typedef strategy::expand::spherical_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

    template <typename Point, typename Box>
    inline void apply(Point const& point1, Point const& point2, Box& box) const
    {
        Point p1_normalized, p2_normalized;
        strategy::normalize::spherical_point::apply(point1, p1_normalized);
        strategy::normalize::spherical_point::apply(point2, p2_normalized);

        geometry::strategy::azimuth::geographic
            <
                FormulaPolicy,
                Spheroid,
                CalculationType
            > azimuth_geographic(m_spheroid);

        typedef typename geometry::detail::cs_angular_units
            <
                Point
            >::type units_type;

        // first compute the envelope range for the first two coordinates
        strategy::envelope::detail::envelope_segment_impl
            <
                geographic_tag
            >::template apply<units_type>(geometry::get<0>(p1_normalized),
                                          geometry::get<1>(p1_normalized),
                                          geometry::get<0>(p2_normalized),
                                          geometry::get<1>(p2_normalized),
                                          box,
                                          azimuth_geographic);

        // now compute the envelope range for coordinates of
        // dimension 2 and higher
        strategy::envelope::detail::envelope_one_segment
            <
                2, dimension<Point>::value
            >::apply(point1, point2, box);
    }

private:
    Spheroid m_spheroid;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, geographic_tag, CalculationType>
{
    typedef strategy::envelope::geographic_segment
        <
            strategy::andoyer,
            srs::spheroid<double>,
            CalculationType
        > type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
YAxPC9BO5X8JDGw6KXPLZkMQ7dehG9+Wf1L+7pNxzdXP250eeXeWkkqOZ6guUC2UC+eddq+9sKoeWJQAt6s2dqaud6MwxArnyuj6avwEYH+7aHQ+JZU855K0DdRGdu/uHFMOPi0++sqSjcS2etMF1Sd5OHAidvjRdBI4n9Aopl8o78RFJNHdGSItrtwRqvdq3BMYcz92PUGmH5gjYLxhPaVjgQWjHbY1dCj4CIwAbicAtZ8ogciI3sdlWKKzmfRYrHFV1/6d6t2giuO3mkZQq+QjdzzuJ4ToT0m/pZWQVHuQ/hUCtn3E1H37NmfxV8WPote5aIgDcVo/6zYO1xTsykZaVVkJ1UNlBR4H0xk6lkdhMNtGXYlqqBmcIAPN04KETzw5jjUuvNbynCPgDNcdV4y6b8ReldYuahBfbMMbWOcdGGr6dhmISaBbFcDzrje2m1g/TtckDWG9ekjFwTCahz4NT6PfBuO7zl4aMEVPwBbFQt8UVowjIEMV1VggbXl0qibaz8SrPUB8V4CNu8ctKZS0OQUVc4SFagrs4ZruMs4SEJHb7ABTTaBhHQex4+le6+dv8wDqYNKjWRVKZgZnDMa5eAXLNUygUaQhKGQSQxE7BgpTVUHefaUguglx06JvxH51LZE6zlXggu3i
*/