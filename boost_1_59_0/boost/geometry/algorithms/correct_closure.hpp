// Boost.Geometry

// Copyright (c) 2017 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CORRECT_CLOSURE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CORRECT_CLOSURE_HPP

#include <cstddef>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/algorithms/disjoint.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace correct_closure
{

struct nop
{
    template <typename Geometry>
    static inline void apply(Geometry& )
    {}
};

// Close a ring, if not closed, or open it
struct close_or_open_ring
{
    template <typename Ring>
    static inline void apply(Ring& r)
    {
        auto size = boost::size(r);
        if (size <= 2)
        {
            return;
        }

        // TODO: This requires relate(pt, pt) strategy
        bool const disjoint = geometry::disjoint(*boost::begin(r), *(boost::end(r) - 1));
        closure_selector const closure = geometry::closure<Ring>::value;

        if (disjoint && closure == closed)
        {
            // Close it by adding first point
            geometry::append(r, *boost::begin(r));
        }
        else if (! disjoint && closure == open)
        {
            // Open it by removing last point
            range::resize(r, size - 1);
        }
    }
};

// Close/open exterior ring and all its interior rings
struct close_or_open_polygon
{
    template <typename Polygon>
    static inline void apply(Polygon& poly)
    {
        close_or_open_ring::apply(exterior_ring(poly));

        auto&& rings = interior_rings(poly);
        auto const end = boost::end(rings);
        for (auto it = boost::begin(rings); it != end; ++it)
        {
            close_or_open_ring::apply(*it);
        }
    }
};

}} // namespace detail::correct_closure
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct correct_closure: not_implemented<Tag>
{};

template <typename Point>
struct correct_closure<Point, point_tag>
    : detail::correct_closure::nop
{};

template <typename LineString>
struct correct_closure<LineString, linestring_tag>
    : detail::correct_closure::nop
{};

template <typename Segment>
struct correct_closure<Segment, segment_tag>
    : detail::correct_closure::nop
{};


template <typename Box>
struct correct_closure<Box, box_tag>
    : detail::correct_closure::nop
{};

template <typename Ring>
struct correct_closure<Ring, ring_tag>
    : detail::correct_closure::close_or_open_ring
{};

template <typename Polygon>
struct correct_closure<Polygon, polygon_tag>
    : detail::correct_closure::close_or_open_polygon
{};


template <typename MultiPoint>
struct correct_closure<MultiPoint, multi_point_tag>
    : detail::correct_closure::nop
{};


template <typename MultiLineString>
struct correct_closure<MultiLineString, multi_linestring_tag>
    : detail::correct_closure::nop
{};


template <typename Geometry>
struct correct_closure<Geometry, multi_polygon_tag>
    : detail::multi_modify
        <
            detail::correct_closure::close_or_open_polygon
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct correct_closure
{
    static inline void apply(Geometry& geometry)
    {
        concepts::check<Geometry const>();
        dispatch::correct_closure<Geometry>::apply(geometry);
    }
};

template <typename Geometry>
struct correct_closure<Geometry, dynamic_geometry_tag>
{
    static void apply(Geometry& geometry)
    {
        traits::visit<Geometry>::apply([](auto & g)
        {
            correct_closure<util::remove_cref_t<decltype(g)>>::apply(g);
        }, geometry);
    }
};

template <typename Geometry>
struct correct_closure<Geometry, geometry_collection_tag>
{
    static void apply(Geometry& geometry)
    {
        detail::visit_breadth_first([](auto & g)
        {
            correct_closure<util::remove_cref_t<decltype(g)>>::apply(g);
            return true;
        }, geometry);
    }
};

} // namespace resolve_variant


// TODO: This algorithm should use relate(pt, pt) strategy


/*!
\brief Closes or opens a geometry, according to its type
\details Corrects a geometry w.r.t. closure points to all rings which do not
    have a closing point and are typed as they should have one, the first point
    is appended.
\ingroup correct_closure
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be corrected if necessary
*/
template <typename Geometry>
inline void correct_closure(Geometry& geometry)
{
    resolve_variant::correct_closure<Geometry>::apply(geometry);
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CORRECT_CLOSURE_HPP

/* correct_closure.hpp
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
*/