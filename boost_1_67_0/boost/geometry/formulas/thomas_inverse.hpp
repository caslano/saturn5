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