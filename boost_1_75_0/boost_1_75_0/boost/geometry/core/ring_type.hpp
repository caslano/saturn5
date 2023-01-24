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
dXvWsQuRUPS7WOJdx0bCw0o7Eaxjx7qfdpMftY5N6LgjWMdG3LOO7RGbX8e+QX/XEGBrVim8uiCfBOTnE5I3lgSMHUcCgieSgNhYLkUWVl7pThK4s4AE7iggsCUhACraAyTEetaxaR8bSe7sdezW8P9vODbv1agFUQ/QfUxDb0fZG1/oCrWzhsBPLQOW3fWrV3pCjf1VqJ03Ampnvygpw4C08RAz7GXoP2QE9ElMg15xKfDEcy/A4/0GQ7c+A8HWKx7MT8ZAZM9n4ZHH+sP/uj0DD9v6wH8svUFvfgq0xidBG9kT1F17gPqRx2BgdDRcnfk81K6bCzUr34LaJTlQmz8aaj8Y1qwML+a8BaM/2wN9538GsXsvwj8Lj8D9Cw/BffkH4S9zD8CfPqqAez/YC7+fXQod3t0F97y1A9rN2AK/nb4R7p7mgLsnfw53T/wU7n5tFWgmLwaY9xLUlK2F2u3LoNaxgNtDVzQFahaOhdqPUpvIkDRuKvTdfBaemZEPL5Z+D4MqLsHzzovw9O6L0GP7BTBvuQD/2XgBVOvPQ/ja8/DPNefgryvPwh9LzkKH4jPw26U/QNDH38Ov7d8BlGA5h3ZAzcGtUFO+Hpb3i4D3H/snJ8PyaVBbMB5q8tKZDN7yX54IMbsuwrCSLTBk2WZIP3QZXjhwCQbsvQTRpRfhKYzrhnJEbq4C/RdV8O9156HzZ+fh76vPwl9W
*/