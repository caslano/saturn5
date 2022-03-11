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
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
*/