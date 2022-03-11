// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_HPP

#include <algorithm>

#include <boost/tuple/tuple.hpp>
#include <boost/algorithm/minmax.hpp>
#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/geographic/azimuth.hpp>
#include <boost/geometry/strategies/geographic/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/geographic/intersection.hpp>

#include <boost/geometry/formulas/vincenty_direct.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/formulas/result_direct.hpp>
#include <boost/geometry/formulas/mean_radius.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
#include <boost/geometry/io/dsv/write.hpp>
#endif

#ifndef BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS
#define BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS 100
#endif

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
#include <iostream>
#endif

namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

namespace detail
{
/*!
\brief Strategy functor for distance point to segment calculation on ellipsoid
       Algorithm uses direct and inverse geodesic problems as subroutines.
       The algorithm approximates the distance by an iterative Newton method.
\ingroup strategies
\details Class which calculates the distance of a point to a segment, for points
on the ellipsoid
\see C.F.F.Karney - Geodesics on an ellipsoid of revolution,
      https://arxiv.org/abs/1102.1215
\tparam FormulaPolicy underlying point-point distance strategy
\tparam Spheroid is the spheroidal model used
\tparam CalculationType \tparam_calculation
\tparam EnableClosestPoint computes the closest point on segment if true
*/
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void,
    bool Bisection = false,
    bool EnableClosestPoint = false
>
class geographic_cross_track
{
public :
    typedef within::spherical_point_point equals_point_point_strategy_type;

    typedef intersection::geographic_segments
        <
            FormulaPolicy,
            strategy::default_order<FormulaPolicy>::value,
            Spheroid,
            CalculationType
        > relate_segment_segment_strategy_type;

    inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy() const
    {
        return relate_segment_segment_strategy_type(m_spheroid);
    }

    typedef within::geographic_winding
        <
            void, void, FormulaPolicy, Spheroid, CalculationType
        > point_in_geometry_strategy_type;

    inline point_in_geometry_strategy_type get_point_in_geometry_strategy() const
    {
        return point_in_geometry_strategy_type(m_spheroid);
    }

    template <typename Point, typename PointOfSegment>
    struct return_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      Point,
                      PointOfSegment,
                      CalculationType
                  >::type
          >
    {};

    explicit geographic_cross_track(Spheroid const& spheroid = Spheroid())
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename PointOfSegment>
    inline typename return_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& sp1, PointOfSegment const& sp2) const
    {
        typedef typename geometry::detail::cs_angular_units<Point>::type units_type;

        return (apply<units_type>(get_as_radian<0>(sp1), get_as_radian<1>(sp1),
                                  get_as_radian<0>(sp2), get_as_radian<1>(sp2),
                                  get_as_radian<0>(p), get_as_radian<1>(p),
                                  m_spheroid)).distance;
    }

    // points on a meridian not crossing poles
    template <typename CT>
    inline CT vertical_or_meridian(CT const& lat1, CT const& lat2) const
    {
        typedef typename formula::meridian_inverse
        <
            CT,
            strategy::default_order<FormulaPolicy>::value
        > meridian_inverse;

        return meridian_inverse::meridian_not_crossing_pole_dist(lat1, lat2,
                                                                 m_spheroid);
    }

    Spheroid const& model() const
    {
        return m_spheroid;
    }

private :

    template <typename CT>
    struct result_distance_point_segment
    {
        result_distance_point_segment()
            : distance(0)
            , closest_point_lon(0)
            , closest_point_lat(0)
        {}

        CT distance;
        CT closest_point_lon;
        CT closest_point_lat;
    };

    template <typename CT>
    result_distance_point_segment<CT>
    static inline non_iterative_case(CT const& lon, CT const& lat, CT const& distance)
    {
        result_distance_point_segment<CT> result;
        result.distance = distance;

        if (EnableClosestPoint)
        {
            result.closest_point_lon = lon;
            result.closest_point_lat = lat;
        }
        return result;
    }

