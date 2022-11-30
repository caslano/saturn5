// Boost.Geometry

// Copyright (c) 2016-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MAXIMUM_LONGITUDE_HPP
#define BOOST_GEOMETRY_FORMULAS_MAXIMUM_LONGITUDE_HPP


#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/flattening.hpp>

#include <boost/math/special_functions/hypot.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Algorithm to compute the vertex longitude of a geodesic segment. Vertex is
a point on the geodesic that maximizes (or minimizes) the latitude. The algorithm
is given the vertex latitude.
*/

//Classes for spesific CS

template <typename CT>
class vertex_longitude_on_sphere
{

public:

    template <typename T>
    static inline CT apply(T const& lat1, //segment point 1
                           T const& lat2, //segment point 2
                           T const& lat3, //vertex latitude
                           T const& sin_l12,
                           T const& cos_l12) //lon1 -lon2
    {
        //https://en.wikipedia.org/wiki/Great-circle_navigation#Finding_way-points
        CT const A = sin(lat1) * cos(lat2) * cos(lat3) * sin_l12;
        CT const B = sin(lat1) * cos(lat2) * cos(lat3) * cos_l12
                - cos(lat1) * sin(lat2) * cos(lat3);
        CT lon = atan2(B, A);
        return lon + math::pi<CT>();
    }
};

template <typename CT>
class vertex_longitude_on_spheroid
{
    template<typename T>
    static inline void normalize(T& x, T& y)
    {
        T h = boost::math::hypot(x, y);
        x /= h;
        y /= h;
    }

public:

    template <typename T, typename Spheroid>
    static inline CT apply(T const& lat1, //segment point 1
                           T const& lat2, //segment point 2
                           T const& lat3, //vertex latitude
                           T& alp1,
                           Spheroid const& spheroid)
    {
        // We assume that segment points lay on different side w.r.t.
        // the vertex

        // Constants
        CT const c0 = 0;
        CT const c2 = 2;
        CT const half_pi = math::pi<CT>() / c2;
        if (math::equals(lat1, half_pi)
                || math::equals(lat2, half_pi)
                || math::equals(lat1, -half_pi)
                || math::equals(lat2, -half_pi))
        {
            // one segment point is the pole
            return c0;
        }

        // More constants
        CT const f = flattening<CT>(spheroid);
        CT const pi = math::pi<CT>();
        CT const c1 = 1;
        CT const cminus1 = -1;

        // First, compute longitude on auxiliary sphere

        CT const one_minus_f = c1 - f;
        CT const bet1 = atan(one_minus_f * tan(lat1));
        CT const bet2 = atan(one_minus_f * tan(lat2));
        CT const bet3 = atan(one_minus_f * tan(lat3));

        CT cos_bet1 = cos(bet1);
        CT cos_bet2 = cos(bet2);
        CT const sin_bet1 = sin(bet1);
        CT const sin_bet2 = sin(bet2);
        CT const sin_bet3 = sin(bet3);

        CT omg12 = 0;

        if (bet1 < c0)
        {
            cos_bet1 *= cminus1;
            omg12 += pi;
        }
        if (bet2 < c0)
        {
            cos_bet2 *= cminus1;
            omg12 += pi;
        }

        CT const sin_alp1 = sin(alp1);
        CT const cos_alp1 = math::sqrt(c1 - math::sqr(sin_alp1));

        CT const norm = math::sqrt(math::sqr(cos_alp1) + math::sqr(sin_alp1 * sin_bet1));
        CT const sin_alp0 = sin(atan2(sin_alp1 * cos_bet1, norm));

        BOOST_ASSERT(cos_bet2 != c0);
        CT const sin_alp2 = sin_alp1 * cos_bet1 / cos_bet2;

        CT const cos_alp0 = math::sqrt(c1 - math::sqr(sin_alp0));
        CT const cos_alp2 = math::sqrt(c1 - math::sqr(sin_alp2));

        CT const sig1 = atan2(sin_bet1, cos_alp1 * cos_bet1);
        CT const sig2 = atan2(sin_bet2, -cos_alp2 * cos_bet2); //lat3 is a vertex

        CT const cos_sig1 = cos(sig1);
        CT const sin_sig1 = math::sqrt(c1 - math::sqr(cos_sig1));

        CT const cos_sig2 = cos(sig2);
        CT const sin_sig2 = math::sqrt(c1 - math::sqr(cos_sig2));

        CT const omg1 = atan2(sin_alp0 * sin_sig1, cos_sig1);
        CT const omg2 = atan2(sin_alp0 * sin_sig2, cos_sig2);

        omg12 += omg1 - omg2;

        CT const sin_omg12 = sin(omg12);
        CT const cos_omg12 = cos(omg12);

        CT omg13 = geometry::formula::vertex_longitude_on_sphere<CT>
                ::apply(bet1, bet2, bet3, sin_omg12, cos_omg12);

        if (lat1 * lat2 < c0)//different hemispheres
        {
            if ((lat2 - lat1) * lat3  > c0)// ascending segment
            {
                omg13 = pi - omg13;
            }
        }

        // Second, compute the ellipsoidal longitude

        CT const e2 = f * (c2 - f);
        CT const ep = math::sqrt(e2 / (c1 - e2));
        CT const k2 = math::sqr(ep * cos_alp0);
        CT const sqrt_k2_plus_one = math::sqrt(c1 + k2);
        CT const eps = (sqrt_k2_plus_one - c1) / (sqrt_k2_plus_one + c1);
        CT const eps2 = eps * eps;
        CT const n = f / (c2 - f);

        // sig3 is the length from equator to the vertex
        CT sig3;
        if(sin_bet3 > c0)
        {
            sig3 = half_pi;
        } else {
            sig3 = -half_pi;
        }
        CT const cos_sig3 = 0;
        CT const sin_sig3 = 1;

        CT sig13 = sig3 - sig1;
        if (sig13 > pi)
        {
            sig13 -= 2 * pi;
        }

        // Order 2 approximation
        CT const c1over2 = 0.5;
        CT const c1over4 = 0.25;
        CT const c1over8 = 0.125;
        CT const c1over16 = 0.0625;
        CT const c4 = 4;
        CT const c8 = 8;

        CT const A3 = 1 - (c1over2 - c1over2 * n) * eps - c1over4 * eps2;
        CT const C31 = (c1over4 - c1over4 * n) * eps + c1over8 * eps2;
        CT const C32 = c1over16 * eps2;

        CT const sin2_sig3 = c2 * cos_sig3 * sin_sig3;
        CT const sin4_sig3 = sin_sig3 * (-c4 * cos_sig3
                                         + c8 * cos_sig3 * cos_sig3 * cos_sig3);
        CT const sin2_sig1 = c2 * cos_sig1 * sin_sig1;
        CT const sin4_sig1 = sin_sig1 * (-c4 * cos_sig1
                                         + c8 * cos_sig1 * cos_sig1 * cos_sig1);
        CT const I3 = A3 * (sig13
                            + C31 * (sin2_sig3 - sin2_sig1)
                            + C32 * (sin4_sig3 - sin4_sig1));

        CT const sign = bet3 >= c0
                      ? c1
                      : cminus1;
        
        CT const dlon_max = omg13 - sign * f * sin_alp0 * I3;

        return dlon_max;
    }
};

