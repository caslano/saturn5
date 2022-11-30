// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP

#include <type_traits>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating interior container type of a polygon
\details defines inner container type, so the container containing
        the interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef X type ( e.g. std::vector&lt;myring&lt;P&gt;&gt; )
\tparam Geometry geometry
*/
template <typename Geometry>
struct interior_const_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};

template <typename Geometry>
struct interior_mutable_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


} // namespace traits




#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename GeometryTag, typename Geometry>
struct interior_return_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


template <typename Polygon>
struct interior_return_type<polygon_tag, Polygon>
{
    typedef typename std::remove_const<Polygon>::type nc_polygon_type;

    typedef std::conditional_t
        <
            std::is_const<Polygon>::value,
            typename traits::interior_const_type<nc_polygon_type>::type,
            typename traits::interior_mutable_type<nc_polygon_type>::type
        > type;
};




template <typename GeometryTag, typename Geometry>
struct interior_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
};


template <typename Polygon>
struct interior_type<polygon_tag, Polygon>
{
    typedef typename std::remove_reference
        <
            typename interior_return_type<polygon_tag, Polygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, interior_type (container type
    of inner rings), \meta_geometry_type}
\details Interior rings should be organized as a container
    (std::vector, std::deque, boost::array) with
    Boost.Range support. This metafunction defines the type
    of the container.
\tparam Geometry A type fullfilling the Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/interior_type.qbk]}
*/
template <typename Geometry>
struct interior_type
{
    typedef typename core_dispatch::interior_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};

template <typename Geometry>
struct interior_return_type
{
    typedef typename core_dispatch::interior_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP

/* interior_type.hpp
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
*/