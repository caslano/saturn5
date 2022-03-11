// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_empty
{

struct always_not_empty
{
    template <typename Geometry>
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

struct range_is_empty
{
    template <typename Range>
    static inline bool apply(Range const& range)
    {
        return boost::empty(range);
    }
};

class polygon_is_empty
{
    template <typename InteriorRings>
    static inline bool check_interior_rings(InteriorRings const& interior_rings)
    {
        return check_iterator_range
            <
                range_is_empty, true // allow empty range
            >::apply(boost::begin(interior_rings), boost::end(interior_rings));
    }

public:
    template <typename Polygon>
    static inline bool apply(Polygon const& polygon)
    {
        return boost::empty(exterior_ring(polygon))
            && check_interior_rings(interior_rings(polygon));
    }
};

template <typename Policy = range_is_empty>
struct multi_is_empty
{
    template <typename MultiGeometry>
    static inline bool apply(MultiGeometry const& multigeometry)
    {
        return check_iterator_range
            <
                Policy, true // allow empty range
            >::apply(boost::begin(multigeometry), boost::end(multigeometry));
    }
    
};

}} // namespace detail::is_empty
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry, typename Tag =  typename tag<Geometry>::type>
struct is_empty : not_implemented<Tag>
{};

template <typename Geometry>
struct is_empty<Geometry, point_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, box_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, segment_tag>
    : detail::is_empty::always_not_empty
{};

template <typename Geometry>
struct is_empty<Geometry, linestring_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, ring_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, polygon_tag>
    : detail::is_empty::polygon_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, multi_point_tag>
    : detail::is_empty::range_is_empty
{};

template <typename Geometry>
struct is_empty<Geometry, multi_linestring_tag>
    : detail::is_empty::multi_is_empty<>
{};

template <typename Geometry>
struct is_empty<Geometry, multi_polygon_tag>
    : detail::is_empty::multi_is_empty<detail::is_empty::polygon_is_empty>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct is_empty
{
    static inline bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::is_empty<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_empty<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor : boost::static_visitor<bool>
    {
        template <typename Geometry>
        inline bool operator()(Geometry const& geometry) const
        {
            return is_empty<Geometry>::apply(geometry);
        }
    };

    static bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{is the empty set}
\ingroup is_empty
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is the empty set}

\qbk{[include reference/algorithms/is_empty.qbk]}
*/
template <typename Geometry>
inline bool is_empty(Geometry const& geometry)
{
    return resolve_variant::is_empty<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

/* is_empty.hpp
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
*/