// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_RING_TYPE_HPP
#define BOOST_GEOMETRY_CORE_RING_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{


/*!
\brief Traits class to indicate ring-type  of a polygon's exterior ring/interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef XXX type ( e.g. ring<P> )
\tparam Geometry geometry
*/
template <typename Geometry>
struct ring_const_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Geometry>
struct ring_mutable_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag, typename Geometry>
struct ring_return_type
{};


template <typename LineString>
struct ring_return_type<linestring_tag, LineString>
{
    typedef LineString& type;
};


template <typename Ring>
struct ring_return_type<ring_tag, Ring>
{
    typedef Ring& type;
};


template <typename Polygon>
struct ring_return_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_const<Polygon>::type nc_polygon_type;

    typedef typename boost::mpl::if_
        <
            boost::is_const<Polygon>,
            typename traits::ring_const_type<nc_polygon_type>::type,
            typename traits::ring_mutable_type<nc_polygon_type>::type
        >::type type;
};


template <typename MultiLinestring>
struct ring_return_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename ring_return_type
        <
            linestring_tag,
            typename boost::mpl::if_
                <
                    boost::is_const<MultiLinestring>,
                    typename boost::range_value<MultiLinestring>::type const,
                    typename boost::range_value<MultiLinestring>::type
                >::type
        >::type type;
};


template <typename MultiPolygon>
struct ring_return_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename ring_return_type
        <
            polygon_tag,
            typename boost::mpl::if_
                <
                    boost::is_const<MultiPolygon>,
                    typename boost::range_value<MultiPolygon>::type const,
                    typename boost::range_value<MultiPolygon>::type
                >::type
        >::type type;
};


template <typename GeometryTag, typename Geometry>
struct ring_type
{};


template <typename Ring>
struct ring_type<ring_tag, Ring>
{
    typedef Ring type;
};


template <typename Polygon>
struct ring_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<polygon_tag, Polygon>::type
        >::type type;
};


template <typename MultiLinestring>
struct ring_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<multi_linestring_tag, MultiLinestring>::type
        >::type type;
};


template <typename MultiPolygon>
struct ring_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename boost::remove_reference
        <
            typename ring_return_type<multi_polygon_tag, MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, ring_type, \meta_geometry_type}
\details A polygon contains one exterior ring
    and zero or more interior rings (holes).
    This metafunction retrieves the type of the rings.
    Exterior ring and each of the interior rings all have the same ring_type.
\tparam Geometry A type fullfilling the Ring, Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/ring_type.qbk]}
*/
template <typename Geometry>
struct ring_type
{
    typedef typename core_dispatch::ring_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


template <typename Geometry>
struct ring_return_type
{
    typedef typename core_dispatch::ring_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_RING_TYPE_HPP

/* ring_type.hpp
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
*/