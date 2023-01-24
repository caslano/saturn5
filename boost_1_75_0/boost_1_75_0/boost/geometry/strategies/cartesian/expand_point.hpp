// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/strategies/expand.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct point_loop
{
    template <typename Box, typename Point>
    static inline void apply(Box& box, Point const& source)
    {
        typedef typename select_coordinate_type
            <
                Point, Box
            >::type coordinate_type;

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;

        coordinate_type const coord = get<Dimension>(source);

        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        point_loop<Dimension + 1, DimensionCount>::apply(box, source);
    }
};


template <std::size_t DimensionCount>
struct point_loop<DimensionCount, DimensionCount>
{
    template <typename Box, typename Point>
    static inline void apply(Box&, Point const&) {}
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct cartesian_point
{
    template <typename Box, typename Point>
    static void apply(Box & box, Point const& point)
    {
        expand::detail::point_loop
            <
                0, dimension<Point>::value
            >::apply(box, point);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, cartesian_tag, CalculationType>
{
    typedef cartesian_point type;
};


} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_EXPAND_POINT_HPP

/* expand_point.hpp
YiDRNUWGxMFsfmjeZBGwVFtQxL7qG6ct+zJ2S9ICD9DRrLWe5gtZJ4knDaxWpivKKacBEcN6KN+SXG1RmZlRbe64IupN3Jm5UHdzGsF62MmfNLR0jnrBZo38CcwkNwbEeAgdhSzKUgZEI5eK6TqviTNM3KINDcYEo3ny23RtYbECBmY+YZdv7kjuFrkWf2e9v9RtedX06QPqna4/neXTgIn3x1N99/zHAvKlBqsjuyM7Gd6sQBJWZVr1c+y0EPQfWzOTM0sNTJMJv3pf+d967g/q3RJ+DIKdind4IUrBIxed4lldPjt3bmApmPq5ebKPa0Ji19iT+MhT14HS5tEnPr+Mpd7dDePvI0+d6u8vzs4tYHkXH1LuAgh5WVHiKXchCbx+zPfCKXeh3IzOUkY3v58rpoB3/GMatdod6/ZDDIuu69n9d4IjAcDgWp/pOObrstYxJVnVMSr+iMLFF2B02CiZkIse5CtP2djjc4+mNTw2wgTg7DsYHmWosrjjE09jQ7e5XcUY3zrREMnhF1Iw2h7kbTRsWE7LvJcfFeNxl59augNo74w1CPbRGrvgcnjYkHNCbgyyHkWqQOy5gy7IuHg2CUH5+nI7qBTYNYFr657+ZtSHAVEkRq0Xh42fholESX6cMcCGRqibudrEEJgpPAqRffg0fo9vlXsY9gRe0buAmECH/8xkP3dIcmoY23cgZxSx0HuwQjUB3tKi
*/