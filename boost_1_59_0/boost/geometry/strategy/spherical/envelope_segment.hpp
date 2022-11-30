// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_SEGMENT_HPP


#include <cstddef>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/meridian_segment.hpp>
#include <boost/geometry/formulas/vertex_latitude.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategy/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategy/envelope.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/azimuth.hpp>
#include <boost/geometry/strategy/spherical/expand_box.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace strategy { namespace envelope
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename CalculationType, typename CS_Tag>
struct envelope_segment_call_vertex_latitude
{
    template <typename T1, typename T2, typename Strategy>
    static inline CalculationType apply(T1 const& lat1,
                                        T2 const& alp1,
                                        Strategy const& )
    {
        return geometry::formula::vertex_latitude<CalculationType, CS_Tag>
            ::apply(lat1, alp1);
    }
};

template <typename CalculationType>
struct envelope_segment_call_vertex_latitude<CalculationType, geographic_tag>
{
    template <typename T1, typename T2, typename Strategy>
    static inline CalculationType apply(T1 const& lat1,
                                        T2 const& alp1,
                                        Strategy const& strategy)
    {
        return geometry::formula::vertex_latitude<CalculationType, geographic_tag>
            ::apply(lat1, alp1, strategy.model());
    }
};

template <typename Units, typename CS_Tag>
struct envelope_segment_convert_polar
{
    template <typename T>
    static inline void pre(T & , T & ) {}

    template <typename T>
    static inline void post(T & , T & ) {}
};

template <typename Units>
struct envelope_segment_convert_polar<Units, spherical_polar_tag>
{
    template <typename T>
    static inline void pre(T & lat1, T & lat2)
    {
        lat1 = math::latitude_convert_ep<Units>(lat1);
        lat2 = math::latitude_convert_ep<Units>(lat2);
    }

    template <typename T>
    static inline void post(T & lat1, T & lat2)
    {
        lat1 = math::latitude_convert_ep<Units>(lat1);
        lat2 = math::latitude_convert_ep<Units>(lat2);
        std::swap(lat1, lat2);
    }
};

template <typename CS_Tag>
class envelope_segment_impl
{
private:

    // degrees or radians
    template <typename CalculationType>
    static inline void swap(CalculationType& lon1,
                            CalculationType& lat1,
                            CalculationType& lon2,
                            CalculationType& lat2)
    {
        std::swap(lon1, lon2);
        std::swap(lat1, lat2);
    }

    // radians
    template <typename CalculationType>
    static inline bool contains_pi_half(CalculationType const& a1,
                                        CalculationType const& a2)
    {
        // azimuths a1 and a2 are assumed to be in radians

        static CalculationType const pi_half = math::half_pi<CalculationType>();

        return (a1 < a2)
                ? (a1 < pi_half && pi_half < a2)
                : (a1 > pi_half && pi_half > a2);
    }

    // radians or degrees
    template <typename Units, typename CoordinateType>
    static inline bool crosses_antimeridian(CoordinateType const& lon1,
                                            CoordinateType const& lon2)
    {
        typedef math::detail::constants_on_spheroid
            <
                CoordinateType, Units
            > constants;

        return math::abs(lon1 - lon2) > constants::half_period(); // > pi
    }

    // degrees or radians
    template <typename Units, typename CalculationType, typename Strategy>
    static inline void compute_box_corners(CalculationType& lon1,
                                           CalculationType& lat1,
                                           CalculationType& lon2,
                                           CalculationType& lat2,
                                           CalculationType a1,
                                           CalculationType a2,
                                           Strategy const& strategy)
    {
        // coordinates are assumed to be in radians
        BOOST_GEOMETRY_ASSERT(lon1 <= lon2);
        boost::ignore_unused(lon1, lon2);

        CalculationType lat1_rad = math::as_radian<Units>(lat1);
        CalculationType lat2_rad = math::as_radian<Units>(lat2);

        if (lat1 > lat2)
        {
            std::swap(lat1, lat2);
            std::swap(lat1_rad, lat2_rad);
            std::swap(a1, a2);
        }

        if (contains_pi_half(a1, a2))
        {
            CalculationType p_max = envelope_segment_call_vertex_latitude
                <CalculationType, CS_Tag>::apply(lat1_rad, a1, strategy);

            CalculationType const mid_lat = lat1 + lat2;
            if (mid_lat < 0)
            {
                // update using min latitude
                CalculationType const lat_min_rad = -p_max;
                CalculationType const lat_min
                    = math::from_radian<Units>(lat_min_rad);

                if (lat1 > lat_min)
                {
                    lat1 = lat_min;
                }
            }
            else
            {
                // update using max latitude
                CalculationType const lat_max_rad = p_max;
                CalculationType const lat_max
                    = math::from_radian<Units>(lat_max_rad);

                if (lat2 < lat_max)
                {
                    lat2 = lat_max;
                }
            }
        }
    }

