// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.Dimension. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP


#include <cstddef>

#include <boost/range.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_on_border
{


struct get_point
{
    template <typename Point>
    static inline bool apply(Point& destination, Point const& source)
    {
        destination = source;
        return true;
    }
};


struct point_on_range
{
    // Version with iterator
    template<typename Point, typename Iterator>
    static inline bool apply(Point& point, Iterator begin, Iterator end)
    {
        if (begin == end)
        {
            return false;
        }

        geometry::detail::conversion::convert_point_to_point(*begin, point);
        return true;
    }

    // Version with range
    template<typename Point, typename Range>
    static inline bool apply(Point& point, Range const& range)
    {
        return apply(point, boost::begin(range), boost::end(range));
    }
};


struct point_on_polygon
{
    template<typename Point, typename Polygon>
    static inline bool apply(Point& point, Polygon const& polygon)
    {
        return point_on_range::apply(point, exterior_ring(polygon));
    }
};


struct point_on_box
{
    template<typename Point, typename Box>
    static inline bool apply(Point& point, Box const& box)
    {
        detail::assign::assign_box_2d_corner<min_corner, min_corner>(box, point);
        return true;
    }
};


template <typename Policy>
struct point_on_multi
{
    template<typename Point, typename MultiGeometry>
    static inline bool apply(Point& point, MultiGeometry const& multi)
    {
        // Take a point on the first multi-geometry
        // (i.e. the first that is not empty)
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            if (Policy::apply(point, *it))
            {
                return true;
            }
        }
        return false;
    }
};


}} // namespace detail::point_on_border
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag>
struct point_on_border
{};

template <>
struct point_on_border<point_tag>
    : detail::point_on_border::get_point
{};

template <>
struct point_on_border<linestring_tag>
    : detail::point_on_border::point_on_range
{};

template <>
struct point_on_border<ring_tag>
    : detail::point_on_border::point_on_range
{};

template <>
struct point_on_border<polygon_tag>
    : detail::point_on_border::point_on_polygon
{};

template <>
struct point_on_border<box_tag>
    : detail::point_on_border::point_on_box
{};


template <>
struct point_on_border<multi_polygon_tag>
    : detail::point_on_border::point_on_multi
        <
            detail::point_on_border::point_on_polygon
        >
{};


template <>
struct point_on_border<multi_linestring_tag>
    : detail::point_on_border::point_on_multi
        <
            detail::point_on_border::point_on_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Take point on a border
\ingroup overlay
\tparam Geometry geometry type. This also defines the type of the output point
\param point to assign
\param geometry geometry to take point from
\return TRUE if successful, else false.
    It is only false if polygon/line have no points
\note for a polygon, it is always a point on the exterior ring
 */
template <typename Point, typename Geometry>
inline bool point_on_border(Point& point, Geometry const& geometry)
{
    concepts::check<Point>();
    concepts::check<Geometry const>();

    return dispatch::point_on_border
            <
                typename tag<Geometry>::type
            >::apply(point, geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP

/* point_on_border.hpp
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
*/