// Boost.Geometry

// Copyright (c) 2018 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2015-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_ANDOYER_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_ANDOYER_INVERSE_HPP


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
       Forsyth-Andoyer-Lambert type approximation with first order terms.
\author See
    - Technical Report: PAUL D. THOMAS, MATHEMATICAL MODELS FOR NAVIGATION SYSTEMS, 1965
      http://www.dtic.mil/docs/citations/AD0627893
    - Technical Report: PAUL D. THOMAS, SPHEROIDAL GEODESICS, REFERENCE SYSTEMS, AND LOCAL GEOMETRY, 1970
      http://www.dtic.mil/docs/citations/AD703541
*/
template <
    typename CT,
    bool EnableDistance,
    bool EnableAzimuth,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false
>
class andoyer_inverse
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

        CT const c0 = CT(0);
        CT const c1 = CT(1);
        CT const pi = math::pi<CT>();
        CT const f = formula::flattening<CT>(spheroid);

        CT const dlon = lon2 - lon1;
        CT const sin_dlon = sin(dlon);
        CT const cos_dlon = cos(dlon);
        CT const sin_lat1 = sin(lat1);
        CT const cos_lat1 = cos(lat1);
        CT const sin_lat2 = sin(lat2);
        CT const cos_lat2 = cos(lat2);

        // H,G,T = infinity if cos_d = 1 or cos_d = -1
        // lat1 == +-90 && lat2 == +-90
        // lat1 == lat2 && lon1 == lon2
        CT cos_d = sin_lat1*sin_lat2 + cos_lat1*cos_lat2*cos_dlon;
        // on some platforms cos_d may be outside valid range
        if (cos_d < -c1)
            cos_d = -c1;
        else if (cos_d > c1)
            cos_d = c1;

        CT const d = acos(cos_d); // [0, pi]
        CT const sin_d = sin(d);  // [-1, 1]

        if ( BOOST_GEOMETRY_CONDITION(EnableDistance) )
        {
            CT const K = math::sqr(sin_lat1-sin_lat2);
            CT const L = math::sqr(sin_lat1+sin_lat2);
            CT const three_sin_d = CT(3) * sin_d;

            CT const one_minus_cos_d = c1 - cos_d;
            CT const one_plus_cos_d = c1 + cos_d;
            // cos_d = 1 means that the points are very close
            // cos_d = -1 means that the points are antipodal

            CT const H = math::equals(one_minus_cos_d, c0) ?
                            c0 :
                            (d + three_sin_d) / one_minus_cos_d;
            CT const G = math::equals(one_plus_cos_d, c0) ?
                            c0 :
                            (d - three_sin_d) / one_plus_cos_d;

            CT const dd = -(f/CT(4))*(H*K+G*L);

            CT const a = CT(get_radius<0>(spheroid));

            result.distance = a * (d + dd);
        }

        if ( BOOST_GEOMETRY_CONDITION(CalcAzimuths) )
        {
            // sin_d = 0 <=> antipodal points (incl. poles) or very close
            if (math::equals(sin_d, c0))
            {
                // T = inf
                // dA = inf
                // azimuth = -inf

                // TODO: The following azimuths are inconsistent with distance
                // i.e. according to azimuths below a segment with antipodal endpoints
                // travels through the north pole, however the distance returned above
                // is the length of a segment traveling along the equator.
                // Furthermore, this special case handling is only done in andoyer
                // formula.
                // The most correct way of fixing it is to handle antipodal regions
                // correctly and consistently across all formulas.

                // points very close
                if (cos_d >= c0)
                {
                    result.azimuth = c0;
                    result.reverse_azimuth = c0;
                }
                // antipodal points
                else
                {
                    // Set azimuth to 0 unless the first endpoint is the north pole
                    if (! math::equals(sin_lat1, c1))
                    {
                        result.azimuth = c0;
                        result.reverse_azimuth = pi;
                    }
                    else
                    {
                        result.azimuth = pi;
                        result.reverse_azimuth = c0;
                    }
                }
            }
            else
            {
                CT const c2 = CT(2);

                CT A = c0;
                CT U = c0;
                if (math::equals(cos_lat2, c0))
                {
                    if (sin_lat2 < c0)
                    {
                        A = pi;
                    }
                }
                else
                {
                    CT const tan_lat2 = sin_lat2/cos_lat2;
                    CT const M = cos_lat1*tan_lat2-sin_lat1*cos_dlon;
                    A = atan2(sin_dlon, M);
                    CT const sin_2A = sin(c2*A);
                    U = (f/ c2)*math::sqr(cos_lat1)*sin_2A;
                }

                CT B = c0;
                CT V = c0;
                if (math::equals(cos_lat1, c0))
                {
                    if (sin_lat1 < c0)
                    {
                        B = pi;
                    }
                }
                else
                {
                    CT const tan_lat1 = sin_lat1/cos_lat1;
                    CT const N = cos_lat2*tan_lat1-sin_lat2*cos_dlon;
                    B = atan2(sin_dlon, N);
                    CT const sin_2B = sin(c2*B);
                    V = (f/ c2)*math::sqr(cos_lat2)*sin_2B;
                }

                CT const T = d / sin_d;

                // even with sin_d == 0 checked above if the second point
                // is somewhere in the antipodal area T may still be great
                // therefore dA and dB may be great and the resulting azimuths
                // may be some more or less arbitrary angles

                if (BOOST_GEOMETRY_CONDITION(CalcFwdAzimuth))
                {
                    CT const dA = V*T - U;
                    result.azimuth = A - dA;
                    normalize_azimuth(result.azimuth, A, dA);
                }

                if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
                {
                    CT const dB = -U*T + V;
                    if (B >= 0)
                        result.reverse_azimuth = pi - B - dB;
                    else
                        result.reverse_azimuth = -pi - B - dB;
                    normalize_azimuth(result.reverse_azimuth, B, dB);
                }
            }
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            CT const b = CT(get_radius<2>(spheroid));

            typedef differential_quantities<CT, EnableReducedLength, EnableGeodesicScale, 1> quantities;
            quantities::apply(dlon, sin_lat1, cos_lat1, sin_lat2, cos_lat2,
                              result.azimuth, result.reverse_azimuth,
                              b, f,
                              result.reduced_length, result.geodesic_scale);
        }

        return result;
    }

private:
    static inline void normalize_azimuth(CT & azimuth, CT const& A, CT const& dA)
    {
        CT const c0 = 0;

        if (A >= c0) // A indicates Eastern hemisphere
        {
            if (dA >= c0) // A altered towards 0
            {
                if (azimuth < c0)
                {
                    azimuth = c0;
                }
            }
            else // dA < 0, A altered towards pi
            {
                CT const pi = math::pi<CT>();
                if (azimuth > pi)
                {
                    azimuth = pi;
                }
            }
        }
        else // A indicates Western hemisphere
        {
            if (dA <= c0) // A altered towards 0
            {
                if (azimuth > c0)
                {
                    azimuth = c0;
                }
            }
            else // dA > 0, A altered towards -pi
            {
                CT const minus_pi = -math::pi<CT>();
                if (azimuth < minus_pi)
                {
                    azimuth = minus_pi;
                }
            }
        }
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_ANDOYER_INVERSE_HPP

/* andoyer_inverse.hpp
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
*/