// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_IMPLEMENTATION_HPP

#include <cstddef>
#include <deque>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <boost/geometry/algorithms/detail/overlay/do_reverse.hpp>
#include <boost/geometry/algorithms/detail/within/interface.hpp>
#include <boost/geometry/algorithms/detail/within/multi_point.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/order_as_direction.hpp>

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
        return strategy.within(point, box).apply(point, box);
    }
};

template <typename Box1, typename Box2>
struct within<Box1, Box2, box_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const& strategy)
    {
        assert_dimension_equal<Box1, Box2>();
        return strategy.within(box1, box2).apply(box1, box2);
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