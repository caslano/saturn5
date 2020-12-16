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
w/g9puMPeB3P4X08j/ZkegEL4iWshOnojZexC17FIXgdkzADk/Emrsdb+BHewRN4F8/iPfwRH+ItfIL6uNFfsRT+jl74HPugzp71wFw4Cu0wAXPjdsyL+zEfHsOCeAkLoT5etDAWREesjEWwJjqhOxbFhlgMW6ALtsc30BeLYx8siYOxFAZgaQzBchiP5TEBK+BqrIrbsBoew+p4B2vgQ6yFj7E2kreuLlbGJlgTm+NcbIEJ2BI3oCduRy88gG3xKLbDi+gt8VsdsBT2wDj0w03YD3dhf8yVh/oEi+EgDMIgjMJgnI7DcQOG4lYMx30YhacxGi/geHyIEzA/x+tELI9x2ACnYD+cioNxGhriEnPJMyt5lpVCqsj/XeT7+iKpt97FergUG+Ny7IkrcBiuxFhMxgW4Surv1bgf1+BhXIc/4nq8jRvQkbw2ohu+j63wU+yKO3AQ7sRxuAsX4x5ci3vxMO7DdNyPv2Iq5mJdPsOCeAAr40HsgH/BQDyE4/EwTscv8W08hgvxK6kPQnTyXAyvSj1SAAdKPTJZ6pGp+CZOx6Y4E31xFvrjbJyGc3AjzsOfcAFewgSlflSed7FOWevHWfq4SJyDpXEeNsD52AGTcCW+i+/hUtyDK3AfrpT9/1Qnz67wqdTD+v19W/L5Rerv21ga72JDvIee+ACH4kMchY9xEj6R4+ApLsPnUl/n1sdpoD1eQAd8gnnwDyyE+vrOEWtgGWyJ5bEPumIgVsTRWAljsSpuxGq4GavjVqyHJ9AN76I7PsIGSJmpwJTnVjzPMq6/vlyP5T1Ab4lf8MMW2B+74EAcjIMwBIfgChyKn2MQHsUR+CuORAcyCUNHjEE3HIsdcBx2xfHYFyfgYJyI0zAO5+NUXIlzZf0W4le4CK/jO3gPk1F//K/GsrgGq+IGbIIbsSVuxgH4AYbhhxiNW3AOkoexPTquwO24BvfhTtyPR/AA3sSjWC435w964VfYGY9jXzyBA/EshuN3OAG/x7n4Aybiz3gCf8F/YAbaUb/ewKp4E2vhHWyMd9EH72NPfICD8RFG4GOchE9wDj7FXfh3TMN/4Pf4DG/ib/g3/B3z6uP6sRg62rE9sQxWwbLohuWwJVbADuiK3bAijsBK+DZWxiVYBVfhm7gHq+IZrIbnsCleRw98iK2xIMekJ7qiF9bDNuiFbbEXtsNB6IPB2BHnYidMwC64HHvi+zgA9+JAPIyD8CscghkYiIU5R4ZiBQxCdwzGhjgM22AMHsYx+DOOw1b5OI7RGyfiCIzDCJyOU3EGXsa5WDc/9RgOwvkYhgtwPCZgAi7EjZiIW3AR7sR3MBUXYzom4U1cis9xGTpRYa/FCrgOG+J69MYN6IcbMRC34nDcjvH4Ca7FT/Eg7sRzuBtv4h7sVJDrDg7EzzAKP8d5+AW+hwdwKx7ENPwL/ohf4lU8gr/jMSxTiPMHa+PX2BCPox+ewEF4CoMwHSfhZZyBf8W5+ByT0E5/X4i5MRXt8Rd0QPvC1L9YDvNiY8yH/TA/BmABDMSCOAILYQIWxsXohMuwGH6Ab+BeLI6HsQQex9L4A1bAK+iKGVgViztyX4a1sTb6YB3sjXWxHzbCYdgYx2ITnIrNMAGb4wpsgWuwFR5FT/wJvfA2tsFn2A6duZC2x1LojZWwA9ZAH+yCHbEv+mIYdsFJ2AfnY19ci374KfbDw9gfT+IgPIsB+HccivmdOJ/wDQzG0jgcK2EIemModsYo7IXROBZjMA4n42cYj9/jVLyA0/ASTsfrOAML6uN0sRLOx2q4AB8a7kfkOS9WlfsAR/4fl9lPjz37B1OwPK7DOrgePXADDsaNOB/fxy34Ee7CrbgHP8Y=
*/