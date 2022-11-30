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

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_EXPAND_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_EXPAND_POINT_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/strategy/expand.hpp>

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

#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_EXPAND_POINT_HPP

/* expand_point.hpp
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
*/