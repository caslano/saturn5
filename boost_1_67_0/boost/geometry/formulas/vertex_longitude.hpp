// Boost.Geometry

// Copyright (c) 2016-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MAXIMUM_LONGITUDE_HPP
#define BOOST_GEOMETRY_FORMULAS_MAXIMUM_LONGITUDE_HPP

#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/flattening.hpp>

#include <boost/mpl/assert.hpp>

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
    BOOST_MPL_ASSERT_MSG
    (
        false, NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM, (types<CS_Tag>)
    );

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