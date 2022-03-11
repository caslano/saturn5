// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

#include <boost/array.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry { namespace strategy
{

namespace within
{

struct decide_within
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = false;
            return false;
        }
        return true; // continue
    }
};

struct decide_covered_by
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = side >= 0;
            return false;
        }
        return true; // continue
    }
};


// WARNING
// This strategy is not suitable for boxes in non-cartesian CSes having edges
// longer than 180deg because e.g. the SSF formula picks the side of the closer
// longitude, so for long edges the side is the opposite.
template <typename Decide = decide_within>
struct point_in_box_by_side
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Box>::type
            >::type side_strategy_type;

        // Create (counterclockwise) array of points, the fifth one closes it
        // Every point should be on the LEFT side (=1), or ON the border (=0),
        // So >= 1 or >= 0
        boost::array<typename point_type<Box>::type, 5> bp;
        geometry::detail::assign_box_corners_oriented<true>(box, bp);
        bp[4] = bp[0];

        bool result = true;
        side_strategy_type strategy;
        boost::ignore_unused(strategy);

        for (int i = 1; i < 5; i++)
        {
            int const side = strategy.apply(point, bp[i - 1], bp[i]);
            if (! Decide::apply(side, result))
            {
                return result;
            }
        }

        return result;
    }
};


} // namespace within


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

/* point_in_box_by_side.hpp
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
*/