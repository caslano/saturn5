// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SIDE_BY_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SIDE_BY_CROSS_TRACK_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/formulas/spherical.hpp>

//#include <boost/geometry/strategies/concepts/side_concept.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

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
        typedef strategy::within::spherical_point_point
            equals_point_point_strategy_type;
        if (equals_point_point_strategy_type::apply(p, p1)
            || equals_point_point_strategy_type::apply(p, p2)
            || equals_point_point_strategy_type::apply(p1, p2))
        {
            return 0;
        }

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