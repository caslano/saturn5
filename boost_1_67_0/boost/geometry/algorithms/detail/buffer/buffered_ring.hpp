// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2015 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING


#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/algorithms/within.hpp>

#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct buffered_ring_collection_tag : polygonal_tag, multi_tag
{};


template <typename Ring>
struct buffered_ring : public Ring
{
    bool has_concave;
    bool has_accepted_intersections;
    bool has_discarded_intersections;
    bool is_untouched_outside_original;

    inline buffered_ring()
        : has_concave(false)
        , has_accepted_intersections(false)
        , has_discarded_intersections(false)
        , is_untouched_outside_original(false)
    {}

    inline bool discarded() const
    {
        return has_discarded_intersections && ! has_accepted_intersections;
    }
    inline bool has_intersections() const
    {
        return has_discarded_intersections || has_accepted_intersections;
    }
};

// This is a collection now special for overlay (needs vector of rings)
template <typename Ring>
struct buffered_ring_collection : public std::vector<Ring>
{
};

}} // namespace detail::buffer


// Turn off concept checking (for now)
namespace dispatch
{
template <typename Geometry, bool IsConst>
struct check<Geometry, detail::buffer::buffered_ring_collection_tag, IsConst>
{
};

}


#endif // DOXYGEN_NO_DETAIL



// Register the types
namespace traits
{


template <typename Ring>
struct tag<geometry::detail::buffer::buffered_ring<Ring> >
{
    typedef ring_tag type;
};


template <typename Ring>
struct point_order<geometry::detail::buffer::buffered_ring<Ring> >
{
    static const order_selector value = geometry::point_order<Ring>::value;
};


template <typename Ring>
struct closure<geometry::detail::buffer::buffered_ring<Ring> >
{
    static const closure_selector value = geometry::closure<Ring>::value;
};


template <typename Ring>
struct point_type<geometry::detail::buffer::buffered_ring_collection<Ring> >
{
    typedef typename geometry::point_type<Ring>::type type;
};

template <typename Ring>
struct tag<geometry::detail::buffer::buffered_ring_collection<Ring> >
{
    typedef geometry::detail::buffer::buffered_ring_collection_tag type;
};


} // namespace traits




namespace core_dispatch
{

template <typename Ring>
struct ring_type
<
    detail::buffer::buffered_ring_collection_tag,
    detail::buffer::buffered_ring_collection<Ring>
>
{
    typedef Ring type;
};


// There is a specific tag, so this specialization cannot be placed in traits
template <typename Ring>
struct point_order<detail::buffer::buffered_ring_collection_tag,
        geometry::detail::buffer::buffered_ring_collection
        <
            geometry::detail::buffer::buffered_ring<Ring>
        > >
{
    static const order_selector value
        = core_dispatch::point_order<ring_tag, Ring>::value;
};


}


template <>
struct single_tag_of<detail::buffer::buffered_ring_collection_tag>
{
    typedef ring_tag type;
};


namespace dispatch
{

template
<
    typename MultiRing,
    bool Reverse,
    typename SegmentIdentifier,
    typename PointOut
>
struct copy_segment_point
    <
        detail::buffer::buffered_ring_collection_tag,
        MultiRing,
        Reverse,
        SegmentIdentifier,
        PointOut
    >
    : detail::copy_segments::copy_segment_point_multi
        <
            MultiRing,
            SegmentIdentifier,
            PointOut,
            detail::copy_segments::copy_segment_point_range
                <
                    typename boost::range_value<MultiRing>::type,
                    Reverse,
                    SegmentIdentifier,
                    PointOut
                >
        >
{};


template<bool Reverse>
struct copy_segments
    <
        detail::buffer::buffered_ring_collection_tag,
        Reverse
    >
    : detail::copy_segments::copy_segments_multi
        <
            detail::copy_segments::copy_segments_ring<Reverse>
        >
{};

template <typename Point, typename MultiGeometry>
struct within
<
    Point,
    MultiGeometry,
    point_tag,
    detail::buffer::buffered_ring_collection_tag
>
{
    template <typename Strategy>
    static inline bool apply(Point const& point,
                MultiGeometry const& multi, Strategy const& strategy)
    {
        return detail::within::point_in_geometry(point, multi, strategy) == 1;
    }
};


template <typename Geometry>
struct is_empty<Geometry, detail::buffer::buffered_ring_collection_tag>
    : detail::is_empty::multi_is_empty<detail::is_empty::range_is_empty>
{};


template <typename Geometry>
struct envelope<Geometry, detail::buffer::buffered_ring_collection_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_range
        >
{};


} // namespace dispatch

namespace detail { namespace overlay
{

template<>
struct get_ring<detail::buffer::buffered_ring_collection_tag>
{
    template<typename MultiGeometry>
    static inline typename ring_type<MultiGeometry>::type const& apply(
                ring_identifier const& id,
                MultiGeometry const& multi_ring)
    {
        BOOST_GEOMETRY_ASSERT
            (
                id.multi_index >= 0
                && id.multi_index < int(boost::size(multi_ring))
            );
        return get_ring<ring_tag>::apply(id, multi_ring[id.multi_index]);
    }
};

}}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_RING

/* buffered_ring.hpp
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
*/