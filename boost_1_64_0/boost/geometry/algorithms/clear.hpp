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
djKaL1h1ZlGZRXPpnGA2zBxuhh1EiwNzZ2byc0U8WhZYbWafl9VOpXOCWTPTcSzRQZNkwfsEs8DVl4vQvMGqMXv5o+gaWqBQ99lq2Am0eDB7ZsfUaefR1Fn0PV/lfv0elFdaVMN0MLxHVtFt7JlxR9b9T93oUjCcrVQ3KrzgzZZ3aGVgcmb/DUsuR5MfgeuFWbMq+hI0VzC+5oLRtRegeYNZMjt4/9kkNH8wO2a53hcUaKPBsL8KS335Ay0CzITVfS26Yo8WB2bGLK3vwJdoKjALZjMSW35GUwtW3anLIbQcMGtmt1usq45WKJi7cp8JmkY4y23JoWVokqMGkvrM6l17lYfmC2bKbN2OhPOUGRjPc3XaklNoQWB8fkWTmhaixR4VcnE/sq/S9ujFs7MY6e7RO2TQsxwtB8yZ2ZFmPTPQSgV7pd54EE1+7O/v+IzBtjknzkXzB8OzmIDdH5vbHy0QzJSZpK/1CbRQMHtmYUcmvqUewBTMbCb7maOpwcyZdW4ov0D9CftZuScXoRWAWTDb9CXnB/UOJmX24uasVWhlYNbMqp62b0i5ZMP7NbM3e0Y1RXMDs2Gm7rNCSZmB8TXfy7oeRQsS6jZ61aKzxIHx3qvIrdegJYHxOdS4HFNGmYGZMKudFxKKliXUDQgtGo+WB+bKbFTdc25oGjA5s58re6xHkx7XtrBgg8ZormAWPOta97ug+QqW2f2dDVqAYBkTdlFdqGB1Nj56TJkJ9n65guqSBEtVJi1ESwfjWV/8t/pHygVMwWxqy/C6aKVgjsyutZl2mnI58fe9TgYWHhp7nHo/QffICuv/ZvUzNCWYITPLsrHpaP5gJmzNhAsZlFkgmJxZF6s2M9AiBGu+vo8aLR7MiNmk3m2dKDOhbtUYnwTKTDDbl6Xf0U4L/U23+ptnAZiM1T2c3bQjWjGYAauLSP+X6krBLHkPbavmVNpePcnJv39TY6q7Vy9JclEfzQ3MnFnw1qTtaEowOTPTGuuj0ALBajNL2XY1Cy0eTMrsn9FfP6GtPEm9V9iDlIkqtFSwgD+/K7cA2/miYCWa7/W/f8thBVarn+UItFCwesxK9u+JpDXBTJnd3Lz0Plo6mDmzzQPvlKPlgeG9xxqspu3zK2ilYO7MrnW9vwrN9cbf31fZgEXfCnpMmYHVZDZKsaEBZQamYNbgul0HNDWYAzPjn+l36Zxg5syuXS76jFYMZsHs9ryxtF8ZmCWz8V130WzlN+k6q7DzB09cR1OA8f08A082RvMGs2M28O3oRWgBYLyH5Kal7mgRYNbMnh1bk0C5gDkyy1w07wHlAmbDbOYz9y6UCxjOwRZs3amBg9Akt+D7T2blt0/IaH5gJsxyT05Mof7A7Jnt/V3FmfoDc2Q2scHA49QfmBWzPt173KX+wKozm+N8awpaurDm5ReD09EKwFyYfV7p9oNmCyZn1mieJpNme1u7vxubQk5Q77dp7hU2rWbXkWhuYI78nJPvrkbzB3Ng1mXkywtooWBGzCTbXvqiRYMZsv2UY1cOR5sunGXHkrbBlBkY/rzbgUm7ZdRGywEzYybb9fYKZQZmx2zwf70vo2nALJntHjeR5icthPsZs14r1w9GU4DxurbJ3c3RvAV7t8XAjTIDs2c2PWSagjIDc2BWpaWxJfUOZsvszphfDmhqMN6fpduvpmh5wlmmVEveglYM5sRs03L7fOr9Drz3MLsYnjqc+gPj55z3yKwGWgCYDbOSh+ln0SIEu/Nx6is0FRjv74ikZBBaumD3f6s302zB+Nw3zjhajfoDkzEbVaZyprnfoedRhdW4nZldafv0ysDwXV+hu08vtsdpOzTvu3/NHuz20g1ZaBE=
*/