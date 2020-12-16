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
cYf/kUPOFvt1kqWuPNlSucQN8MoR7Jcu50XW4tOYu3oMeUn5ArCAOARPPYO5rdvwxx9ngiXE+fBLYLXFds9kDMFSYjWGeQEmEfvh40F9Cu3hO8Fi4np4M1hG3ADfHbRUKbH/LMZwHONJHIP94/HX5fANYCOx5ofA1hTynMC+ANUhTdXBYyeyj5RH4Z/AXN3mHMYK9E9jW/A3IIv2JKh6Az+xHz4a+DrQHp4IBhLnwwtBBn3r4Q2g0SI3+GOwhbgRTvstuRH74IPANj1W8KmgQY8PXAKa9HjC14AYcS18P/DpMYE3AKX3Hf4Y+FPwh9POZR1LwR8+CGSl4A+fCgam4A+XgHTiEHyNjjvgD3+t23dMs/kw/phmEDHMvS/rALHmInA+seYmECLWnHIB85+4Dr78QtqnMbbwiZM51pT7CznfwaRUxrPIUkNBaSqecAmYSw6aPwG1xJq3gXpiX7GlOpZwvIg1z5jCnCTWfHIZPh3w4eXX6qmsh8RR+K5yxoG4Ae46jTzZluYaDWLNC8AS4hjcv4I1l/aal4IGYs2vgB06h0pL5YAs2mu+Ggwk1nybriNugMeEWEM60v5i5gZoIA7Bj4MtxDH45jD7pttEGFuwmr6anwGbiDVfPJ02xJqvAql6DGewr2AHcQ28CaTquQp/A4YSq5nMVTCc2K8ZDCIOwitn0odY8zPgXWLNCy/hmkWs+cLfsY97pdk8YBaexJq3gSCx7zJLHQEaiBt4oW6/Gsacvjnw1SBCueaTr2DtItY8HSwh1vwUWEWs+TOwiTh0JfWgnDgKfwiKiHOustQTc5gbXdgXXr4fAeqIg5pBsFOazdvBJGLNna7hWHeiL3wBmEMcgt8DucRRXlL/CswjVnMZKzBLjxV8NCjS+wJPBOcT58PTQTlxDbwQzCGug58EET3P4bfAKn0s4G/AEmJ1Hf5gnvaHjwbLtT88ESzV/vB0sFb7wwvBAu0JfwAa09NsPpQ/BlLkrDkb9CfOh98Awc5pNj8wn/yJNa8Gc4lrr+fYgQxizWfdwHEl1nwRGE5cB78DFuCp+aVa8iTW3OlGjhGx5n1u4rgTa46CJuIG/gih3wK2RZ6a71nIsSHW/ARYm47/IvqBjC5pNq+7g/yJNY+6k+NCrPlsECH21bHegyXkpvltsIpYc+Xd5EOs+XqwlVjzvaCpM33vYc0BOeQWhBeDbcwlza+AHcSaz3mYayK5aZ4Ksok1j1rBfQ6x5nNAhNhfb6kzQIw4H74ZBPTcgw9YxXlNeeAJ1jGQTXkNvBksy2B/4cOeZB0jzoHng9UZ9IXPfIpxzKA9/BfwJnEjPGw1+0UchC8CRV2Zw/B8UN6VvnATiBD7nmZNALO64gNPe4b5SVwPH7iGMSTOgSvBct0G7rOWNb8b5fAWkEWs1llqERhIHIUnPcu+ENfA74Bc4kb49OeoI86H7wClxJqHRVlXiTWPBYuJ6+Drn2cfOaYx+BOwhVhz+QvMCWLN08COLrSHN4DVuj18+Ytc7zLIZz3nygbmLbH/ZeYCGKrHFh64kWsNse8VjhFYxT5qvgasJ9a8ArxLrHkd2E7cCB/4R2L6ar4G7CDWvBRk0UbzOjCUWPOLIEis/sScAZ/Tvha+HyzrwpjDG0C9nsObuJ8BaxkHzdvAJmLNX2hNHNhsqQ6vclz0sYAPfo25p/cX/g6cT6z5oRhrGrHm9D+znhDnw/eC1L1pDx/yOucXseYHQSax5qfBIGL1BvcD4HziAHweKCKuhef/he0S+95iroIJxDnw1WAkcR38Jhjdl3GD+77NvmfhAxeAWb2Yn/BWsLEnfbewzv+N+Ul59F3WXjAvk75w1/dYZzJpA38Nztc=
*/