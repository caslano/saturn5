// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/dispatch/envelope.hpp>

// TEMP
#include <boost/geometry/strategies/detail.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

// TEMP
template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct envelope_segment_call_strategy
{
    template <typename Point, typename Segment, typename Box>
    static inline void apply(Point const& p1, Point const& p2,
                             Segment const& segment, Box& mbr,
                             Strategy const& strategy)
    {
        strategy.envelope(segment, mbr).apply(p1, p2, mbr);
    }
};

template <typename Strategy>
struct envelope_segment_call_strategy<Strategy, false>
{
    template <typename Point, typename Segment, typename Box>
    static inline void apply(Point const& p1, Point const& p2,
                             Segment const&, Box& mbr,
                             Strategy const& strategy)
    {
        strategy.apply(p1, p2, mbr);
    }
};

struct envelope_segment
{
    template <typename Segment, typename Box, typename Strategy>
    static inline void apply(Segment const& segment, Box& mbr,
                             Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);

        // TEMP - expand calls this and Umbrella strategies are not yet supported there
        envelope_segment_call_strategy<Strategy>::apply(p[0], p[1], segment, mbr, strategy);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment>
struct envelope<Segment, segment_tag>
{
    template <typename Box, typename Strategy>
    static inline void apply(Segment const& segment,
                             Box& mbr,
                             Strategy const& strategy)
    {
        detail::envelope::envelope_segment
            /*<
               dimension<Segment>::value
            >*/::apply(segment, mbr, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

/* segment.hpp
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
*/