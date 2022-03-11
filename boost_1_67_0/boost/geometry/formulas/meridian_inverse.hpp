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