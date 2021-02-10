// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP
#define BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

#include <boost/concept/requires.hpp>
#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/add_const_if_c.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Point, int Dimension, int DimensionCount, bool IsConst>
struct coordinates_scanner
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& point, Op operation)
    {
        operation.template apply<Point, Dimension>(point);
        return coordinates_scanner
            <
                Point,
                Dimension+1,
                DimensionCount,
                IsConst
            >::apply(point, operation);
    }
};

template <typename Point, int DimensionCount, bool IsConst>
struct coordinates_scanner<Point, DimensionCount, DimensionCount, IsConst>
{
    template <typename Op>
    static inline Op apply(typename add_const_if_c
        <
            IsConst,
            Point
        >::type& , Op operation)
    {
        return operation;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

template <typename Point, typename Op>
inline void for_each_coordinate(Point& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, false
        > scanner;

    scanner::apply(point, operation);
}

template <typename Point, typename Op>
inline Op for_each_coordinate(Point const& point, Op operation)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point>) );

    typedef typename detail::coordinates_scanner
        <
            Point, 0, dimension<Point>::type::value, true
        > scanner;

    return scanner::apply(point, operation);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_FOR_EACH_COORDINATE_HPP

/* for_each_coordinate.hpp
/a9d2PYe/BQ+OkOX8m10pYkTnMJG62tJJcMsMmkVlKEI55rdivcppF3rYIri5HkzEfJLAGQ7GKW2JxiSuHl8hTyeo85IGQuv+SsDW3Tp2ZPImGfjCy3z9g31BaLM8wgBX9wx2YVcAHOdnCkbnABZnv/52z+aliUpCs4RoJLJtgy1mIqBL/YxW/EItE3knecXozHCgXisj811nmfXs20gCD+//lodoOI/TtkXj33nrHdmZFeyXjr6NJI6spJqsjBthd+DK+imu7kMdsi2iiL6u9mA1eE2jtfdlUeKd/8F3f0TyhV/xH1/+T/3/X/u+//c999831/8F993e+Ff0oUfRiAh2J5IdOmfmg+fGlVNrSN8UbN0jViBaltIFzGPc2yhKnfTIi0/2Ea/tzQpYIlYLa+YXcL3nLe3j5E+Lbirc+wX5wwlT8EQBAwjTiEOixOfxX+SJLnpFz6pKEMexuzV/v41YNb6qj1JF/uI5vyfGLWXbP+PL17+6Q/0O3yNctfed8+//e7b5wff/rmIefeHOLlG7fsepz25EVEPeJ4Q9dEvEaY6GQiPQNWXbnHsB+Je4KjPUi32DWjg8yw63ID0cIzflHvN25GcHMS/7CDG7LzagSltFTsH4Q2+f/uK08yA76RTRhdXsP9W4vO5
*/