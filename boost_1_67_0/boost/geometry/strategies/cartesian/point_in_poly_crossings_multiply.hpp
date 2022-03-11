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