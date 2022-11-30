// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

#include <algorithm>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace reverse
{


struct range_reverse
{
    template <typename Range>
    static inline void apply(Range& range)
    {
        std::reverse(boost::begin(range), boost::end(range));
    }
};


struct polygon_reverse: private range_reverse
{
    template <typename Polygon>
    static inline void apply(Polygon& polygon)
    {
        range_reverse::apply(exterior_ring(polygon));

        auto&& rings = interior_rings(polygon);
        auto const end = boost::end(rings);
        for (auto it = boost::begin(rings); it != end; ++it)
        {
            range_reverse::apply(*it);
        }
    }
};


}} // namespace detail::reverse
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct reverse
{
    static inline void apply(Geometry&)
    {}
};


template <typename Ring>
struct reverse<Ring, ring_tag>
    : detail::reverse::range_reverse
{};


template <typename LineString>
struct reverse<LineString, linestring_tag>
    : detail::reverse::range_reverse
{};


template <typename Polygon>
struct reverse<Polygon, polygon_tag>
    : detail::reverse::polygon_reverse
{};


template <typename Geometry>
struct reverse<Geometry, multi_linestring_tag>
    : detail::multi_modify<detail::reverse::range_reverse>
{};


template <typename Geometry>
struct reverse<Geometry, multi_polygon_tag>
    : detail::multi_modify<detail::reverse::polygon_reverse>
{};



} // namespace dispatch
#endif


namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct reverse
{
    static void apply(Geometry& geometry)
    {
        concepts::check<Geometry>();
        dispatch::reverse<Geometry>::apply(geometry);
    }
};

template <typename Geometry>
struct reverse<Geometry, dynamic_geometry_tag>
{
    static void apply(Geometry& geometry)
    {
        traits::visit<Geometry>::apply([](auto & g)
        {
            reverse<util::remove_cref_t<decltype(g)>>::apply(g);
        }, geometry);
    }
};

template <typename Geometry>
struct reverse<Geometry, geometry_collection_tag>
{
    static void apply(Geometry& geometry)
    {
        detail::visit_breadth_first([](auto & g)
        {
            reverse<util::remove_cref_t<decltype(g)>>::apply(g);
            return true;
        }, geometry);
    }
};

} // namespace resolve_dynamic


/*!
\brief Reverses the points within a geometry
\details Generic function to reverse a geometry. It resembles the std::reverse
   functionality, but it takes the geometry type into account. Only for a ring
   or for a linestring it is the same as the std::reverse.
\ingroup reverse
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be reversed

\qbk{[include reference/algorithms/reverse.qbk]}
*/
template <typename Geometry>
inline void reverse(Geometry& geometry)
{
    resolve_dynamic::reverse<Geometry>::apply(geometry);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

/* reverse.hpp
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
*/