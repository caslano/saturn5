// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_ORDER_HPP
#define BOOST_GEOMETRY_CORE_POINT_ORDER_HPP


#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/type_traits_std.hpp>

namespace boost { namespace geometry
{

/*!
\brief Enumerates options for the order of points within polygons
\ingroup enum
\details The enumeration order_selector describes options for the order of
    points within a polygon. Polygons can be ordered either clockwise or
    counterclockwise. The specific order of a polygon type is defined by the
    point_order metafunction. The point_order metafunction defines a value,
    which is one of the values enumerated in the order_selector

\qbk{
[heading See also]
[link geometry.reference.core.point_order The point_order metafunction]
}
*/
enum order_selector
{
    /// Points are ordered clockwise
    clockwise = 1,
    /// Points are ordered counter clockwise
    counterclockwise = 2,
    /// Points might be stored in any order, algorithms will determine it on the
    /// fly (not yet supported)
    order_undetermined = 0
};

namespace traits
{

/*!
\brief Traits class indicating the order of contained points within a
    ring or (multi)polygon, clockwise, counter clockwise or not known.
\ingroup traits
\tparam Ring ring
*/
template <typename Ring>
struct point_order
{
    static const order_selector value = clockwise;
};


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_order
{

struct clockwise
{
    static const order_selector value = geometry::clockwise;
};


}} // namespace detail::point_order
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_order
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};

template <typename Point>
struct point_order<point_tag, Point>
    : public detail::point_order::clockwise {};

template <typename Segment>
struct point_order<segment_tag, Segment>
    : public detail::point_order::clockwise {};


template <typename Box>
struct point_order<box_tag, Box>
    : public detail::point_order::clockwise {};

template <typename LineString>
struct point_order<linestring_tag, LineString>
    : public detail::point_order::clockwise {};


template <typename Ring>
struct point_order<ring_tag, Ring>
{
    static const order_selector value
        = geometry::traits::point_order<Ring>::value;
};

// Specialization for polygon: the order is the order of its rings
template <typename Polygon>
struct point_order<polygon_tag, Polygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};

template <typename MultiPoint>
struct point_order<multi_point_tag, MultiPoint>
    : public detail::point_order::clockwise {};

template <typename MultiLinestring>
struct point_order<multi_linestring_tag, MultiLinestring>
    : public detail::point_order::clockwise {};


// Specialization for multi_polygon: the order is the order of its polygons
template <typename MultiPolygon>
struct point_order<multi_polygon_tag, MultiPolygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::value ;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{value, point order (clockwise\, counterclockwise),
    \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/point_order.qbk]}
*/
template <typename Geometry>
struct point_order
{
    static const order_selector value = core_dispatch::point_order
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type
        >::value;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_POINT_ORDER_HPP

/* point_order.hpp
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
*/