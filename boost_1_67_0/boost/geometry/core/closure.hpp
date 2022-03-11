// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CLOSURE_HPP
#define BOOST_GEOMETRY_CORE_CLOSURE_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{


/*!
\brief Enumerates options for defining if polygons are open or closed
\ingroup enum
\details The enumeration closure_selector describes options for if a polygon is
    open or closed. In a closed polygon the very first point (per ring) should
    be equal to the very last point.
    The specific closing property of a polygon type is defined by the closure
    metafunction. The closure metafunction defines a value, which is one of the
    values enumerated in the closure_selector

\qbk{
[heading See also]
[link geometry.reference.core.closure The closure metafunction]
}
*/
enum closure_selector
{
    /// Rings are open: first point and last point are different, algorithms
    /// close them explicitly on the fly
    open = 0,
    /// Rings are closed: first point and last point must be the same
    closed = 1,
    /// (Not yet implemented): algorithms first figure out if ring must be
    /// closed on the fly
    closure_undertermined = -1
};

namespace traits
{

/*!
    \brief Traits class indicating if points within a
        ring or (multi)polygon are closed (last point == first point),
        open or not known.
    \ingroup traits
    \par Geometries:
        - ring
    \tparam G geometry
*/
template <typename G>
struct closure
{
    static const closure_selector value = closed;
};


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace core_detail { namespace closure
{

struct closed
{
    static const closure_selector value = geometry::closed;
};


/// Metafunction to define the minimum size of a ring:
/// 3 for open rings, 4 for closed rings
template <closure_selector Closure>
struct minimum_ring_size {};

template <>
struct minimum_ring_size<geometry::closed> : boost::mpl::size_t<4> {};

template <>
struct minimum_ring_size<geometry::open> : boost::mpl::size_t<3> {};


}} // namespace detail::point_order
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct closure
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Box>
struct closure<point_tag, Box> : public core_detail::closure::closed {};

template <typename Box>
struct closure<box_tag, Box> : public core_detail::closure::closed {};

template <typename Box>
struct closure<segment_tag, Box> : public core_detail::closure::closed {};

template <typename LineString>
struct closure<linestring_tag, LineString>
    : public core_detail::closure::closed {};


template <typename Ring>
struct closure<ring_tag, Ring>
{
    static const closure_selector value
        = geometry::traits::closure<Ring>::value;
};

// Specialization for Polygon: the closure is the closure of its rings
template <typename Polygon>
struct closure<polygon_tag, Polygon>
{
    static const closure_selector value = core_dispatch::closure
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};

template <typename MultiPoint>
struct closure<multi_point_tag, MultiPoint>
    : public core_detail::closure::closed {};

template <typename MultiLinestring>
struct closure<multi_linestring_tag, MultiLinestring>
    : public core_detail::closure::closed {};

// Specialization for MultiPolygon: the closure is the closure of Polygon's rings
template <typename MultiPolygon>
struct closure<multi_polygon_tag, MultiPolygon>
{
    static const closure_selector value = core_dispatch::closure
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::value ;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{value, closure (clockwise\, counterclockwise),
    \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/closure.qbk]}
*/
template <typename Geometry>
struct closure
{
    static const closure_selector value = core_dispatch::closure
        <
            typename tag<Geometry>::type,
            typename util::bare_type<Geometry>::type
        >::value;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_CLOSURE_HPP

/* closure.hpp
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
*/