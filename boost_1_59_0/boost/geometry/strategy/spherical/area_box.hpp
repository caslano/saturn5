// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_BOX_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_BOX_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>
#include <boost/geometry/strategy/area.hpp>
#include <boost/geometry/util/normalize_spheroidal_box_coordinates.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace area
{

// https://math.stackexchange.com/questions/131735/surface-element-in-spherical-coordinates
// http://www.cs.cmu.edu/afs/cs/academic/class/16823-s16/www/pdfs/appearance-modeling-3.pdf
// https://www.astronomyclub.xyz/celestial-sphere-2/solid-angle-on-the-celestial-sphere.html
// https://mathworld.wolfram.com/SolidAngle.html
// https://en.wikipedia.org/wiki/Spherical_coordinate_system
// Note that the equations used in the above articles are spherical polar coordinates.
// We use spherical equatorial, so the equation is different:
// assume(y_max > y_min);
// assume(x_max > x_min);
// /* because of polar to equatorial conversion */
// sin(%pi / 2 - y);
// O: r ^ 2 * cos(y);
// S: integrate(integrate(O, y, y_min, y_max), x, x_min, x_max);
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical_box
{
    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

public:
    template <typename Box>
    struct result_type
        : strategy::area::detail::result_type
            <
                Box,
                CalculationType
            >
    {};

    // For consistency with other strategies the radius is set to 1
    inline spherical_box()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit inline spherical_box(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}
    
    template <typename Box>
    inline auto apply(Box const& box) const
    {
        typedef typename result_type<Box>::type return_type;

        return_type x_min = get_as_radian<min_corner, 0>(box); // lon
        return_type y_min = get_as_radian<min_corner, 1>(box); // lat
        return_type x_max = get_as_radian<max_corner, 0>(box);
        return_type y_max = get_as_radian<max_corner, 1>(box);

        if (x_min == x_max || y_max == y_min)
        {
            return return_type(0);
        }

        math::normalize_spheroidal_box_coordinates<radian>(x_min, y_min, x_max, y_max);

        return (x_max - x_min)
             * (sin(y_max) - sin(y_min))
             * return_type(m_radius * m_radius);
    }

    srs::sphere<radius_type> model() const
    {
        return srs::sphere<radius_type>(m_radius);
    }

private:
    radius_type m_radius;
};


}} // namespace strategy::area


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_BOX_HPP

/* area_box.hpp
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
*/