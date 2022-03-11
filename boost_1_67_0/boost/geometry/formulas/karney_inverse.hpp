// Boost.Geometry

// Copyright (c) 2018 Adeel Ahmad, Islamabad, Pakistan.

// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from GeographicLib, https://geographiclib.sourceforge.io
// GeographicLib is originally written by Charles Karney.

// Author: Charles Karney (2008-2017)

// Last updated version of GeographicLib: 1.49

// Original copyright notice:

// Copyright (c) Charles Karney (2008-2017) <charles@karney.com> and licensed
// under the MIT/X11 License. For more information, see
// https://geographiclib.sourceforge.io

#ifndef BOOST_GEOMETRY_FORMULAS_KARNEY_INVERSE_HPP
#define BOOST_GEOMETRY_FORMULAS_KARNEY_INVERSE_HPP


#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/series_expansion.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_inverse.hpp>


namespace boost { namespace geometry { namespace math {

// TODO: Moved temporarily because of C++11 is used

/*!
\brief The exact difference of two angles reduced to (-180deg, 180deg].
*/
template<typename T>
inline T difference_angle(T const& x, T const& y, T& e)
{
    T t, d = math::sum_error(std::remainder(-x, T(360)), std::remainder(y, T(360)), t);

    normalize_azimuth<degree, T>(d);

    // Here y - x = d + t (mod 360), exactly, where d is in (-180,180] and
    // abs(t) <= eps (eps = 2^-45 for doubles).  The only case where the
    // addition of t takes the result outside the range (-180,180] is d = 180
    // and t > 0.  The case, d = -180 + eps, t = -eps, can't happen, since
    // sum_error would have returned the exact result in such a case (i.e., given t = 0).
    return math::sum_error(d == 180 && t > 0 ? -180 : d, t, e);
}

}}} // namespace boost::geometry::math


namespace boost { namespace geometry { namespace formula
{

namespace se = series_expansion;

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates,
       after Karney (2011).
\author See
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/
template <
    typename CT,
    bool EnableDistance,
    bool EnableAzimuth,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false,
    size_t SeriesOrder = 8
>
class karney_inverse
{
    static const bool CalcQuantities = EnableReducedLength || EnableGeodesicScale;
    static const bool CalcAzimuths = EnableAzimuth || EnableReverseAzimuth || CalcQuantities;
    static const bool CalcFwdAzimuth = EnableAzimuth || CalcQuantities;
    static const bool CalcRevAzimuth = EnableReverseAzimuth || CalcQuantities;

public:
    typedef result_inverse<CT> result_type;

