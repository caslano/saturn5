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
Yb6v9rIhrOBGmPWWwWL4tN0sJuF1jnZMwX9kqMxHmkoCGXJq6zVZDuTNRbm5/Dh6G9siT/yzyitfNfw1dvXmYnKvjwg+jGcou+JrEAYuj2IHFTmNI9GqGmgZ/NNYBx/D4v8EBM21TNtawYL6/lnHgwHglULs73OcVxb2c0i4hoHVi1KBSTZTl8Ks32+z2Y6+ZpWs7BFgHXut+3Ka+4+D1aCpCm6bMKMmbJJjnyI+l6MRbvzc0SZahWHAdR9xwsePKY+EVPGtjwUZLTjd+UXNUZu5viaDJubM9zBA0hjJNQyMwlo01iBOxyTgyw+wQ8rFCHrmDCYqw0QJgUrr7C3yY3qci+gZ2DO50pdGjgKDZGF44D9jOH/Y+8XxvMHQwG4Dv3p8gy4bnK8lFMya5n5K2qwq4kbANyDuFJGdzK1gZmpuwq1hn+o7/kG13ipzZDO2b2hVpRKU4IarR11Bd7OG7j/XYL5rIIKeAKffQb1rKnVR6x0OsemcWl/Uv2bhMP8FUEsDBAoAAAAIAC1nSlKGy53seAIAAHsFAAAbAAkAY3VybC1tYXN0ZXIvbGliL2luZXRfbnRvcC5oVVQFAAG2SCRgrVRRb9owEH7PrzjBS0EZ6fa0blW1iLKBNgECugoJyTLxpfZm7Mh2aDv1
*/