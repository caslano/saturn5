// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{




/*!
    \brief Traits class binding a convex hull calculation strategy to a coordinate system
    \ingroup convex_hull
    \tparam Tag tag of coordinate system
    \tparam Geometry the geometry type (hull operates internally per hull over geometry)
    \tparam Point point-type of output points
*/
template
<
    typename Geometry1,
    typename Point,
    typename CsTag = typename cs_tag<Point>::type
>
struct strategy_convex_hull
{
    typedef strategy::not_implemented type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP

/* convex_hull.hpp
TTah2vbjXPytivUFYkAzS0YUfK0dsDj3+YqboKf1kD0QrHivXdDJyzwkFO5GFq8LjEQjBJN1Wg0AuQW0K9Zn64H+ssGRvDLsAxQ+W6b0WSlIktgtOkKSRvy6Dl4UeH1/VFxkQd10Nr6xjNKM2NpqFPPtBDAK6WWVQEaaYL7BSug/NnoBQ4MyCkIu61NC0BplMKQqlq7I82tk7aiIzLnxPCrA5wUqa3Rmkiow4wzVA5W8Kz8askfDSvo5RCOqUjXTDAVbgbodKOV/gW+yT/03YRz5fD84fNdBgGcGwmRBuc/VJA1fjA+NhyxWiHp8heceFYpTqcWF50usfK7EEo2hXv+K0ycWQPmikyf+iDMjihrIwwD/xAMe8k7e+dMPd1A5+bF1yEPhAQ9Jotw+f+G/xzccmbEDrDsyPYPlhyN8yVPhB1/xqXD6s+B0BlyZPp4Bv6iHoeSSkzgF3RT3ppEvjjGni+AnyMY2ILaVXC/VHw1LuSyzxNM+yDn46CB78JHpmS84/Eg3E8+dk5N2xa2HqVc6lILqybT2X3g+hWxTMFEsO6yLwxPgkvE49JecZoGnaXtikR57hmdHeZubloTPesX3OhjCu0y4slgI3eN4CIO2PivR2WzTeaat87eHlhFUtDuHK2/PYbI/h8Ub
*/