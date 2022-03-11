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