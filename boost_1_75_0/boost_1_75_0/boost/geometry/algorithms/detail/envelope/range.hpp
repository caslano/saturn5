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
MfdT9tx2hgAXLOjTMKhciCqx7cXsz1LyZ4dtScPwxJ8dHHkST8Lszxdx1E3+LeVk2b/TkjHKCK7OTRQ1YLsIDZ6SM/sBIV+sknKApatXWsUG9VXtXhHXqUWOTucjuN3R6Nppc0/Gbe5j3g3uuCvsmOdrI7f9s6SMx3BwQ0bcHxZrhGYUF4l0VunwOx1sb8Ot+Rx0d4Mx80mqgNSkNER2RW9mm5b3Ha4HLoFIB4TfQ3BLll1G0o7cL/lsY1WoN60KrBdyy9DTMJ86XWu+Y4zfO1bDauwpXoeXCh+K07G8UZqjdAIblu0YneyMOJZqLnWO4pcKtCdcEa0QumNMXAvDrZz2AYWw7o7Pgbl1Jfaxfg7laYLyzO5THiGP2yOlQeQqBHV8Jqowj8dOOko6knXhmVrmNBnl4nJbexMrfMVFSZe09d0fug/2SvhRanhjmMFyWOpX3Kdsel+x/kE3yb6ibsamcx+C9NaCFApBfS6FvqILj8a32meTTHTYYpJU6cRCL8G/h3v6nKZiVD4VjTd2Fi5DtU+LPbIMlqmHpBSbXKR8rUa07Y7Vzk533Bv2tXu/cgddu23+aEZBMBxqD36VEfT3ZEXDBdnhSHv2V+Fg1mic83rWtmhxXjw3lhXz78Oucud+zanGZCc0kh3nVxWUFYaKsgofLp4TbykrL49NbSybHI8VHiwIxorEF+jU2aLvyGmKQ3NneUMu0leL
*/