// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP

#include <iterator>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/envelope/initialize.hpp>
#include <boost/geometry/algorithms/detail/expand/box.hpp>
#include <boost/geometry/algorithms/detail/expand/point.hpp>
#include <boost/geometry/algorithms/detail/expand/segment.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


// implementation for simple ranges
struct envelope_range
{
    template <typename Range, typename Box, typename Strategies>
    static inline void apply(Range const& range, Box& mbr, Strategies const& strategies)
    {
        strategies.envelope(range, mbr).apply(range, mbr);
    }
};


// implementation for multi-ranges
template <typename EnvelopePolicy>
struct envelope_multi_range
{
    template <typename MultiRange, typename Box, typename Strategies>
    static inline void apply(MultiRange const& multirange,
                             Box& mbr,
                             Strategies const& strategies)
    {
        using strategy_t = decltype(strategies.envelope(multirange, mbr));
        apply<strategy_t>(multirange, mbr, strategies);
    }

    template <typename Strategy, typename MultiRange, typename Box, typename Strategies>
    static inline void apply(MultiRange const& multirange,
                             Box& mbr,
                             Strategies const& strategies)
    {
        typename Strategy::template state<Box> state;
        auto const end = boost::end(multirange);
        for (auto it = boost::begin(multirange); it != end; ++it)
        {
            if (! geometry::is_empty(*it))
            {
                Box helper_mbr;
                EnvelopePolicy::apply(*it, helper_mbr, strategies);
                Strategy::apply(state, helper_mbr);
            }
        }
        Strategy::result(state, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP

/* range.hpp
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
*/