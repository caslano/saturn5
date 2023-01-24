// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

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

// For backward compatibility
#include <boost/geometry/strategies/cartesian/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/geographic/envelope_segment.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t DimensionCount>
struct envelope_segment
{
    template <typename Point, typename Box, typename Strategy>
    static inline void apply(Point const& p1,
                             Point const& p2,
                             Box& mbr,
                             Strategy const& strategy)
    {
        strategy.apply(p1, p2, mbr);
    }

    template <typename Segment, typename Box, typename Strategy>
    static inline void apply(Segment const& segment, Box& mbr,
                             Strategy const& strategy)
    {
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        apply(p[0], p[1], mbr, strategy);
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
        typename point_type<Segment>::type p[2];
        detail::assign_point_from_index<0>(segment, p[0]);
        detail::assign_point_from_index<1>(segment, p[1]);
        detail::envelope::envelope_segment
            <
               dimension<Segment>::value
            >::apply(p[0], p[1], mbr, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_SEGMENT_HPP

/* segment.hpp
6MgQE4Z/Rwrl/DskBlGdQn92p9AnTnOIboHVBp+9dzP7U26GepqZjHIL1RL+3xCG4M+MRi9Gp6dSqngJ9YdBbQEDUhPJ9mlm6cJxtncnM3jvIVsxGZBHZIp+XcIyxfxjH0meTg0CurY6qAcT+xD6Rgr1d9B9bhh9BtuHUrYkhaFnp+hlY7MTdc4tbHJJpaUT06HKc2rrAvDjq58dhR/cPG8C+aFtvPm3HjTaraNgJyvrPOjcDG6tlST9+7qEeqBEeni9B73c9vB8jK9gaaqcpfhUH/AZUWfQFXQHvek4uCyjMbQka172w5ENOQXRabg0TcDLJqbi0rdwvLF0VfzjMl+8uLx56pq0iu1TaypzptqHlD8Vb6mKVT+Ja3y16+I7bHUX5Pidtlx/dHt2S/0DsyP1201hf3ZZeFXGljkf2ea90fyJb5V3gl0iINT5IHlRd1AZfmIDWlo3tbAa1o+67Gxtjr85w0fnfxMutLMwE43xw+VbELo55vNujDcLqA8+dDF5lvhxOdgYRBf7/l9PaRUEGH60Ph429zseNsKzv4ZvxHZCZPKETPQLCPmK4Sd9Fp7DvM0zbmGWrskv4FoQvsozhiCmO19nKlLd0YVZo9p8Pg3YhKbV1Unww3TRpxknu7GVPUGHhk3faKl/KZlgzkcn2Qme+jEtCYaUndm7zJIFRzR3OmRYyM2bNSFh0nc4vsGwB/07xG8fv/xJ
*/