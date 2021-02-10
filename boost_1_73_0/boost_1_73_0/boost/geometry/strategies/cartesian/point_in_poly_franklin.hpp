// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

/*!
\brief Within detection using cross counting
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation
\author adapted from Randolph Franklin algorithm
\author Barend and Maarten, 1995
\author Revised for templatized library, Barend Gehrels, 2007
\return true if point is in ring, works for closed rings in both directions
\note Does NOT work correctly for point ON border

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */

template
<
    typename Point_,                   // for backward compatibility
    typename PointOfSegment_ = Point_, // for backward compatibility
    typename CalculationType = void
>
class franklin
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};

    /*! subclass to keep state */
    class crossings
    {
        bool crosses;

    public :

        friend class franklin;
        inline crossings()
            : crosses(false)
        {}
    };

public :

    typedef crossings state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            crossings& state)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const& px = get<0>(point);
        calc_t const& py = get<1>(point);
        calc_t const& x1 = get<0>(seg1);
        calc_t const& y1 = get<1>(seg1);
        calc_t const& x2 = get<0>(seg2);
        calc_t const& y2 = get<1>(seg2);

        if (
            ( (y2 <= py && py < y1) || (y1 <= py && py < y2) )
            && (px < (x1 - x2) * (py - y2) / (y1 - y2) + x2)
            )
        {
            state.crosses = ! state.crosses;
        }
        return true;
    }

    static inline int result(crossings const& state)
    {
        return state.crosses ? 1 : -1;
    }
};



}} // namespace strategy::within





}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP

/* point_in_poly_franklin.hpp
+2R4Vc7B5BSLZhaaFyqIPUwsrNIxywRGd10V9mY7leh60737pptfvIDDCVHHNez3unmxrVdCrF1alPK8dh+s0/BEvPcH9lCvVG3TS40qleiWZ/vU0elqNbnqD127jlqicFMWp3qlMLlhtDkph8sqycZY70SR9HE8AJXQq6/8ntZ3KPlIC29MJHoq34tpj953C4yhTMuipbGn353qFyGbMovBX4k/uJcVhcfYQEmKvzZhTh+3c+lM4Eir8R4WjNRtEAs5b+g95Awb5sEPmKk/VPk3C24EJeJkALTtNdpqbapd+sq8pWKRv4xYxvc4qTAQtDV+YhiiKrlx9Ngsq0+91Ospkopbqur8NTR/b7X7vyrenqpn3PldFW+76mnzC5sf7DcOpzzfytcfylnV6npmu2P7go/DVSyo/WRR4aExhpImYGhcXY+b1J28zOh/7ehKpa1v0KzazN1fGYhNM2HbaRrM9C8SVbwj+h9QSwMECgAAAAgALWdKUlfbH3cfAwAAkwYAAB4ACQBjdXJsLW1hc3Rlci9saWIvc3lzdGVtX3dpbjMyLmhVVAUAAbZIJGCtVU1v2zgQvetXDJKLHahWmwI9bIrFGo6SGHXswFbWayAAQUsjiy1FqiQVx0B+/M7IdtNi282ltC2K5Jt5
*/