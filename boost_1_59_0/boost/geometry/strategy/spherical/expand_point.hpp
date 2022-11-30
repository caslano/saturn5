// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_POINT_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <type_traits>

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

#include <boost/geometry/strategy/expand.hpp>
#include <boost/geometry/strategy/cartesian/expand_point.hpp>


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
                ! std::is_same<typename cs_tag<Point>::type, spherical_polar_tag>::value
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

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_EXPAND_POINT_HPP

/* expand_point.hpp
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
*/