// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MERIDIAN_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_MERIDIAN_DIRECT_HPP

#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/differential_quantities.hpp>
#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/meridian_inverse.hpp>
#include <boost/geometry/formulas/quarter_meridian.hpp>
#include <boost/geometry/formulas/result_direct.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Compute the direct geodesic problem on a meridian
*/

template <
    typename CT,
    bool EnableCoordinates = true,
    bool EnableReverseAzimuth = false,
    bool EnableReducedLength = false,
    bool EnableGeodesicScale = false,
    unsigned int Order = 4
>
class meridian_direct
{
    static const bool CalcQuantities = EnableReducedLength || EnableGeodesicScale;
    static const bool CalcRevAzimuth = EnableReverseAzimuth || CalcQuantities;
    static const bool CalcCoordinates = EnableCoordinates || CalcRevAzimuth;

public:
    typedef result_direct<CT> result_type;

    template <typename T, typename Dist, typename Spheroid>
    static inline result_type apply(T const& lo1,
                                    T const& la1,
                                    Dist const& distance,
                                    bool north,
                                    Spheroid const& spheroid)
    {
        result_type result;

        CT const half_pi = math::half_pi<CT>();
        CT const pi = math::pi<CT>();
        CT const one_and_a_half_pi = pi + half_pi;
        CT const c0 = 0;

        CT azimuth = north ? c0 : pi;

        if (BOOST_GEOMETRY_CONDITION(CalcCoordinates))
        {
            CT s0 = meridian_inverse<CT, Order>::apply(la1, spheroid);
            int signed_distance = north ? distance : -distance;
            result.lon2 = lo1;
            result.lat2 = apply(s0 + signed_distance, spheroid);
        }

        if (BOOST_GEOMETRY_CONDITION(CalcRevAzimuth))
        {
            result.reverse_azimuth = azimuth;


            if (result.lat2 > half_pi &&
                result.lat2 < one_and_a_half_pi)
            {
                result.reverse_azimuth =  pi;
            }
            else if (result.lat2 < -half_pi &&
                     result.lat2 >  -one_and_a_half_pi)
            {
                result.reverse_azimuth =  c0;
            }

        }

        if (BOOST_GEOMETRY_CONDITION(CalcQuantities))
        {
            CT const b = CT(get_radius<2>(spheroid));
            CT const f = formula::flattening<CT>(spheroid);

            boost::geometry::math::normalize_spheroidal_coordinates
                <
                    boost::geometry::radian,
                    double
                >(result.lon2, result.lat2);

            typedef differential_quantities
            <
                CT,
                EnableReducedLength,
                EnableGeodesicScale,
                Order
            > quantities;
            quantities::apply(lo1, la1, result.lon2, result.lat2,
                              azimuth, result.reverse_azimuth,
                              b, f,
                              result.reduced_length, result.geodesic_scale);
        }
        return result;
    }

    // https://en.wikipedia.org/wiki/Meridian_arc#The_inverse_meridian_problem_for_the_ellipsoid
    // latitudes are assumed to be in radians and in [-pi/2,pi/2]
    template <typename T, typename Spheroid>
    static CT apply(T m, Spheroid const& spheroid)
    {
        CT const f = formula::flattening<CT>(spheroid);
        CT n = f / (CT(2) - f);
        CT mp = formula::quarter_meridian<CT>(spheroid);
        CT mu = geometry::math::pi<CT>()/CT(2) * m / mp;

        if (Order == 0)
        {
            return mu;
        }

        CT H2 = 1.5 * n;

        if (Order == 1)
        {
            return mu + H2 * sin(2*mu);
        }

        CT n2 = n * n;
        CT H4 = 1.3125 * n2;

        if (Order == 2)
        {
            return mu + H2 * sin(2*mu) + H4 * sin(4*mu);
        }

        CT n3 = n2 * n;
        H2 -= 0.84375 * n3;
        CT H6 = 1.572916667 * n3;

        if (Order == 3)
        {
            return mu + H2 * sin(2*mu) + H4 * sin(4*mu) + H6 * sin(6*mu);
        }

        CT n4 = n2 * n2;
        H4 -= 1.71875 * n4;
        CT H8 = 2.142578125 * n4;

        // Order 4 or higher
        return mu + H2 * sin(2*mu) + H4 * sin(4*mu) + H6 * sin(6*mu) + H8 * sin(8*mu);
    }
};

}}} // namespace boost::geometry::formula

#endif // BOOST_GEOMETRY_FORMULAS_MERIDIAN_DIRECT_HPP

/* meridian_direct.hpp
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
*/