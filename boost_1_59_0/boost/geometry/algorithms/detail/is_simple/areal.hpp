// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Ring, typename Strategy>
inline bool is_simple_ring(Ring const& ring, Strategy const& strategy)
{
    simplicity_failure_policy policy;
    return ! boost::empty(ring)
        && ! detail::is_valid::has_duplicates<Ring>::apply(ring, policy, strategy);
}

template <typename InteriorRings, typename Strategy>
inline bool are_simple_interior_rings(InteriorRings const& interior_rings,
                                      Strategy const& strategy)
{
    return std::all_of(boost::begin(interior_rings),
                       boost::end(interior_rings),
                       [&](auto const& r)
                       {
                           return is_simple_ring(r, strategy);
                       }); // non-simple ring not found
    // allow empty ring
}

template <typename Polygon, typename Strategy>
inline bool is_simple_polygon(Polygon const& polygon, Strategy const& strategy)
{
    return is_simple_ring(geometry::exterior_ring(polygon), strategy)
        && are_simple_interior_rings(geometry::interior_rings(polygon), strategy);
}


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A Ring is a Polygon.
// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Ring>
struct is_simple<Ring, ring_tag>
{
    template <typename Strategy>
    static inline bool apply(Ring const& ring, Strategy const& strategy)
    {
        return detail::is_simple::is_simple_ring(ring, strategy);
    }
};


// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for validity of Polygons): OGC 06-103r4 (6.1.11.1)
template <typename Polygon>
struct is_simple<Polygon, polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(Polygon const& polygon, Strategy const& strategy)
    {
        return detail::is_simple::is_simple_polygon(polygon, strategy);
    }
};


// Not clear what the definition is.
// Right now we consider a MultiPolygon as simple if it is valid.
//
// Reference (for validity of MultiPolygons): OGC 06-103r4 (6.1.14)
template <typename MultiPolygon>
struct is_simple<MultiPolygon, multi_polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(MultiPolygon const& multipolygon, Strategy const& strategy)
    {
        return std::none_of(boost::begin(multipolygon), boost::end(multipolygon),
                            [&](auto const& po) {
                                return ! detail::is_simple::is_simple_polygon(po, strategy);
                            }); // non-simple polygon not found
                                // allow empty multi-polygon
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

/* areal.hpp
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
*/