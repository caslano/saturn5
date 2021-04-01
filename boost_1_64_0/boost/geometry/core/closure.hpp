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
Q6gIKT9HyT7m7C9R79xlviob90O97rYbu4e4TdV3o2bXkmy83qVl7v1tLIDw4ksZoUYaxvLSGrTDAin/WSiZC14qWZblZEhP3XUti4Zs8gfeMWvWL1FgwO37sR/2gE2Pp43lEPjhB81uFLwfN5/K+Tzkv9PIdyJnnSGCVaP3jG4FfszMF5qpdetwkvsK2CickK2HBFD+jCOIiMaI3c9dj0eRIgX7d5mceMlvX56J7TDesj9zgaJLA6TSHVZlxYD8dO0+iovDN/9RZft8JudV5x7Okd2l9u4pW1QW6Y3fTFHXyHw0VLEqBfZ7BjCx6apna3CBPKucEay0LlCTT+aS9i6VWhafqlI3GJps4t9YA28o2FelEsrgyozE0/cs6DUvef/3Wbr/74XOV1Lq0guJFaW8rL3mWGq4TGiLqd5HUYsI78PTzb1IoOOH6aZRZzrIp3N6lphpSQymiOmBHVIuYrhlmXvuhLTWwHpXfHelSr1BFbz8JcGEeEzY7Jb+1WRjI9HUZZ/Pwarg1tV5Asz1vRDUZRabEOWMuu2kOKF2lvEfRAzukFQCbsY42w==
*/