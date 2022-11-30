// Boost.Geometry

// Copyright (c) 2018-2021 Oracle and/or its affiliates.

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

#include <boost/geometry/views/reversible_view.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


struct envelope_hole
{
    template <typename Range, typename Box, typename Strategies>
    static inline void apply(Range const& range, Box& mbr, Strategies const& strategies)
    {
        // Reverse holes to avoid calculating the envelope for the outside
        // in spherical and geographic coordinate systems
        detail::clockwise_view
            <
                Range const,
                geometry::point_order<Range>::value == counterclockwise
                    ? clockwise : counterclockwise
            > view(range);
        strategies.envelope(range, mbr).apply(view, mbr);
    }
};

struct envelope_polygon
{
    template <typename Polygon, typename Box, typename Strategy>
    static inline void apply(Polygon const& polygon, Box& mbr, Strategy const& strategy)
    {
        typename ring_return_type<Polygon const>::type ext_ring
            = exterior_ring(polygon);

        if (geometry::is_empty(ext_ring))
        {
            // use dummy multi polygon to get the strategy because there is no multi ring concept
            using strategy_t = decltype(strategy.envelope(detail::dummy_multi_polygon(),
                                                          detail::dummy_box()));
            // if the exterior ring is empty, consider the interior rings
            envelope_multi_range
                <
                    envelope_hole
                >::template apply<strategy_t>(interior_rings(polygon), mbr, strategy);
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
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
*/