    template <typename CT>
    result_distance_point_segment<CT>
    static inline non_iterative_case(CT const& lon1, CT const& lat1, //p1
                                     CT const& lon2, CT const& lat2, //p2
                                     Spheroid const& spheroid)
    {
        CT distance = geometry::strategy::distance::geographic<FormulaPolicy, Spheroid, CT>
                              ::apply(lon1, lat1, lon2, lat2, spheroid);

        return non_iterative_case(lon1, lat1, distance);
    }

    template <typename CT>
    CT static inline normalize(CT const& g4, CT& der)
    {
        CT const pi = math::pi<CT>();
        if (g4 < -1.25*pi)//close to -270
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "g4=" << g4 * math::r2d<CT>() <<  ", close to -270" << std::endl;
#endif
            return g4 + 1.5 * pi;
        }
        else if (g4 > 1.25*pi)//close to 270
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "g4=" << g4 * math::r2d<CT>() <<  ", close to 270" << std::endl;
#endif
            der = -der;
            return - g4 + 1.5 * pi;
        }
        else if (g4 < 0 && g4 > -0.75*pi)//close to -90
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "g4=" << g4 * math::r2d<CT>() <<  ", close to -90" << std::endl;
#endif
            der = -der;
            return -g4 - pi/2;
        }
        return g4 - pi/2;
    }

    template <typename CT>
    static void bisection(CT const& lon1, CT const& lat1, //p1
                          CT const& lon2, CT const& lat2, //p2
                          CT const& lon3, CT const& lat3, //query point p3
                          Spheroid const& spheroid,
                          CT const& s14_start, CT const& a12,
                          result_distance_point_segment<CT>& result)
    {
        typedef typename FormulaPolicy::template direct<CT, true, false, false, false>
                direct_distance_type;
        typedef typename FormulaPolicy::template inverse<CT, true, false, false, false, false>
                inverse_distance_type;

        geometry::formula::result_direct<CT> res14;

        int counter = 0; // robustness
        bool dist_improve = true;

        CT pl_lon = lon1;
        CT pl_lat = lat1;
        CT pr_lon = lon2;
        CT pr_lat = lat2;

        CT s14 = s14_start;

        do{
            // Solve the direct problem to find p4 (GEO)
            res14 = direct_distance_type::apply(lon1, lat1, s14, a12, spheroid);

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "dist(pl,p3)="
                      << inverse_distance_type::apply(lon3, lat3,
                                                      pr_lon, pr_lat,
                                                      spheroid).distance
                      << std::endl;
            std::cout << "dist(pr,p3)="
                      << inverse_distance_type::apply(lon3, lat3,
                                                      pr_lon, pr_lat,
                                                      spheroid).distance
                      << std::endl;
#endif
            if (inverse_distance_type::apply(lon3, lat3, pl_lon, pl_lat, spheroid).distance
                < inverse_distance_type::apply(lon3, lat3, pr_lon, pr_lat, spheroid).distance)
            {
                s14 -= inverse_distance_type::apply(res14.lon2, res14.lat2, pl_lon, pl_lat,
                                                    spheroid).distance/2;
                pr_lon = res14.lon2;
                pr_lat = res14.lat2;
            }
            else
            {
                s14 += inverse_distance_type::apply(res14.lon2, res14.lat2, pr_lon, pr_lat,
                                                    spheroid).distance/2;
                pl_lon = res14.lon2;
                pl_lat = res14.lat2;
            }

            CT new_distance = inverse_distance_type::apply(lon3, lat3,
                                                           res14.lon2, res14.lat2,
                                                           spheroid).distance;

            dist_improve = new_distance != result.distance;

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "p4=" << res14.lon2 * math::r2d<CT>() <<
                         "," << res14.lat2 * math::r2d<CT>() << std::endl;
            std::cout << "pl=" << pl_lon * math::r2d<CT>() << "," << pl_lat * math::r2d<CT>()<< std::endl;
            std::cout << "pr=" << pr_lon * math::r2d<CT>() << "," << pr_lat * math::r2d<CT>() << std::endl;
            std::cout << "new_s14=" << s14 << std::endl;
            std::cout << std::setprecision(16) << "result.distance =" << result.distance << std::endl;
            std::cout << std::setprecision(16) << "new_distance =" << new_distance << std::endl;
            std::cout << "---------end of step " << counter << std::endl<< std::endl;
            if (!dist_improve)
            {
                std::cout << "Stop msg: res34.distance >= prev_distance" << std::endl;
            }
            if (counter == BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS)
            {
                std::cout << "Stop msg: counter" << std::endl;
            }
#endif

            result.distance = new_distance;

        } while (dist_improve
                 && counter++ < BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS);
    }

    template <typename CT>
    static void newton(CT const& lon1, CT const& lat1, //p1
                       CT const& lon2, CT const& lat2, //p2
                       CT const& lon3, CT const& lat3, //query point p3
                       Spheroid const& spheroid,
                       CT const& s14_start, CT const& a12,
                       result_distance_point_segment<CT>& result)
    {
        typedef typename FormulaPolicy::template inverse<CT, true, true, false, true, true>
                inverse_distance_azimuth_quantities_type;
        typedef typename FormulaPolicy::template inverse<CT, false, true, false, false, false>
                inverse_dist_azimuth_type;
        typedef typename FormulaPolicy::template direct<CT, true, false, false, false>
                direct_distance_type;

        CT const half_pi = math::pi<CT>() / CT(2);
        CT prev_distance;
        geometry::formula::result_direct<CT> res14;
        geometry::formula::result_inverse<CT> res34;
        res34.distance = -1;

        int counter = 0; // robustness
        CT g4;
        CT delta_g4 = 0;
        bool dist_improve = true;
        CT s14 = s14_start;

        do{
            prev_distance = res34.distance;

            // Solve the direct problem to find p4 (GEO)
            res14 = direct_distance_type::apply(lon1, lat1, s14, a12, spheroid);

            // Solve an inverse problem to find g4
            // g4 is the angle between segment (p1,p2) and segment (p3,p4) that meet on p4 (GEO)

            CT a4 = inverse_dist_azimuth_type::apply(res14.lon2, res14.lat2,
                                                lon2, lat2, spheroid).azimuth;
            res34 = inverse_distance_azimuth_quantities_type::apply(res14.lon2, res14.lat2,
                                                                    lon3, lat3, spheroid);
            g4 = res34.azimuth - a4;

            CT M43 = res34.geodesic_scale; // cos(s14/earth_radius) is the spherical limit
            CT m34 = res34.reduced_length;

            if (m34 != 0)
            {
                CT der = (M43 / m34) * sin(g4);
                delta_g4 = normalize(g4, der);
                s14 -= der != 0 ? delta_g4 / der : 0;
            }

            result.distance = res34.distance;

            dist_improve = prev_distance > res34.distance || prev_distance == -1;
            if (!dist_improve)
            {
                result.distance = prev_distance;
            }

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "p4=" << res14.lon2 * math::r2d<CT>() <<
                         "," << res14.lat2 * math::r2d<CT>() << std::endl;
            std::cout << "a34=" << res34.azimuth * math::r2d<CT>() << std::endl;
            std::cout << "a4=" << a4 * math::r2d<CT>() << std::endl;
            std::cout << "g4(normalized)=" << g4 * math::r2d<CT>() << std::endl;
            std::cout << "delta_g4=" << delta_g4 * math::r2d<CT>()  << std::endl;
            std::cout << "der=" << der  << std::endl;
            std::cout << "M43=" << M43 << std::endl;
            std::cout << "m34=" << m34 << std::endl;
            std::cout << "new_s14=" << s14 << std::endl;
            std::cout << std::setprecision(16) << "dist     =" << res34.distance << std::endl;
            std::cout << "---------end of step " << counter << std::endl<< std::endl;
            if (g4 == half_pi)
            {
                std::cout << "Stop msg: g4 == half_pi" << std::endl;
            }
            if (!dist_improve)
            {
                std::cout << "Stop msg: res34.distance >= prev_distance" << std::endl;
            }
            if (delta_g4 == 0)
            {
                std::cout << "Stop msg: delta_g4 == 0" << std::endl;
            }
            if (counter == BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS)
            {
                std::cout << "Stop msg: counter" << std::endl;
            }
#endif

        } while (g4 != half_pi
                 && dist_improve
                 && delta_g4 != 0
                 && counter++ < BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS);
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << "distance=" << res34.distance << std::endl;

        std::cout << "s34(geo) ="
                  << inverse_distance_azimuth_quantities_type::apply(res14.lon2, res14.lat2, lon3, lat3, spheroid).distance
                  << ", p4=(" << res14.lon2 * math::r2d<double>() << ","
                              << res14.lat2 * math::r2d<double>() << ")"
                  << std::endl;

        CT s31 = inverse_distance_azimuth_quantities_type::apply(lon3, lat3, lon1, lat1, spheroid).distance;
        CT s32 = inverse_distance_azimuth_quantities_type::apply(lon3, lat3, lon2, lat2, spheroid).distance;

        CT a4 = inverse_dist_azimuth_type::apply(res14.lon2, res14.lat2, lon2, lat2, spheroid).azimuth;
        geometry::formula::result_direct<CT> res4 = direct_distance_type::apply(res14.lon2, res14.lat2, .04, a4, spheroid);
        CT p4_plus = inverse_distance_azimuth_quantities_type::apply(res4.lon2, res4.lat2, lon3, lat3, spheroid).distance;

        geometry::formula::result_direct<CT> res1 = direct_distance_type::apply(lon1, lat1, s14-.04, a12, spheroid);
        CT p4_minus = inverse_distance_azimuth_quantities_type::apply(res1.lon2, res1.lat2, lon3, lat3, spheroid).distance;

        std::cout << "s31=" << s31 << "\ns32=" << s32
                  << "\np4_plus=" << p4_plus << ", p4=(" << res4.lon2 * math::r2d<double>() << "," << res4.lat2 * math::r2d<double>() << ")"
                  << "\np4_minus=" << p4_minus << ", p4=(" << res1.lon2 * math::r2d<double>() << "," << res1.lat2 * math::r2d<double>() << ")"
                  << std::endl;

        if (res34.distance <= p4_plus && res34.distance <= p4_minus)
        {
            std::cout << "Closest point computed" << std::endl;
        }
        else
        {
            std::cout << "There is a closer point nearby" << std::endl;
        }
#endif
    }

    template <typename Units, typename CT>
    result_distance_point_segment<CT>
    static inline apply(CT const& lo1, CT const& la1, //p1
                        CT const& lo2, CT const& la2, //p2
                        CT const& lo3, CT const& la3, //query point p3
                        Spheroid const& spheroid)
    {
        typedef typename FormulaPolicy::template inverse<CT, true, true, false, false, false>
                inverse_dist_azimuth_type;
        typedef typename FormulaPolicy::template inverse<CT, true, true, true, false, false>
                inverse_dist_azimuth_reverse_type;

        CT const earth_radius = geometry::formula::mean_radius<CT>(spheroid);

        result_distance_point_segment<CT> result;

        // Constants
        //CT const f = geometry::formula::flattening<CT>(spheroid);
        CT const pi = math::pi<CT>();
        CT const half_pi = pi / CT(2);
        CT const c0 = CT(0);

        CT lon1 = lo1;
        CT lat1 = la1;
        CT lon2 = lo2;
        CT lat2 = la2;
        CT lon3 = lo3;
        CT lat3 = la3;

        if (lon1 > lon2)
        {
            std::swap(lon1, lon2);
            std::swap(lat1, lat2);
        }

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << ">>\nSegment=(" << lon1 * math::r2d<CT>();
        std::cout << "," << lat1 * math::r2d<CT>();
        std::cout << "),(" << lon2 * math::r2d<CT>();
        std::cout << "," << lat2 * math::r2d<CT>();
        std::cout << ")\np=(" << lon3 * math::r2d<CT>();
        std::cout << "," << lat3 * math::r2d<CT>();
        std::cout << ")" << std::endl;
#endif

        //segment on equator
        //Note: antipodal points on equator does not define segment on equator
        //but pass by the pole
        CT diff = geometry::math::longitude_distance_signed<geometry::radian>(lon1, lon2);

        typedef typename formula::meridian_inverse<CT>
                                            meridian_inverse;

        bool meridian_not_crossing_pole =
              meridian_inverse::meridian_not_crossing_pole
                                                            (lat1, lat2, diff);

        bool meridian_crossing_pole =
              meridian_inverse::meridian_crossing_pole(diff);

        if (math::equals(lat1, c0) && math::equals(lat2, c0) && !meridian_crossing_pole)
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "Equatorial segment" << std::endl;
            std::cout << "segment=(" << lon1 * math::r2d<CT>();
            std::cout << "," << lat1 * math::r2d<CT>();
            std::cout << "),(" << lon2 * math::r2d<CT>();
            std::cout << "," << lat2 * math::r2d<CT>();
            std::cout << ")\np=(" << lon3 * math::r2d<CT>();
            std::cout << "," << lat3 * math::r2d<CT>() << ")\n";
#endif
            if (lon3 <= lon1)
            {
                return non_iterative_case(lon1, lat1, lon3, lat3, spheroid);
            }
            if (lon3 >= lon2)
            {
                return non_iterative_case(lon2, lat2, lon3, lat3, spheroid);
            }
            return non_iterative_case(lon3, lat1, lon3, lat3, spheroid);
        }

        if ( (meridian_not_crossing_pole || meridian_crossing_pole ) && std::abs(lat1) > std::abs(lat2))
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "Meridian segment not crossing pole" << std::endl;
#endif
            std::swap(lat1,lat2);
        }

        if (meridian_crossing_pole)
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "Meridian segment crossing pole" << std::endl;
#endif
            CT sign_non_zero = lat3 >= c0 ? 1 : -1;
            result_distance_point_segment<CT> res13 =
                    apply<geometry::radian>(lon1, lat1,
                                            lon1, half_pi * sign_non_zero,
                                            lon3, lat3, spheroid);
            result_distance_point_segment<CT> res23 =
                    apply<geometry::radian>(lon2, lat2,
                                            lon2, half_pi * sign_non_zero,
                                            lon3, lat3, spheroid);
            if (res13.distance < res23.distance)
            {
                return res13;
            }
            else
            {
                return res23;
            }
        }

        geometry::formula::result_inverse<CT> res12 =
                inverse_dist_azimuth_reverse_type::apply(lon1, lat1, lon2, lat2, spheroid);
        geometry::formula::result_inverse<CT> res13 =
                inverse_dist_azimuth_type::apply(lon1, lat1, lon3, lat3, spheroid);

        if (geometry::math::equals(res12.distance, c0))
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "Degenerate segment" << std::endl;
            std::cout << "distance between points=" << res13.distance << std::endl;
