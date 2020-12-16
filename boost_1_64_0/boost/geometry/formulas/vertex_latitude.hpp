// Boost.Geometry

// Copyright (c) 2016-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP
#define BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP


#include <boost/geometry/formulas/flattening.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry { namespace formula
{

/*!
\brief Algorithm to compute the vertex latitude of a geodesic segment. Vertex is
a point on the geodesic that maximizes (or minimizes) the latitude.
\author See
    [Wood96] Wood - Vertex Latitudes on Ellipsoid Geodesics, SIAM Rev., 38(4),
             637–644, 1996
*/

template <typename CT>
class vertex_latitude_on_sphere
{

public:
    template<typename T1, typename T2>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1)
    {
        return std::acos( math::abs(cos(lat1) * sin(alp1)) );
    }
};

template <typename CT>
class vertex_latitude_on_spheroid
{

public:
/*
 * formula based on paper
 *   [Wood96] Wood - Vertex Latitudes on Ellipsoid Geodesics, SIAM Rev., 38(4),
 *            637–644, 1996
    template <typename T1, typename T2, typename Spheroid>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1,
                           Spheroid const& spheroid)
    {
        CT const f = formula::flattening<CT>(spheroid);

        CT const e2 = f * (CT(2) - f);
        CT const sin_alp1 = sin(alp1);
        CT const sin2_lat1 = math::sqr(sin(lat1));
        CT const cos2_lat1 = CT(1) - sin2_lat1;

        CT const e2_sin2 = CT(1) - e2 * sin2_lat1;
        CT const cos2_sin2 = cos2_lat1 * math::sqr(sin_alp1);
        CT const vertex_lat = std::asin( math::sqrt((e2_sin2 - cos2_sin2)
                                                    / (e2_sin2 - e2 * cos2_sin2)));
        return vertex_lat;
    }
*/

    // simpler formula based on Clairaut relation for spheroids
    template <typename T1, typename T2, typename Spheroid>
    static inline CT apply(T1 const& lat1,
                           T2 const& alp1,
                           Spheroid const& spheroid)
    {
        CT const f = formula::flattening<CT>(spheroid);

        CT const one_minus_f = (CT(1) - f);

        //get the reduced latitude
        CT const bet1 = atan( one_minus_f * tan(lat1) );

        //apply Clairaut relation
        CT const betv =  vertex_latitude_on_sphere<CT>::apply(bet1, alp1);

        //return the spheroid latitude
        return atan( tan(betv) / one_minus_f );
    }

    /*
    template <typename T>
    inline static void sign_adjustment(CT lat1, CT lat2, CT vertex_lat, T& vrt_result)
    {
        // signbit returns a non-zero value (true) if the sign is negative;
        // and zero (false) otherwise.
        bool sign = std::signbit(std::abs(lat1) > std::abs(lat2) ? lat1 : lat2);

        vrt_result.north = sign ? std::max(lat1, lat2) : vertex_lat;
        vrt_result.south = sign ? vertex_lat * CT(-1) : std::min(lat1, lat2);
    }

    template <typename T>
    inline static bool vertex_on_segment(CT alp1, CT alp2, CT lat1, CT lat2, T& vrt_result)
    {
        CT const half_pi = math::pi<CT>() / CT(2);

        // if the segment does not contain the vertex of the geodesic
        // then return the endpoint of max (min) latitude
        if ((alp1 < half_pi && alp2 < half_pi)
                || (alp1 > half_pi && alp2 > half_pi))
        {
            vrt_result.north = std::max(lat1, lat2);
            vrt_result.south = std::min(lat1, lat2);
            return false;
        }
        return true;
    }
    */
};


template <typename CT, typename CS_Tag>
struct vertex_latitude
{
    BOOST_MPL_ASSERT_MSG
         (
             false, NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM, (types<CS_Tag>)
         );

};

template <typename CT>
struct vertex_latitude<CT, spherical_equatorial_tag>
        : vertex_latitude_on_sphere<CT>
{};

template <typename CT>
struct vertex_latitude<CT, geographic_tag>
        : vertex_latitude_on_spheroid<CT>
{};


}}} // namespace boost::geometry::formula

#endif // BOOST_GEOMETRY_FORMULAS_MAXIMUM_LATITUDE_HPP

