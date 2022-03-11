// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013, 2014, 2017, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_IMPLEMENTATION_HPP

#include <cstddef>

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/within/interface.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/order_as_direction.hpp>

#include <boost/geometry/algorithms/detail/within/multi_point.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <deque>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within {

struct use_point_in_geometry
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        return detail::within::within_point_geometry(geometry1, geometry2, strategy);
    }
};

struct use_relate
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        typedef typename detail::de9im::static_mask_within_type
            <
                Geometry1, Geometry2
            >::type within_mask;
        return geometry::relate(geometry1, geometry2, within_mask(), strategy);
    }
};

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Point, typename Box>
struct within<Point, Box, point_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        return strategy.apply(point, box);
    }
};

template <typename Box1, typename Box2>
struct within<Box1, Box2, box_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        assert_dimension_equal<Box1, Box2>();
        boost::ignore_unused(strategy);
        return strategy.apply(box1, box2);
    }
};

// P/P

template <typename Point1, typename Point2>
struct within<Point1, Point2, point_tag, point_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename Point, typename MultiPoint>
struct within<Point, MultiPoint, point_tag, multi_point_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename MultiPoint, typename Point>
struct within<MultiPoint, Point, multi_point_tag, point_tag>
    : public detail::within::multi_point_point
{};

template <typename MultiPoint1, typename MultiPoint2>
struct within<MultiPoint1, MultiPoint2, multi_point_tag, multi_point_tag>
    : public detail::within::multi_point_multi_point
{};

// P/L

template <typename Point, typename Segment>
struct within<Point, Segment, point_tag, segment_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename Point, typename Linestring>
struct within<Point, Linestring, point_tag, linestring_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename Point, typename MultiLinestring>
struct within<Point, MultiLinestring, point_tag, multi_linestring_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename MultiPoint, typename Segment>
struct within<MultiPoint, Segment, multi_point_tag, segment_tag>
    : public detail::within::multi_point_single_geometry<true>
{};

template <typename MultiPoint, typename Linestring>
struct within<MultiPoint, Linestring, multi_point_tag, linestring_tag>
    : public detail::within::multi_point_single_geometry<true>
{};

template <typename MultiPoint, typename MultiLinestring>
struct within<MultiPoint, MultiLinestring, multi_point_tag, multi_linestring_tag>
    : public detail::within::multi_point_multi_geometry<true>
{};

// P/A

template <typename Point, typename Ring>
struct within<Point, Ring, point_tag, ring_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename Point, typename Polygon>
struct within<Point, Polygon, point_tag, polygon_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename Point, typename MultiPolygon>
struct within<Point, MultiPolygon, point_tag, multi_polygon_tag>
    : public detail::within::use_point_in_geometry
{};

template <typename MultiPoint, typename Ring>
struct within<MultiPoint, Ring, multi_point_tag, ring_tag>
    : public detail::within::multi_point_single_geometry<true>
{};

template <typename MultiPoint, typename Polygon>
struct within<MultiPoint, Polygon, multi_point_tag, polygon_tag>
    : public detail::within::multi_point_single_geometry<true>
{};

template <typename MultiPoint, typename MultiPolygon>
struct within<MultiPoint, MultiPolygon, multi_point_tag, multi_polygon_tag>
    : public detail::within::multi_point_multi_geometry<true>
{};

// L/L

template <typename Linestring1, typename Linestring2>
struct within<Linestring1, Linestring2, linestring_tag, linestring_tag>
    : public detail::within::use_relate
{};

template <typename Linestring, typename MultiLinestring>
struct within<Linestring, MultiLinestring, linestring_tag, multi_linestring_tag>
    : public detail::within::use_relate
{};

template <typename MultiLinestring, typename Linestring>
struct within<MultiLinestring, Linestring, multi_linestring_tag, linestring_tag>
    : public detail::within::use_relate
{};

template <typename MultiLinestring1, typename MultiLinestring2>
struct within<MultiLinestring1, MultiLinestring2, multi_linestring_tag, multi_linestring_tag>
    : public detail::within::use_relate
{};

// L/A

template <typename Linestring, typename Ring>
struct within<Linestring, Ring, linestring_tag, ring_tag>
    : public detail::within::use_relate
{};

template <typename MultiLinestring, typename Ring>
struct within<MultiLinestring, Ring, multi_linestring_tag, ring_tag>
    : public detail::within::use_relate
{};

template <typename Linestring, typename Polygon>
struct within<Linestring, Polygon, linestring_tag, polygon_tag>
    : public detail::within::use_relate
{};

template <typename MultiLinestring, typename Polygon>
struct within<MultiLinestring, Polygon, multi_linestring_tag, polygon_tag>
    : public detail::within::use_relate
{};

template <typename Linestring, typename MultiPolygon>
struct within<Linestring, MultiPolygon, linestring_tag, multi_polygon_tag>
    : public detail::within::use_relate
{};

template <typename MultiLinestring, typename MultiPolygon>
struct within<MultiLinestring, MultiPolygon, multi_linestring_tag, multi_polygon_tag>
    : public detail::within::use_relate
{};

// A/A

template <typename Ring1, typename Ring2>
struct within<Ring1, Ring2, ring_tag, ring_tag>
    : public detail::within::use_relate
{};

template <typename Ring, typename Polygon>
struct within<Ring, Polygon, ring_tag, polygon_tag>
    : public detail::within::use_relate
{};

template <typename Polygon, typename Ring>
struct within<Polygon, Ring, polygon_tag, ring_tag>
    : public detail::within::use_relate
{};

template <typename Polygon1, typename Polygon2>
struct within<Polygon1, Polygon2, polygon_tag, polygon_tag>
    : public detail::within::use_relate
{};

template <typename Ring, typename MultiPolygon>
struct within<Ring, MultiPolygon, ring_tag, multi_polygon_tag>
    : public detail::within::use_relate
{};

template <typename MultiPolygon, typename Ring>
struct within<MultiPolygon, Ring, multi_polygon_tag, ring_tag>
    : public detail::within::use_relate
{};

template <typename Polygon, typename MultiPolygon>
struct within<Polygon, MultiPolygon, polygon_tag, multi_polygon_tag>
    : public detail::within::use_relate
{};

template <typename MultiPolygon, typename Polygon>
struct within<MultiPolygon, Polygon, multi_polygon_tag, polygon_tag>
    : public detail::within::use_relate
{};

template <typename MultiPolygon1, typename MultiPolygon2>
struct within<MultiPolygon1, MultiPolygon2, multi_polygon_tag, multi_polygon_tag>
    : public detail::within::use_relate
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#include <boost/geometry/index/rtree.hpp>

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/