#endif
            typename meridian_inverse::result res =
                     meridian_inverse::apply(lon1, lat1, lon3, lat3, spheroid);

            return non_iterative_case(lon1, lat2,
                                      res.meridian ? res.distance : res13.distance);
        }

        // Compute a12 (GEO)
        CT a312 = res13.azimuth - res12.azimuth;

        // TODO: meridian case optimization
        if (geometry::math::equals(a312, c0) && meridian_not_crossing_pole)
        {
            boost::tuple<CT,CT> minmax_elem = boost::minmax(lat1, lat2);
            if (lat3 >= minmax_elem.template get<0>() &&
                lat3 <= minmax_elem.template get<1>())
            {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
                std::cout << "Point on meridian segment" << std::endl;
#endif
                return non_iterative_case(lon3, lat3, c0);
            }
        }

        CT projection1 = cos( a312 ) * res13.distance / res12.distance;

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << "a1=" << res12.azimuth * math::r2d<CT>() << std::endl;
        std::cout << "a13=" << res13.azimuth * math::r2d<CT>() << std::endl;
        std::cout << "a312=" << a312 * math::r2d<CT>() << std::endl;
        std::cout << "cos(a312)=" << cos(a312) << std::endl;
        std::cout << "projection 1=" << projection1 << std::endl;