/* vertex_latitude.hpp
JJk9kILbkPm2Bz0SSv0hj51ezIewn3YUQi/kk/72iSitXVZTX40MoKZEnbcyx0i1Rl7MobR35jGVsuUjmC0/5zLvBFXVqDxP1eNmvr2w+QEuPV3MxzwtUTzm+L0uXEnvRpt1Q1D5bYUcpV/JcX1SeR05h0kmmc1x677sa7aOkW/3cR+68qtGH9pVqPs6N9Oe6l3UthOm/qtDig7fTjbb7mK7tpvbaNhtTBvdHNVGb43TRrfEaaN3RLbRLBvbRjfHtNGxfhm8/gSbgF+kTYSYv4H4uXyVXtTWsz/f9b+R7AR7MimRa51nJ5nnHdP5fuUA+SZOtmrn1bnQkqKqksXGGlwXWmOWPmqtSslcZrS93yH3AuzCarFnRplfnW/frdvfYus75j8j+g1iBPS1zg9SeX7wOtEn4L5ZgMa+TRP19xk3YUBCo14MlLrbjX2ZvwX8myV/wuCYMQTL0eO5P0k9/3kutV7YhdbCOW/gN9Q8k0p5P5nzfugUXfg5PhP4NOBd8BV3i8r72NXConBJbeWyqL5WzUtXkfwDogz/LzfPCnK43S3tJNsjzytqiT4H+iVYeNiOef++kXimQ9/rZDtP6V1PfpuM8VpVioTz51fM+Td21wuuP2y7Byh83P1Pifwux/6pemDfY9t9HjAedaWw+/nzr7KkPmz3fYelJL9F3Gp+l4PDvELEGx9MMehdDdtdTO7Poz554ua3TMCLxDNcpIhkoy/7gPwC1EfV6etb4dr6mkXhZeZ85tPE04XdpozK/+RU2MCFnD/0ROb/Vyh8jI+TI9uOwhl6YD003X67yr6wK+ysR1T+Y8WnqK5kQUltRbw1bubvZPTBDeRO1OKdu59i8A8y3vu5syetO1rW4KiEef42FnbLiSa+dPbTPYt78hjUetdVj474prDsgxRnDvkV8n3XNeQ3kvmI0dSF77/6IvzG0BmK5STn12ahxpvzzfplNWE9jRUI6nnimc9u5BaFkSzo2xmw+90FADkHLkXXmBIIJoWCHVCHW72X/jaF2duYb58mt4fpZhzx7v1O53z4gGRWkd8kzoffk99myOnp+x65n6N7kEPlm7QFfM+36RH5cIBb+p+Efxr8nyL/Fnnd20ntMtP6FqjvGTQ9Iv2pz+fwdoD2tKSlVOGSbyjQECjFJV+HC4HL6+CUR4PBs4LD9zgQyho8+CLv+wb4fSTm2V7A932rMLrwJoCDXj5wyHBUvMTP+Z5TyPeLhwSqcbu4jKABMbudQvLspXd0zTvG42WcPnRFUgkfj12Yr2chxz1EyidIdj+xy9zwm/FncNxl4H9Whut1ZkDCn8Z3qfvSe72cl/1lMOa96BDLbgTdQ2eRfguD6eQ23zOJ7OsS0yScf85r960V652UXJRQPtqDDfR+4KIbqAXA64KLq6uub6wPV9VVVFfVTdXNtDd4B8m2w8prco2prC419pazrXelKarI/fMTM3VFH+V2aaum96tHeka1S7GzV2v7ZJxX/QPJrdaekLMZ1MUSTfWpKsyMmDZerVlu6yXpi2P6U9QVyr+3SX6FZQ4opxZmW5dG8rN4rRy9LLnnirHCG/e852iiD+PzqIp/BnaRXHyWUx8vP5ys+umPVtaj4vTTR3tF9tPXcj/tmqUH9kce57wJ2JmBcuptlAdvKJVV1JXMrwyXxd0LZf5MxM93E8j9fbQ0HfT9IOIv5bxifsR6WKRZ9oWra4CMMeR7xPMD8QqPk8oNuS7CXANrfx6pu0ibyF3K511VnpEOlvsh9DY1/aZq+h74WODXM9GX56g8ovshJQ2YEpeVx80f5p1jlH0tuf+Acn9WmHPwsnLYfen8CrkDg3RxPswl3g8QbjLqkVt8EqM=
*/