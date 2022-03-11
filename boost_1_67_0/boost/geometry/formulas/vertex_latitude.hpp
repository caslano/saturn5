// Boost.Geometry

// Copyright (c) 2016-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP
#define BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP


#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#include <boost/mpl/assert.hpp>


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
    BOOST_MPL_ASSERT_MSG
         (
             false, NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM, (types<CS_Tag>)
         );

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
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
*/