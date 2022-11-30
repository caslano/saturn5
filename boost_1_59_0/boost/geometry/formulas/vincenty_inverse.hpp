// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2018 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2016, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_VINCENTY_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_VINCENTY_INVERSE_HPP


#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/formulas/differential_quantities.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_inverse.hpp>


#ifndef BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS
#define BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS 1000
#endif


namespace boost { namespace geometry { namespace formula
{

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates, after Vincenty, 1975
\author See
    - http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
    - http://www.icsm.gov.au/gda/gda-v_2.4.pdf
\author Adapted from various implementations to get it close to the original document
    - http://www.movable-type.co.uk/scripts/LatLongVincenty.html
    - http://exogen.case.edu/projects/geopy/source/geopy.distance.html
    - http://futureboy.homeip.net/fsp/colorize.fsp?fileName=navigation.frink

*/
template <
    typename CT,
    bool EnableDistance,
    bool EnableAzimuth,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false
>
struct vincenty_inverse
{
    static const bool CalcQuantities = EnableReducedLength || EnableGeodesicScale;
    static const bool CalcAzimuths = EnableAzimuth || EnableReverseAzimuth || CalcQuantities;
    static const bool CalcFwdAzimuth = EnableAzimuth || CalcQuantities;
    static const bool CalcRevAzimuth = EnableReverseAzimuth || CalcQuantities;

public:
    typedef result_inverse<CT> result_type;

