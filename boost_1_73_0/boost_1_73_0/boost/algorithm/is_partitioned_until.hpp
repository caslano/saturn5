/*
   Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.by>, 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned_until.hpp
/// \brief Tell if a sequence is partitioned
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename InputIterator, typename UnaryPredicate>
InputIterator is_partitioned_until ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return first;
    return last;
}

/// \fn is_partitioned_until ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
///
/// \param r        The input range
/// \param p        The predicate to test the values with
///
/// \note Returns the first iterator 'it' in the sequence [first, last) for which is_partitioned(first, it, p) is false.
///     Returns last if the entire sequence is partitioned.
///     Complexity: O(N).
template <typename Range, typename UnaryPredicate>
typename boost::range_iterator<const Range>::type is_partitioned_until ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned_until (boost::begin(r), boost::end(r), p);
}

}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_UNTIL_HPP

/* is_partitioned_until.hpp
E6dRnwTnce8d85FJ5ExwM5PVlvtXvbLYv5KpoZJubWEFMf4OO7MN1RyAqPJEEx5XSoAAcSOAr+tFVl2uiusf1IsJQY0rxE87C3qwGT1Zrd7j9rDpLObGGKtnb6Hod9/2idWUWyedBP9uSVQO3R3Y2eZoOHzdi2wr3SZ+JzudB+U5Fc51Ni8as1tWsS1tUeSzt2V9wXf5rRHrNRSh1ZVdC4B0krZkwNmRb18MSKJ2wzK6qxpw4LAEBBN43mZTCRgpHh7yvHKiogpv7+qu5AWbVGwpz6B/F8ISrk7vLBxQxxKG6conBlAqBUBp0stwWim0Cd0Va8OhwVTa0W+fidfoft65wzEs5yReRg96gwgrWyxFrB6eYrFkqkmCl7OsalhD/q74iz3VGcxb/i64PCW39VlRslxEjTisVrInLRRimY/NAkby2sZZN4OVuqGjF7ti9KhzlkRhJzW4bdD97XN8mVfFpDGrCXQtr0mph8+kXHkl0EZWw2ReMVSJ3jWH4yg96+rcNSn+9tm7LlZXGIF/eJ1XefM9u17NdjjVin1upzoewXoX/jpvUhNF6OzazuY5hi1hnoRBlPK8te7B/S7koZxtLi9x2xEnd9+TYR1S36nolyVD7tP0AkjZq9lo63S9Wlts2vTqO7LgTs9P
*/