// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP


#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/algorithm.hpp>


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

    detail::for_each_dimension<Geometry>([&](auto dimension)
    {
        geometry::set<Index, dimension>(geometry,
            boost::numeric_cast
                <
                    typename coordinate_type<Geometry>::type
                >(geometry::get<dimension>(point)));
    });
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

    detail::for_each_dimension<Geometry>([&](auto dimension)
    {
        geometry::set<dimension>(point,
            boost::numeric_cast
                <
                    typename coordinate_type<Point>::type
                >(geometry::get<Index, dimension>(geometry)));
    });
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP

/* assign_indexed_point.hpp
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
*/