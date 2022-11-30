// Boost.Geometry

// Copyright (c) 2016-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP
#define BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP


#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/spherical.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief Algorithm to compute the vertex latitude of a geodesic segment. Vertex is
a point on the geodesic that maximizes (or minimizes) the latitude.
\author See
    [Wood96] Wood - Vertex Latitudes on Ellipsoid Geodesics, SIAM Rev., 38(4),
             637–644, 1996
*/

template <typename CT>
class vertex_latitude_on_sphere
{

public:
    template<typename T1, typename T2>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1)
    {
        return std::acos( math::abs(cos(lat1) * sin(alp1)) );
    }
};

template <typename CT>
class vertex_latitude_on_spheroid
{

public:
/*
 * formula based on paper
 *   [Wood96] Wood - Vertex Latitudes on Ellipsoid Geodesics, SIAM Rev., 38(4),
 *            637–644, 1996
    template <typename T1, typename T2, typename Spheroid>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1,
                           Spheroid const& spheroid)
    {
        CT const f = formula::flattening<CT>(spheroid);

        CT const e2 = f * (CT(2) - f);
        CT const sin_alp1 = sin(alp1);
        CT const sin2_lat1 = math::sqr(sin(lat1));
        CT const cos2_lat1 = CT(1) - sin2_lat1;

        CT const e2_sin2 = CT(1) - e2 * sin2_lat1;
        CT const cos2_sin2 = cos2_lat1 * math::sqr(sin_alp1);
        CT const vertex_lat = std::asin( math::sqrt((e2_sin2 - cos2_sin2)
                                                    / (e2_sin2 - e2 * cos2_sin2)));
        return vertex_lat;
    }
*/

    // simpler formula based on Clairaut relation for spheroids
    template <typename T1, typename T2, typename Spheroid>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1,
                           Spheroid const& spheroid)
    {
        CT const f = formula::flattening<CT>(spheroid);

        CT const one_minus_f = (CT(1) - f);

        //get the reduced latitude
        CT const bet1 = atan( one_minus_f * tan(lat1) );

        //apply Clairaut relation
        CT const betv =  vertex_latitude_on_sphere<CT>::apply(bet1, alp1);

        //return the spheroid latitude
        return atan( tan(betv) / one_minus_f );
    }

    /*
    template <typename T>
    inline static void sign_adjustment(CT lat1, CT lat2, CT vertex_lat, T& vrt_result)
    {
        // signbit returns a non-zero value (true) if the sign is negative;
        // and zero (false) otherwise.
        bool sign = std::signbit(std::abs(lat1) > std::abs(lat2) ? lat1 : lat2);

        vrt_result.north = sign ? std::max(lat1, lat2) : vertex_lat;
        vrt_result.south = sign ? vertex_lat * CT(-1) : std::min(lat1, lat2);
    }

    template <typename T>
    inline static bool vertex_on_segment(CT alp1, CT alp2, CT lat1, CT lat2, T& vrt_result)
    {
        CT const half_pi = math::pi<CT>() / CT(2);

        // if the segment does not contain the vertex of the geodesic
        // then return the endpoint of max (min) latitude
        if ((alp1 < half_pi && alp2 < half_pi)
                || (alp1 > half_pi && alp2 > half_pi))
        {
            vrt_result.north = std::max(lat1, lat2);
            vrt_result.south = std::min(lat1, lat2);
            return false;
        }
        return true;
    }
    */
};


template <typename CT, typename CS_Tag>
struct vertex_latitude
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this coordinate system.",
        CT, CS_Tag);
};

template <typename CT>
struct vertex_latitude<CT, spherical_equatorial_tag>
        : vertex_latitude_on_sphere<CT>
{};

template <typename CT>
struct vertex_latitude<CT, geographic_tag>
        : vertex_latitude_on_spheroid<CT>
{};


}}} // namespace boost::geometry::formula

#endif // BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP

/* vertex_latitude.hpp
++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
*/