// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP


#include <algorithm>
#include <cstddef>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// returns the number of distinct values in the range;
// return values are 0u through MaximumNumber, where MaximumNumber
// corresponds to MaximumNumber or more distinct values
//
// FUTURE: take into account topologically closed ranges;
//         add appropriate template parameter(s) to control whether
//         the closing point for topologically closed ranges is to be
//         accounted for separately or not
template
<
    typename Range,
    std::size_t MaximumNumber,
    bool AllowDuplicates /* true */
>
struct num_distinct_consecutive_points
{
    template <typename Strategy>
    static inline std::size_t apply(Range const& range, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        std::size_t const size = boost::size(range);

        if ( size < 2u )
        {
            return (size < MaximumNumber) ? size : MaximumNumber;
        }

        iterator current = boost::begin(range);
        iterator const end = boost::end(range);
        std::size_t counter(0);
        do
        {
            ++counter;
            iterator next = std::find_if(current, end, [&](auto const& pt) {
                    return ! equals::equals_point_point(pt, *current, strategy);
                });
            current = next;
        }
        while ( current != end && counter <= MaximumNumber );

        return counter;
    }
};


template <typename Range, std::size_t MaximumNumber>
struct num_distinct_consecutive_points<Range, MaximumNumber, false>
{
    template <typename Strategy>
    static inline std::size_t apply(Range const& range, Strategy const&)
    {
        std::size_t const size = boost::size(range);
        return (size < MaximumNumber) ? size : MaximumNumber;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP

/* num_distinct_consecutive_points.hpp
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
*/