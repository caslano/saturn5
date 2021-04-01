// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP

#include <cstddef>

#include <algorithm>

#include <boost/range.hpp>



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
    bool AllowDuplicates /* true */,
    typename NotEqualTo
>
struct num_distinct_consecutive_points
{
    static inline std::size_t apply(Range const& range)
    {
        typedef typename boost::range_iterator<Range const>::type iterator;

        std::size_t const size = boost::size(range);

        if ( size < 2u )
        {
            return (size < MaximumNumber) ? size : MaximumNumber;
        }

        iterator current = boost::begin(range);
        std::size_t counter(0);
        do
        {
            ++counter;
            iterator next = std::find_if(current,
                                         boost::end(range),
                                         NotEqualTo(*current));
            current = next;
        }
        while ( current != boost::end(range) && counter <= MaximumNumber );

        return counter;
    }
};


template <typename Range, std::size_t MaximumNumber, typename NotEqualTo>
struct num_distinct_consecutive_points<Range, MaximumNumber, false, NotEqualTo>
{
    static inline std::size_t apply(Range const& range)
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
oIZERDRZE4nk9m654BM8Nkj+zv0qC738X1GK3/DKXlJufV8KOG0RFeCnJbfUEG/COPsKS1hsMTz37zQYZXuAwiJyB3qT/+itOFlLpEWoapAWlcEMo+jOCWrIAsMAGgLPQhkW4TMniVTX60dcJPJeF+n2L7eZTl7QnhApaqzw/GZ1AqEgQizfy05n2JBwWjYbhhoyFnuoWL/UWWonGGgEHaUoe2EYKLJ7i9A3PZvlPhLOHhcZtMQNp+kdTWadeK6LcdD+QW0zq6jyeZ5hncpGb0WLB/lslZbQxSy3e2GkKVE12PKaDKFvaV8Y2gc42WUJG2rX+1GHnQp5y+/CnIkt2la5sht0Y0kTzvwLRvoArudZaznzc80DuCb6LWNDJ4ZgsWAg/xw+MKByaFDonUsfM4pBq1pDXHm6TIX6DUemAfZXh5QciS1dUQL/d4ONxd6fKXgCHojnjK+t5SXYJm1VcRqoGxxP6veVIAk4W9bURhTo2CzREHoP47/DmuSFdSw51Mss9q8Rclf9UqKHUKbnd/M2FFKOdGzm9lQxv7GQMij6kEwYcmlSkJBMFg==
*/