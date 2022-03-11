// Boost.Geometry

// Copyright (c) 2018 Adeel Ahmad, Islamabad, Pakistan.

// Contributed and/or modified by Adeel Ahmad,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
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

#ifndef BOOST_GEOMETRY_FORMULAS_KARNEY_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_KARNEY_DIRECT_HPP


#include <boost/array.hpp>

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/hypot.hpp>

#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/result_direct.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/series_expansion.hpp>


namespace boost { namespace geometry { namespace formula
{

namespace se = series_expansion;

/*!
\brief The solution of the direct problem of geodesics on latlong coordinates,
       after Karney (2011).
\author See
- Charles F.F Karney, Algorithms for geodesics, 2011
https://arxiv.org/pdf/1109.4448.pdf
*/
template <
    typename CT,
    bool EnableCoordinates = true,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false,
    size_t SeriesOrder = 8
>
class karney_direct
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

        CT lon1 = lo1;
        CT const lat1 = la1;

        Azi azi12 = azimuth12;
        math::normalize_azimuth<degree, Azi>(azi12);

        CT const c0 = 0;
        CT const c1 = 1;
        CT const c2 = 2;

        CT const b = CT(get_radius<2>(spheroid));
        CT const f = formula::flattening<CT>(spheroid);
        CT const one_minus_f = c1 - f;
        CT const two_minus_f = c2 - f;

        CT const n = f / two_minus_f;
        CT const e2 = f * two_minus_f;
        CT const ep2 = e2 / math::sqr(one_minus_f);

        CT sin_alpha1, cos_alpha1;
        math::sin_cos_degrees<CT>(azi12, sin_alpha1, cos_alpha1);

        // Find the reduced latitude.
        CT sin_beta1, cos_beta1;
        math::sin_cos_degrees<CT>(lat1, sin_beta1, cos_beta1);
        sin_beta1 *= one_minus_f;

        math::normalize_unit_vector<CT>(sin_beta1, cos_beta1);

        cos_beta1 = (std::max)(c0, cos_beta1);

        // Obtain alpha 0 by solving the spherical triangle.
        CT const sin_alpha0 = sin_alpha1 * cos_beta1;
        CT const cos_alpha0 = boost::math::hypot(cos_alpha1, sin_alpha1 * sin_beta1);

        CT const k2 = math::sqr(cos_alpha0) * ep2;

        CT const epsilon = k2 / (c2 * (c1 + math::sqrt(c1 + k2)) + k2);

        // Find the coefficients for A1 by computing the
        // series expansion using Horner scehme.
        CT const expansion_A1 = se::evaluate_A1<SeriesOrder>(epsilon);

        // Index zero element of coeffs_C1 is unused.
        se::coeffs_C1<SeriesOrder, CT> const coeffs_C1(epsilon);

        // Tau is an integration variable.
        CT const tau12 = distance / (b * (c1 + expansion_A1));

        CT const sin_tau12 = sin(tau12);
        CT const cos_tau12 = cos(tau12);

        CT sin_sigma1 = sin_beta1;
        CT sin_omega1 = sin_alpha0 * sin_beta1;

        CT cos_sigma1, cos_omega1;
        cos_sigma1 = cos_omega1 = sin_beta1 != c0 || cos_alpha1 != c0 ? cos_beta1 * cos_alpha1 : c1;
        math::normalize_unit_vector<CT>(sin_sigma1, cos_sigma1);

        CT const B11 = se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C1);
        CT const sin_B11 = sin(B11);
        CT const cos_B11 = cos(B11);

        CT const sin_tau1 = sin_sigma1 * cos_B11 + cos_sigma1 * sin_B11;
        CT const cos_tau1 = cos_sigma1 * cos_B11 - sin_sigma1 * sin_B11;

        // Index zero element of coeffs_C1p is unused.
        se::coeffs_C1p<SeriesOrder, CT> const coeffs_C1p(epsilon);

        CT const B12 = - se::sin_cos_series
                             (sin_tau1 * cos_tau12 + cos_tau1 * sin_tau12,
                              cos_tau1 * cos_tau12 - sin_tau1 * sin_tau12,
                              coeffs_C1p);

        CT const sigma12 = tau12 - (B12 - B11);
        CT const sin_sigma12 = sin(sigma12);
        CT const cos_sigma12 = cos(sigma12);

