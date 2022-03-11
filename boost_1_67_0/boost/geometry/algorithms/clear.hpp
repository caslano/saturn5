// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP


#include <boost/type_traits/remove_const.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
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
                typename boost::remove_reference
                    <
                        typename traits::interior_mutable_type<Polygon>::type
                    >::type
            >::apply(interior_rings(polygon));
        traits::clear
            <
                typename boost::remove_reference
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


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant {

template <typename Geometry>
struct clear
{
    static inline void apply(Geometry& geometry)
    {
        dispatch::clear<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct clear<variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: static_visitor<void>
    {
        template <typename Geometry>
        inline void operator()(Geometry& geometry) const
        {
            clear<Geometry>::apply(geometry);
        }
    };

    static inline void apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry)
    {
        boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


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

    resolve_variant::clear<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CLEAR_HPP

/* clear.hpp
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
*/