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
BmEYNsbOGI5dcAh2w/vxbszA7rgYe+BS7CnxVSkh7z/yXkR8+vt2OTmvLsrz0WWsir9jC7yCHfBPnIL/xhz0YL0vgiduRS88gmXwMt6KpUqwfiyP5dEfb8MO6IPd0Q8Hoz9Owoo4FSvjIqyCa7EqfoQBeAZrYknt2sBqGIRtsA6GY31MxAb4CDaV49IcX8MWuAZDsKVX4WNCBtwcF/K61CMrbh2y/+X6YzfHhfzrdcb+Sn2x611X7D06x8gnXCEExVKXi5BJWEzYTDhGKMNDfkvCyLib9bWu9e+Glv9Hj75u5f+9SaGMJ6aev5oQKhLqE37Xyv+H6ffU6OQkyh2T7P2PR8Q+UGi/XvKbt6NPaZffvEeb+tFdLnHXk7hrEf4k7mzruCNCPQofs60o8Tu2PVBO9QYSf5Bse55V/GMK79OsKHHLttN3k+W2kzFYxn3dtr2TxO/vNGaeL6Eu4d/EH2wVf0JqxKTYlGSPa0iD8/7Oljh7yDZ3kf1ts4ozMa3YcRW8v+Xi5M9P/usr27vPKu7xqWqcOLhq/GWM+E3xzZf46hLKE+oQSrDR563iS41NjI1OKzQ+PyM+GX/MngYfl31QpYBj3thbfvgnVCV0JNQhTYEjCkyTOu/wqukKw0BTuqQs3ild4fLZSJePPV23Sh+K5XhuxeexHunKGmGUa5D9SdGiFEhLuujn5urlfJ5GOV+lOHN/kTl8513RUZ4kZf+eqr5ATIRePGXvRzKX6bWdpkekJkyKlWU2eDrKUqUPaNkneWq6XnStjxGxU1uPh2NahC0xPVUrLZLV8TzPPPus57H/xxYVE0OOri8gaTsk8bjWcajOd/Tvw7lg/i6CIrUxafZ6Haf53qZ/z0XOns4IsS/X2DjPYmR+e5QS53z1PWVC9rImVS9jg3PZkMxf33l9+uz66vQ07GN6w4rynV7NhWWkHKqJTJeC/JSoCUYfuO195DsOn2N749HY3tgkDlZcXCrJkOt1JqY7lccGuZTHtrQoj5VrKSFNxlTy0PqEspdZEYl2RCS9anpcQgonqr6Zsv3DMdixLWn0C5yqDcfEd87jScn54zg+tez5mRwfOQgcptEJY7QtS4hKknosJRzlmSRHTlptegenfa7vbdlHmWp6RlQKa4mOlQMoy6029glVHTIjRstyaWq6fqJoGy5JlWvHZbkox7VD+jb5Om3D6Ilpsan27zbLMqbrKiLdo4Jp7K1x+rw5Tsc2U7siZEXacVpsrmOo7zub6RzlxEpJ48px3lZPX61/Ka0vi4t8fjTSGK8rUS2bTM/LWkUsGVdGltH6I6qj/d4z2hgTxsPTcfz1KEizlP/L9SXnfZTjGmru9h27WtJ1kjQtJ46IEjjaSFdfp2U4AJxl0fq6+rlPtzWXcz7QnO+q/oYzI1ivnJfa5/WR5s/Vo8yfU10+73b5XHG0+XOVGPPnxvK5ifQn290xbqXk/zFyf44gtGAeW4Ip/5eM33EbSE232ejVNjam0Povch075/Wme3VfKd//lcgq4yVszLzn7fEzmE/ziPExrZyyoMLroUr9P+oume8v9dF0f5F5NVtK/tDKJX3nJH0fSTvOXailz5ZopI83h+ZGAm9M+lrr6dNiMo+/vFzqJXxJqEw4TCB9JNCUvhatWjul8Drvw0rybBTqSCOxOfJ8cORLpnSPlPFS58px/5cc98AHTOlu1bzFjU93O0e6ia3gdMuYCjJe3w+EmoSzhE5aulMd6Sa9tlTHhRKbyf3Gowj196rKfbWDnhapdkryHemMx/bqOYMvVL0j03OOPi/fOT/DkCm79s1Of9hj7NMln5Tpkmr9rirPDuo7pwcH+S7U/B0bTXTyXZjrd1o=
*/