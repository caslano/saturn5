// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/num_interior_rings.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct needs_self_turns
{
};

template <typename Geometry>
struct needs_self_turns<Geometry, box_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, ring_tag>
{
    static inline bool apply(Geometry const&)
    {
        return false;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, polygon_tag>
{
    static inline bool apply(Geometry const& polygon)
    {
        return geometry::num_interior_rings(polygon) > 0;
    }
};

template <typename Geometry>
struct needs_self_turns<Geometry, multi_polygon_tag>
{
    static inline bool apply(Geometry const& multi)
    {
        typedef typename boost::range_value<Geometry>::type polygon_type;
        std::size_t const n = boost::size(multi);
        return n > 1 || (n == 1
             && needs_self_turns<polygon_type>
                         ::apply(*boost::begin(multi)));
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_NEEDS_SELF_TURNS_HPP

/* needs_self_turns.hpp
JXoSJV/8yGzIPd4jvxxz9zzxA0aAacJW2YadmvtAFBwwM/TVmAWV9hRyurBY+A+k/OpNkECGtiTGu02Z7vQvm3NQpBEYHyC8JZf24KFeSbAorB3R3TmOUJr5wuR79jR5QoQW12afgCkgQwjBKK6LB9Y3j6sh14jNyTzu4Ysfb3ZmATZNwqswNVfxf43QPcKQT8taKzGgCz99wln0z85quSrWR7zfom73WSWe4R2zNj9sOZlQq8A/zY6Cn7sn5g9ySXyKxf+uQssb2+QRx4iE9YJYWyy7L+ffssBs1ZD2FiICDJw+g/rsWz8Q76mXYmSdkw2JRLDDXvm3OJT2wYm4NXOounJXQsxVMTxeAik42XywyRnWgLWUg4vDksbTJBZHQA2EtYTcPALSWUNNFqunjj3MJqFBmNc+k7frKis6BSaWvpXR1JbxM8us52CTZ5dHG4hS1ugVdpAO/8FPLC13wV0j7NQLjdm6seOuDc1U/VrCBZiv5c4rn8X3KKJtly/LMAdgGDmp1WhP4evpyHwP2pdEBuHYbRQ5/MpxHqn+V9MSZqwchanySDFzLA==
*/