#endif

        if (projection1 < c0)
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "projection closer to p1" << std::endl;
#endif
            // projection of p3 on geodesic spanned by segment (p1,p2) fall
            // outside of segment on the side of p1

            return non_iterative_case(lon1, lat1, lon3, lat3, spheroid);
        }

        geometry::formula::result_inverse<CT> res23 =
                inverse_dist_azimuth_type::apply(lon2, lat2, lon3, lat3, spheroid);

        CT a321 = res23.azimuth - res12.reverse_azimuth + pi;
        CT projection2 = cos( a321 ) * res23.distance / res12.distance;

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << "a21=" << res12.reverse_azimuth * math::r2d<CT>() << std::endl;
        std::cout << "a23=" << res23.azimuth * math::r2d<CT>() << std::endl;
        std::cout << "a321=" << a321 * math::r2d<CT>() << std::endl;
        std::cout << "cos(a321)=" << cos(a321) << std::endl;
        std::cout << "projection 2=" << projection2 << std::endl;
#endif

        if (projection2 < c0)
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "projection closer to p2" << std::endl;
#endif
            // projection of p3 on geodesic spanned by segment (p1,p2) fall
            // outside of segment on the side of p2
            return non_iterative_case(lon2, lat2, lon3, lat3, spheroid);
        }

        // Guess s14 (SPHERICAL) aka along-track distance
        typedef geometry::model::point
                <
                    CT, 2,
                    geometry::cs::spherical_equatorial<geometry::radian>
                > point;

        point p1 = point(lon1, lat1);
        point p2 = point(lon2, lat2);
        point p3 = point(lon3, lat3);

        geometry::strategy::distance::cross_track<CT> cross_track(earth_radius);
        CT s34_sph = cross_track.apply(p3, p1, p2);

        geometry::strategy::distance::haversine<CT> str(earth_radius);
        CT s13_sph = str.apply(p1, p3);

        //CT s14 = acos( cos(s13/earth_radius) / cos(s34/earth_radius) ) * earth_radius;
        CT cos_frac = cos(s13_sph / earth_radius) / cos(s34_sph / earth_radius);
        CT s14_sph = cos_frac >= 1 ? CT(0)
                     : cos_frac <= -1 ? pi * earth_radius
                     : acos(cos_frac) * earth_radius;

        CT a12_sph = geometry::formula::spherical_azimuth<>(lon1, lat1, lon2, lat2);

        geometry::formula::result_direct<CT> res
                = geometry::formula::spherical_direct<true, false>
                  (lon1, lat1, s14_sph, a12_sph, srs::sphere<CT>(earth_radius));

        // this is what postgis (version 2.5) returns
        // geometry::strategy::distance::geographic<FormulaPolicy, Spheroid, CT>
        //                     ::apply(lon3, lat3, res.lon2, res.lat2, spheroid);

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << "s34=" << s34_sph << std::endl;
        std::cout << "s13=" << res13.distance << std::endl;
        std::cout << "s14=" << s14_sph << std::endl;
        std::cout << "===============" << std::endl;
