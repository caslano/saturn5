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
uIe40cSnBi8KvDL3w5gfflruEJ6/Eb1EvSyO8BWCD+jtHo0m97kawN1GLH2xp/Jp3EsGBJCEnn8aG1+ZF2t3k6RfM7fs8jobdfBvtUkfN9f+taZ4hK1X0CSOxt37mPifQ3MdT9qvj67Prrof2qfwycHal7pdAmOQAUX4xvvEUbdgWCDG8aifz9mpnl/vFf48oZvbh+3GhWw2Llbaqot+NNVtXOB9XR3n6u7RnC78vMNsQGcL2AT8xruAfvBSVVG3B5t5ir9uvYKbUky2CZcP1szsHbg0o/gy/scshgE2P2J7XMrWqyz+B7bDjd4kxTiawldv2ledi+Ofuj+eHZ3/BNitiFT9uvMbfMez0N+vTy871LB99Ru1SgaN9cbHrVcf43gKF/mp+qndft+9bB//3H1/BNxJs0l7BpJ8nY6QX5pGM+SMt/CFjTQKCKSQFNzHgFApcWOIWA+AMPfRQ65ukeXW8Btk0TiGFWJrebOl2Q1yzlH/gRBsAqQcUAh7yEY/251eto9O8JeGs6cm7QkWex8/A34xL5LRCF7U0SRCEoS8HiK4LHoUPQBrcB+lBXGwSAsVn/ULBkzDA0yDINNpn598Nr9pGKnDQ2U+BJHo81qITHZxru59lsAt7229AprZrNnbh8vTq3Z4cxmw
*/