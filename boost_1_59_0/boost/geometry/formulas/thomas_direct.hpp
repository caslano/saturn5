// Boost.Geometry

// Copyright (c) 2016-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_THOMAS_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_THOMAS_DIRECT_HPP


#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/formulas/differential_quantities.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_direct.hpp>


namespace boost { namespace geometry { namespace formula
{


/*!
\brief The solution of the direct problem of geodesics on latlong coordinates,
       Forsyth-Andoyer-Lambert type approximation with first/second order terms.
\author See
    - Technical Report: PAUL D. THOMAS, MATHEMATICAL MODELS FOR NAVIGATION SYSTEMS, 1965
      http://www.dtic.mil/docs/citations/AD0627893
    - Technical Report: PAUL D. THOMAS, SPHEROIDAL GEODESICS, REFERENCE SYSTEMS, AND LOCAL GEOMETRY, 1970
      http://www.dtic.mil/docs/citations/AD0703541
*/
template <
    typename CT,
    bool SecondOrder = true,
    bool EnableCoordinates = true,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false
>
class thomas_direct
{
    static const bool CalcQuantities = EnableReducedLength || EnableGeodesicScale;
    static const bool CalcCoordinates = EnableCoordinates || CalcQuantities;
    static const bool CalcRevAzimuth = EnableReverseAzimuth || CalcCoordinates || CalcQuantities;

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

        CT const c0 = 0;
        CT const c1 = 1;
        CT const c2 = 2;
        CT const c4 = 4;

        CT const a = CT(get_radius<0>(spheroid));
        CT const b = CT(get_radius<2>(spheroid));
        CT const f = formula::flattening<CT>(spheroid);
        CT const one_minus_f = c1 - f;

        CT const pi = math::pi<CT>();
        CT const pi_half = pi / c2;

        BOOST_GEOMETRY_ASSERT(-pi <= azimuth12 && azimuth12 <= pi);

        // keep azimuth small - experiments show low accuracy
        // if the azimuth is closer to (+-)180 deg.
        CT azi12_alt = azimuth12;
        CT lat1_alt = lat1;
        bool alter_result = vflip_if_south(lat1, azimuth12, lat1_alt, azi12_alt);

        CT const theta1 = math::equals(lat1_alt, pi_half) ? lat1_alt :
                          math::equals(lat1_alt, -pi_half) ? lat1_alt :
                          atan(one_minus_f * tan(lat1_alt));
        CT const sin_theta1 = sin(theta1);
        CT const cos_theta1 = cos(theta1);

        CT const sin_a12 = sin(azi12_alt);
        CT const cos_a12 = cos(azi12_alt);

        CT const M = cos_theta1 * sin_a12; // cos_theta0
        CT const theta0 = acos(M);
        CT const sin_theta0 = sin(theta0);

        CT const N = cos_theta1 * cos_a12;
        CT const C1 = f * M; // lower-case c1 in the technical report
        CT const C2 = f * (c1 - math::sqr(M)) / c4; // lower-case c2 in the technical report
        CT D = 0;
        CT P = 0;
        if ( BOOST_GEOMETRY_CONDITION(SecondOrder) )
        {
            D = (c1 - C2) * (c1 - C2 - C1 * M);
            P = C2 * (c1 + C1 * M / c2) / D;
        }
        else
        {
            D = c1 - c2 * C2 - C1 * M;
            P = C2 / D;
        }
        // special case for equator:
        // sin_theta0 = 0 <=> lat1 = 0 ^ |azimuth12| = pi/2
        // NOTE: in this case it doesn't matter what's the value of cos_sigma1 because
        //       theta1=0, theta0=0, M=1|-1, C2=0 so X=0 and Y=0 so d_sigma=d
        //       cos_a12=0 so N=0, therefore
        //       lat2=0, azi21=pi/2|-pi/2
        //       d_eta = atan2(sin_d_sigma, cos_d_sigma)
        //       H = C1 * d_sigma
        CT const cos_sigma1 = math::equals(sin_theta0, c0)
                                ? c1
                                : normalized1_1(sin_theta1 / sin_theta0);
        CT const sigma1 = acos(cos_sigma1);
        CT const d = distance / (a * D);
        CT const u = 2 * (sigma1 - d);
        CT const cos_d = cos(d);
        CT const sin_d = sin(d);
        CT const cos_u = cos(u);
        CT const sin_u = sin(u);

