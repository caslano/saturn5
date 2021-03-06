// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP


#include <cstddef>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Assign a box or segment with the value of a point
\ingroup assign
\tparam Index indicates which box-corner, min_corner (0) or max_corner (1)
    or which point of segment (0/1)
\tparam Point \tparam_point
\tparam Geometry \tparam_box_or_segment
\param point \param_point
\param geometry \param_box_or_segment

\qbk{
[heading Example]
[assign_point_to_index] [assign_point_to_index_output]
}
*/
template <std::size_t Index, typename Geometry, typename Point>
inline void assign_point_to_index(Point const& point, Geometry& geometry)
{
    concepts::check<Point const>();
    concepts::check<Geometry>();

    detail::assign::assign_point_to_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(point, geometry);
}


/*!
\brief Assign a point with a point of a box or segment
\ingroup assign
\tparam Index indicates which box-corner, min_corner (0) or max_corner (1)
    or which point of segment (0/1)
\tparam Geometry \tparam_box_or_segment
\tparam Point \tparam_point
\param geometry \param_box_or_segment
\param point \param_point

\qbk{
[heading Example]
[assign_point_from_index] [assign_point_from_index_output]
}
*/
template <std::size_t Index, typename Point, typename Geometry>
inline void assign_point_from_index(Geometry const& geometry, Point& point)
{
    concepts::check<Geometry const>();
    concepts::check<Point>();

    detail::assign::assign_point_from_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(geometry, point);
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP

/* assign_indexed_point.hpp
QIayu0Uhdm1H0jo26fzMBO5VIue6iQqXEDmjJ2SnmkjqKSNftFLaCuXHdNmCohaobkIOWP/hPjZNtDJcO+4mgzIiYTPqSSWUklnMYs8nfAOHxcDlYo47d6LPgsAgHh7chcpMjVwn5cxlBe7imp/KHLpgF0iFbi1RwHHxhRt2dgz8OzXSw7n6PKAjL/LeOx9SxaBoR+6WK9y3bb+RphXeKDidxBBSq3Dms8B8EyskuqEGgOZzBIn7GTDg6TtjR8uQRbunf1A8dIGjuTHGrvf8PqojILlznk8mvrOP21zLhhXFNi2YbRiTtg9p/5jXWPER1FuKropI1rtoaPtRbnn1JEAgAGwvVwGl8mh+zFaQLKKNKi+8cjsJOt5PbbUhuqAltO+Te5dd//wYjxQ9/UgP0CS9HH69Hyisb69NPJnzVOZdS3j3T3AYMpLD1T3DJy4b3KMwQsQpTL8hli39vniQf/k6B1syI5xwKKbOQWZBExryoU3oQxdJf/FNnmA6TYCHPz6loIibQYiLJAM3aBApCUg41BJ2CLGeTKH75qJJYxT7xItBZBmwCPoZZg==
*/