    template <typename T1, typename T2, typename Spheroid>
    static inline result_type apply(T1 const& lon1,
                                    T1 const& lat1,
                                    T2 const& lon2,
                                    T2 const& lat2,
                                    Spheroid const& spheroid)
    {
        result_type result;

        if (math::equals(lat1, lat2) && math::equals(lon1, lon2))
        {
            return result;
        }

        CT const c0 = 0;
        CT const c1 = 1;
        CT const c2 = 2;
        CT const c3 = 3;
        CT const c4 = 4;
        CT const c16 = 16;
        CT const c_e_12 = CT(1e-12);

        CT const pi = geometry::math::pi<CT>();
        CT const two_pi = c2 * pi;

        // lambda: difference in longitude on an auxiliary sphere
        CT L = lon2 - lon1;
        CT lambda = L;

        if (L < -pi) L += two_pi;
        if (L > pi) L -= two_pi;

        CT const radius_a = CT(get_radius<0>(spheroid));
        CT const radius_b = CT(get_radius<2>(spheroid));
        CT const f = formula::flattening<CT>(spheroid);

        // U: reduced latitude, defined by tan U = (1-f) tan phi
        CT const one_min_f = c1 - f;
        CT const tan_U1 = one_min_f * tan(lat1); // above (1)
        CT const tan_U2 = one_min_f * tan(lat2); // above (1)

        // calculate sin U and cos U using trigonometric identities
        CT const temp_den_U1 = math::sqrt(c1 + math::sqr(tan_U1));
        CT const temp_den_U2 = math::sqrt(c1 + math::sqr(tan_U2));
        // cos = 1 / sqrt(1 + tan^2)
        CT const cos_U1 = c1 / temp_den_U1;
        CT const cos_U2 = c1 / temp_den_U2;
        // sin = tan / sqrt(1 + tan^2)
        // sin = tan * cos
        CT const sin_U1 = tan_U1 * cos_U1;
        CT const sin_U2 = tan_U2 * cos_U2;

        // calculate sin U and cos U directly
        //CT const U1 = atan(tan_U1);
        //CT const U2 = atan(tan_U2);
        //cos_U1 = cos(U1);
        //cos_U2 = cos(U2);
        //sin_U1 = tan_U1 * cos_U1; // sin(U1);
        //sin_U2 = tan_U2 * cos_U2; // sin(U2);

        CT previous_lambda;
        CT sin_lambda;
        CT cos_lambda;
        CT sin_sigma;
        CT sin_alpha;
        CT cos2_alpha;
        CT cos_2sigma_m;
        CT cos2_2sigma_m;
        CT sigma;

        int counter = 0; // robustness

        do
        {
            previous_lambda = lambda; // (13)
            sin_lambda = sin(lambda);
            cos_lambda = cos(lambda);
            sin_sigma = math::sqrt(math::sqr(cos_U2 * sin_lambda) + math::sqr(cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda)); // (14)
            CT cos_sigma = sin_U1 * sin_U2 + cos_U1 * cos_U2 * cos_lambda; // (15)
            sin_alpha = cos_U1 * cos_U2 * sin_lambda / sin_sigma; // (17)
            cos2_alpha = c1 - math::sqr(sin_alpha);
            cos_2sigma_m = math::equals(cos2_alpha, c0) ? c0 : cos_sigma - c2 * sin_U1 * sin_U2 / cos2_alpha; // (18)
            cos2_2sigma_m = math::sqr(cos_2sigma_m);

            CT C = f/c16 * cos2_alpha * (c4 + f * (c4 - c3 * cos2_alpha)); // (10)
            sigma = atan2(sin_sigma, cos_sigma); // (16)
            lambda = L + (c1 - C) * f * sin_alpha *
                (sigma + C * sin_sigma * (cos_2sigma_m + C * cos_sigma * (-c1 + c2 * cos2_2sigma_m))); // (11)

            ++counter; // robustness

        } while ( geometry::math::abs(previous_lambda - lambda) > c_e_12
               && geometry::math::abs(lambda) < pi
               && counter < BOOST_GEOMETRY_DETAIL_VINCENTY_MAX_STEPS ); // robustness
    
        if ( BOOST_GEOMETRY_CONDITION(EnableDistance) )
        {
            // Some types cannot divide by doubles
            CT const c6 = 6;
            CT const c47 = 47;
            CT const c74 = 74;
            CT const c128 = 128;
            CT const c256 = 256;
            CT const c175 = 175;
            CT const c320 = 320;
            CT const c768 = 768;
            CT const c1024 = 1024;
            CT const c4096 = 4096;
            CT const c16384 = 16384;

            //CT sqr_u = cos2_alpha * (math::sqr(radius_a) - math::sqr(radius_b)) / math::sqr(radius_b); // above (1)
            CT sqr_u = cos2_alpha * ( math::sqr(radius_a / radius_b) - c1 ); // above (1)

            CT A = c1 + sqr_u/c16384 * (c4096 + sqr_u * (-c768 + sqr_u * (c320 - c175 * sqr_u))); // (3)
            CT B = sqr_u/c1024 * (c256 + sqr_u * ( -c128 + sqr_u * (c74 - c47 * sqr_u))); // (4)
            CT const cos_sigma = cos(sigma);
            CT const sin2_sigma = math::sqr(sin_sigma);
            CT delta_sigma = B * sin_sigma * (cos_2sigma_m + (B/c4) * (cos_sigma* (-c1 + c2 * cos2_2sigma_m)
                - (B/c6) * cos_2sigma_m * (-c3 + c4 * sin2_sigma) * (-c3 + c4 * cos2_2sigma_m))); // (6)

            result.distance = radius_b * A * (sigma - delta_sigma); // (19)
        }
    
        if ( BOOST_GEOMETRY_CONDITION(CalcAzimuths) )
        {
            if (BOOST_GEOMETRY_CONDITION(CalcFwdAzimuth))
            {
                result.azimuth = atan2(cos_U2 * sin_lambda, cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda); // (20)
            }

            if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
            {
                result.reverse_azimuth = atan2(cos_U1 * sin_lambda, -sin_U1 * cos_U2 + cos_U1 * sin_U2 * cos_lambda); // (21)
            }
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            typedef differential_quantities<CT, EnableReducedLength, EnableGeodesicScale, 2> quantities;
            quantities::apply(lon1, lat1, lon2, lat2,
                              result.azimuth, result.reverse_azimuth,
                              radius_b, f,
                              result.reduced_length, result.geodesic_scale);
        }

        return result;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_VINCENTY_INVERSE_HPP

/* vincenty_inverse.hpp
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
*/