// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2021, Oracle and/or its affiliates.

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

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
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

template <bool EnableClosestPoint>
struct set_result
{
    template <typename CT, typename ResultType>
    static void apply(CT const& distance,
                      CT const&,
                      CT const&,
                      ResultType& result)
    {
        result.distance = distance;
    }
};

template<>
struct set_result<true>
{
    template <typename CT, typename ResultType>
    static void apply(CT const&,
                      CT const& lon,
                      CT const& lat,
                      ResultType& result)
    {
        result.lon = lon;
        result.lat = lat;
    }
};


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

public:

    geographic_cross_track() = default;

    explicit geographic_cross_track(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    Spheroid const& model() const
    {
        return m_spheroid;
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

    template <typename Point, typename PointOfSegment>
    auto apply(Point const& p,
               PointOfSegment const& sp1,
               PointOfSegment const& sp2) const
    {
        return apply(get_as_radian<0>(sp1), get_as_radian<1>(sp1),
                     get_as_radian<0>(sp2), get_as_radian<1>(sp2),
                     get_as_radian<0>(p), get_as_radian<1>(p),
                     m_spheroid).distance;
    }
    
    // points on a meridian not crossing poles
    template <typename CT>
    inline CT vertical_or_meridian(CT const& lat1, CT const& lat2) const
    {
        using meridian_inverse = typename formula::meridian_inverse
        <
            CT,
            strategy::default_order<FormulaPolicy>::value
        >;

        return meridian_inverse::meridian_not_crossing_pole_dist(lat1, lat2, m_spheroid);
    }

private: 

    template <typename CT>
    struct result_type
    {
        result_type()
            : distance(0)
            , lon(0)
            , lat(0)
        {}

        CT distance;
        CT lon;
        CT lat;
    };

    template <typename CT>
    auto static inline normalize(CT const& g4, CT& der)
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
                          result_type<CT>& result)
    {
        using direct_distance_type = 
            typename FormulaPolicy::template direct<CT, true, false, false, false>;
        using inverse_distance_type = 
            typename FormulaPolicy::template inverse<CT, true, false, false, false, false>;

        geometry::formula::result_direct<CT> res14;

        int counter = 0; // robustness
        bool dist_improve = true;

        CT pl_lon = lon1;
        CT pl_lat = lat1;
        CT pr_lon = lon2;
        CT pr_lat = lat2;

        CT s14 = s14_start;

        do {
            // Solve the direct problem to find p4 (GEO)
            res14 = direct_distance_type::apply(lon1, lat1, s14, a12, spheroid);

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "dist(pl,p3)="
                      << inverse_distance_type::apply(lon3, lat3, pr_lon, pr_lat, spheroid).distance
                      << std::endl;
            std::cout << "dist(pr,p3)="
                      << inverse_distance_type::apply(lon3, lat3, pr_lon, pr_lat, spheroid).distance
                      << std::endl;
#endif
            CT const dist_l = 
                inverse_distance_type::apply(lon3, lat3, pl_lon, pl_lat, spheroid).distance;
            CT const dist_r = 
                inverse_distance_type::apply(lon3, lat3, pr_lon, pr_lat, spheroid).distance;
            
            if (dist_l < dist_r)
            {
                s14 -= inverse_distance_type::apply(res14.lon2, res14.lat2, pl_lon, 
                    pl_lat, spheroid).distance/2;
                pr_lon = res14.lon2;
                pr_lat = res14.lat2;
            }
            else
            {
                s14 += inverse_distance_type::apply(res14.lon2, res14.lat2, pr_lon, 
                    pr_lat, spheroid).distance/2;
                pl_lon = res14.lon2;
                pl_lat = res14.lat2;
            }

            CT new_distance = inverse_distance_type::apply(lon3, lat3, res14.lon2, res14.lat2,
                spheroid).distance;

            dist_improve = new_distance != result.distance;

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "p4=" << res14.lon2 * math::r2d<CT>() <<
                         "," << res14.lat2 * math::r2d<CT>() << std::endl;
            std::cout << "pl=" << pl_lon * math::r2d<CT>() << ","
                      << pl_lat * math::r2d<CT>()<< std::endl;
            std::cout << "pr=" << pr_lon * math::r2d<CT>() << ","
                      << pr_lat * math::r2d<CT>() << std::endl;
            std::cout << "new_s14=" << s14 << std::endl;
            std::cout << std::setprecision(16) << "result.distance ="
                      << result.distance << std::endl;
            std::cout << std::setprecision(16) << "new_distance ="
                      << new_distance << std::endl;
            std::cout << "---------end of step " << counter
                      << std::endl<< std::endl;
            if (!dist_improve)
            {
                std::cout << "Stop msg: res34.distance >= prev_distance" << std::endl;
            }
            if (counter == BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS)
            {
                std::cout << "Stop msg: counter" << std::endl;
            }
#endif
            set_result<EnableClosestPoint>::apply(new_distance, res14.lon2, res14.lat2, result);

        } while (dist_improve && counter++
                 < BOOST_GEOMETRY_DETAIL_POINT_SEGMENT_DISTANCE_MAX_STEPS);
    }

    template <typename CT>
    static void newton(CT const& lon1, CT const& lat1, //p1
                       CT const& lon2, CT const& lat2, //p2
                       CT const& lon3, CT const& lat3, //query point p3
                       Spheroid const& spheroid,
                       CT const& s14_start, CT const& a12,
                       result_type<CT>& result)
    {
        using inverse_distance_azimuth_quantities_type = 
            typename FormulaPolicy::template inverse<CT, true, true, false, true, true>;
    
        using inverse_dist_azimuth_type = 
            typename FormulaPolicy::template inverse<CT, false, true, false, false, false>;

        using direct_distance_type = 
            typename FormulaPolicy::template direct<CT, true, false, false, false>;

        CT const half_pi = math::pi<CT>() / CT(2);
        geometry::formula::result_direct<CT> res14;
        geometry::formula::result_inverse<CT> res34;
        res34.distance = -1;

        int counter = 0; // robustness
        CT g4;
        CT delta_g4 = 0;
        bool dist_improve = true;
        CT s14 = s14_start;

        do {
            auto prev_distance = res34.distance;
            auto prev_res = res14;

            // Solve the direct problem to find p4 (GEO)
            res14 = direct_distance_type::apply(lon1, lat1, s14, a12, spheroid);

            // Solve an inverse problem to find g4
            // g4 is the angle between segment (p1,p2) and segment (p3,p4)
            // that meet on p4 (GEO)

            CT a4 = inverse_dist_azimuth_type::apply(res14.lon2, res14.lat2, 
                                                     lon2, lat2, spheroid).azimuth;
            res34 = inverse_distance_azimuth_quantities_type::apply(res14.lon2, res14.lat2, 
                                                                    lon3, lat3, spheroid);
            g4 = res34.azimuth - a4;

            // cos(s14/earth_radius) is the spherical limit
            CT M43 = res34.geodesic_scale;
            CT m34 = res34.reduced_length;

            if (m34 != 0)
            {
                CT der = (M43 / m34) * sin(g4);
                delta_g4 = normalize(g4, der);
                s14 -= der != 0 ? delta_g4 / der : 0;
            }

            dist_improve = prev_distance > res34.distance || prev_distance == -1;

            if (dist_improve)
            {
                set_result<EnableClosestPoint>::apply(res34.distance, res14.lon2, res14.lat2, 
                                                      result);
            }
            else
            {
                set_result<EnableClosestPoint>::apply(prev_distance, prev_res.lon2, prev_res.lat2, 
                                                      result);
            }

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "p4=" << res14.lon2 * math::r2d<CT>() <<
                         "," << res14.lat2 * math::r2d<CT>() << std::endl;
            std::cout << "a34=" << res34.azimuth * math::r2d<CT>() << std::endl;
            std::cout << "a4=" << a4 * math::r2d<CT>() << std::endl;
            std::cout << "g4(normalized)=" << g4 * math::r2d<CT>() << std::endl;
            std::cout << "delta_g4=" << delta_g4 * math::r2d<CT>()  << std::endl;
            std::cout << "M43=" << M43 << std::endl;
            std::cout << "m34=" << m34 << std::endl;
            std::cout << "new_s14=" << s14 << std::endl;
            std::cout << std::setprecision(16) << "dist     ="
                      << res34.distance << std::endl;
            std::cout << "---------end of step " << counter
                      << std::endl<< std::endl;
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
                  << inverse_distance_azimuth_quantities_type
                     ::apply(res14.lon2, res14.lat2,
                             lon3, lat3, spheroid).distance
                  << ", p4=(" << res14.lon2 * math::r2d<CT>() << ","
                              << res14.lat2 * math::r2d<CT>() << ")"
                  << std::endl;

        CT s31 = inverse_distance_azimuth_quantities_type::apply(lon3, lat3, lon1, lat1, spheroid)
            .distance;
        CT s32 = inverse_distance_azimuth_quantities_type::apply(lon3, lat3, lon2, lat2, spheroid)
            .distance;

        CT a4 = inverse_dist_azimuth_type::apply(res14.lon2, res14.lat2, lon2, lat2, spheroid)
            .azimuth;
        
        geometry::formula::result_direct<CT> res4 =
            direct_distance_type::apply(res14.lon2, res14.lat2, .04, a4, spheroid);
        
        CT p4_plus = inverse_distance_azimuth_quantities_type::apply(res4.lon2, res4.lat2, lon3, 
            lat3, spheroid).distance;

        geometry::formula::result_direct<CT> res1 = 
            direct_distance_type::apply(lon1, lat1, s14-.04, a12, spheroid);
        
        CT p4_minus = inverse_distance_azimuth_quantities_type::apply(res1.lon2, res1.lat2, lon3, 
            lat3, spheroid).distance;

        std::cout << "s31=" << s31 << "\ns32=" << s32
                  << "\np4_plus=" << p4_plus << ", p4=("
                  << res4.lon2 * math::r2d<CT>() << ","
                  << res4.lat2 * math::r2d<CT>() << ")"
                  << "\np4_minus=" << p4_minus << ", p4=("
                  << res1.lon2 * math::r2d<CT>() << ","
                  << res1.lat2 * math::r2d<CT>() << ")"
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

    
    template <typename CT>
    static inline auto non_iterative_case(CT const& lon1, CT const& lat1, //p1
                                          CT const& lon2, CT const& lat2, //p2
                                          CT const& distance)
    {
        result_type<CT> result;

        set_result<EnableClosestPoint>::apply(distance, lon2, lat2, result);

        return result;
    }

    template <typename CT>
    static inline auto non_iterative_case(CT const& lon1, CT const& lat1, //p1
                                          CT const& lon2, CT const& lat2, //p2
                                          Spheroid const& spheroid)
    {
        CT distance = geometry::strategy::distance::geographic
            <
                FormulaPolicy, 
                Spheroid, 
                CT
            >::apply(lon1, lat1, lon2, lat2, spheroid);

        return non_iterative_case(lon1, lat1, lon2, lat2, distance);
    }

protected:

    template <typename CT>
    static inline auto apply(CT const& lo1, CT const& la1, //p1
                             CT const& lo2, CT const& la2, //p2
                             CT const& lo3, CT const& la3, //query point p3
                             Spheroid const& spheroid)
    {
        using inverse_dist_azimuth_type = 
            typename FormulaPolicy::template inverse<CT, true, true, false, false, false>;

        using inverse_dist_azimuth_reverse_type = 
            typename FormulaPolicy::template inverse<CT, true, true, true, false, false>;

        CT const earth_radius = geometry::formula::mean_radius<CT>(spheroid);

        result_type<CT> result;

        // if the query points coincide with one of segments' endpoints
        if ((lo1 == lo3 && la1 == la3) || (lo2 == lo3 && la2 == la3))
        {
            result.lon = lo3;
            result.lat = la3;
            return result;
        }

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

        using meridian_inverse = typename formula::meridian_inverse<CT>;

        bool meridian_not_crossing_pole =
            meridian_inverse::meridian_not_crossing_pole(lat1, lat2, diff);

        bool meridian_crossing_pole =
            meridian_inverse::meridian_crossing_pole(diff);

        if (math::equals(lat1, c0) && math::equals(lat2, c0)
            && !meridian_crossing_pole)
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
                return non_iterative_case(lon3, lat3, lon1, lat1, spheroid);
            }
            if (lon3 >= lon2)
            {
                return non_iterative_case(lon3, lat3, lon2, lat2, spheroid);
            }
            return non_iterative_case(lon3, lat3, lon3, lat1, spheroid);
        }

        if ( (meridian_not_crossing_pole || meridian_crossing_pole )
            && std::abs(lat1) > std::abs(lat2))
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
            
            auto res13 = apply(lon1, lat1, lon1, half_pi * sign_non_zero, lon3, lat3, spheroid);
            
            auto res23 = apply(lon2, lat2, lon2, half_pi * sign_non_zero, lon3, lat3, spheroid);

            return (res13.distance) < (res23.distance) ? res13 : res23;
        }

        auto res12 = inverse_dist_azimuth_reverse_type::apply(lon1, lat1, lon2, lat2, spheroid);
        
        auto res13 = inverse_dist_azimuth_type::apply(lon1, lat1, lon3, lat3, spheroid);

        if (geometry::math::equals(res12.distance, c0))
        {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
            std::cout << "Degenerate segment" << std::endl;
            std::cout << "distance between points="
                      << res13.distance << std::endl;
#endif
            auto res = meridian_inverse::apply(lon1, lat1, lon3, lat3, spheroid);

            return non_iterative_case(lon3, lat3, lon1, lat2, 
                res.meridian ? res.distance : res13.distance);
        }

        // Compute a12 (GEO)
        CT a312 = res13.azimuth - res12.azimuth;

        // TODO: meridian case optimization
        if (geometry::math::equals(a312, c0) && meridian_not_crossing_pole)
        {
            auto const minmax_elem = std::minmax(lat1, lat2);
            
            if (lat3 >= std::get<0>(minmax_elem) &&
                lat3 <= std::get<1>(minmax_elem))
            {
#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
                std::cout << "Point on meridian segment" << std::endl;
#endif
                return non_iterative_case(lon3, lat3, lon3, lat3, c0);
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

            return non_iterative_case(lon3, lat3, lon1, lat1, spheroid);
        }

        auto res23 = inverse_dist_azimuth_type::apply(lon2, lat2, lon3, lat3, spheroid);

        CT a321 = res23.azimuth - res12.reverse_azimuth + pi;
        CT projection2 = cos( a321 ) * res23.distance / res12.distance;

#ifdef BOOST_GEOMETRY_DEBUG_GEOGRAPHIC_CROSS_TRACK
        std::cout << "a21=" << res12.reverse_azimuth * math::r2d<CT>()
                  << std::endl;
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
            return non_iterative_case(lon3, lat3, lon2, lat2, spheroid);
        }

        // Guess s14 (SPHERICAL) aka along-track distance
        using point = geometry::model::point
            <
                CT, 
                2,
                geometry::cs::spherical_equatorial<geometry::radian>
            >;

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

        CT const a12_sph = geometry::formula::spherical_azimuth<>(lon1, lat1, lon2, lat2);

        auto res = geometry::formula::spherical_direct<true, false>(lon1, lat1, 
            s14_sph, a12_sph, srs::sphere<CT>(earth_radius));

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
            bisection(lon1, lat1, lon2, lat2, lon3, lat3, spheroid, 
                res12.distance/2, res12.azimuth, result);
        }
        else
        {
            CT s14_start = geometry::strategy::distance::geographic
                <
                    FormulaPolicy, 
                    Spheroid, 
                    CT
                >::apply(lon1, lat1, res.lon2, res.lat2, spheroid);

            newton(lon1, lat1, lon2, lat2, lon3, lat3, spheroid, s14_start, res12.azimuth, result);
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
    using base_t = detail::geographic_cross_track
        <
            FormulaPolicy,
            Spheroid,
            CalculationType,
            false,
            false
        >;

public :
    explicit geographic_cross_track(Spheroid const& spheroid = Spheroid())
        : base_t(spheroid)
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
    bool Bisection,
    bool EnableClosestPoint
>
struct tag<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint> >
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
    bool EnableClosestPoint,
    typename P,
    typename PS
>
struct return_type<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint>, P, PS>
    : detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint>::template return_type<P, PS>
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
    bool Bisection,
    bool EnableClosestPoint
>
struct comparable_type<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint> >
{
    typedef detail::geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint
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
    bool Bisection,
    bool EnableClosestPoint
>
struct get_comparable<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint> >
{
public :
    static inline detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint>
    apply(detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint> const& strategy)
    {
        return strategy;
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

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    bool Bisection,
    bool EnableClosestPoint,
    typename P,
    typename PS
>
struct result_from_distance<detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint>, P, PS>
{
private :
    typedef typename detail::geographic_cross_track
        <
            FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint
        >::template return_type<P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(detail::geographic_cross_track<FormulaPolicy, Spheroid, CalculationType, Bisection, EnableClosestPoint> const& , T const& distance)
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