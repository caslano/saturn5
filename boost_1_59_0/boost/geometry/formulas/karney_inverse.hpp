// Boost.Geometry

// Copyright (c) 2018 Adeel Ahmad, Islamabad, Pakistan.

// Contributed and/or modified by Adeel Ahmad, as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
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
#include <boost/geometry/util/precise_math.hpp>
#include <boost/geometry/util/series_expansion.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_inverse.hpp>


namespace boost { namespace geometry { namespace math {

/*!
\brief The exact difference of two angles reduced to (-180deg, 180deg].
*/
template<typename T>
inline T difference_angle(T const& x, T const& y, T& e)
{
    auto res1 = boost::geometry::detail::precise_math::two_sum(
        std::remainder(-x, T(360)), std::remainder(y, T(360)));

    normalize_azimuth<degree, T>(res1[0]);

    // Here y - x = d + t (mod 360), exactly, where d is in (-180,180] and
    // abs(t) <= eps (eps = 2^-45 for doubles).  The only case where the
    // addition of t takes the result outside the range (-180,180] is d = 180
    // and t > 0.  The case, d = -180 + eps, t = -eps, can't happen, since
    // sum_error would have returned the exact result in such a case (i.e., given t = 0).
    auto res2 = boost::geometry::detail::precise_math::two_sum(
        res1[0] == 180 && res1[1] > 0 ? -180 : res1[0], res1[1]);
    e = res2[1];
    return res2[0];
}

}}} // namespace boost::geometry::math


namespace boost { namespace geometry { namespace formula
{

namespace se = series_expansion;

namespace detail
{

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

        CT lat1 = la1 * r2d;
        CT lat2 = la2 * r2d;

        CT lon1 = lo1 * r2d;
        CT lon2 = lo2 * r2d;

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
        CT m12x = c0;
        CT s12x;
        CT M21;

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
            CT dnm = c1;
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
                    CT dv = c0;
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
                result.azimuth = atan2(sin_alpha1, cos_alpha1);
            }

            if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
            {
                result.reverse_azimuth = atan2(sin_alpha2, cos_alpha2);
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
                                  CT const& tol1, CT const& tol2, CT const& etol2, CT const& n,
                                  CT const& f)
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

                CT m12b = c0;
                CT m0 = c1;
                CT dummy;
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

} // namespace detail

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
    bool EnableGeodesicScale = false
>
struct karney_inverse
    : detail::karney_inverse
        <
            CT,
            EnableDistance,
            EnableAzimuth,
            EnableReverseAzimuth,
            EnableReducedLength,
            EnableGeodesicScale
        >
{};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_KARNEY_INVERSE_HPP

/* karney_inverse.hpp
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
*/