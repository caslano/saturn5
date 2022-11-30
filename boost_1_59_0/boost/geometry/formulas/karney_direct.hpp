// Boost.Geometry

// Copyright (c) 2018 Adeel Ahmad, Islamabad, Pakistan.

// Contributed and/or modified by Adeel Ahmad,
//   as part of Google Summer of Code 2018 program.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.
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

            // For longitudes close to the antimeridian the result can be out
            // of range. Therefore normalize.
            // In other formulas this has to be done at the end because
            // otherwise differential quantities are calculated incorrectly.
            // But here it's ok since result.lon2 is not used after this point.
            math::normalize_longitude<degree, CT>(result.lon2);
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