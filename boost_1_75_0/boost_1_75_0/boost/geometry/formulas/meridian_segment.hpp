// Boost.Geometry

// Copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP
#define BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP

#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Test if a segment is meridian or not.
*/

class meridian_segment
{

public :

    enum SegmentType {NonMeridian, MeridianCrossingPole, MeridianNotCrossingPole};

    template <typename T>
    static inline SegmentType is_meridian(T lon1, T lat1, T lon2, T lat2)
    {
        SegmentType res = NonMeridian;
        T diff = geometry::math::longitude_distance_signed<geometry::radian>(lon1, lon2);

        if ( meridian_not_crossing_pole(lat1, lat2, diff) )
        {
            res = MeridianNotCrossingPole;
        }
        else if ( meridian_crossing_pole(diff) )
        {
            res = MeridianCrossingPole;
        }
        return res;
    }

    template <typename T>
    static bool meridian_not_crossing_pole(T lat1, T lat2, T diff)
    {
        T half_pi = math::half_pi<T>();
        return math::equals(diff, T(0)) ||
               (math::equals(lat2, half_pi) && math::equals(lat1, -half_pi));
    }

    template <typename T>
    static bool meridian_crossing_pole(T diff)
    {
        return math::equals(math::abs(diff), math::pi<T>());
    }

};

}}} // namespace boost::geometry::formula

#endif //BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP

/* meridian_segment.hpp
Ez9TN2B/xz/nuxw0Jel8Pr91blNnb0QYEAjZ9RDbdTdhiuNQVgDBA59OgnrumzV/sJr+fYsnq943oSHPMyzy77eHFYLvZ4gY3eBIymU4M09n9GPMS9dozOex0I8RlD1BPoM2bsbKwJL7/jeZ7YJub54f2tErU2iEBGJPLEZ/2nKt+P1YaamrHJ4+mPnwPPu5fq25Ua7v8VY7tTD8+L7w63bA/pUWTE3cwGv4fKrky4KB5xfPAP4XVV9v55mlT+pciCwPWZaP53F8cLd+fcn4gb/rmOTOotuGpMunwCeTbLVKb3Odoh9MldAU/YCGrewT7S+VsyyfNZqFyGh99XusAatw4GwMbLQ+jnlsRYU8cci4F/WRSi7G3NmfHdoTv5z/BbToqa5Q356ydYY6C1mWHfm1Y8lUO5DaIIPsaL2sO5pQLReueN/bgh3ebe4dXo/NYr+Csd3lleboZnBvUSnX7UonO67VMl6qeU0ruS+c+bvrWk3MOoCLI/IVU2xpS74dQHZgeN1r9+6YkIYrqy7LyBQG7MdIPv6WO//ezoZMNe0wqd959CO4ofzqnmij4MOuLLcdtR1aZbu3s7Wo2svWcXuCLa/B06TQJAOwGBrYtCqUgJluuM1kV9s6O79VkP/FtZPNKmtNSPR6UbNhdC8azDZV8XgkyX2bcE9DJ4bA5hWTx3g+jVbmhCj8nTdXhNDX2hok20Kr7vdEbqos
*/