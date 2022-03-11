// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_TYPE_HPP
#define BOOST_GEOMETRY_CORE_POINT_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Geometry>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_type
{
    // Default: call traits to get point type
    typedef typename boost::remove_const
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
            typename boost::geometry::util::bare_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_POINT_TYPE_HPP

/* point_type.hpp
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
*/