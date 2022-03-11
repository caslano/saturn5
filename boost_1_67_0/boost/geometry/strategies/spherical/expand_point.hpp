// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_POINT_HPP

#include <cstddef>
#include <algorithm>
#include <functional>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/is_inverse_spheroidal_coordinates.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/strategies/expand.hpp>
#include <boost/geometry/strategies/cartesian/expand_point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// implementation for the spherical and geographic coordinate systems
template <std::size_t DimensionCount, bool IsEquatorial>
struct point_loop_on_spheroid
{
    template <typename Box, typename Point>
    static inline void apply(Box& box, Point const& point)
    {
        typedef typename point_type<Box>::type box_point_type;
        typedef typename coordinate_type<Box>::type box_coordinate_type;
        typedef typename geometry::detail::cs_angular_units<Box>::type units_type;

        typedef math::detail::constants_on_spheroid
            <
                box_coordinate_type,
                units_type
            > constants;

        // normalize input point and input box
        Point p_normalized;
        strategy::normalize::spherical_point::apply(point, p_normalized);

        // transform input point to be of the same type as the box point
        box_point_type box_point;
        geometry::detail::envelope::transform_units(p_normalized, box_point);

        if (is_inverse_spheroidal_coordinates(box))
        {
            geometry::set_from_radian<min_corner, 0>(box, geometry::get_as_radian<0>(p_normalized));
            geometry::set_from_radian<min_corner, 1>(box, geometry::get_as_radian<1>(p_normalized));
            geometry::set_from_radian<max_corner, 0>(box, geometry::get_as_radian<0>(p_normalized));
            geometry::set_from_radian<max_corner, 1>(box, geometry::get_as_radian<1>(p_normalized));

        } else {

            strategy::normalize::spherical_box::apply(box, box);

            box_coordinate_type p_lon = geometry::get<0>(box_point);
            box_coordinate_type p_lat = geometry::get<1>(box_point);

            typename coordinate_type<Box>::type
                    b_lon_min = geometry::get<min_corner, 0>(box),
                    b_lat_min = geometry::get<min_corner, 1>(box),
                    b_lon_max = geometry::get<max_corner, 0>(box),
                    b_lat_max = geometry::get<max_corner, 1>(box);

            if (math::is_latitude_pole<units_type, IsEquatorial>(p_lat))
            {
                // the point of expansion is the either the north or the
                // south pole; the only important coordinate here is the
                // pole's latitude, as the longitude can be anything;
                // we, thus, take into account the point's latitude only and return
                geometry::set<min_corner, 1>(box, (std::min)(p_lat, b_lat_min));
                geometry::set<max_corner, 1>(box, (std::max)(p_lat, b_lat_max));
                return;
            }

            if (math::equals(b_lat_min, b_lat_max)
                    && math::is_latitude_pole<units_type, IsEquatorial>(b_lat_min))
            {
                // the box degenerates to either the north or the south pole;
                // the only important coordinate here is the pole's latitude,
                // as the longitude can be anything;
                // we thus take into account the box's latitude only and return
                geometry::set<min_corner, 0>(box, p_lon);
                geometry::set<min_corner, 1>(box, (std::min)(p_lat, b_lat_min));
                geometry::set<max_corner, 0>(box, p_lon);
                geometry::set<max_corner, 1>(box, (std::max)(p_lat, b_lat_max));
                return;
            }

            // update latitudes
            b_lat_min = (std::min)(b_lat_min, p_lat);
            b_lat_max = (std::max)(b_lat_max, p_lat);

            // update longitudes
            if (math::smaller(p_lon, b_lon_min))
            {
                box_coordinate_type p_lon_shifted = p_lon + constants::period();

                if (math::larger(p_lon_shifted, b_lon_max))
                {
                    // here we could check using: ! math::larger(.., ..)
                    if (math::smaller(b_lon_min - p_lon, p_lon_shifted - b_lon_max))
                    {
                        b_lon_min = p_lon;
                    }
                    else
                    {
                        b_lon_max = p_lon_shifted;
                    }
                }
            }
            else if (math::larger(p_lon, b_lon_max))
            {
                // in this case, and since p_lon is normalized in the range
                // (-180, 180], we must have that b_lon_max <= 180
                if (b_lon_min < 0
                        && math::larger(p_lon - b_lon_max,
                                        constants::period() - p_lon + b_lon_min))
                {
                    b_lon_min = p_lon;
                    b_lon_max += constants::period();
                }
                else
                {
                    b_lon_max = p_lon;
                }
            }

            geometry::set<min_corner, 0>(box, b_lon_min);
            geometry::set<min_corner, 1>(box, b_lat_min);
            geometry::set<max_corner, 0>(box, b_lon_max);
            geometry::set<max_corner, 1>(box, b_lat_max);
        }

        point_loop
            <
                2, DimensionCount
            >::apply(box, point);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct spherical_point
{
    template <typename Box, typename Point>
    static void apply(Box & box, Point const& point)
    {
        expand::detail::point_loop_on_spheroid
            <
                dimension<Point>::value,
                ! boost::is_same<typename cs_tag<Point>::type, spherical_polar_tag>::value
            >::apply(box, point);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, spherical_equatorial_tag, CalculationType>
{
    typedef spherical_point type;
};

template <typename CalculationType>
struct default_strategy<point_tag, spherical_polar_tag, CalculationType>
{
    typedef spherical_point type;
};

template <typename CalculationType>
struct default_strategy<point_tag, geographic_tag, CalculationType>
{
    typedef spherical_point type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_POINT_HPP

/* expand_point.hpp
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
*/