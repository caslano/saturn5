/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_point.hpp
/// \brief Find the partition point in a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_POINT_HPP
#define BOOST_ALGORITHM_PARTITION_POINT_HPP

#include <iterator>    // for std::distance, advance

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
/// \brief Given a partitioned range, returns the partition point, i.e, the first element 
///     that does not satisfy p
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename ForwardIterator, typename Predicate>
ForwardIterator partition_point ( ForwardIterator first, ForwardIterator last, Predicate p )
{
    std::size_t dist = std::distance ( first, last );
    while ( first != last ) {
        std::size_t d2 = dist / 2;
        ForwardIterator ret_val = first;
        std::advance (ret_val, d2);
        if (p (*ret_val)) {
            first = ++ret_val;
            dist -= d2 + 1;
            }
        else {
            last = ret_val;
            dist = d2;
            }
        }
    return first;
}

/// \fn partition_point ( Range &r, Predicate p )
/// \brief Given a partitioned range, returns the partition point
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename Predicate>
typename boost::range_iterator<Range>::type partition_point ( Range &r, Predicate p )
{
    return boost::algorithm::partition_point (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_PARTITION_POINT_HPP

/* partition_point.hpp
J8vjnoGs2XqIqg0xdbitSOHTsPNVB7u77HwIf84xNM4YT9SATXxQ4NB01G+kFv+oNnm49vlSrkUypVJewHGE0wsgO7n14ChxyyOUPj8gq1R93SKLqvxWG2MbusPgu4NLfylA628aDK0l953HAZua10eYOSsgf/BFPwbupgu5fZhr+WhYaRaJSbkIBSSu6SAVz+wl8x54rpbgEWPbipMjXMXxI8eNUFavP0VH9RNSqbotm/cAwraHVGap9WyHM71nr555TD4eV1/5KG407muIVmlQy85CytMPoM0/8A34sFRpBa+TdXKv6STwsUW6a0FMzLO+SF97SRHsaXrW2d/aJu+IzjU/doLEDGUQyyBHXIVSrDhMJQ8q5uW6kcoNzGilr3l/EisYrY0t5QcY1KtHPWm/qcQOjSdLQakVmD/E2PcvacbfeseNLO2M5RhxBjpgI8RrpYtPBl+rZDWgF2EV2c/TGXHOv08UusmQznXvLheFjavh+U3gsvWK64nqEx5oyAAvxTfxQi8HdqTqCr4jVZiaiS92ISzas34d/wBWTIkkZEa7FfddV4jDbdEzforVpJexR8LOc3ejgFE76f4QBseRG4iTOXQ3ZRSdtHKS5LOiVZCwvFn8ukIimg6WvsGBv79yHqiOV0uUV8Fbkai4pjioctnLyOidZOWB2eimu3/H+5NTJl5a6xYdNBJAYZ64H8wik/w1CSopat6d
*/