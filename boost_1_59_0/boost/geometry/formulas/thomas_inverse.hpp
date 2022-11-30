// Boost.Geometry

// Copyright (c) 2015-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_THOMAS_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_THOMAS_INVERSE_HPP


#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/formulas/differential_quantities.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_inverse.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates,
       Forsyth-Andoyer-Lambert type approximation with second order terms.
\author See
    - Technical Report: PAUL D. THOMAS, MATHEMATICAL MODELS FOR NAVIGATION SYSTEMS, 1965
      http://www.dtic.mil/docs/citations/AD0627893
    - Technical Report: PAUL D. THOMAS, SPHEROIDAL GEODESICS, REFERENCE SYSTEMS, AND LOCAL GEOMETRY, 1970
      http://www.dtic.mil/docs/citations/AD0703541
*/
template <
    typename CT,
    bool EnableDistance,
    bool EnableAzimuth,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false
>
class thomas_inverse
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

        // coordinates in radians

        if ( math::equals(lon1, lon2) && math::equals(lat1, lat2) )
        {
            return result;
        }

        CT const c0 = 0;
        CT const c1 = 1;
        CT const c2 = 2;
        CT const c4 = 4;

        CT const pi_half = math::pi<CT>() / c2;
        CT const f = formula::flattening<CT>(spheroid);
        CT const one_minus_f = c1 - f;

//        CT const tan_theta1 = one_minus_f * tan(lat1);
//        CT const tan_theta2 = one_minus_f * tan(lat2);
//        CT const theta1 = atan(tan_theta1);
//        CT const theta2 = atan(tan_theta2);

        CT const theta1 = math::equals(lat1, pi_half) ? lat1 :
                          math::equals(lat1, -pi_half) ? lat1 :
                          atan(one_minus_f * tan(lat1));
        CT const theta2 = math::equals(lat2, pi_half) ? lat2 :
                          math::equals(lat2, -pi_half) ? lat2 :
                          atan(one_minus_f * tan(lat2));

        CT const theta_m = (theta1 + theta2) / c2;
        CT const d_theta_m = (theta2 - theta1) / c2;
        CT const d_lambda = lon2 - lon1;
        CT const d_lambda_m = d_lambda / c2;

        CT const sin_theta_m = sin(theta_m);
        CT const cos_theta_m = cos(theta_m);
        CT const sin_d_theta_m = sin(d_theta_m);
        CT const cos_d_theta_m = cos(d_theta_m);
        CT const sin2_theta_m = math::sqr(sin_theta_m);
        CT const cos2_theta_m = math::sqr(cos_theta_m);
        CT const sin2_d_theta_m = math::sqr(sin_d_theta_m);
        CT const cos2_d_theta_m = math::sqr(cos_d_theta_m);
        CT const sin_d_lambda_m = sin(d_lambda_m);
        CT const sin2_d_lambda_m = math::sqr(sin_d_lambda_m);

        CT const H = cos2_theta_m - sin2_d_theta_m;
        CT const L = sin2_d_theta_m + H * sin2_d_lambda_m;
        CT const cos_d = c1 - c2 * L;
        CT const d = acos(cos_d);
        CT const sin_d = sin(d);

        CT const one_minus_L = c1 - L;

        if ( math::equals(sin_d, c0)
          || math::equals(L, c0)
          || math::equals(one_minus_L, c0) )
        {
            return result;
        }

        CT const U = c2 * sin2_theta_m * cos2_d_theta_m / one_minus_L;
        CT const V = c2 * sin2_d_theta_m * cos2_theta_m / L;
        CT const X = U + V;
        CT const Y = U - V;
        CT const T = d / sin_d;
        CT const D = c4 * math::sqr(T);
        CT const E = c2 * cos_d;
        CT const A = D * E;
        CT const B = c2 * D;
        CT const C = T - (A - E) / c2;

        CT const f_sqr = math::sqr(f);
        CT const f_sqr_per_64 = f_sqr / CT(64);
    
        if ( BOOST_GEOMETRY_CONDITION(EnableDistance) )
        {
            CT const n1 = X * (A + C*X);
            CT const n2 = Y * (B + E*Y);
            CT const n3 = D*X*Y;

            CT const delta1d = f * (T*X-Y) / c4;
            CT const delta2d = f_sqr_per_64 * (n1 - n2 + n3);

            CT const a = get_radius<0>(spheroid);

            //result.distance = a * sin_d * (T - delta1d);
            result.distance = a * sin_d * (T - delta1d + delta2d);
        }
    
        if ( BOOST_GEOMETRY_CONDITION(CalcAzimuths) )
        {
            // NOTE: if both cos_latX == 0 then below we'd have 0 * INF
            // it's a situation when the endpoints are on the poles +-90 deg
            // in this case the azimuth could either be 0 or +-pi
            // but above always 0 is returned

            CT const F = c2*Y-E*(c4-X);
            CT const M = CT(32)*T-(CT(20)*T-A)*X-(B+c4)*Y;
            CT const G = f*T/c2 + f_sqr_per_64 * M;
            
            // TODO:
            // If d_lambda is close to 90 or -90 deg then tan(d_lambda) is big
            // and F is small. The result is not accurate.
            // In the edge case the result may be 2 orders of magnitude less
            // accurate than Andoyer's.
            CT const tan_d_lambda = tan(d_lambda);
            CT const Q = -(F*G*tan_d_lambda) / c4;
            CT const d_lambda_m_p = (d_lambda + Q) / c2;
            CT const tan_d_lambda_m_p = tan(d_lambda_m_p);

            CT const v = atan2(cos_d_theta_m, sin_theta_m * tan_d_lambda_m_p);
            CT const u = atan2(-sin_d_theta_m, cos_theta_m * tan_d_lambda_m_p);

            CT const pi = math::pi<CT>();

            if (BOOST_GEOMETRY_CONDITION(CalcFwdAzimuth))
            {
                CT alpha1 = v + u;
                if (alpha1 > pi)
                {
                    alpha1 -= c2 * pi;
                }

                result.azimuth = alpha1;
            }

            if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
            {
                CT alpha2 = pi - (v - u);
                if (alpha2 > pi)
                {
                    alpha2 -= c2 * pi;
                }

                result.reverse_azimuth = alpha2;
            }
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            typedef differential_quantities<CT, EnableReducedLength, EnableGeodesicScale, 2> quantities;
            quantities::apply(lon1, lat1, lon2, lat2,
                              result.azimuth, result.reverse_azimuth,
                              get_radius<2>(spheroid), f,
                              result.reduced_length, result.geodesic_scale);
        }

        return result;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_THOMAS_INVERSE_HPP

/* thomas_inverse.hpp
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
*/