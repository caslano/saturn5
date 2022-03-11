// Boost.Geometry

// Copyright (c) 2016-2018 Oracle and/or its affiliates.

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