    template <typename Units, typename CalculationType>
    static inline void special_cases(CalculationType& lon1,
                                     CalculationType& lat1,
                                     CalculationType& lon2,
                                     CalculationType& lat2)
    {
        typedef math::detail::constants_on_spheroid
            <
                CalculationType, Units
            > constants;

        bool is_pole1 = math::equals(math::abs(lat1), constants::max_latitude());
        bool is_pole2 = math::equals(math::abs(lat2), constants::max_latitude());

        if (is_pole1 && is_pole2)
        {
            // both points are poles; nothing more to do:
            // longitudes are already normalized to 0
            // but just in case
            lon1 = 0;
            lon2 = 0;
        }
        else if (is_pole1 && !is_pole2)
        {
            // first point is a pole, second point is not:
            // make the longitude of the first point the same as that
            // of the second point
            lon1 = lon2;
        }
        else if (!is_pole1 && is_pole2)
        {
            // second point is a pole, first point is not:
            // make the longitude of the second point the same as that
            // of the first point
            lon2 = lon1;
        }

        if (lon1 == lon2)
        {
            // segment lies on a meridian
            if (lat1 > lat2)
            {
                std::swap(lat1, lat2);
            }
            return;
        }

        BOOST_GEOMETRY_ASSERT(!is_pole1 && !is_pole2);

        if (lon1 > lon2)
        {
            swap(lon1, lat1, lon2, lat2);
        }

        if (crosses_antimeridian<Units>(lon1, lon2))
        {
            lon1 += constants::period();
            swap(lon1, lat1, lon2, lat2);
        }
    }

    template
    <
        typename Units,
        typename CalculationType,
        typename Box
    >
    static inline void create_box(CalculationType lon1,
                                  CalculationType lat1,
                                  CalculationType lon2,
                                  CalculationType lat2,
                                  Box& mbr)
    {
        typedef typename coordinate_type<Box>::type box_coordinate_type;

        typedef typename helper_geometry
            <
                Box, box_coordinate_type, Units
            >::type helper_box_type;

        helper_box_type helper_mbr;

        geometry::set
            <
                min_corner, 0
            >(helper_mbr, boost::numeric_cast<box_coordinate_type>(lon1));

        geometry::set
            <
                min_corner, 1
            >(helper_mbr, boost::numeric_cast<box_coordinate_type>(lat1));

        geometry::set
            <
                max_corner, 0
            >(helper_mbr, boost::numeric_cast<box_coordinate_type>(lon2));

        geometry::set
            <
                max_corner, 1
            >(helper_mbr, boost::numeric_cast<box_coordinate_type>(lat2));

        geometry::detail::envelope::transform_units(helper_mbr, mbr);
    }


    template <typename Units, typename CalculationType, typename Strategy>
    static inline void apply(CalculationType& lon1,
                             CalculationType& lat1,
                             CalculationType& lon2,
                             CalculationType& lat2,
                             Strategy const& strategy)
    {
        special_cases<Units>(lon1, lat1, lon2, lat2);

        CalculationType lon1_rad = math::as_radian<Units>(lon1);
        CalculationType lat1_rad = math::as_radian<Units>(lat1);
        CalculationType lon2_rad = math::as_radian<Units>(lon2);
        CalculationType lat2_rad = math::as_radian<Units>(lat2);
        CalculationType alp1, alp2;
        strategy.apply(lon1_rad, lat1_rad, lon2_rad, lat2_rad, alp1, alp2);

        compute_box_corners<Units>(lon1, lat1, lon2, lat2, alp1, alp2, strategy);
    }

public:
    template
    <
        typename Units,
        typename CalculationType,
        typename Box,
        typename Strategy
    >
    static inline void apply(CalculationType lon1,
                             CalculationType lat1,
                             CalculationType lon2,
                             CalculationType lat2,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typedef envelope_segment_convert_polar<Units, typename cs_tag<Box>::type> convert_polar;

        convert_polar::pre(lat1, lat2);

        apply<Units>(lon1, lat1, lon2, lat2, strategy);

        convert_polar::post(lat1, lat2);

        create_box<Units>(lon1, lat1, lon2, lat2, mbr);
    }

};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


template
<
    typename CalculationType = void
>
class spherical_segment
{
public:
    template <typename Point, typename Box>
    static inline void apply(Point const& point1, Point const& point2,
                             Box& box)
    {
        Point p1_normalized, p2_normalized;
        strategy::normalize::spherical_point::apply(point1, p1_normalized);
        strategy::normalize::spherical_point::apply(point2, p2_normalized);

        geometry::strategy::azimuth::spherical<CalculationType> azimuth_spherical;

        typedef typename geometry::detail::cs_angular_units<Point>::type units_type;

        // first compute the envelope range for the first two coordinates
        strategy::envelope::detail::envelope_segment_impl
            <
                spherical_equatorial_tag
            >::template apply<units_type>(geometry::get<0>(p1_normalized),
                                          geometry::get<1>(p1_normalized),
                                          geometry::get<0>(p2_normalized),
                                          geometry::get<1>(p2_normalized),
                                          box,
                                          azimuth_spherical);

        // now compute the envelope range for coordinates of
        // dimension 2 and higher
        strategy::envelope::detail::envelope_one_segment
            <
                2, dimension<Point>::value
            >::apply(point1, point2, box);
  }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<segment_tag, spherical_equatorial_tag, CalculationType>
{
    typedef strategy::envelope::spherical_segment<CalculationType> type;
};


template <typename CalculationType>
struct default_strategy<segment_tag, spherical_polar_tag, CalculationType>
{
    typedef strategy::envelope::spherical_segment<CalculationType> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_ENVELOPE_SEGMENT_HPP


/* envelope_segment.hpp
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
*/