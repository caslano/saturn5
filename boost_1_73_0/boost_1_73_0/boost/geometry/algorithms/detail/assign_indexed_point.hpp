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
DJrxT1PZx3g2SwAcaDUl8SXlYgA0HBrUgK3Bwmn5HEvcz2KbAnhLmlnLcyh8jbJhw+Mc+o6zYTs2inpe4RLB1PCty7gyhVWF4T/kEZRwTTutkTZ5JtvkguIlKqYyon4ezsq7RkeD49dnJTRN3LxjtNY9df1QxEi9HpF3TFWnYcQJGe7qggXrAvmu+pVCT8sNzQ7c/3cAX9amcPFaTCWczydIQoFz+8FPeIEJp1gXwI38yjMsUxuL1odUbMWOg4kvj2MGKc7alGfYr4jFk4mDh1ST/EWAdETDIVXWuB0/tLTw7w4lCgqKmrrLxjFHFjaj2yhJW67cvgjNnAENwnmHJYindjqPcWZobNe21t4NgV413t8dzKpao7sxJ+rpbEsU0znc0sHqUATJf64a3LQhxR9FReYmVrHxdEVWREDbyXwZjwbsKLQW3o2LXt/UOhN91QODB/afemC0xnYIKiDyBvoGGq6ggKct+qcTsSYsxcv035SAVJdHTVLR0fOrGPlqTG0fxnXwdf3ad+ZJ/rWgWov9PryCeRot+XP4suX5ZOuyL4Y4HsLuf1IWxYV8UtN7uQ5MiQV8xJyXy/mmUqakjmJsb36VH80MXeIMbD9ilTw7fahJHKW50fXiWoELo90wnvPnmNtdj8QVF1wK
*/