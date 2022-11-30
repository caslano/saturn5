// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CLOSURE_HPP
#define BOOST_GEOMETRY_CORE_CLOSURE_HPP

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/type_traits_std.hpp>

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
struct minimum_ring_size<geometry::closed>
    : std::integral_constant<std::size_t, 4>
{};

template <>
struct minimum_ring_size<geometry::open>
    : std::integral_constant<std::size_t, 3>
{};


}} // namespace core_detail::closure
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct closure
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry type.",
        Geometry);
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
            typename util::remove_cptrref<Geometry>::type
        >::value;
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Geometry,
    closure_selector Closure = geometry::closure<Geometry>::value
>
using minimum_ring_size = core_detail::closure::minimum_ring_size<Closure>;

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_CLOSURE_HPP

/* closure.hpp
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
*/