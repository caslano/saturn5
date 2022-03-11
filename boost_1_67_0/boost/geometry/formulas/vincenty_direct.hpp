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
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
*/