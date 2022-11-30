// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/type_traits_std.hpp>

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
        return std::all_of(boost::begin(interior_rings), boost::end(interior_rings),
                           []( auto const& range ){ return boost::empty(range); });
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
        return std::all_of(boost::begin(multigeometry), 
                           boost::end(multigeometry), 
                           []( auto const& range ){ return Policy::apply(range); });
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


namespace resolve_dynamic
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_empty
{
    static inline bool apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::is_empty<Geometry>::apply(geometry);
    }
};

template <typename Geometry>
struct is_empty<Geometry, dynamic_geometry_tag>
{
    static inline bool apply(Geometry const& geometry)
    {
        bool result = true;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = is_empty<util::remove_cref_t<decltype(g)>>::apply(g);
        }, geometry);
        return result;
    }
};

template <typename Geometry>
struct is_empty<Geometry, geometry_collection_tag>
{
    static inline bool apply(Geometry const& geometry)
    {
        bool result = true;
        detail::visit_breadth_first([&](auto const& g)
        {
            result = is_empty<util::remove_cref_t<decltype(g)>>::apply(g);
            return result;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic


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
    return resolve_dynamic::is_empty<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_IS_EMPTY_HPP

/* is_empty.hpp
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
*/