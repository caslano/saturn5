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
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
*/