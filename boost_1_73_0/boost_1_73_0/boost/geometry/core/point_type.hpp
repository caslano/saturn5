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
70/w+xx+X8Dvz/D7y5frDSizAWU2oMwGlNmAMhvPUU8jY5vM607nt/cnVpsgYx+V9zgYoq0KqHRQx2qoRft5OctJLXXWcz8ZhTHprvwRoIeDLJQenn5wBoXRUbFCet95mHcuh1kHGyRoqpeEmbq6CHJQqIAa30LyqUE5cowB8AFZLsZThhW1DrkH2lQ/ugZthtBvwj9xTyVjrikrtY/21Nkg6X4jD17Q++c4y5cFlGAwUAm6xgAIeTABA+oWVgaFL0q17zOKyW3YDVLWsSEbxiuHIhnCU+8TGLsR/EGFNLzOtRflKoIGQIPMYNwH7EZk00bnD6Jvofo+iM5UkHYvosuQXaJQbGd3Zfe3XQUMc+55Y7QnL1Anp8ft1nvUBVGlBSpidwxZKEV3dGVO2Gy/DbNjoOwetH5CNptjuifEApNsQ2nCdZA91BNiErA3G3NouLGRQdbn55/Xfln/ujWnpMXYTcZxjmmg1KNuS0Dw+97+QRsdp4AWMKtimm8zc2nW3Dv60D7soLfntP2P08YWzjngZJq9KuovcpVthbZRg3rByrNaJYjUNIBcxeZM0/B9Db9fXUDlRZv6Sq02yBD1SvbJwja29Rqb10lfpzSahHRji6oBPrbmPDTamDMURCyebnudv8UOdwdJFi5q
*/