// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2016, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_VINCENTY_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_VINCENTY_DIRECT_HPP


#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/formulas/differential_quantities.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_direct.hpp>


#ifndef BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS
#define BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS 1000
#endif


namespace boost { namespace geometry { namespace formula
{

/*!
\brief The solution of the direct problem of geodesics on latlong coordinates, after Vincenty, 1975
\author See
    - http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
    - http://www.icsm.gov.au/gda/gdav2.3.pdf
\author Adapted from various implementations to get it close to the original document
    - http://www.movable-type.co.uk/scripts/LatLongVincenty.html
    - http://exogen.case.edu/projects/geopy/source/geopy.distance.html
    - http://futureboy.homeip.net/fsp/colorize.fsp?fileName=navigation.frink

*/
template <
    typename CT,
    bool EnableCoordinates = true,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false
>
class vincenty_direct
{
    static const bool CalcQuantities = EnableReducedLength || EnableGeodesicScale;
    static const bool CalcCoordinates = EnableCoordinates || CalcQuantities;
    static const bool CalcRevAzimuth = EnableReverseAzimuth || CalcQuantities;

public:
    typedef result_direct<CT> result_type;

    template <typename T, typename Dist, typename Azi, typename Spheroid>
    static inline result_type apply(T const& lo1,
                                    T const& la1,
                                    Dist const& distance,
                                    Azi const& azimuth12,
                                    Spheroid const& spheroid)
    {
        result_type result;

        CT const lon1 = lo1;
        CT const lat1 = la1;

        CT const radius_a = CT(get_radius<0>(spheroid));
        CT const radius_b = CT(get_radius<2>(spheroid));
        CT const flattening = formula::flattening<CT>(spheroid);

        CT const sin_azimuth12 = sin(azimuth12);
        CT const cos_azimuth12 = cos(azimuth12);

        // U: reduced latitude, defined by tan U = (1-f) tan phi
        CT const one_min_f = CT(1) - flattening;
        CT const tan_U1 = one_min_f * tan(lat1);
        CT const sigma1 = atan2(tan_U1, cos_azimuth12); // (1)

        // may be calculated from tan using 1 sqrt()
        CT const U1 = atan(tan_U1);
        CT const sin_U1 = sin(U1);
        CT const cos_U1 = cos(U1);

        CT const sin_alpha = cos_U1 * sin_azimuth12; // (2)
        CT const sin_alpha_sqr = math::sqr(sin_alpha);
        CT const cos_alpha_sqr = CT(1) - sin_alpha_sqr;

        CT const b_sqr = radius_b * radius_b;
        CT const u_sqr = cos_alpha_sqr * (radius_a * radius_a - b_sqr) / b_sqr;
        CT const A = CT(1) + (u_sqr/CT(16384)) * (CT(4096) + u_sqr*(CT(-768) + u_sqr*(CT(320) - u_sqr*CT(175)))); // (3)
        CT const B = (u_sqr/CT(1024))*(CT(256) + u_sqr*(CT(-128) + u_sqr*(CT(74) - u_sqr*CT(47)))); // (4)

        CT s_div_bA = distance / (radius_b * A);
        CT sigma = s_div_bA; // (7)

        CT previous_sigma;
        CT sin_sigma;
        CT cos_sigma;
        CT cos_2sigma_m;
        CT cos_2sigma_m_sqr;

        int counter = 0; // robustness

        do
        {
            previous_sigma = sigma;

            CT const two_sigma_m = CT(2) * sigma1 + sigma; // (5)

            sin_sigma = sin(sigma);
            cos_sigma = cos(sigma);
            CT const sin_sigma_sqr = math::sqr(sin_sigma);
            cos_2sigma_m = cos(two_sigma_m);
            cos_2sigma_m_sqr = math::sqr(cos_2sigma_m);

            CT const delta_sigma = B * sin_sigma * (cos_2sigma_m
                                        + (B/CT(4)) * ( cos_sigma * (CT(-1) + CT(2)*cos_2sigma_m_sqr)
                                            - (B/CT(6) * cos_2sigma_m * (CT(-3)+CT(4)*sin_sigma_sqr) * (CT(-3)+CT(4)*cos_2sigma_m_sqr)) )); // (6)

            sigma = s_div_bA + delta_sigma; // (7)

            ++counter; // robustness

        } while ( geometry::math::abs(previous_sigma - sigma) > CT(1e-12)
               //&& geometry::math::abs(sigma) < pi
               && counter < BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS ); // robustness

        if (BOOST_GEOMETRY_CONDITION(CalcCoordinates))
        {
            result.lat2
                = atan2( sin_U1 * cos_sigma + cos_U1 * sin_sigma * cos_azimuth12,
                         one_min_f * math::sqrt(sin_alpha_sqr + math::sqr(sin_U1 * sin_sigma - cos_U1 * cos_sigma * cos_azimuth12))); // (8)
            
            CT const lambda = atan2( sin_sigma * sin_azimuth12,
                                     cos_U1 * cos_sigma - sin_U1 * sin_sigma * cos_azimuth12); // (9)
            CT const C = (flattening/CT(16)) * cos_alpha_sqr * ( CT(4) + flattening * ( CT(4) - CT(3) * cos_alpha_sqr ) ); // (10)
            CT const L = lambda - (CT(1) - C) * flattening * sin_alpha
                            * ( sigma + C * sin_sigma * ( cos_2sigma_m + C * cos_sigma * ( CT(-1) + CT(2) * cos_2sigma_m_sqr ) ) ); // (11)

            result.lon2 = lon1 + L;
        }

        if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
        {
            result.reverse_azimuth
                = atan2(sin_alpha, -sin_U1 * sin_sigma + cos_U1 * cos_sigma * cos_azimuth12); // (12)
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            typedef differential_quantities<CT, EnableReducedLength, EnableGeodesicScale, 2> quantities;
            quantities::apply(lon1, lat1, result.lon2, result.lat2,
                              azimuth12, result.reverse_azimuth,
                              radius_b, flattening,
                              result.reduced_length, result.geodesic_scale);
        }

        return result;
    }

};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_VINCENTY_DIRECT_HPP

/* vincenty_direct.hpp
xFDy68PvI8bYWNz2PMR9ZDrJbvTPxKvhv/XdLmg/VJZjmW5bQf+q4c5kmvEEA169TvcFrbxMvW+9qkAamVrDVPQNgD0sL6WTmU48HMeZMra1VemBxdRq+AKS1gz/Qyp816peCN/XgeWzmH4asFeXlcEnWHVQoNqnwQu53Vj1M2o3xtHqZ+tz2vf7Uz4Z69fnyB1S58Ws+RttG9xuAA8g29C+LMJiPPmZ9rEbUoex7tNZk6csHhD3O7eLua4XRL67M+4hVoupnte023DScb3vXsM2VvkTW30n869sB1bbEKRDtt7OtMM2iuXcnML7hu9O8Yg3E7ZBb/Mi3w8v4HZntYfaHbs7yx6Ke5RaT7TGS2FNRDi7AU9RWKlmW8W0Q4A9HI+1rcpgPfIWKvt5Q9mPn854Qc630LCfv0j7SVT2w/S+oO/VZZX9+KPtJ4PtZ24F28/q2dJ+gv5xrdvOsgF6Pqbyuuwd5P6kN0P7hKc/+Sk72O1/WLtc+6NjpXjdebP4iutmUeB5RUtFeXOZx9oWn0XaTGEu8noQZi75cZg46/m05tEedz4olrq2iVOeOmEJr9X+awmFmRNhP58kvyy9/2qj/fRn+1G27tDuFK86Pi/ucn5ZTHAdFre41+D08Qca66Tv3SxEe1Cu7Gq10Z+1wO9IubKRzaaNMO00YA/LRNgIhzmrAjZC9KJAlW4jCZL2DuT6VigbWb2Y3hVVNsL0QtD36rKQc0kbSfBF2UiIbWQ3eHcSr2zuOjil/zz4baxQuo+UurtIhmk7KvR1IQhAzAw3lcM8CPrCkNx7Wv2y1R773oa13k4yzF+hj+6CcJ1ZUe96xb4LxmsSv6LyLOA1CutcJtkvy8Iaz4HbeB9nTQU64UQ3joJa36a3fed+eB6dERNZMX3iVsdzjiUe1c+pdsMvz9lH7Z+WURhuYR0nrFmkn8WVCV4zmr7Z7sD4QBaLPK3qTmzljZgJFF7uBbTDD1rbYdu3ZiZTPH2NseZ6cjsj8nXfIi6/NR/alp/Vto4sYjtwr/lNECeArX3bOWRcmMro0cAktE2uoTiGfZ712mdJp7FtGg/T2RriXyn6k7t9bZddW/M8hXl5xLrvV9mvtbHy5Nixcpz25lktqq1hvcz25ijydNtibm/WvBi/H+M6c4D0auY9uuj5vxlmMsJbAXiKwvyO2VYxbStgD8cX0VaxPmdB30n0L4DuDYJFSFoL/I8Z4T4rRy+0yExhM/0dwC6WtYYd0W7UsK2svZFsxT+0dTu5baBM520ig9wq3RMxv/T5M/0JIs+fFGsz3D+tItkHxcXqmxYPjLWXJQMvnr2gf2rVXkQVxj3VbC9rb2/VXupIr8fPay+jEN5uwFMU5irTXph2CLCH44uwF9Ynpwb2QvRbI+zlCOR8NSrc2yLthek9Qd/Fsirs6Pl2GXi8ZC8veBxop5KdXuBeMi5/9LvFVjs7XsvjpXVZbRovjcyPHGuPJnelGE/ueG31o+1uq+PZ6ByKZ9tFs9HhFF6viPHT9eSXfYHjJ90+0abZ2qfc8KysZftcN6VV+5xCOu04r32eWCLE1Fq2o3VzTPtkWjloezi+iLUE1ucY6E8T/Qr0cyn66IvXhWpA212rxl/rhsrxl+y3yP6YfhSwV5cP3Ba5jCDi2WtaHdvruk+3y16HN7C9rs/X7XVM6/Y6ZxCtL7S7XZTtVgXJjuNxyMWxbbv54FSK64qI9dNZ5NfDdj5IdtqONpP72bg2mV6HMWw92+T6Txhj+nr4bQc8Rf4Vpl0x7SXAHpax2lV3DnNoA+yK6MMCi/WDUXwqS7etQ/VIa4OyrfUT6QNcOK5F61RMHwz6Xj0Mnv+BQe7d+vQTWfE=
*/