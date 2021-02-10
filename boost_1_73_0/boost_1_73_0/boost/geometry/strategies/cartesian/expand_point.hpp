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
FkJKtEkZ2GiF4RhqSkAWYuypJxyAsVWmiUYHbXuw2eI6r1Cq0Wn7hJqAe2ptLaaoP8J+0MmeLQnSb62/A9bWIT3P71ZjY1TQ8byowkJyybRvwmIbtAGCkslwYCG3DBy4nrrdJYyia9NSSVTN0NooEXXka8QV+/SSb3Cdxz6rVIohFrqsrMh2q2EYM1h/MNyhsRO3iyiKMYcweGRpIBZCqyw0O3XoitY948SoCHzIG5wFs+6amwVHUHs+bneKwCEOd/I5U22pI5mx2bW2R7ZVGO8yihf21TY2pijKWHvO4DzT6FPwIjdqlnB2XUzvworhIHCtJ8MN9f/iRBXyplD6Owadi03eRQrGWOG1LUA7+XlQ6p5Z2xXUuxwMO3dZXyTrfjQNFOloz8eXfTMui65lfaB0oAeU8uI3sjul7/kUG2dzhRy1inGQ+e4yaocRRbNOOXzcNssF7SDYu4h9RnsE7gjYKejKFCe4qyfhreVndsxARTR4o26qITUX1YT2mTrxm7uDTMOQ7sx+o+ouZr/hnZatUBV9yJJ8o6GLXq4SmO9HiZkleEzKCsxGd6F0pb1N7wrwncIMoANA/OC+MGWPb4wfxXH8890Bxy2uS5LWvN19xw5UF3ebVxhRH15gjzs1zdWny0Gh3zli325e
*/