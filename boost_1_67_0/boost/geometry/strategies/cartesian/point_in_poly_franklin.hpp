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