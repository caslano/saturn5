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