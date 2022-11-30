// Boost.Geometry

// Copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MERIDIAN_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_MERIDIAN_INVERSE_HPP

#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/meridian_segment.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Compute the arc length of an ellipse.
*/

template <typename CT, unsigned int Order = 1>
class meridian_inverse
{

public :

    struct result
    {
        result()
            : distance(0)
            , meridian(false)
        {}

        CT distance;
        bool meridian;
    };

    template <typename T>
    static bool meridian_not_crossing_pole(T lat1, T lat2, CT diff)
    {
        CT half_pi = math::pi<CT>()/CT(2);
        return math::equals(diff, CT(0)) ||
                    (math::equals(lat2, half_pi) && math::equals(lat1, -half_pi));
    }

    static bool meridian_crossing_pole(CT diff)
    {
        return math::equals(math::abs(diff), math::pi<CT>());
    }


    template <typename T, typename Spheroid>
    static CT meridian_not_crossing_pole_dist(T lat1, T lat2, Spheroid const& spheroid)
    {
        return math::abs(apply(lat2, spheroid) - apply(lat1, spheroid));
    }

    template <typename T, typename Spheroid>
    static CT meridian_crossing_pole_dist(T lat1, T lat2, Spheroid const& spheroid)
    {
        CT c0 = 0;
        CT half_pi = math::pi<CT>()/CT(2);
        CT lat_sign = 1;
        if (lat1+lat2 < c0)
        {
            lat_sign = CT(-1);
        }
        return math::abs(lat_sign * CT(2) * apply(half_pi, spheroid)
                         - apply(lat1, spheroid) - apply(lat2, spheroid));
    }

    template <typename T, typename Spheroid>
    static result apply(T lon1, T lat1, T lon2, T lat2, Spheroid const& spheroid)
    {
        result res;

        CT diff = geometry::math::longitude_distance_signed<geometry::radian>(lon1, lon2);

        if (lat1 > lat2)
        {
            std::swap(lat1, lat2);
        }

        if ( meridian_not_crossing_pole(lat1, lat2, diff) )
        {
            res.distance = meridian_not_crossing_pole_dist(lat1, lat2, spheroid);
            res.meridian = true;
        }
        else if ( meridian_crossing_pole(diff) )
        {
            res.distance = meridian_crossing_pole_dist(lat1, lat2, spheroid);
            res.meridian = true;
        }
        return res;
    }

    // Distance computation on meridians using series approximations
    // to elliptic integrals. Formula to compute distance from lattitude 0 to lat
    // https://en.wikipedia.org/wiki/Meridian_arc
    // latitudes are assumed to be in radians and in [-pi/2,pi/2]
    template <typename T, typename Spheroid>
    static CT apply(T lat, Spheroid const& spheroid)
    {
        CT const a = get_radius<0>(spheroid);
        CT const f = formula::flattening<CT>(spheroid);
        CT n = f / (CT(2) - f);
        CT M = a/(1+n);
        CT C0 = 1;

        if (Order == 0)
        {
           return M * C0 * lat;
        }

        CT C2 = -1.5 * n;

        if (Order == 1)
        {
            return M * (C0 * lat + C2 * sin(2*lat));
        }

        CT n2 = n * n;
        C0 += .25 * n2;
        CT C4 = 0.9375 * n2;

        if (Order == 2)
        {
            return M * (C0 * lat + C2 * sin(2*lat) + C4 * sin(4*lat));
        }

        CT n3 = n2 * n;
        C2 += 0.1875 * n3;
        CT C6 = -0.729166667 * n3;

        if (Order == 3)
        {
            return M * (C0 * lat + C2 * sin(2*lat) + C4 * sin(4*lat)
                      + C6 * sin(6*lat));
        }

        CT n4 = n2 * n2;
        C4 -= 0.234375 * n4;
        CT C8 = 0.615234375 * n4;

        if (Order == 4)
        {
            return M * (C0 * lat + C2 * sin(2*lat) + C4 * sin(4*lat)
                      + C6 * sin(6*lat) + C8 * sin(8*lat));
        }

        CT n5 = n4 * n;
        C6 += 0.227864583 * n5;
        CT C10 = -0.54140625 * n5;

        // Order 5 or higher
        return M * (C0 * lat + C2 * sin(2*lat) + C4 * sin(4*lat)
                  + C6 * sin(6*lat) + C8 * sin(8*lat) + C10 * sin(10*lat));

    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_MERIDIAN_INVERSE_HPP

/* meridian_inverse.hpp
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
*/