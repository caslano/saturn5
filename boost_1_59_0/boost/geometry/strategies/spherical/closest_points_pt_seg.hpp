// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_CLOSEST_POINTS_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_CLOSEST_POINTS_CROSS_TRACK_HPP

#include <algorithm>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/concept_check.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{

namespace strategy { namespace closest_points
{

template
<
    typename CalculationType = void,
    typename Strategy = distance::comparable::haversine<double, CalculationType>
>
class cross_track
{
public:
    template <typename Point, typename PointOfSegment>
    struct calculation_type
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

    using radius_type = typename Strategy::radius_type;

    cross_track() = default;

    explicit inline cross_track(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track(Strategy const& s)
        : m_strategy(s)
    {}

    template <typename Point, typename PointOfSegment>
    inline auto apply(Point const& p, 
                      PointOfSegment const& sp1, 
                      PointOfSegment const& sp2) const
    {
        using CT = typename calculation_type<Point, PointOfSegment>::type;
        
        // http://williams.best.vwh.net/avform.htm#XTE
        CT d3 = m_strategy.apply(sp1, sp2);

        if (geometry::math::equals(d3, 0.0))
        {
            // "Degenerate" segment, return either d1 or d2
            return sp1;
        }

        CT d1 = m_strategy.apply(sp1, p);
        CT d2 = m_strategy.apply(sp2, p);

        auto d_crs_pair = distance::detail::compute_cross_track_pair<CT>::apply(
            p, sp1, sp2);

        // d1, d2, d3 are in principle not needed, only the sign matters
        CT projection1 = cos(d_crs_pair.first) * d1 / d3;
        CT projection2 = cos(d_crs_pair.second) * d2 / d3;

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
        std::cout << "Course " << dsv(sp1) << " to " << dsv(p) << " "
                  << crs_AD * geometry::math::r2d<CT>() << std::endl;
        std::cout << "Course " << dsv(sp1) << " to " << dsv(sp2) << " "
                  << crs_AB * geometry::math::r2d<CT>() << std::endl;
        std::cout << "Course " << dsv(sp2) << " to " << dsv(sp1) << " "
                  << crs_BA * geometry::math::r2d<CT>() << std::endl;
        std::cout << "Course " << dsv(sp2) << " to " << dsv(p) << " "
                  << crs_BD * geometry::math::r2d<CT>() << std::endl;
        std::cout << "Projection AD-AB " << projection1 << " : "
                  << d_crs1 * geometry::math::r2d<CT>() << std::endl;
        std::cout << "Projection BD-BA " << projection2 << " : "
                  << d_crs2 * geometry::math::r2d<CT>() << std::endl;
        std::cout << " d1: " << (d1 )
                  << " d2: " << (d2 )
                  << std::endl;
#endif

        if (projection1 > 0.0 && projection2 > 0.0)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
            CT XTD = radius() * geometry::math::abs( asin( sin( d1 ) * sin( d_crs1 ) ));

            std::cout << "Projection ON the segment" << std::endl;
            std::cout << "XTD: " << XTD
                      << " d1: " << (d1 * radius())
                      << " d2: " << (d2 * radius())
                      << std::endl;
#endif
            auto distance = distance::detail::compute_cross_track_distance::apply(
                d_crs_pair.first, d1);

            CT lon1 = geometry::get_as_radian<0>(sp1);
            CT lat1 = geometry::get_as_radian<1>(sp1);
            CT lon2 = geometry::get_as_radian<0>(sp2);
            CT lat2 = geometry::get_as_radian<1>(sp2);

            CT dist = CT(2) * asin(math::sqrt(distance)) * m_strategy.radius();
            CT dist_d1 = CT(2) * asin(math::sqrt(d1)) * m_strategy.radius();
            
            // Note: this is similar to spherical computation in geographic
            // point_segment_distance formula
            CT earth_radius = m_strategy.radius();
            CT cos_frac = cos(dist_d1 / earth_radius) / cos(dist / earth_radius);
            CT s14_sph = cos_frac >= 1 
                ? CT(0) : cos_frac <= -1 ? math::pi<CT>() * earth_radius
                                         : acos(cos_frac) * earth_radius;

            CT a12 = geometry::formula::spherical_azimuth<>(lon1, lat1, lon2, lat2);
            auto res_direct = geometry::formula::spherical_direct
                <
                    true,
                    false
                >(lon1, lat1, s14_sph, a12, srs::sphere<CT>(earth_radius));

            model::point
                <
                    CT,
                    dimension<PointOfSegment>::value,
                    typename coordinate_system<PointOfSegment>::type
                > cp;
            
            geometry::set_from_radian<0>(cp, res_direct.lon2);
            geometry::set_from_radian<1>(cp, res_direct.lat2);

            return cp;
        }
        else
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
            std::cout << "Projection OUTSIDE the segment" << std::endl;
#endif
            return d1 < d2 ? sp1 : sp2;
        }
    }

    template <typename T1, typename T2>
    inline radius_type vertical_or_meridian(T1 lat1, T2 lat2) const
    {
        return m_strategy.radius() * (lat1 - lat2);
    }

    inline typename Strategy::radius_type radius() const
    { return m_strategy.radius(); }

private :
    Strategy m_strategy;
};

}} // namespace strategy::closest_points

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_CLOSEST_POINTS_CROSS_TRACK_HPP

/* closest_points_pt_seg.hpp
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
*/