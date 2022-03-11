// Boost.Geometry

// Copyright (c) 2017 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CORRECT_CLOSURE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CORRECT_CLOSURE_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>

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

template <typename Geometry>
struct nop
{
    static inline void apply(Geometry& )
    {}
};


// Close a ring, if not closed, or open it
template <typename Ring>
struct close_or_open_ring
{
    static inline void apply(Ring& r)
    {
        if (boost::size(r) <= 2)
        {
            return;
        }

        bool const disjoint = geometry::disjoint(*boost::begin(r),
                                                 *(boost::end(r) - 1));
        closure_selector const s = geometry::closure<Ring>::value;

        if (disjoint && s == closed)
        {
            // Close it by adding first point
            geometry::append(r, *boost::begin(r));
        }
        else if (! disjoint && s != closed)
        {
            // Open it by removing last point
            geometry::traits::resize<Ring>::apply(r, boost::size(r) - 1);
        }
    }
};

// Close/open exterior ring and all its interior rings
template <typename Polygon>
struct close_or_open_polygon
{
    typedef typename ring_type<Polygon>::type ring_type;

    static inline void apply(Polygon& poly)
    {
        close_or_open_ring<ring_type>::apply(exterior_ring(poly));

        typename interior_return_type<Polygon>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            close_or_open_ring<ring_type>::apply(*it);
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
    : detail::correct_closure::nop<Point>
{};

template <typename LineString>
struct correct_closure<LineString, linestring_tag>
    : detail::correct_closure::nop<LineString>
{};

template <typename Segment>
struct correct_closure<Segment, segment_tag>
    : detail::correct_closure::nop<Segment>
{};


template <typename Box>
struct correct_closure<Box, box_tag>
    : detail::correct_closure::nop<Box>
{};

template <typename Ring>
struct correct_closure<Ring, ring_tag>
    : detail::correct_closure::close_or_open_ring<Ring>
{};

template <typename Polygon>
struct correct_closure<Polygon, polygon_tag>
    : detail::correct_closure::close_or_open_polygon<Polygon>
{};


template <typename MultiPoint>
struct correct_closure<MultiPoint, multi_point_tag>
    : detail::correct_closure::nop<MultiPoint>
{};


template <typename MultiLineString>
struct correct_closure<MultiLineString, multi_linestring_tag>
    : detail::correct_closure::nop<MultiLineString>
{};


template <typename Geometry>
struct correct_closure<Geometry, multi_polygon_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::correct_closure::close_or_open_polygon
                <
                    typename boost::range_value<Geometry>::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct correct_closure
{
    static inline void apply(Geometry& geometry)
    {
        concepts::check<Geometry const>();
        dispatch::correct_closure<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct correct_closure<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<void>
    {
        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            correct_closure<Geometry>::apply(geometry);
        }
    };

    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry)
    {
        visitor vis;
        boost::apply_visitor(vis, geometry);
    }
};

} // namespace resolve_variant


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