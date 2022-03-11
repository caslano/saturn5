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
            // Oops getting hard here
            // (again, problem is that ttmath cannot divide by doubles, which is OK)
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