//CS_tag dispatching

template <typename CT, typename CS_Tag>
struct compute_vertex_lon
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this coordinate system.",
        CT, CS_Tag);
};

template <typename CT>
struct compute_vertex_lon<CT, spherical_equatorial_tag>
{
    template <typename Strategy>
    static inline CT apply(CT const& lat1,
                           CT const& lat2,
                           CT const& vertex_lat,
                           CT const& sin_l12,
                           CT const& cos_l12,
                           CT,
                           Strategy)
    {
        return vertex_longitude_on_sphere<CT>
                ::apply(lat1,
                        lat2,
                        vertex_lat,
                        sin_l12,
                        cos_l12);
    }
};

template <typename CT>
struct compute_vertex_lon<CT, geographic_tag>
{
    template <typename Strategy>
    static inline CT apply(CT const& lat1,
                           CT const& lat2,
                           CT const& vertex_lat,
                           CT,
                           CT,
                           CT& alp1,
                           Strategy const& azimuth_strategy)
    {
        return vertex_longitude_on_spheroid<CT>
                ::apply(lat1,
                        lat2,
                        vertex_lat,
                        alp1,
                        azimuth_strategy.model());
    }
};

// Vertex longitude interface
// Assume that lon1 < lon2 and vertex_lat is the latitude of the vertex

template <typename CT, typename CS_Tag>
class vertex_longitude
{
public :
    template <typename Strategy>
    static inline CT apply(CT& lon1,
                           CT& lat1,
                           CT& lon2,
                           CT& lat2,
                           CT const& vertex_lat,
                           CT& alp1,
                           Strategy const& azimuth_strategy)
    {
        CT const c0 = 0;
        CT pi = math::pi<CT>();

        //Vertex is a segment's point
        if (math::equals(vertex_lat, lat1))
        {
            return lon1;
        }
        if (math::equals(vertex_lat, lat2))
        {
            return lon2;
        }

        //Segment lay on meridian
        if (math::equals(lon1, lon2))
        {
            return (std::max)(lat1, lat2);
        }
        BOOST_ASSERT(lon1 < lon2);

        CT dlon = compute_vertex_lon<CT, CS_Tag>::apply(lat1, lat2,
                                                        vertex_lat,
                                                        sin(lon1 - lon2),
                                                        cos(lon1 - lon2),
                                                        alp1,
                                                        azimuth_strategy);

        CT vertex_lon = std::fmod(lon1 + dlon, 2 * pi);

        if (vertex_lat < c0)
        {
            vertex_lon -= pi;
        }

        if (std::abs(lon1 - lon2) > pi)
        {
            vertex_lon -= pi;
        }

        return vertex_lon;
    }
};

template <typename CT>
class vertex_longitude<CT, cartesian_tag>
{
public :
    template <typename Strategy>
    static inline CT apply(CT& /*lon1*/,
                           CT& /*lat1*/,
                           CT& lon2,
                           CT& /*lat2*/,
                           CT const& /*vertex_lat*/,
                           CT& /*alp1*/,
                           Strategy const& /*azimuth_strategy*/)
    {
        return lon2;
    }
};

}}} // namespace boost::geometry::formula
#endif // BOOST_GEOMETRY_FORMULAS_MAXIMUM_LONGITUDE_HPP


/* vertex_longitude.hpp
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
*/