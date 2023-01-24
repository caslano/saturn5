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
3T1I0ECCy5BggQR3BhgCBJcQ3N3dncHd3Qd3GBwGmVmrrT3sVm3Vnrr/Wx/68ur973tyH44dl5o9S7UflVDs2CVUfB6O1TCXG92DHLnwJu27uGcFTPKkkebNwGyRoR74DSuFHfpEGxxVnJfoTbsNsyl2Q5feck9HWGwaXGwMwnaxd35hnTJVU2Q5U99vhNRniE1yZm71Tii8La4/bRmnrGXEpmFr7hets0xq7hXVANeGTiR7xFOSWt2t1uPO08VXRTOy3E32dM5adyd0fgvvjOcz06QW9wyN5thRuC7kZWBZA5JH1PZquHMQxn5Xv4bH3q2Y6gjtAowQ+5gKLi8kbcM4pyqzsPK3c2FSlLUT6/02RXxLe29vGL3JHny9YypnGJc2v9/gmsyxK1tcTUlxeAw6VvIWnSIoD928A/3IfKaIOlpdJLz1LVT2TIRHmKubOqf917GBlo1/Ge2oJsNgAyvf1Et8Yrjqay/WHE67em9xQpoGFvf6SxbDPnrmBK1JKvwhKSTkBPGg0rBUc6aJ+Akd9ZM73oiGXpuSHWtAqXPOLyox3cgecj7e/5QmOdZwlCxpk6EteeqiKwF2Ef/tbur3HAwT+9swmr8LVjqWuqQsEe/HU15n/1sM+rwCvjLyiIe45R5O8ft44rwWicc08Mfed8vsgpps8bLDLCtFTcn8XJlN8hvTmqy5QCL5QRlD0+OnLmoKciHF3PAs
*/