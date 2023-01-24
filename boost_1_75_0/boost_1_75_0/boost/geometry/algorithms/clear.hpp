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
EwCqN5ZI03w1uxceA7z/VfxFdCdRW+8jPHAUGzOVTVQme0/a2rpg7vyOKxNpLbFxxHQarbQ1wYWRqyGE+mr+HM6W78ZHAgoP9Hd9dfouQyQbiQpLWVqOloLVClIpPYhac6YVZGE/omIcIy1lONpeh30XF4VU1u6w8ZBljV2V/bg10/pij9HkwqU0oXjW+1ggzKKUmyArE1Cpx1xhHTfTgGx++zXBnbEAA7/ETt+1TXQ4xMS4/21fFNEcKXWYRntXOYze3K7AK4rH9B0oPYdV3JZnF5QSz+v6NIXfkuk1ok7/50hekjZ9wie0YsoPaNMtaHXvBAG6n2BevW/VElATkz1tiIy71dkZGuoXUCqpD93XKFg7uAOZ3Vc53a6CwQ6jXB+yZyEeahGvOWBdE0uVVgUTp913KmQqUUvZaLrTXbotoH7ZXZX+yDEEjGrpsWpcB7tarx6kEyA0osVMcwjVXlhyYhk9LNwLe9tQ9PKzrKKydoiJOygtltl1WKsn8M+KAf7kydL12/DkMh6u/cph8VfPhP6O4zqAm+EPph4cTUJVvCkPFQUIsjFqYeCQJS3X6amEgWGnhk+Ijv5t6qLjXVFGiHnmCb2EQIkkR9JmmHjD1owipPu0U+63mcuwj0JQPSSPMoFKv5RwuWop0lbxW7FE1l2tExS5JtdwqpbMa24ACdJ23q3VpiS7orK0j35HoJxkAkDa0QINDrsT
*/