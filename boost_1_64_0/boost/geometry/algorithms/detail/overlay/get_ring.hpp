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
9ppL/F0Ob9tQ/yDt4HXe/3SruylwuWrlj6gxN3tMWIPF5oomdR4DhiBBnlnZPo7pfsYYwA8ePCN5fZBe+KAezU+A9GW3377PdUtkGLUmM6WnWPjq36BLHv1g9Y6F9Lc4NNS68xMfIWkUbMUvFE2uIwiYBs0wBVEOimnCnUmWScwYW2HWRs3CqBAfvMXbBeCgSZkxdtbwJe0aXtdPp2Gzmogs2b81GCN9wuIZN+jbMAvnj73CJt5ak9o3OJEJgbasq78KTiiBixNKsTBdZYfB8dhdJQ8GGe1rDWW972QfTd23UBdxf+ReMw8RrfjfDwZR42HX+e/AYCVowrGF5XVzkPsPO3fvJh3XGnPBKHrAaQGcHD020FueFz8VEV6OdK3YC8sG4pcb6mgo7O3ECwJPjC1rJJlB36mYfasOqtQMihk+FV8MkvNwKtxCAoh0wE3eXtJ9Q5axAa3froIThjG13+kQXNi+Txah1KoEGDfOJEMCdIclhEyGm5WURGTqTvbOCfbD5FpXnxtT+BmZVtimyp3bukz99fGpcUlUWEMGIcFTA867OuLyvgJG0Q==
*/