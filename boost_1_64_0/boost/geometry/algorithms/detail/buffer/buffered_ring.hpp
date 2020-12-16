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
WT+gM/QZKmftvgNQRtYgPgup8419w7zI4oMHdKDl7Xg4T/hZW0p0qj87jg4xslo8a7MeavqH42/b+zAqr9/XTPkjym2fAA3TJyaX0xlStMFG4xsrLQc/I0sp9b3yKJ2nuLqftWlnn9m0s8NsOkP0HiX4fZS+h9IPUPohm9a6+LcLVS+SZ/QWwj9aHoe7elh4LcGfprE2k+CunhZeR3A+qz2H4I9S+XqC30fw4wh+D8HnE/wBgi8k+EME/1i59nHdYw9L+ObSVI49VgIe77EWEW4BcAsSzlqeUI79MdFNliMvWFKOc4W58MGDz11+vFz37lQuF6/dgk+W05ljgzcwvxFBixnT/eZn75W2mrGCe6baFjKf6zzC+9F2ni/ygKPrgLw1gvH/p3F+Dsb+Nfz7rlicy+5lHZk0bG2nKdnPmX3YTyc421A2PZmuXms3F8q+wNu82CdK/V28y3bB0XRx0LVieRnyUK7U72E6U9g/eL3WBBkXWlPT0wNv0HW2LkvFfJ9zTb5Q8PcFd3fviZQH+q8haGyqlbtLdUtaZjYv9iaczfC2IcYDvqvRHXmhlehjHgRd/42gPG4X9pSH9pfl0Wvaz9rGti/0GZx1+ck4GR1nvh/gTjHqRWNylY4zxgU+jbM1RBu4iXeVTyPahm7iGF4H/GTfSEjD4p8xEH6wPf76cuNLGTawL4XLfg5lt6IsdIAzJ4YG6eBMMy+xjBP1myfzGx5skHLTpNxebGPg93zOH9uRewVnCy3y/STgDQvODdf/kR2HZc+qnF9u7GjjQ7ugPG5zXQj9dNjvjcD/coSLfv4VbTelJzpwNJP9uRfpHM34uf2rXzN1tjKz7/bSnLIk+2G/oetmCN+H3hK/TG0ohg0JrojKAsY+zm/p2HbwZB/nd6wukZ6N97QuHyc0d3hPOL2ytazFfwQPn3nq6ZMXsKZNq5we+6YqXWNb8t3Qprm15VXVMaewybL77Kticx787GSP/lD1RTApd43qw8GS9XFdpFPgsE43Wn0B/9id1ZdULkFj5dMRw/VT40K5RFO5dVZVVk460yyrs5sSdHYz6eynqjOCSbmfqc4ElkNnP490BhzW2S+szoDv6nnEASGtq6RvgIedd7C/DMvcruMP8EQ8iZWp40/hA+DnBb8x68/AuLsGdwuukVPvrFg57y2P33HYgDnxyANwX0TxFe510YtxUouzBu8VZe2pzdSGW8rdj87pYr58ELg7eMOyqbGhpT8tL9X1rm733ScRAh/UQ4OnuWJBS1tr28qUoUkQ0HwkpKm+6oe9beUYp71M3h8uecMDJbkNPk/nn06l2p2THL5N7/dtTy1v7e/MtKwIorwizVsQVOPsy2PGhisOnGDHz6htqtNRpBkYQ9oW5nvM49D9+NFhm/4Run8CdbL73FrEH30KsB29c9lQt6CpaV5Lg0R3lgctocZkoMr3dPlAMSk6nXPWFjekc8DQRs+CrvdxmrplqG4vGLwX8ff5cdtfHNTL3UcD9Yk/49rWnFt6XtIjA3FNp9b49nup3LXpqe7kAb4JeH9+X5+84hylDw5a+1aUZeHFLl0epl3blLp0S1/PavfWLM4uvKzt7/cDazIt7cuixkcqd4yQQfaXv5TH+8sr5Pv4q86XHqbfu8sPwNlNHduaTo7JkEt+tN+28kHFZAhHZ9KIBZ3XTduLvIgFr/Ms5kGNE4e0nQfzgjfL42es7hwRbOPyr+3vfzr3Wnv5behkqs6j5t4GdGjn1f9EOgb9N1D+SOj4vXKjc/IdS57KYNetIRUWJ/nO4lDCSfLR7Vrh11s3btUu3q0i3meGS9qOtREVqA9gkm/mIIlxWmHuklF/2yuSCTCnQ94=
*/