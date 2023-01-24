// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2017.
// Modifications copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SIDE_BY_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SIDE_BY_CROSS_TRACK_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/side.hpp>
//#include <boost/geometry/strategies/concepts/side_concept.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

/*!
\brief Check at which side of a Great Circle segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam CalculationType \tparam_calculation
 */
template <typename CalculationType = void>
class side_by_cross_track
{

public :
    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType,
                        P1, P2, P
                    >::type
            >::type calc_t;

        calc_t d1 = 0.001; // m_strategy.apply(sp1, p);

        calc_t lon1 = geometry::get_as_radian<0>(p1);
        calc_t lat1 = geometry::get_as_radian<1>(p1);
        calc_t lon2 = geometry::get_as_radian<0>(p2);
        calc_t lat2 = geometry::get_as_radian<1>(p2);
        calc_t lon = geometry::get_as_radian<0>(p);
        calc_t lat = geometry::get_as_radian<1>(p);

        calc_t crs_AD = geometry::formula::spherical_azimuth<calc_t, false>
                             (lon1, lat1, lon, lat).azimuth;

        calc_t crs_AB = geometry::formula::spherical_azimuth<calc_t, false>
                             (lon1, lat1, lon2, lat2).azimuth;

        calc_t XTD = asin(sin(d1) * sin(crs_AD - crs_AB));

        return math::equals(XTD, 0) ? 0 : XTD < 0 ? 1 : -1;
    }
};

}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SIDE_BY_CROSS_TRACK_HPP

/* side_by_cross_track.hpp
yuA6F7CqHD8Ua658oJwtU3lS56rSiKCw6fNmr2pdO9DqrTAe4jw1ZLtYq15GjAgvKg+ntVhS4GQZTbumJzSHV948alPBXr33bo7jLViWXKhKdiUdMm/aqvLtVHlyiJGs1stabIhGiujSgNcqilSzRgKaawTupO/C6NsJhLw+eBbXbIDpFzjq9YZJim304O2u31mn4VO1hiUHWHEjxCNIHofulgE3I3gVR6WTfe9vjR4daI6C13S7FLQsNmcTgn5WFHMRrVG+Gv6MDtHtwklxqKvpLNn2lD1Zs+rVPd599ymcEu188fk0i7TZIM6Sz69VB5gitRGWrpJTlM2glVIJXExWJeucb7SxcWpu79ADXGn8Ofbitu1oDO0ovRSPLdLqOCtsLp8lcyvpBmNPM6KHBWIodzPxHr5M9phCX9LrbSuU2F5kPcp9qAnKPCT2P+syU8zqtJN0X7UX1t2y09gMu+fwAf7h9/0Lba6oV054ZJnRiPUkuCj92q7BL4yPOrbwmU9zWoBY5FNH/Bqd1hPT5VtWTx2hyofpcPCgtqPiKf7TLE/Alns+Ehru6KlTRQiNdCj6BGb/XZoX6Y+HZPM7/EV1aXPjJYU/uxy320hxiSY0wV4YcsQ9raHyh9qsmJywwEG7zt+S5n/W1lFYSSzy+nhynE08lbZvaDESZLfdg3OzZv8EW7tTVGNyPbdbbePfX6PzqfhVev/y1ikp
*/