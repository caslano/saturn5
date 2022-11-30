// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP


#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template<typename Tag>
struct get_ring
{};

// A range of rings (multi-ring but that does not exist)
// gets the "void" tag and is dispatched here.
template<>
struct get_ring<void>
{
    template<typename Range>
    static inline typename boost::range_value<Range>::type const&
                apply(ring_identifier const& id, Range const& container)
    {
        return range::at(container, id.multi_index);
    }
};


template<>
struct get_ring<ring_tag>
{
    template<typename Ring>
    static inline Ring const& apply(ring_identifier const& , Ring const& ring)
    {
        return ring;
    }
};


template<>
struct get_ring<box_tag>
{
    template<typename Box>
    static inline Box const& apply(ring_identifier const& ,
                    Box const& box)
    {
        return box;
    }
};


template<>
struct get_ring<polygon_tag>
{
    template<typename Polygon>
    static inline typename ring_return_type<Polygon const>::type const apply(
                ring_identifier const& id,
                Polygon const& polygon)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.ring_index >= -1
                && id.ring_index < int(boost::size(interior_rings(polygon)))
            );
        return id.ring_index < 0
            ? exterior_ring(polygon)
            : range::at(interior_rings(polygon), id.ring_index);
    }
};


template<>
struct get_ring<multi_polygon_tag>
{
    template<typename MultiPolygon>
    static inline typename ring_type<MultiPolygon>::type const& apply(
                ring_identifier const& id,
                MultiPolygon const& multi_polygon)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.multi_index >= 0
                && id.multi_index < int(boost::size(multi_polygon))
            );
        return get_ring<polygon_tag>::apply(id,
                    range::at(multi_polygon, id.multi_index));
    }
};

// Returns the number of segments on a ring (regardless whether the ring is open or closed)
template <typename Geometry>
inline signed_size_type segment_count_on_ring(Geometry const& geometry,
                                              ring_identifier const& ring_id)
{
    using tag = typename geometry::tag<Geometry>::type;

    // A closed polygon, a triangle of 4 points, including starting point,
    // contains 3 segments. So handle as if it is closed, and subtract one.
    return geometry::num_points(detail::overlay::get_ring<tag>::apply(ring_id, geometry), true) - 1;
}

// Returns the number of segments on a ring (regardless whether the ring is open or closed)
template <typename Geometry>
inline signed_size_type segment_count_on_ring(Geometry const& geometry,
                                              segment_identifier const& seg_id)
{
    return segment_count_on_ring(geometry, ring_identifier(0, seg_id.multi_index, seg_id.ring_index));
}


// Returns the distance between the second and the first segment identifier (second-first)
// It supports circular behavior and for this it is necessary to pass the geometry.
// It will not report negative values
template <typename Geometry>
inline signed_size_type segment_distance(Geometry const& geometry,
        segment_identifier const& first, segment_identifier const& second)
{
    // It is an internal function, make sure the preconditions are met
    BOOST_ASSERT(second.source_index == first.source_index);
    BOOST_ASSERT(second.multi_index == first.multi_index);
    BOOST_ASSERT(second.ring_index == first.ring_index);

    signed_size_type const result = second.segment_index - first.segment_index;
    if (second.segment_index >= first.segment_index)
    {
        return result;
    }
    // Take wrap into account, counting segments on the ring (passing any of the ids is fine).
    // Suppose point_count=10 (10 points, 9 segments), first.seg_id=7, second.seg_id=2,
    // then distance=9-7+2=4, being segments 7,8,0,1
    return segment_count_on_ring(geometry, first) + result;
}

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP

/* get_ring.hpp
+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
*/