#endif

        // Update s14 (using Newton method)

        if (Bisection)
        {
            bisection<CT>(lon1, lat1, lon2, lat2, lon3, lat3,
                          spheroid, res12.distance/2, res12.azimuth, result);
        }
        else
        {
            CT s14_start = geometry::strategy::distance::geographic<FormulaPolicy, Spheroid, CT>
                           ::apply(lon1, lat1, res.lon2, res.lat2, spheroid);

            newton<CT>(lon1, lat1, lon2, lat2, lon3, lat3,
                              spheroid, s14_start, res12.azimuth, result);
        }

        return result;
    }

    Spheroid m_spheroid;
};

} // namespace detail

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_cross_track
    : public detail::geographic_cross_track
        <
            FormulaPolicy,
            Spheroid,
            CalculationType,
            false,
            false
        >
{
public :
    explicit geographic_cross_track(Spheroid const& spheroid = Spheroid())
        :
        detail::geographic_cross_track<
                FormulaPolicy,
                Spheroid,
                CalculationType,
                false,
                false
            >(spheroid)
        {}

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

//tags
template <typename FormulaPolicy>
struct tag<geographic_cross_track<FormulaPolicy> >
{
    typedef strategy_tag_distance_point_segment type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid
>
struct tag<geographic_cross_track<FormulaPolicy, Spheroid> >
{
    typedef strategy_tag_distance_point_segment type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct tag<geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_segment type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        bool Bisection
>
struct tag<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection> >
{
    typedef strategy_tag_distance_point_segment type;
};

//return types
template <typename FormulaPolicy, typename P, typename PS>
struct return_type<geographic_cross_track<FormulaPolicy>, P, PS>
    : geographic_cross_track<FormulaPolicy>::template return_type<P, PS>
{};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename P,
        typename PS
>
struct return_type<geographic_cross_track<FormulaPolicy, Spheroid>, P, PS>
    : geographic_cross_track<FormulaPolicy, Spheroid>::template return_type<P, PS>
{};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        typename P,
        typename PS
>
struct return_type<geographic_cross_track<FormulaPolicy, Spheroid, CalculationType>, P, PS>
    : geographic_cross_track<FormulaPolicy, Spheroid, CalculationType>::template return_type<P, PS>
{};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        bool Bisection,
        typename P,
        typename PS
>
struct return_type<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection>, P, PS>
    : detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection>::template return_type<P, PS>
{};

//comparable types
template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct comparable_type<geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType
        >  type;
};


template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        bool Bisection
>
struct comparable_type<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection> >
{
    typedef detail::geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType, Bisection
        >  type;
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType
>
struct get_comparable<geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> >
{
public :
    static inline geographic_cross_track<FormulaPolicy, Spheroid, CalculationType>
    apply(geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> const& strategy)
    {
        return strategy;
    }
};

template
<
        typename FormulaPolicy,
        typename Spheroid,
        typename CalculationType,
        bool Bisection
>
struct get_comparable<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection> >
{
public :
    static inline detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection>
    apply(detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection> const& strategy)
    {
        return strategy;
    }
};


template
<
    typename FormulaPolicy,
    typename P,
    typename PS
>
struct result_from_distance<geographic_cross_track<FormulaPolicy>, P, PS>
{
private :
    typedef typename geographic_cross_track
        <
            FormulaPolicy
        >::template return_type<P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(geographic_cross_track<FormulaPolicy> const& , T const& distance)
    {
        return distance;
    }
};

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename P,
    typename PS
>
struct result_from_distance<geographic_cross_track<FormulaPolicy, Spheroid, CalculationType>, P, PS>
{
private :
    typedef typename geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType
        >::template return_type<P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(geographic_cross_track<FormulaPolicy, Spheroid, CalculationType> const& , T const& distance)
    {
        return distance;
    }
};


template <typename Point, typename PointOfSegment>
struct default_strategy
    <
        point_tag, segment_tag, Point, PointOfSegment,
        geographic_tag, geographic_tag
    >
{
    typedef geographic_cross_track<> type;
};


template <typename PointOfSegment, typename Point>
struct default_strategy
    <
        segment_tag, point_tag, PointOfSegment, Point,
        geographic_tag, geographic_tag
    >
{
    typedef typename default_strategy
        <
            point_tag, segment_tag, Point, PointOfSegment,
            geographic_tag, geographic_tag
        >::type type;
};

} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::distance

}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_CROSS_TRACK_HPP

/* distance_cross_track.hpp
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
*/