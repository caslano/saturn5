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
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
*/