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
1wXML99XQIZEBmMKuOC7GOQHoxOsoTbQj0J0dPJqlYW88BfHQ/LMZ/rE8JlSNAPGuwqYkTRp4M/S7LvZlHIjtb6ZzJeHbc+qeOIPN7DQx58N5LTqV7Zzv07nosr/OPmFe5ftMBN4bhvWHVv6rVdQvq9uWZcmHj+/0vi2kKIX/mjiP/qU8rULkuvfXAC9FnYvNEbeT/LPxrghILFBzU0F+AgyPjx9/vBlO4/k3P1EhXnMl7GNCK2eBvZEHoN5snpdyDai8ZWoZAnigizxEA1SFUkR0AjXQQsbyrR/l4UEIfqQGQkfYJtHh3+npiL+30e0KY6Fosvq4MRi7QWFCcqKqDruZCcCdMPXs/2DmmNVn8lyKgrO8jaF9UqTOf0lpv/CpM2ELBu125MJ8YzcUJyrIHOcciQv3STJWGdmLocHHTYtC6x/ooEhPzuPboYAkwFrZ5fq9u89ZG1t67TRjc6yZoIfeyKa1hj3li6UgHbWnxYgOilEWxPMf0O99nEACY7rr7MFxUi74FlecU++4rwVH2hUOUpe+/GIze0bqEsEVgtZz7Ocp0SxCx/cvA==
*/