        CT const W = c1 - c2 * P * cos_u;
        CT const V = cos_u * cos_d - sin_u * sin_d;
        CT const Y = c2 * P * V * W * sin_d;
        CT X = 0;
        CT d_sigma = d - Y;
        if ( BOOST_GEOMETRY_CONDITION(SecondOrder) )
        {
            X = math::sqr(C2) * sin_d * cos_d * (2 * math::sqr(V) - c1);
            d_sigma += X;
        }
        CT const sin_d_sigma = sin(d_sigma);
        CT const cos_d_sigma = cos(d_sigma);

        if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
        {
            result.reverse_azimuth = atan2(M, N * cos_d_sigma - sin_theta1 * sin_d_sigma);

            if (alter_result)
            {
                vflip_rev_azi(result.reverse_azimuth, azimuth12);
            }
        }

        if (BOOST_GEOMETRY_CONDITION(CalcCoordinates))
        {
            CT const S_sigma = c2 * sigma1 - d_sigma;
            CT cos_S_sigma = 0;
            CT H = C1 * d_sigma;
            if ( BOOST_GEOMETRY_CONDITION(SecondOrder) )
            {
                cos_S_sigma = cos(S_sigma);
                H = H * (c1 - C2) - C1 * C2 * sin_d_sigma * cos_S_sigma;
            }
            CT const d_eta = atan2(sin_d_sigma * sin_a12, cos_theta1 * cos_d_sigma - sin_theta1 * sin_d_sigma * cos_a12);
            CT const d_lambda = d_eta - H;

            result.lon2 = lon1 + d_lambda;

            if (! math::equals(M, c0))
            {
                CT const sin_a21 = sin(result.reverse_azimuth);
                CT const tan_theta2 = (sin_theta1 * cos_d_sigma + N * sin_d_sigma) * sin_a21 / M;
                result.lat2 = atan(tan_theta2 / one_minus_f);
            }
            else
            {
                CT const sigma2 = S_sigma - sigma1;
                //theta2 = asin(cos(sigma2)) <=> sin_theta0 = 1
                // NOTE: cos(sigma2) defines the sign of tan_theta2
                CT const tan_theta2 = cos(sigma2) / math::abs(sin(sigma2));
                result.lat2 = atan(tan_theta2 / one_minus_f);
            }

            if (alter_result)
            {
                result.lat2 = -result.lat2;
            }
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            typedef differential_quantities<CT, EnableReducedLength, EnableGeodesicScale, 2> quantities;
            quantities::apply(lon1, lat1, result.lon2, result.lat2,
                              azimuth12, result.reverse_azimuth,
                              b, f,
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

private:
    static inline bool vflip_if_south(CT const& lat1, CT const& azi12, CT & lat1_alt, CT & azi12_alt)
    {
        CT const c2 = 2;
        CT const pi = math::pi<CT>();
        CT const pi_half = pi / c2;

        if (azi12 > pi_half)
        {
            azi12_alt = pi - azi12;
            lat1_alt = -lat1;
            return true;
        }
        else if (azi12 < -pi_half)
        {
            azi12_alt = -pi - azi12;
            lat1_alt = -lat1;
            return true;
        }

        return false;
    }

    static inline void vflip_rev_azi(CT & rev_azi, CT const& azimuth12)
    {
        CT const c0 = 0;
        CT const pi = math::pi<CT>();

        if (rev_azi == c0)
        {
            rev_azi = azimuth12 >= 0 ? pi : -pi;
        }
        else if (rev_azi > c0)
        {
            rev_azi = pi - rev_azi;
        }
        else
        {
            rev_azi = -pi - rev_azi;
        }
    }

    static inline CT normalized1_1(CT const& value)
    {
        CT const c1 = 1;
        return value > c1 ? c1 :
               value < -c1 ? -c1 :
               value;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_THOMAS_DIRECT_HPP

/* thomas_direct.hpp
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
*/