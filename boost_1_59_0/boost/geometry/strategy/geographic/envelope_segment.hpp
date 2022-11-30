// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategy/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategy/envelope.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategy/spherical/envelope_segment.hpp>
#include <boost/geometry/strategy/spherical/expand_box.hpp>

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

    Spheroid model() const
    {
        return m_spheroid;
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

#endif // BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_SEGMENT_HPP

/* envelope_segment.hpp
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
*/