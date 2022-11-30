// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

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
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

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

        if (BOOST_GEOMETRY_CONDITION(CalcCoordinates))
        {
            // For longitudes close to the antimeridian the result can be out
            // of range. Therefore normalize.
            // It has to be done at the end because otherwise differential
            // quantities are calculated incorrectly.
            math::detail::normalize_angle_cond<radian>(result.lon2);
        }

        return result;
    }

};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_VINCENTY_DIRECT_HPP

/* vincenty_direct.hpp
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
*/