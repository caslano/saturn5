// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.Dimension. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP


#include <cstddef>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
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