        CT const sin_sigma2 = sin_sigma1 * cos_sigma12 + cos_sigma1 * sin_sigma12;
        CT const cos_sigma2 = cos_sigma1 * cos_sigma12 - sin_sigma1 * sin_sigma12;

        if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
        {
            CT const sin_alpha2 = sin_alpha0;
            CT const cos_alpha2 = cos_alpha0 * cos_sigma2;

            result.reverse_azimuth = atan2(sin_alpha2, cos_alpha2);

            // Convert the angle to radians.
            result.reverse_azimuth /= math::d2r<CT>();
        }

        if (BOOST_GEOMETRY_CONDITION(CalcCoordinates))
        {
            // Find the latitude at the second point.
            CT const sin_beta2 = cos_alpha0 * sin_sigma2;
            CT const cos_beta2 = boost::math::hypot(sin_alpha0, cos_alpha0 * cos_sigma2);

            result.lat2 = atan2(sin_beta2, one_minus_f * cos_beta2);

            // Convert the coordinate to radians.
            result.lat2 /= math::d2r<CT>();

            // Find the longitude at the second point.
            CT const sin_omega2 = sin_alpha0 * sin_sigma2;
            CT const cos_omega2 = cos_sigma2;

            CT const omega12 = atan2(sin_omega2 * cos_omega1 - cos_omega2 * sin_omega1,
                                     cos_omega2 * cos_omega1 + sin_omega2 * sin_omega1);

            se::coeffs_A3<SeriesOrder, CT> const coeffs_A3(n);

            CT const A3 = math::horner_evaluate(epsilon, coeffs_A3.begin(), coeffs_A3.end());
            CT const A3c = -f * sin_alpha0 * A3;

            se::coeffs_C3<SeriesOrder, CT> const coeffs_C3(n, epsilon);

            CT const B31 = se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C3);

            CT const lam12 = omega12 + A3c *
                             (sigma12 + (se::sin_cos_series
                                             (sin_sigma2,
                                              cos_sigma2,
                                              coeffs_C3) - B31));

            // Convert to radians to get the
            // longitudinal difference.
            CT lon12 = lam12 / math::d2r<CT>();

            // Add the longitude at first point to the longitudinal
            // difference and normalize the result.
            math::normalize_longitude<degree, CT>(lon1);
            math::normalize_longitude<degree, CT>(lon12);

            result.lon2 = lon1 + lon12;
        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            // Evaluate the coefficients for C2.
            // Index zero element of coeffs_C2 is unused.
            se::coeffs_C2<SeriesOrder, CT> const coeffs_C2(epsilon);

            CT const B21 = se::sin_cos_series(sin_sigma1, cos_sigma1, coeffs_C2);
            CT const B22 = se::sin_cos_series(sin_sigma2, cos_sigma2, coeffs_C2);

            // Find the coefficients for A2 by computing the
            // series expansion using Horner scehme.
            CT const expansion_A2 = se::evaluate_A2<SeriesOrder>(epsilon);

            CT const AB1 = (c1 + expansion_A1) * (B12 - B11);
            CT const AB2 = (c1 + expansion_A2) * (B22 - B21);
            CT const J12 = (expansion_A1 - expansion_A2) * sigma12 + (AB1 - AB2);

            CT const dn1 = math::sqrt(c1 + ep2 * math::sqr(sin_beta1));
            CT const dn2 = math::sqrt(c1 + k2 * math::sqr(sin_sigma2));

            // Find the reduced length.
            result.reduced_length = b * ((dn2 * (cos_sigma1 * sin_sigma2) -
                                          dn1 * (sin_sigma1 * cos_sigma2)) -
                                          cos_sigma1 * cos_sigma2 * J12);

            // Find the geodesic scale.
            CT const t = k2 * (sin_sigma2 - sin_sigma1) *
                              (sin_sigma2 + sin_sigma1) / (dn1 + dn2);

            result.geodesic_scale = cos_sigma12 +
                                    (t * sin_sigma2 - cos_sigma2 * J12) *
                                    sin_sigma1 / dn1;
        }

        return result;
    }
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_KARNEY_DIRECT_HPP

/* karney_direct.hpp
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
*/