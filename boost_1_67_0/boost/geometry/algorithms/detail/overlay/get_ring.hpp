// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP


#include <boost/range.hpp>

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


template <typename Geometry>
inline std::size_t segment_count_on_ring(Geometry const& geometry,
                                         segment_identifier const& seg_id)
{
    typedef typename geometry::tag<Geometry>::type tag;
    ring_identifier const rid(0, seg_id.multi_index, seg_id.ring_index);
    // A closed polygon, a triangle of 4 points, including starting point,
    // contains 3 segments. So handle as if closed and subtract one.
    return geometry::num_points(detail::overlay::get_ring<tag>::apply(rid, geometry), true) - 1;
}

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RING_HPP

/* get_ring.hpp
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
*/