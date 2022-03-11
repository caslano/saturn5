// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

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
    template <typename Iterator, typename Box, typename Strategy>
    static inline void apply(Iterator it,
                             Iterator last,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;

        // initialize MBR
        initialize<Box, 0, dimension<Box>::value>::apply(mbr);

        if (it != last)
        {
            // initialize box with first element in range
            dispatch::envelope
                <
                    value_type
                >::apply(*it, mbr, strategy.get_element_envelope_strategy());

            // consider now the remaining elements in the range (if any)
            for (++it; it != last; ++it)
            {
                dispatch::expand
                    <
                        Box, value_type
                    >::apply(mbr, *it, strategy.get_element_expand_strategy());
            }
        }
    }

    template <typename Range, typename Box, typename Strategy>
    static inline void apply(Range const& range, Box& mbr, Strategy const& strategy)
    {
        return apply(Strategy::begin(range), Strategy::end(range), mbr, strategy);
    }
};


// implementation for multi-ranges
template <typename EnvelopePolicy>
struct envelope_multi_range
{
    template <typename MultiRange, typename Box, typename Strategy>
    static inline void apply(MultiRange const& multirange,
                             Box& mbr,
                             Strategy const& strategy)
    {
        apply(boost::begin(multirange), boost::end(multirange), mbr, strategy);
    }

    template <typename Iter, typename Box, typename Strategy>
    static inline void apply(Iter it,
                             Iter last,
                             Box& mbr,
                             Strategy const& strategy)
    {
        typename Strategy::template multi_state<Box> state;
        for (; it != last; ++it)
        {
            if (! geometry::is_empty(*it))
            {
                Box helper_mbr;
                EnvelopePolicy::apply(*it, helper_mbr, strategy);
                state.apply(helper_mbr);
            }
        }
        state.result(mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_RANGE_HPP

/* range.hpp
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
*/