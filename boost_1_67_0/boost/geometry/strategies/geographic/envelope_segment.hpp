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
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
*/