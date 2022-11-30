// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP


#include <type_traits>

#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // for backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace clear
{

template <typename Geometry>
struct collection_clear
{
    static inline void apply(Geometry& geometry)
    {
        traits::clear<Geometry>::apply(geometry);
    }
};

template <typename Polygon>
struct polygon_clear
{
    static inline void apply(Polygon& polygon)
    {
        traits::clear
            <
                typename std::remove_reference
                    <
                        typename traits::interior_mutable_type<Polygon>::type
                    >::type
            >::apply(interior_rings(polygon));
        traits::clear
            <
                typename std::remove_reference
                    <
                        typename traits::ring_mutable_type<Polygon>::type
                    >::type
            >::apply(exterior_ring(polygon));
    }
};

template <typename Geometry>
struct no_action
{
    static inline void apply(Geometry& )
    {
    }
};


}} // namespace detail::clear
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag_cast<typename tag<Geometry>::type, multi_tag>::type
>
struct clear: not_implemented<Tag>
{};

// Point/box/segment do not have clear. So specialize to do nothing.
template <typename Geometry>
struct clear<Geometry, point_tag>
    : detail::clear::no_action<Geometry>
{};

template <typename Geometry>
struct clear<Geometry, box_tag>
    : detail::clear::no_action<Geometry>
{};

template <typename Geometry>
struct clear<Geometry, segment_tag>
    : detail::clear::no_action<Geometry>
{};

template <typename Geometry>
struct clear<Geometry, linestring_tag>
    : detail::clear::collection_clear<Geometry>
{};

template <typename Geometry>
struct clear<Geometry, ring_tag>
    : detail::clear::collection_clear<Geometry>
{};


// Polygon can (indirectly) use std for clear
template <typename Polygon>
struct clear<Polygon, polygon_tag>
    : detail::clear::polygon_clear<Polygon>
{};


template <typename Geometry>
struct clear<Geometry, multi_tag>
    : detail::clear::collection_clear<Geometry>
{};


template <typename Geometry>
struct clear<Geometry, dynamic_geometry_tag>
{
    static void apply(Geometry& geometry)
    {
        traits::visit<Geometry>::apply([](auto & g)
        {
            clear<std::remove_reference_t<decltype(g)>>::apply(g);
        }, geometry);
    }
};


template <typename Geometry>
struct clear<Geometry, geometry_collection_tag>
{
    static void apply(Geometry& geometry)
    {
        traits::clear<Geometry>::apply(geometry);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Clears a linestring, ring or polygon (exterior+interiors) or multi*
\details Generic function to clear a geometry. All points will be removed from the collection or collections
    making up the geometry. In most cases this is equivalent to the .clear() method of a std::vector<...>. In
    the case of a polygon, this clear functionality is automatically called for the exterior ring, and for the
    interior ring collection. In the case of a point, boxes and segments, nothing will happen.
\ingroup clear
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be cleared
\note points and boxes cannot be cleared, instead they can be set to zero by "assign_zero"

\qbk{[include reference/algorithms/clear.qbk]}
*/
template <typename Geometry>
inline void clear(Geometry& geometry)
{
    concepts::check<Geometry>();

    dispatch::clear<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP

/* clear.hpp
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
*/