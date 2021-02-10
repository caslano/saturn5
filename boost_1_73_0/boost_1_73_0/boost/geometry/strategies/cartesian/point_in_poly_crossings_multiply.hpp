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
SPeDM6654d48NW8L9vLKTTTTLk78KfczGjOtKRNdXE3VDIsx0fgzWNJTjI0htjRKnYGkYX8lEPZUp4jFcS1H/W4gLdQLc6iYInBjAqouRnlZc8ZjLC45o/CTEVwWw+0sgmQDU+UoWXQQLLcFfX7H05hHWAKU1O0ittlM24Ot9UtV5Jui2Q2Dn4mFbY4LhT7mHN4Tc6OeGaltj5OLKPubZwVRs1bppap6OhkGxLxa0p3rhk14S+lJkyCgsVK+xMKA5EE9xXpm7nZ6j8Rm8t6qvu2goh/c7n22XXu4VdhufAoDWxspn/c7aGAXc8bP56CUo69ZhH1AgMaY3Ki8A9RwJyN0ZtOqRRHoiwc/mge6o61HrLfwAcEIMyrEKmIKa7EmxyRfsTQo1vTbwxnncTnd2JFb13YSxFkaCexNArbW7WZ3NCUoIEywjkPE73mEimM9Wd6GRLDWZSKWmWVUTE2zNc4ii4V+pYcpiaHNZ3Yv81UyS+8auaktMMD58uWYOsSi/T2CZ37I/TuV+s/o7ZwO+AdnOOx1KW7wExzZjrfMkq1Y/8tGcHO5Ipkw2Hr8Rm7CW8ulwqRg0cybvY0Yf/xw+o9Xr16fviLI4riVYaGm+ZWpxy9mC/BtZ1ZQrnvIVjlu8RRLOGH/Tbn4Tx19
*/