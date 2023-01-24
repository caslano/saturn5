// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, typename Strategy>
struct distance
    <
        Box1, Box2, Strategy, box_tag, box_tag,
        strategy_tag_distance_box_box, false
    >
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Box1>::type,
            typename point_type<Box2>::type
        >::type
    apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BOX_TO_BOX_HPP

/* box_to_box.hpp
W/W9gddgctiFF2N5G4UixDrJk1iR87vpxdWTQi+ec9LSi4dOOkXalL+vU99XdbKbDmYifCA/DSz2DJscmcUxpAWv3HxS8LXrofLqDSH0wEkmTzOP4KQ00YUqqSt5d31Np3nP9pOCZr4AlY+g9Pt9Kocx31JtjM9IbmTXk4w2fcBoE/cZuGY9W3N0SA56XAlOxPDitpDdWN2m/ZO48XhSifx4CXuXeaqhlfXxLFW/tz3LRGj84Pec76//vVO+TXNJo1wcWLu3fjaZ/dzz1xDaAY3f/J7TqsesfpircKZLuZX2Q32R83rXc3b93vZOTp0IoffgA+ktprbtSwfmflrowEJQmQ9l7dOW/18PvZfpQGfpKNvtejI21wdGMUiKTmYgrWYG++os5ui19Glri9O0EgfVsjQsUd+3GVqxvspY6I7pbi2mRjxlatyb9F3wj/G61ZgcIAEcA+EjDm+mIbW/qAuM6tP95vo0HDld/vG07f18Ao0Bp/j7STvlfD+HiXYOzyD9aSRDBfBhlb3z7yWnbDGfo6ExTvRXvSKElEcw6WL5dor7kiuX2n+/Bho/E7+/v9t4Qi55uovn7umrr9On7HsPGn8/JfSf3fo67pLSCFd4cH1eNqwBkL3P2fy/nxG66BBUCqBUPMPskMxjttgW//CMxbVS5IhX+ntfICQLS7V4PnkDt7hQGQi1AaA2XLDlMWfXAy/tccScrXhG
*/