// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

struct envelope_polygon
{
    template <typename Polygon, typename Box, typename Strategy>
    static inline void apply(Polygon const& polygon, Box& mbr, Strategy const& strategy)
    {
        typename ring_return_type<Polygon const>::type ext_ring
            = exterior_ring(polygon);

        if (geometry::is_empty(ext_ring))
        {
            // if the exterior ring is empty, consider the interior rings
            envelope_multi_range
                <
                    envelope_range
                >::apply(interior_rings(polygon), mbr, strategy);
        }
        else
        {
            // otherwise, consider only the exterior ring
            envelope_range::apply(ext_ring, mbr, strategy);
        }
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Ring>
struct envelope<Ring, ring_tag>
    : detail::envelope::envelope_range
{};

template <typename Polygon>
struct envelope<Polygon, polygon_tag>
    : detail::envelope::envelope_polygon
{};

template <typename MultiPolygon>
struct envelope<MultiPolygon, multi_polygon_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_polygon
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

/* areal.hpp
+HjXwzBsTyvBblxiEx8RvpIq5WzFL7+ihOQmqUCogmW8WNQEr1xtlNVab5JiqrePWgMoHW5IAYxTMa2igWz3is3v3Q6Jnyqsvqcr1vo+YpNKMH4uYctO+9BI6EM+6EPOPn1oO7xO7Tj3QuQEhPcgaHofMhBg603IXRwbnZ2XPWl8v/MG1M4UR+hNfAALD4hhKSR3K6k29W0lFcslWJoqVgoFUEVVsqbE5ciAZY2kmsp6GyR+lMrKWpJqLesJmzSF4dyystJzAGkoHWimA830g+wcwNLUTAMndg0k/kDpYWFTqrVb3W7XZmB8nOPENiZwYm+CufoOkElgrn4EiW8IXexyXzLoU7DUKVrxKbzr/wkstR+o1AHL2aCayjkfEotVVs6UGwGkTcP4FSjZQqNkfXwQdRu2xV3wKrUtPgSRNyF8AiHhC4idtie9g9kW11NfQD2qMaf86nvAB6kZx/F+oVOsks7INdJB3ChukCrEg9JacR0KCkUEFK33OZHw0EyGY0l5EEiUDWVtP2Go0fbEaHg/zClIL0MTlGF2H2y6NnjFRs5sdUBESstEfghLmX10yRAz7Kpshl01JwLmxJEUM+yqOfH/g9uaZCawWzKDuJoTp5PNpM2JgDnBT3DwvJkTSebEbr3YzDbbAGbpB0RoEkVZujgQ1OzAiLID49vqR8inuTFatERLSzTp4bO/8qCU8rOjybnXsLBRapTD
*/