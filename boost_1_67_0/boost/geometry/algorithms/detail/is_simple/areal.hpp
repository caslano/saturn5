// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Ring, typename CSTag>
struct is_simple_ring
{
    static inline bool apply(Ring const& ring)
    {
        simplicity_failure_policy policy;
        return ! boost::empty(ring)
            && ! detail::is_valid::has_duplicates
                    <
                        Ring, geometry::closure<Ring>::value, CSTag
                    >::apply(ring, policy);
    }
};


template <typename Polygon, typename CSTag>
class is_simple_polygon
{
private:
    template <typename InteriorRings>
    static inline
    bool are_simple_interior_rings(InteriorRings const& interior_rings)
    {
        return
            detail::check_iterator_range
                <
                    is_simple_ring
                        <
                            typename boost::range_value<InteriorRings>::type,
                            CSTag
                        >
                >::apply(boost::begin(interior_rings),
                         boost::end(interior_rings));
    }

public:
    static inline bool apply(Polygon const& polygon)
    {
        return
            is_simple_ring
                <
                    typename ring_type<Polygon>::type,
                    CSTag
                >::apply(exterior_ring(polygon))
            &&
            are_simple_interior_rings(geometry::interior_rings(polygon));
    }
};


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
    static inline bool apply(Ring const& ring, Strategy const&)
    {
        return detail::is_simple::is_simple_ring
            <
                Ring,
                typename Strategy::cs_tag
            >::apply(ring);
    }
};


// A Polygon is always a simple geometric object provided that it is valid.
//
// Reference (for validity of Polygons): OGC 06-103r4 (6.1.11.1)
template <typename Polygon>
struct is_simple<Polygon, polygon_tag>
{
    template <typename Strategy>
    static inline bool apply(Polygon const& polygon, Strategy const&)
    {
        return detail::is_simple::is_simple_polygon
            <
                Polygon,
                typename Strategy::cs_tag
            >::apply(polygon);
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
    static inline bool apply(MultiPolygon const& multipolygon, Strategy const&)
    {
        return
            detail::check_iterator_range
                <
                    detail::is_simple::is_simple_polygon
                        <
                            typename boost::range_value<MultiPolygon>::type,
                            typename Strategy::cs_tag
                        >,
                    true // allow empty multi-polygon
                >::apply(boost::begin(multipolygon), boost::end(multipolygon));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_AREAL_HPP

/* areal.hpp
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
*/