    template <typename T1, typename T2, typename Spheroid>
    static inline result_type apply(T1 const& lo1,
                                    T1 const& la1,
                                    T2 const& lo2,
                                    T2 const& la2,
                                    Spheroid const& spheroid)
    {
        static CT const c0 = 0;
        static CT const c0_001 = 0.001;
        static CT const c0_1 = 0.1;
        static CT const c1 = 1;
        static CT const c2 = 2;
        static CT const c3 = 3;
        static CT const c8 = 8;
        static CT const c16 = 16;
        static CT const c90 = 90;
        static CT const c180 = 180;
        static CT const c200 = 200;
        static CT const pi = math::pi<CT>();
        static CT const d2r = math::d2r<CT>();
        static CT const r2d = math::r2d<CT>();

        result_type result;

        CT lat1 = la1;
        CT lat2 = la2;

        CT lon1 = lo1;
        CT lon2 = lo2;

        CT const a = CT(get_radius<0>(spheroid));
        CT const b = CT(get_radius<2>(spheroid));
        CT const f = formula::flattening<CT>(spheroid);
        CT const one_minus_f = c1 - f;
        CT const two_minus_f = c2 - f;

        CT const tol0 = std::numeric_limits<CT>::epsilon();
        CT const tol1 = c200 * tol0;
        CT const tol2 = sqrt(tol0);

        // Check on bisection interval.
        CT const tol_bisection = tol0 * tol2;

        CT const etol2 = c0_1 * tol2 /
            sqrt((std::max)(c0_001, std::abs(f)) * (std::min)(c1, c1 - f / c2) / c2);

        CT tiny = std::sqrt((std::numeric_limits<CT>::min)());

        CT const n = f / two_minus_f;
        CT const e2 = f * two_minus_f;
        CT const ep2 = e2 / math::sqr(one_minus_f);

        // Compute the longitudinal difference.
        CT lon12_error;
        CT lon12 = math::difference_angle(lon1, lon2, lon12_error);

        int lon12_sign = lon12 >= 0 ? 1 : -1;

        // Make points close to the meridian to lie on it.
        lon12 = lon12_sign * lon12;
        lon12_error = (c180 - lon12) - lon12_sign * lon12_error;

        // Convert to radians.
        CT lam12 = lon12 * d2r;
        CT sin_lam12;
        CT cos_lam12;

        if (lon12 > c90)
        {
            math::sin_cos_degrees(lon12_error, sin_lam12, cos_lam12);
            cos_lam12 *= -c1;
        }
        else
        {
            math::sin_cos_degrees(lon12, sin_lam12, cos_lam12);
        }

        // Make points close to the equator to lie on it.
        lat1 = math::round_angle(std::abs(lat1) > c90 ? c90 : lat1);
        lat2 = math::round_angle(std::abs(lat2) > c90 ? c90 : lat2);

        // Arrange points in a canonical form, as explained in
        // paper, Algorithms for geodesics, Eq. (44):
        //
        //     0 <= lon12 <= 180
        //     -90 <= lat1 <= 0
        //     lat1 <= lat2 <= -lat1
        int swap_point = std::abs(lat1) < std::abs(lat2) ? -1 : 1;

        if (swap_point < 0)
        {
            lon12_sign *= -1;
            swap(lat1, lat2);
        }

        // Enforce lat1 to be <= 0.
        int lat_sign = lat1 < 0 ? 1 : -1;
        lat1 *= lat_sign;
        lat2 *= lat_sign;

        CT sin_beta1, cos_beta1;
        math::sin_cos_degrees(lat1, sin_beta1, cos_beta1);
        sin_beta1 *= one_minus_f;

        math::normalize_unit_vector<CT>(sin_beta1, cos_beta1);
        cos_beta1 = (std::max)(tiny, cos_beta1);

        CT sin_beta2, cos_beta2;
        math::sin_cos_degrees(lat2, sin_beta2, cos_beta2);
        sin_beta2 *= one_minus_f;

        math::normalize_unit_vector<CT>(sin_beta2, cos_beta2);
        cos_beta2 = (std::max)(tiny, cos_beta2);

        // If cos_beta1 < -sin_beta1, then cos_beta2 - cos_beta1 is a
        // sensitive measure of the |beta1| - |beta2|. Alternatively,
        // (cos_beta1 >= -sin_beta1), abs(sin_beta2) + sin_beta1 is
        // a better measure.
        // Sometimes these quantities vanish and in that case we
        // force beta2 = +/- bet1a exactly.
        if (cos_beta1 < -sin_beta1)
        {
            if (cos_beta1 == cos_beta2)
            {
                sin_beta2 = sin_beta2 < 0 ? sin_beta1 : -sin_beta1;
            }
        }
        else
        {
            if (std::abs(sin_beta2) == -sin_beta1)
            {
                cos_beta2 = cos_beta1;
            }
        }

        CT const dn1 = sqrt(c1 + ep2 * math::sqr(sin_beta1));
        CT const dn2 = sqrt(c1 + ep2 * math::sqr(sin_beta2));

        CT sigma12;
        CT m12x, s12x, M21;

        // Index zero element of coeffs_C1 is unused.
        se::coeffs_C1<SeriesOrder, CT> const coeffs_C1(n);

        bool meridian = lat1 == -90 || sin_lam12 == 0;

        CT cos_alpha1, sin_alpha1;
        CT cos_alpha2, sin_alpha2;

        if (meridian)
        {
            // Endpoints lie on a single full meridian.

            // Point to the target latitude.
            cos_alpha1 = cos_lam12;
            sin_alpha1 = sin_lam12;

            // Heading north at the target.
            cos_alpha2 = c1;
            sin_alpha2 = c0;

            CT sin_sigma1 = sin_beta1;
            CT cos_sigma1 = cos_alpha1 * cos_beta1;

            CT sin_sigma2 = sin_beta2;
            CT cos_sigma2 = cos_alpha2 * cos_beta2;

            CT sigma12 = std::atan2((std::max)(c0, cos_sigma1 * sin_sigma2 - sin_sigma1 * cos_sigma2),
                                                   cos_sigma1 * cos_sigma2 + sin_sigma1 * sin_sigma2);

            CT dummy;
            meridian_length(n, ep2, sigma12, sin_sigma1, cos_sigma1, dn1,
                                             sin_sigma2, cos_sigma2, dn2,
                                             cos_beta1, cos_beta2, s12x,
                                             m12x, dummy, result.geodesic_scale,
                                             M21, coeffs_C1);

            if (sigma12 < c1 || m12x >= c0)
            {
                if (sigma12 < c3 * tiny)
                {
                    sigma12  = m12x = s12x = c0;
                }

                m12x *= b;
                s12x *= b;
            }
            else
            {
                // m12 < 0, i.e., prolate and too close to anti-podal.
                meridian = false;
            }
        }

        CT omega12;

        if (!meridian && sin_beta1 == c0 &&
            (f <= c0 || lon12_error >= f * c180))
        {
            // Points lie on the equator.
            cos_alpha1 = cos_alpha2 = c0;
            sin_alpha1 = sin_alpha2 = c1;

            s12x = a * lam12;
            sigma12 = omega12 = lam12 / one_minus_f;
            m12x = b * sin(sigma12);

            if (BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
            {
                result.geodesic_scale = cos(sigma12);
            }
        }
        else if (!meridian)
        {
            // If point1 and point2 belong within a hemisphere bounded by a
            // meridian and geodesic is neither meridional nor equatorial.

            // Find the starting point for Newton's method.
            CT dnm;
            sigma12 = newton_start(sin_beta1, cos_beta1, dn1,
                                   sin_beta2, cos_beta2, dn2,
                                   lam12, sin_lam12, cos_lam12,
                                   sin_alpha1, cos_alpha1,
                                   sin_alpha2, cos_alpha2,
                                   dnm, coeffs_C1, ep2,
                                   tol1, tol2, etol2,
                                   n, f);

            if (sigma12 >= c0)
            {
                // Short lines case (newton_start sets sin_alpha2, cos_alpha2, dnm).
                s12x = sigma12 * b * dnm;
                m12x = math::sqr(dnm) * b * sin(sigma12 / dnm);
                if (BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
                {
                    result.geodesic_scale = cos(sigma12 / dnm);
                }

                // Convert to radians.
                omega12 = lam12 / (one_minus_f * dnm);
            }
            else
            {
                // Apply the Newton's method.
                CT sin_sigma1 = c0, cos_sigma1 = c0;
                CT sin_sigma2 = c0, cos_sigma2 = c0;
                CT eps = c0, diff_omega12 = c0;

                // Bracketing range.
                CT sin_alpha1a = tiny, cos_alpha1a = c1;
                CT sin_alpha1b = tiny, cos_alpha1b = -c1;

                size_t iteration = 0;
                size_t max_iterations = 20 + std::numeric_limits<size_t>::digits + 10;

                for (bool tripn = false, tripb = false;
                     iteration < max_iterations;
                     ++iteration)
                {
                    CT dv;
                    CT v = lambda12(sin_beta1, cos_beta1, dn1,
                                    sin_beta2, cos_beta2, dn2,
                                    sin_alpha1, cos_alpha1,
                                    sin_lam12, cos_lam12,
                                    sin_alpha2, cos_alpha2,
                                    sigma12,
                                    sin_sigma1, cos_sigma1,
                                    sin_sigma2, cos_sigma2,
                                    eps, diff_omega12,
                                    iteration < max_iterations,
                                    dv, f, n, ep2, tiny, coeffs_C1);

                    // Reversed test to allow escape with NaNs.
                    if (tripb || !(std::abs(v) >= (tripn ? c8 : c1) * tol0))
                        break;

                    // Update bracketing values.
                    if (v > c0 && (iteration > max_iterations ||
                        cos_alpha1 / sin_alpha1 > cos_alpha1b / sin_alpha1b))
                    {
                        sin_alpha1b = sin_alpha1;
                        cos_alpha1b = cos_alpha1;   
                    }
                    else if (v < c0 && (iteration > max_iterations ||
                             cos_alpha1 / sin_alpha1 < cos_alpha1a / sin_alpha1a))
                    {
                        sin_alpha1a = sin_alpha1;
                        cos_alpha1a = cos_alpha1;
                    }

                    if (iteration < max_iterations && dv > c0)
                    {
                        CT diff_alpha1 = -v / dv;

                        CT sin_diff_alpha1 = sin(diff_alpha1);
                        CT cos_diff_alpha1 = cos(diff_alpha1);

                        CT nsin_alpha1 = sin_alpha1 * cos_diff_alpha1 +
                            cos_alpha1 * sin_diff_alpha1;

                        if (nsin_alpha1 > c0 && std::abs(diff_alpha1) < pi)
                        {
                            cos_alpha1 = cos_alpha1 * cos_diff_alpha1 - sin_alpha1 * sin_diff_alpha1;
                            sin_alpha1 = nsin_alpha1;
                            math::normalize_unit_vector<CT>(sin_alpha1, cos_alpha1);

                            // In some regimes we don't get quadratic convergence because
                            // slope -> 0. So use convergence conditions based on epsilon
                            // instead of sqrt(epsilon).
                            tripn = std::abs(v) <= c16 * tol0;
                            continue;
                        }
                    }

                    // Either dv was not positive or updated value was outside legal
                    // range. Use the midpoint of the bracket as the next estimate.
                    // This mechanism is not needed for the WGS84 ellipsoid, but it does
                    // catch problems with more eeccentric ellipsoids. Its efficacy is
                    // such for the WGS84 test set with the starting guess set to alp1 =
                    // 90deg:
                    // the WGS84 test set: mean = 5.21, sd = 3.93, max = 24
                    // WGS84 and random input: mean = 4.74, sd = 0.99
                    sin_alpha1 = (sin_alpha1a + sin_alpha1b) / c2;
                    cos_alpha1 = (cos_alpha1a + cos_alpha1b) / c2;
                    math::normalize_unit_vector<CT>(sin_alpha1, cos_alpha1);
                    tripn = false;
                    tripb = (std::abs(sin_alpha1a - sin_alpha1) + (cos_alpha1a - cos_alpha1) < tol_bisection ||
                             std::abs(sin_alpha1 - sin_alpha1b) + (cos_alpha1 - cos_alpha1b) < tol_bisection);
                }

                CT dummy;
                se::coeffs_C1<SeriesOrder, CT> const coeffs_C1_eps(eps);
                // Ensure that the reduced length and geodesic scale are computed in
                // a "canonical" way, with the I2 integral.
                meridian_length(eps, ep2, sigma12, sin_sigma1, cos_sigma1, dn1,
                                                   sin_sigma2, cos_sigma2, dn2,
                                                   cos_beta1, cos_beta2, s12x,
                                                   m12x, dummy, result.geodesic_scale,
                                                   M21, coeffs_C1_eps);

                m12x *= b;
                s12x *= b;
            }
        }

        if (swap_point < 0)
        {
            swap(sin_alpha1, sin_alpha2);
            swap(cos_alpha1, cos_alpha2);
            swap(result.geodesic_scale, M21);
        }

        sin_alpha1 *= swap_point * lon12_sign;
        cos_alpha1 *= swap_point * lat_sign;

        sin_alpha2 *= swap_point * lon12_sign;
        cos_alpha2 *= swap_point * lat_sign;

        if (BOOST_GEOMETRY_CONDITION(EnableReducedLength))
        {
            result.reduced_length = m12x;
        }

        if (BOOST_GEOMETRY_CONDITION(CalcAzimuths))
        {
            if (BOOST_GEOMETRY_CONDITION(CalcFwdAzimuth))
            {
                result.azimuth = atan2(sin_alpha1, cos_alpha1) * r2d;
            }

            if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
            {
                result.reverse_azimuth = atan2(sin_alpha2, cos_alpha2) * r2d;
            }
        }

        if (BOOST_GEOMETRY_CONDITION(EnableDistance))
        {
            result.distance = s12x;
        }

        return result;
    }

    template <typename CoeffsC1>
    static inline void meridian_length(CT const& epsilon, CT const& ep2, CT const& sigma12,
                                       CT const& sin_sigma1, CT const& cos_sigma1, CT const& dn1,
                                       CT const& sin_sigma2, CT const& cos_sigma2, CT const& dn2,
                                       CT const& cos_beta1, CT const& cos_beta2,
                                       CT& s12x, CT& m12x, CT& m0,
                                       CT& M12, CT& M21,
                                       CoeffsC1 const& coeffs_C1)
    {
        static CT const c1 = 1;

        CT A12x = 0, J12 = 0;
        CT expansion_A1, expansion_A2;

        // Evaluate the coefficients for C2.
        se::coeffs_C2<SeriesOrder, CT> coeffs_C2(epsilon);

        if (BOOST_GEOMETRY_CONDITION(EnableDistance) ||
            BOOST_GEOMETRY_CONDITION(EnableReducedLength) ||
            BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
        {
            // Find the coefficients for A1 by computing the
            // series expansion using Horner scehme.
            expansion_A1 = se::evaluate_A1<SeriesOrder>(epsilon);

            if (BOOST_GEOMETRY_CONDITION(EnableReducedLength) ||
                BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
            {
                // Find the coefficients for A2 by computing the
                // series expansion using Horner scehme.
                expansion_A2 = se::evaluate_A2<SeriesOrder>(epsilon);

                A12x = expansion_A1 - expansion_A2;
                expansion_A2 += c1;
            }
            expansion_A1 += c1;
        }

        if (BOOST_GEOMETRY_CONDITION(EnableDistance))
        {
            CT B1 = se::sin_cos_series(sin_sigma2, cos_sigma2, coeffs_C1)
                  - se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C1);

            s12x = expansion_A1 * (sigma12 + B1);

            if (BOOST_GEOMETRY_CONDITION(EnableReducedLength) ||
                BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
            {
                CT B2 = se::sin_cos_series(sin_sigma2, cos_sigma2, coeffs_C2)
                      - se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C2);

                J12 = A12x * sigma12 + (expansion_A1 * B1 - expansion_A2 * B2);
            }
        }
        else if (BOOST_GEOMETRY_CONDITION(EnableReducedLength) ||
                 BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
        {
            for (size_t i = 1; i <= SeriesOrder; ++i)
            {
                coeffs_C2[i] = expansion_A1 * coeffs_C1[i] -
                               expansion_A2 * coeffs_C2[i];
            }

            J12 = A12x * sigma12 +
                   (se::sin_cos_series(sin_sigma2, cos_sigma2, coeffs_C2)
                  - se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C2));
        }

        if (BOOST_GEOMETRY_CONDITION(EnableReducedLength))
        {
            m0 = A12x;

            m12x = dn2 * (cos_sigma1 * sin_sigma2) -
                   dn1 * (sin_sigma1 * cos_sigma2) -
                   cos_sigma1 * cos_sigma2 * J12;
        }

        if (BOOST_GEOMETRY_CONDITION(EnableGeodesicScale))
        {
            CT cos_sigma12 = cos_sigma1 * cos_sigma2 + sin_sigma1 * sin_sigma2;
            CT t = ep2 * (cos_beta1 - cos_beta2) *
                         (cos_beta1 + cos_beta2) / (dn1 + dn2);

            M12 = cos_sigma12 + (t * sin_sigma2 - cos_sigma2 * J12) * sin_sigma1 / dn1;
            M21 = cos_sigma12 - (t * sin_sigma1 - cos_sigma1 * J12) * sin_sigma2 / dn2;
        }
    }

    /*
     Return a starting point for Newton's method in sin_alpha1 and
     cos_alpha1 (function value is -1). If Newton's method
     doesn't need to be used, return also sin_alpha2 and
     cos_alpha2 and function value is sig12.
    */
    template <typename CoeffsC1>
    static inline CT newton_start(CT const& sin_beta1, CT const& cos_beta1, CT const& dn1,
                                  CT const& sin_beta2, CT const& cos_beta2, CT dn2,
                                  CT const& lam12, CT const& sin_lam12, CT const& cos_lam12,
                                  CT& sin_alpha1, CT& cos_alpha1,
                                  CT& sin_alpha2, CT& cos_alpha2,
                                  CT& dnm, CoeffsC1 const& coeffs_C1, CT const& ep2,
                                  CT const& tol1, CT const& tol2, CT const& etol2, CT const& n, CT const& f)
    {
        static CT const c0 = 0;
        static CT const c0_01 = 0.01;
        static CT const c0_1 = 0.1;
        static CT const c0_5 = 0.5;
        static CT const c1 = 1;
        static CT const c2 = 2;
        static CT const c6 = 6;
        static CT const c1000 = 1000;
        static CT const pi = math::pi<CT>();

        CT const one_minus_f = c1 - f;
        CT const x_thresh = c1000 * tol2;

        // Return a starting point for Newton's method in sin_alpha1
        // and cos_alpha1 (function value is -1). If Newton's method
        // doesn't need to be used, return also sin_alpha2 and
        // cos_alpha2 and function value is sig12.
        CT sig12 = -c1;

        // bet12 = bet2 - bet1 in [0, pi); beta12a = bet2 + bet1 in (-pi, 0]
        CT sin_beta12 = sin_beta2 * cos_beta1 - cos_beta2 * sin_beta1;
        CT cos_beta12 = cos_beta2 * cos_beta1 + sin_beta2 * sin_beta1;

        CT sin_beta12a = sin_beta2 * cos_beta1 + cos_beta2 * sin_beta1;

        bool shortline = cos_beta12 >= c0 && sin_beta12 < c0_5 &&
            cos_beta2 * lam12 < c0_5;

        CT sin_omega12, cos_omega12;

        if (shortline)
        {
            CT sin_beta_m2 = math::sqr(sin_beta1 + sin_beta2);

            sin_beta_m2 /= sin_beta_m2 + math::sqr(cos_beta1 + cos_beta2);
            dnm = math::sqrt(c1 + ep2 * sin_beta_m2);

            CT omega12 = lam12 / (one_minus_f * dnm);

            sin_omega12 = sin(omega12);
            cos_omega12 = cos(omega12);
        }
        else
        {
            sin_omega12 = sin_lam12;
            cos_omega12 = cos_lam12;
        }

        sin_alpha1 = cos_beta2 * sin_omega12;
        cos_alpha1 = cos_omega12 >= c0 ?
            sin_beta12 + cos_beta2 * sin_beta1 * math::sqr(sin_omega12) / (c1 + cos_omega12) :
            sin_beta12a - cos_beta2 * sin_beta1 * math::sqr(sin_omega12) / (c1 - cos_omega12);

        CT sin_sigma12 = boost::math::hypot(sin_alpha1, cos_alpha1);
        CT cos_sigma12 = sin_beta1 * sin_beta2 + cos_beta1 * cos_beta2 * cos_omega12;

        if (shortline && sin_sigma12 < etol2)
        {
            sin_alpha2 = cos_beta1 * sin_omega12;
            cos_alpha2 = sin_beta12 - cos_beta1 * sin_beta2 *
                (cos_omega12 >= c0 ? math::sqr(sin_omega12) /
                (c1 + cos_omega12) : c1 - cos_omega12);

            math::normalize_unit_vector<CT>(sin_alpha2, cos_alpha2);
            // Set return value.
            sig12 = atan2(sin_sigma12, cos_sigma12);
        }
        // Skip astroid calculation if too eccentric.
        else if (std::abs(n) > c0_1 ||
                 cos_sigma12 >= c0 ||
                 sin_sigma12 >= c6 * std::abs(n) * pi *
                 math::sqr(cos_beta1))
        {
            // Nothing to do, zeroth order spherical approximation will do.
        }
        else
        {
            // Scale lam12 and bet2 to x, y coordinate system where antipodal
            // point is at origin and singular point is at y = 0, x = -1.
            CT lambda_scale, beta_scale;

            CT y;
            volatile CT x;

            CT lam12x = atan2(-sin_lam12, -cos_lam12);
            if (f >= c0)
            {
                CT k2 = math::sqr(sin_beta1) * ep2;
                CT eps = k2 / (c2 * (c1 + sqrt(c1 + k2)) + k2);

                se::coeffs_A3<SeriesOrder, CT> const coeffs_A3(n);

                CT const A3 = math::horner_evaluate(eps, coeffs_A3.begin(), coeffs_A3.end());

                lambda_scale = f * cos_beta1 * A3 * pi;
                beta_scale = lambda_scale * cos_beta1;

                x = lam12x / lambda_scale;
                y = sin_beta12a / beta_scale;
            }
            else
            {
                CT cos_beta12a = cos_beta2 * cos_beta1 - sin_beta2 * sin_beta1;
                CT beta12a = atan2(sin_beta12a, cos_beta12a);

                CT m12b, m0, dummy;
                meridian_length(n, ep2, pi + beta12a,
                                sin_beta1, -cos_beta1, dn1,
                                sin_beta2, cos_beta2, dn2,
                                cos_beta1, cos_beta2, dummy,
                                m12b, m0, dummy, dummy, coeffs_C1);

                x = -c1 + m12b / (cos_beta1 * cos_beta2 * m0 * pi);
                beta_scale = x < -c0_01
                           ? sin_beta12a / x
                           : -f * math::sqr(cos_beta1) * pi;
                lambda_scale = beta_scale / cos_beta1;

                y = lam12x / lambda_scale;
            }

            if (y > -tol1 && x > -c1 - x_thresh)
            {
                // Strip near cut.
                if (f >= c0)
                {
                    sin_alpha1 = (std::min)(c1, -CT(x));
                    cos_alpha1 = - math::sqrt(c1 - math::sqr(sin_alpha1));
                }
                else
                {
                    cos_alpha1 = (std::max)(CT(x > -tol1 ? c0 : -c1), CT(x));
                    sin_alpha1 = math::sqrt(c1 - math::sqr(cos_alpha1));
                }
            }
            else
            {
                // Solve the astroid problem.
                CT k = astroid(CT(x), y);

                CT omega12a = lambda_scale * (f >= c0 ? -x * k /
                    (c1 + k) : -y * (c1 + k) / k);

                sin_omega12 = sin(omega12a);
                cos_omega12 = -cos(omega12a);

                // Update spherical estimate of alpha1 using omgega12 instead of lam12.
                sin_alpha1 = cos_beta2 * sin_omega12;
                cos_alpha1 = sin_beta12a - cos_beta2 * sin_beta1 *
                    math::sqr(sin_omega12) / (c1 - cos_omega12);
            }
        }

        // Sanity check on starting guess. Backwards check allows NaN through.
        if (!(sin_alpha1 <= c0))
        {
            math::normalize_unit_vector<CT>(sin_alpha1, cos_alpha1);
        }
        else
        {
            sin_alpha1 = c1;
            cos_alpha1 = c0;
        }

        return sig12;
    }

    /*
     Solve the astroid problem using the equation:
     κ4 + 2κ3 + (1 − x2 − y 2 )κ2 − 2y 2 κ − y 2 = 0.

     For details, please refer to Eq. (65) in,
     Geodesics on an ellipsoid of revolution, Charles F.F Karney,
     https://arxiv.org/abs/1102.1215
    */
    static inline CT astroid(CT const& x, CT const& y)
    {
        static CT const c0 = 0;
        static CT const c1 = 1;
        static CT const c2 = 2;
        static CT const c3 = 3;
        static CT const c4 = 4;
        static CT const c6 = 6;

        CT k;

        CT p = math::sqr(x);
        CT q = math::sqr(y);
        CT r = (p + q - c1) / c6;

        if (!(q == c0 && r <= c0))
        {
            // Avoid possible division by zero when r = 0 by multiplying
            // equations for s and t by r^3 and r, respectively.
            CT S = p * q / c4;
            CT r2 = math::sqr(r);
            CT r3 = r * r2;

            // The discriminant of the quadratic equation for T3. This is
            // zero on the evolute curve p^(1/3)+q^(1/3) = 1.
            CT discriminant = S * (S + c2 * r3);

            CT u = r;

            if (discriminant >= c0)
            {
                CT T3 = S + r3;

                // Pick the sign on the sqrt to maximize abs(T3). This minimizes
                // loss of precision due to cancellation. The result is unchanged
                // because of the way the T is used in definition of u.
                T3 += T3 < c0 ? -std::sqrt(discriminant) : std::sqrt(discriminant);

                CT T = std::cbrt(T3);

                // T can be zero; but then r2 / T -> 0.
                u += T + (T != c0 ? r2 / T : c0);
            }
            else
            {
                CT ang = std::atan2(std::sqrt(-discriminant), -(S + r3));

                // There are three possible cube roots. We choose the root which avoids
                // cancellation. Note that discriminant < 0 implies that r < 0.
                u += c2 * r * cos(ang / c3);
            }

            CT v = std::sqrt(math::sqr(u) + q);

            // Avoid loss of accuracy when u < 0.
            CT uv = u < c0 ? q / (v - u) : u + v;
            CT w = (uv - q) / (c2 * v);

            // Rearrange expression for k to avoid loss of accuracy due to
            // subtraction. Division by 0 not possible because uv > 0, w >= 0.
            k = uv / (std::sqrt(uv + math::sqr(w)) + w);
        }
        else // q == 0 && r <= 0
        {
            // y = 0 with |x| <= 1. Handle this case directly.
            // For y small, positive root is k = abs(y)/sqrt(1-x^2).
            k = c0;
        }
        return k;
    }

    template <typename CoeffsC1>
    static inline CT lambda12(CT const& sin_beta1, CT const& cos_beta1, CT const& dn1,
                              CT const& sin_beta2, CT const& cos_beta2, CT const& dn2,
                              CT const& sin_alpha1, CT cos_alpha1,
                              CT const& sin_lam120, CT const& cos_lam120,
                              CT& sin_alpha2, CT& cos_alpha2,
                              CT& sigma12,
                              CT& sin_sigma1, CT& cos_sigma1,
                              CT& sin_sigma2, CT& cos_sigma2,
                              CT& eps, CT& diff_omega12,
                              bool diffp, CT& diff_lam12,
                              CT const& f, CT const& n, CT const& ep2, CT const& tiny,
                              CoeffsC1 const& coeffs_C1)
    {
        static CT const c0 = 0;
        static CT const c1 = 1;
        static CT const c2 = 2;

        CT const one_minus_f = c1 - f;

        if (sin_beta1 == c0 && cos_alpha1 == c0)
        {
            // Break degeneracy of equatorial line.
            cos_alpha1 = -tiny;
        }


        CT sin_alpha0 = sin_alpha1 * cos_beta1;
        CT cos_alpha0 = boost::math::hypot(cos_alpha1, sin_alpha1 * sin_beta1);

        CT sin_omega1, cos_omega1;
        CT sin_omega2, cos_omega2;
        CT sin_omega12, cos_omega12;

        CT lam12;

        sin_sigma1 = sin_beta1;
        sin_omega1 = sin_alpha0 * sin_beta1;

        cos_sigma1 = cos_omega1 = cos_alpha1 * cos_beta1;

        math::normalize_unit_vector<CT>(sin_sigma1, cos_sigma1);

        // Enforce symmetries in the case abs(beta2) = -beta1.
        // Otherwise, this can yield singularities in the Newton iteration.

        // sin(alpha2) * cos(beta2) = sin(alpha0).
        sin_alpha2 = cos_beta2 != cos_beta1 ?
            sin_alpha0 / cos_beta2 : sin_alpha1;

        cos_alpha2 = cos_beta2 != cos_beta1 || std::abs(sin_beta2) != -sin_beta1 ?
            sqrt(math::sqr(cos_alpha1 * cos_beta1) +
                (cos_beta1 < -sin_beta1 ?
                    (cos_beta2 - cos_beta1) * (cos_beta1 + cos_beta2) :
                    (sin_beta1 - sin_beta2) * (sin_beta1 + sin_beta2))) / cos_beta2 :
            std::abs(cos_alpha1);

        sin_sigma2 = sin_beta2;
        sin_omega2 = sin_alpha0 * sin_beta2;

        cos_sigma2 = cos_omega2 =
            (cos_alpha2 * cos_beta2);

        // Break degeneracy of equatorial line.
        math::normalize_unit_vector<CT>(sin_sigma2, cos_sigma2);


        // sig12 = sig2 - sig1, limit to [0, pi].
        sigma12 = atan2((std::max)(c0, cos_sigma1 * sin_sigma2 - sin_sigma1 * cos_sigma2),
                                          cos_sigma1 * cos_sigma2 + sin_sigma1 * sin_sigma2);

        // omg12 = omg2 - omg1, limit to [0, pi].
        sin_omega12 = (std::max)(c0, cos_omega1 * sin_omega2 - sin_omega1 * cos_omega2);
        cos_omega12 = cos_omega1 * cos_omega2 + sin_omega1 * sin_omega2;

        // eta = omg12 - lam120.
        CT eta = atan2(sin_omega12 * cos_lam120 - cos_omega12 * sin_lam120,
                       cos_omega12 * cos_lam120 + sin_omega12 * sin_lam120);

        CT B312;
        CT k2 = math::sqr(cos_alpha0) * ep2;

        eps = k2 / (c2 * (c1 + std::sqrt(c1 + k2)) + k2);

        se::coeffs_C3<SeriesOrder, CT> const coeffs_C3(n, eps);

        B312 = se::sin_cos_series(sin_sigma2, cos_sigma2, coeffs_C3)
             - se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C3);

        se::coeffs_A3<SeriesOrder, CT> const coeffs_A3(n);

        CT const A3 = math::horner_evaluate(eps, coeffs_A3.begin(), coeffs_A3.end());

        diff_omega12 = -f * A3 * sin_alpha0 * (sigma12 + B312);
        lam12 = eta + diff_omega12;

        if (diffp)
        {
            if (cos_alpha2 == c0)
            {
                diff_lam12 = - c2 * one_minus_f * dn1 / sin_beta1;
            }
            else
            {
                CT dummy;
                meridian_length(eps, ep2, sigma12, sin_sigma1, cos_sigma1, dn1,
                                                   sin_sigma2, cos_sigma2, dn2,
                                                   cos_beta1, cos_beta2, dummy,
                                                   diff_lam12, dummy, dummy,
                                                   dummy, coeffs_C1);

                diff_lam12 *= one_minus_f / (cos_alpha2 * cos_beta2);
            }
        }
        return lam12;
    }

};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_KARNEY_INVERSE_HPP

/* karney_inverse.hpp
C/nbjR0i2UWg6Qks6EMJ4AtMF0WHIrhG5pB53DpIHiLEWYmbyOwWk5erZvO/487bfQ/+fOGzPV/VMEZRyBfVXzR1H6jhygAmChNS8iYcsEI+VlSh5QY36feALMkGTz438Jpr/4cRqwnmifDKGIzXvMcs4WHZ/APgJgBa1s033btcOLFOkzvxW2etXOhl7nuf8b7v4JN+3Qf3nB3BMHWLCDldmdkhhJx9BtHPLOCnwWoqCHee/H1XLTxLo0Tuh6RJvLJG/dw4Hec4M07Ql34IzyKQF8/BYnvUq96Cp7uwp12js9OLArZwqq0y/Eh4gYTFiKu8pM9h54s40uBd00mlNaASjoZMmPyaS5ff+tTqsUVqy1W/xZ9K/d8wbZnirs7koQpjSDS9gTmTwCUkfSuIPKeUI4mHAsIyzWgA9ehPZIYVQqyUnOvv0cuJUzYLXU24wr7+dHskwGn4aCoAlWy0oty9m5iqbaEY0ZbYjdyvj/4rxCahIIEsdcBpEzashmaHrAXvzKhEDujy4TEdd6o/rFtbLp3h2P0S3VzVb4EuKZT/uQCRiv6R2seJxFj9GyPP7qNuz27GwOW5EnCf0HDEPjtR7nzTCv0qT0auD+9z/IbU4ZPcgXKuB/CRoD4Pyt3BumFliE1ejXrguV67JSa8isFgGnT9IKZAvIDA8xfYJKg7BZIOpduonmpfBkeZHcpmvGEMFl1iGmPQmqk0sANpyDdcosznr0gDDApEep7Emv9z0tK3UIPLNx0xli2IeK2fs3D8G0lfpJlJC7fZbKQFzj7d+MiDHjFWB9sBwzH+KQ8KC9bN+K4+Zzj8rG55Zl4DsjIdP4+NGHq7RPoDM2nWPiyF+PxBfXxKX1WEf5ljgajpM1INprAuhsjzwlsRz2W44in+xIFlJyOFxpFpxcBGRC0v8dH1dK0DmO4vz/i8AymKCJTG1ci+X+H5zAmoraLJd3QS0T/9XFRhYWOo0F/gxfs4A3s0L3eR7iiy38CZ+AyXsTOVWUou5N+YMCKBN1qoseZRn8Etp/GphGVynQj1bY2fIZwKYiaKenUqQpLkAaWVbX81QCUIQkD9W5zX+cmsYLwuVx2Y9dpBKtIhjg32+nPqtNvNDfZ/qz/t8OGto2wT88ZOlQhDFEi1gGJZjcR3XY42diLHsQxbnh/uzn02tjFNT8n5sr7aSM74IRPhNkMoLIO68utDIAYn8SGG0lu4L8+bNWDN7iqPCDZeyA87mIx7mHEOI9Dr7OzsbVsGfsoC5gB8nL9YcqsrDCyCqzYTl0SF6ozqEi7nev+shYnV4aTWq1GPJFnSVpj82++WaBcrEZoNDj8cuxfd+jnBlVeo5s/wE5Xc79WoOJVhHvKosx67bcmjvIpFGdnutJrU5eUpGjlpcCoaaOXlzHfWs+RKH45Ny07TDhePQTdvKaspegcSVTxR4S9sHNDmpmROHzV+izk2+ozCelQDacxwXg/99Fuqf4GmVkZxidZAXh/qiy89/o08nYwfsmxVwG+L71W9qlFdECQcfiRbtvZDbjUue/z2pz18Ce7/p97Qf+foCnJC5qV03Krk+O5R8uqRVQl2/dmy/5ld/sqg9+AhK3jXYJ1pQ7YiYRAeYneIoUwz1PLe7HzsMgRiddocJHjXYv0BjqRkIrJnigBenzptOviaKjARxoCNu10wT6YwAiW8W8jOmSGoX6TaQ6oCF2+LbhzK0njX9+YhVa00/DYAlfpEwY1lH66p3ydnkxe1jITEE5KT3gfisdoPld5+gy8TRwwkeZeG1ymVz32GCxEBtGoA13ADZPtoBmtUPmYMZ14vGGUlRtDDtGCEDADh2QkgS2/bAXwTpvbly10ASSwIUPjW9g9V7qdhJeyMSy7Hqx5nlUAFXJxqqd0vVwkk8saLNBE/XtQVYNj+vOj3qfoOqt5t8wdmFk4DFHvOBBoEbY0mKU9Jnwd5bG9+7xThs6kxuybgnzheLoO9jtL+XoJd1BZgktEm1kU7avXdJJ/UWRk0mSDVvjropH3NFtX3yqXdEKqN60/nGiqNLMT49hhtbK/b8VIUch1PkREZF8jgbuh6sP4iNA82KFtU4SUMPPxsH8EGs1gWKoZmlJEM+L/gYztqrXrZ+j55Wq3ZtSEPA0o+zr9OkmyV1cABWncf3366rlUwibQhPSGBLMYdis4in0X74I/h/4YwTKjVdkd6FUU+t1g7TKPnlQCLNUGKHtk0Xs0uJhdJ0kXkOE4xnPAwu3OphXpEYK+oYv4LnTCzvGd2KAhLqRg2C5ajIxMLVRi1Msl6BFDBIreOF2uUL0ZNXTdCkOuQptGJ/F9bFJ3wsex5CfVy+Yo4aD8ltBgIv2Z1iPTpMIRhWDIDIjjym0osTBdkrckrnTIYiE0UdrQrg6gU2QcJvvRbOFb/oTkvJAcu1b6Tek0wMQJzbBc+rphUyovJoAIOuIy4IGaK/eMjASIpumYZ6/MCxsXmNVz/jwUDuwcbmOGM5UbnTntDDKZZ9CwcfKixLThFHS9RExHczZiKlRgse778yAYtNdzrvDWxLKnkb8B/iS9fVqJdahlG96gq9dsZRHsvO1Mquon5mQzO1zBOlJR2GyawGe7EkWN8tj8KDOw5vtgeLGTN8SRRpQJU5qJHIVihfIqXkZIe7KQeW7o7kodDUgCagpt1cSgpFMQWn30983V0TptrE7B7r0nYdu0Inm3lrzV4lLOD/zmTxBkY0B6RCF+LVY3Hs6B92ptpA5xgS+xohgcLpD/qc5hkp0AViCWO9k2WyOvsqIc3Y5QEAuiS1i4bihPUFvToMSRPZL4SKfy8Du3uiVTRuo1BhB3wW3XJ7IanWs6Kb/jH4ayl9x4r6M61BxoHET3orY7S6rVJi2ca3GxUhzs8JldvXnU2aRVNPg57t9VRQEIHh9u6fv7EBGS3+ESFeVt8OEN8RlWH3LVg7bFCSKxWTwqDcsL18OjUG2j4Vft098H/pwfX/IjaC4GA3Wur/tA+6M2RneJjF8jNG/Be+T7zjaL74DFYBjUD5cXlX/AKCzTnxaU54StRah8b98xh+u3d8WS905XUubAusnf4EXxlEATsfeu5swzkO6K7fdVB8XHjwwgCePbmrp0V6YeGy0R0HADQhdfg0lu+7OzXc+INi/uevYz1yPbavh3y0H17JkB85mNi4wPSMtgZ927ixSv7g1TpAQpct26uVd4GT7yPp5ZY16KhZxtMl7ITJdcPPJHXyvUGgpFr8U8mEaqpmG8EtR7AicAEtMdPN41iTn92F67OxvZiyk097OJC+Lfx94a1oPqu7BMnPrbfGTxRwrfiqeIof/9LNWQz8bicJNOmw/WxBTEvJkApSUS+JaKjwHx2k741KO3OLKbRzsBkOw5AY7851QjkWiCrPAI3RJAtVh0wLijSjojvXwJ6rg+KJiZ0QLPRAkHfe/fifZoO1Khjg2qNaWFeYrovmwXDPKYq5+KBnxAtGYQrSzTfWAFG1KveR5j24xtb+4lCakUQQ3oAnr0XKTgPm+QawcflpnNUh2i7E6NEialxiBtjLPms49NOmEkAUNdisUmvEEmHNhYdjSjMgvrXSQxpGOXQWJ6kexoWrrzJMrZdCz+JcTv6Eir0fBDYQX2L+6EqBErFl8hkXye1ctXBdXGV92AQzhl8fTWmHV6RcfJByk260hhyzkUIHEdUM6Yvsc01170+1LouMATQZUqGGs3s0pnTEB7WDXL28+RDRVvqBnazEc+Qk91s7KslWK1GknblgA/XGEiJ/yUR7x6lTY+1Suzbf79NsbwZN/GsehJ04d+R8av0fD5VN2jt7yyRwhlszYSJ0nWJEvFdzetWt18TcOzA36X82vfGYb9yH9k1+0y5yjy3C5Vk+aghMDge0JSXri0ajBRJWZfiuVef9Hanhke9cyz/rruGR+DCW4sNZ/NYPI5hnufdZnNSEMBMZR/23Afs84VRcdEatOEuefDgiknO1qsqeK+fXWcOdQ4cVLkXUFKtCrthH3/jrRD+u5uO3IPBRVo1nDzNwPtskBDcIoHFxDo9EEwO2LzI6mXkuJLlgL8N0yfiso7uosup9VFf/020Msy5sZHZKdmyndYFM784qT63q1pq2fAuMFtwTSwAu1juCNkwfJ4E4WZxisXX0Ed0n+EjOnfXTlQTJA9ZOKcyF7Owc6wNmydnzFVlB/+gyk0g65GhtiAG6/xWn0pdrZdys0sTNc+IaTz7eVF/ViQ0/f2MdgvXMVBUSGBCCbgS/v7Ll8D/ykCQ37QM38i7/5NoYRpyHHqQjUvRhBwYfFcwGKz976VnFFSY8373bPMyEvLS0l0ICihkfN06oO3JzUay7qQvKLa3Mrjg1GBadQgGy2W3GxqfNbJ7V9a38JScm7sW976Y/UGvtzVBc3SzfBnpPgEz+9A9BMjMU9SueGT4ygzmXlMRYX12oziO0XW229v8t6G0Bb4xqqJeUvdeUDd/p810rHUY6SdMWymYZkyNnsXqdTKrTQMf5EZpi/zH5CfGPTMJPo7GDOAHUGiimJKJ30NMPT/4UwZPpTTxAM8+Bl5LrESB4nx3b0MpxHmal23H6rwovjGB8iUucmacV3D2AG0m21k9lwoZ6NQSpYugqT8yxgAGpSOJ3ympdy8TSQ0oa2o7e2Ll4SsHMnp5hnlKthfJcf0/1QgTGLfjuNH+Pm6towoTYanykGmOtxAD1MCCmdgfXcrgddZu72WO9KFNEpWnTwiltCVlMZe3IX1SM1iWNMfKM0VsLZQXWHmlUpjFKOl6mXxSwH9bIE2YbFZIYR3svRnBtxpS0t4zAbmggludCVdyW3KPDsehnoxsm11yI1wpyNaYQKilRv0sjPx9UkO/pKttlTLr+NFpMcFNGjw9WkuwTZU7+bzGc4wT4TBSlpHkE2waZq0YJ9qEXU+/JKu4Udk5lW6TSxk/BKv52b7MUI2l9jAGzikpB21IZavGk5DFkg4D8D+oABP3wXIfJIDh1sB1MDpxzULBO8blTt9BNcPmrQJKAqX9meA2vhT8OHhshcoJmC9vSdiUHVq72tFVYbMO8sj28IU+SVKTZ8u4AvyD7/OpZG8x/7Xer93apsN3z/seKJfPQjIu6SvicyNmQ1YlfYYb5I9PMfx32oJTMkV27YPREOxruAjEGI4Yc6N49Ttew8Aik6Mp+cUeXVVuVyuNEWa2vB4Jo1J17snjsvz47d435utRc278o1vVhViwMCTIEh5nqMCrqLKTh3qX5b6T+8Kzf4+3am5O/TayurzqRZZ2WaJGvffRVDhS9n4BY/TRYTFceXkuPPO6vIymzaRKI8eO5XzoR+kGW3rT29bswrIcULFSVvOwWEr9CYzm4CBt5Ei0xzNnX8gvvbBhb4qe5I6bjqyJFE/nf0DPrMwOxQhjNQju/SaQvIwOj+Larcfn4w0u76zox662HTqp9q7yqWRD8YwUmA5goGD+7N11smIW2TAjtL5d8qqUGuKr0FBZ+v7b8ya9vT2er1DlO4q7Dtgp+oKUtAeyU/rslODs9M9ZPgd+7tylWw5ymEblsksnuZVnd3bcp3tb5v79Yob2H+O45v7z/tvuO/4KQQ0dTy1nnikp49oT5WTWb/Tk+LTr7LxibQC6py6b4V9/ccShi9DW5shi8pZ5gYOJiJISJGOsfmF9RA5cUU0R2yWKxsYJy8Vf5VwrdIhrb/D2thmEbnGdDFVVaPF2DQxr2IZbbMhs9d7Z+P3S1CEH8Eipps2LWyVhVV0Zj4Orhu5RyUZlpXYyKTi2NCvt15y/lPve6FgcoubeKSVVgWw7TZq0zOCjmlaYrpTq3qVvNXHAenHn27V65Nlceu6xNL0G3BxJFA+Ol+lLeeh7Jmp8cSwgARdNp4BDmW/kJonYyhbVuGdHkstvY+bo9A5qGP6q7y3C08J1HXvsiFFeT46Eveu/WCfCgZThcdpk5tQJiwY5fjcNGXel+9C/NZVyNLXvUpdAamU1yw1BoeHidXBgjLMUvEllNkat46FLnuJ/JyKL7qHwRQ7HUserBbNwLyaq6xA96R7cxXpG93MwJ0z+wQ9/Ruu9rlMqTiKg5wpix0JSFdP9vJ3aw70/w8EqKN0IZ6Qx/Rg0D9M9vf6OTSOPjJDIToGuVvcNbGpxbavsgC7sQUGRfPCEZ8a/xeid4T/Pm3tjjfoxDbW1P2NAVT3TOCM1N+4PId4wZPX3fXEjXvUSlHtpiQ4bNMpyAnKYWieHMIwoHrhtg5C2UMf5avlXw2OYlL4JWHkVnnZmYeDllxmxGiRTT6aXO8lJwN1Glpte/ooc8m/0WV87AZDwKl7ET85aqWHwmhiF/j6IEgOZ9KbX6/D90PdzSbjJmVJ0o2+Tng0NtoKfI6zsHyvcP5WnyYNVCtlHtXoomxSx2thB4L1zVSg4Iwm+U4WhPiiW9knhIWzQbveQRjkpfcCEdDRS4IrlmMmkiePe8iIREpn/0CgFkoxB9dXxFAtztaESpg/B4lNNjvqQwFdDMTcsNlT1fiagfMG5WNhzy5eQJcneAY6bCGsET0K6Z7Ce8R/gg66JVetR0Whmy+a6ItkfGHrruqL8AMhnfgCWlG3+47o5D4OvcGvowzWMovXkPPjKpZ3Dj1dI3+N484dg+cAhzAnSjfBfiSAvzgzQle+VzLuUVuHdpvcrT7nvBsEhcZ3oe1g7EOaV2AlGVHDB1xs0AnUlY6cbbP6XChUOWJq6UZBVr1tNCGAb3MyM5yEqIVBCqVgQ3QV9h82PtOieCWbEz0JNW9w3xpxon7NaVnKTQK1UwhF9BdTVv8B17i+aZe7jDUCiuJJAX1RIT/+fuBAxLB4mlqVfNBSseakGPVMifh6N88AZ1TKKqyIqCe5siSSvD0abZFNSV0lNyoSU5DYpEsXtXK2q7JZqACgzHoatNCa0Wjc3clfyFT3XfrRgjo4k6c8ID8TsUCnspB9/P++h8o/IK1JMajkp+CH+dEQ5v3pMOPIkHWrfdnv1eG9GdauLSrFa8qkEscQ4qFiqMHPZbEFidKI1YSKLtPisS0l5trZxYYnB1Q0cnyLfdO0/nezUMTBXHZAWYO+stwd74WOe0XWNTD0zSZGMYGNd0Er92LMIX1jOkn+oI9GgHIA+Ofk4xAlV4MxI+wB7h1huI93f8amx8cGgSv2RdMWUhrRkMf4PaLNdcG4AaAjF1yBNKVVg4AxQyGD+bT4s8IbRPE8ERmgEE1GUUvEZQ0QvJ0mEisZChx/fqKlxSfjAQAxkg4CZjYHePSPaif+pu8na1rqqK7ZbYy0rWPEUuS5zlP/UTqyOMeSEqmb0tEVMQBdEsHM1scv77t1PVfjazrjB/wTpDorBVNLYanzKn0BW2jXaeGyObz6Y52wKRplWqYus5TlWp6p/HFGwUxscIrzD/eQQtUNeWAdkBD9S6jOfYTb3DS7hd/cdOFBy3LSKA0jzZyIk2dfKBibsSR+3dUkOIlD7R4wYD8alMQJ9eOvfx9If+3jnhES7qY/y8Y4T+1HUQK6u0QVgIqEwM9MtY2e/T8Ky7UXPJQjwL+HJQ7ZY304csMPSx53WDNNXNMbA7053I0tsyCHQTV5hk1SHlH7TuAAcY6zKrgJCy5sfWey2MMSm6lMohs4CzRecMhcFwoGbJRNf0IjBAMD6R4jHz+RcrOeFuPjHSdq5xXzS8OcS0zwwSS7MaqvzZ8Lg+iM+Sjk05TKXKLNjtwPqw9Ja/BfgCvEfTQsAHHrTf+fYybqjZ3R61dkwkpn5MOIsmM72pqrK8NRNANNK41K0cHFIrGbskqDSilJwPBTkR7x6YfgAjW2WOmXT7DKGp59UJMCs/nIvTacDnRCRYVYA4ilWvIOfUulXvxdIllpbtuHj/xVIB8OGieqJrJtOvF36y975omoq/9hmQMLL5YZWaEfIx98Flap2MfnOxPC1CA2UpQ7cTrzZRmuTQ0vLAbLiHBf/FjUFvJPFtgG98P7MssnT8t3ax+CRlpEM8XmhFhnQ06+fNbVC7PGpgxhLbVk8tFiC5Pg+xVXKlpEkVJ35+fGbRkqbGiSmyrEmwIRH8ZMKltjhfRz4DjBaxTOlS7DarSHixgCmgld8jutJQXuDpgw/GVlthchr6l973aRc4XD6hVqTo4VWz+TJcEC10e/wX9xb3zIpjANqnsSRJt2r3/HX9t2J169a28tCldWkqOWOSSvSAsI+VKrQQgkX9f9SBJh24Bu4tpuZRNvgDsXRIMh3Ej4x+eDAoiqJxZ+XJVbgv0hXK2Mod8RcL2IaSnXmVv22qgdXoLeSbVf751LOsqnNoaOjgjgNF4Z1LXQNXOkJQyo3I5RImEcWCUTLj8+NHEI4JIgURcKyzfxjsDdMaCRRpxcQL1b9T2oRMPukQVqaGOnw0X00P7AXsgwo0RcHVDoBqVdX27qJiTPbRtc1Fh3CbQv6QcXHuvev18aMogE+Nz3sYIYJu6womw79gFqz0aq8StlYdGmA+tKKDR/keVaQFeCb+/Z8nm0Q2qOOavP2mp3wjtPV83vmlos58jmeeDcLaBPI50rPdeu1+f5uCPuT9X33g/ucMYO00XZUJkOYLGw+uDL8h7bN5YAedJi56eDj7e1ydNnG0wXoIQtcQD4vobzGq1N+55PjrexV+OjDftplX4iF5SDEgtORgeblK181b+H3RZ0o+b11zWNn1Inuf/HiQ9HRGD19ssaO7oDreBk27t7xArrkPyalpzuDZ/ugXctsqOxXXbDoE9uTus6Yh5EYLY8t2ugPYN3SYd622Y901o5bmMpWBhr+1K/nqlq4uXUbCrCeL391Uyas5khferdyz/aIZ5J3Y+bTx0u+9fjuCPMsKyqEwI7OShmFlXkKqJNvBOeBBtapoolr5j0Ny0800tx69TnPbv3aDa/22evyEs+hpztr+bZW5uDfBCzm5RprtGxC8XN1zMC/rlz3chMwWge8nSa0MuDLszrWL9eKHg1UcEZwGfTdQByhVaHMmXBbQtdpFeWE57QGXVwGZem5ApGBgWGlhGOXVq9364THBqyRW4ZRj7P6+PmoPV2tMcvCcWukIXRk1yPXarTbO+e9DcvdMV1W4573ordIDg6O2fPMebZn/97GXqnjA9Nce25AkK6LJUdkU1LX8dDVG1vS+ojY4smdfeLM6i3s5tZ121NnfMt57uT76OjYveF1Z/zJjdwbrb7P9GXqtd4=
*/