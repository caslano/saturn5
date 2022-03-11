// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_SEGMENT_HPP


#include <cstddef>
#include <utility>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_same.hpp>

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

#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/envelope.hpp>
#include <boost/geometry/strategies/normalize.hpp>
#include <boost/geometry/strategies/spherical/azimuth.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>

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
        BOOST_GEOMETRY_ASSERT(! math::equals(a1, a2));

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

        if (math::equals(a1, a2))
        {
            // the segment must lie on the equator or is very short or is meridian
            return;
        }

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
    typedef strategy::expand::spherical_box box_expand_strategy_type;
    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

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

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_ENVELOPE_SEGMENT_HPP


/* envelope_segment.hpp
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
*/