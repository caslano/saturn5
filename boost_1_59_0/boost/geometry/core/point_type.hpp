// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_TYPE_HPP
#define BOOST_GEOMETRY_CORE_POINT_TYPE_HPP


#include <boost/range/value_type.hpp>

#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating the type of contained points
\ingroup traits
\par Geometries:
    - all geometries except point
\par Specializations should provide:
    - typedef P type (where P should fulfil the Point concept)
\tparam Geometry geometry
*/
template <typename Geometry>
struct point_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_type
{
    // Default: call traits to get point type
    typedef typename std::remove_const
        <
            typename traits::point_type<Geometry>::type
        >::type type;
};


// Specialization for point: the point itself
template <typename Point>
struct point_type<point_tag, Point>
{
    typedef Point type;
};


// Specializations for linestring/ring, via boost::range
template <typename Linestring>
struct point_type<linestring_tag, Linestring>
{
    typedef typename boost::range_value<Linestring>::type type;
};


template <typename Ring>
struct point_type<ring_tag, Ring>
{
    typedef typename boost::range_value<Ring>::type type;
};


// Specialization for polygon: the point-type is the point-type of its rings
template <typename Polygon>
struct point_type<polygon_tag, Polygon>
{
    typedef typename point_type
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::type type;
};


template <typename MultiPoint>
struct point_type<multi_point_tag, MultiPoint>
{
    typedef typename boost::range_value
        <
            MultiPoint
        >::type type;
};


template <typename MultiLinestring>
struct point_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename point_type
        <
            linestring_tag,
            typename boost::range_value<MultiLinestring>::type
        >::type type;
};


template <typename MultiPolygon>
struct point_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename point_type
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::type type;
};


template <typename DynamicGeometry>
struct point_type<dynamic_geometry_tag, DynamicGeometry>
{
    using geometry_t = typename util::sequence_front
        <
            typename traits::geometry_types<DynamicGeometry>::type
        >::type;
    using type = typename point_type
        <
            typename tag<geometry_t>::type,
            typename util::remove_cptrref<geometry_t>::type
        >::type;
};


template <typename GeometryCollection>
struct point_type<geometry_collection_tag, GeometryCollection>
{
    using geometry_t = typename util::sequence_front
        <
            typename traits::geometry_types<GeometryCollection>::type
        >::type;
    using type = typename point_type
        <
            typename tag<geometry_t>::type,
            typename util::remove_cptrref<geometry_t>::type
        >::type;
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{type, point_type, \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/point_type.qbk]}
*/
template <typename Geometry>
struct point_type
{
    typedef typename core_dispatch::point_type
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_POINT_TYPE_HPP

/* point_type.hpp
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
*/