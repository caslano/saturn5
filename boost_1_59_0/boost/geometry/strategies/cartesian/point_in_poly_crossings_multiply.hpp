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

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

/*!
\brief Within detection using cross counting,
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation
\see http://tog.acm.org/resources/GraphicsGems/gemsiv/ptpoly_haines/ptinpoly.c
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
class crossings_multiply
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

    class flags
    {
        bool inside_flag;
        bool first;
        bool yflag0;

    public :

        friend class crossings_multiply;

        inline flags()
            : inside_flag(false)
            , first(true)
            , yflag0(false)
        {}
    };

public :

    typedef flags state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            flags& state)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const tx = get<0>(point);
        calc_t const ty = get<1>(point);
        calc_t const x0 = get<0>(seg1);
        calc_t const y0 = get<1>(seg1);
        calc_t const x1 = get<0>(seg2);
        calc_t const y1 = get<1>(seg2);

        if (state.first)
        {
            state.first = false;
            state.yflag0 = y0 >= ty;
        }


        bool yflag1 = y1 >= ty;
        if (state.yflag0 != yflag1)
        {
            if ( ((y1-ty) * (x0-x1) >= (x1-tx) * (y0-y1)) == yflag1 )
            {
                state.inside_flag = ! state.inside_flag;
            }
        }
        state.yflag0 = yflag1;
        return true;
    }

    static inline int result(flags const& state)
    {
        return state.inside_flag ? 1 : -1;
    }
};



}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_CROSSINGS_MULTIPLY_HPP

/* point_in_poly_crossings_multiply.hpp
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
*/