/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_partitioned.hpp
/// \brief Tell if a sequence is partitioned
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param p        The predicate to test the values with
/// \note           This function is part of the C++2011 standard library.
template <typename InputIterator, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( InputIterator first, InputIterator last, UnaryPredicate p )
{
//  Run through the part that satisfy the predicate
    for ( ; first != last; ++first )
        if ( !p (*first))
            break;
//  Now the part that does not satisfy the predicate
    for ( ; first != last; ++first )
        if ( p (*first))
            return false;
    return true;
}

/// \fn is_partitioned ( const Range &r, UnaryPredicate p )
/// \brief Tests to see if a sequence is partitioned according to a predicate. 
///	   In other words, all the items in the sequence that satisfy the predicate are at the beginning of the sequence.
/// 
/// \param r        The input range
/// \param p        The predicate to test the values with
///
template <typename Range, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR bool is_partitioned ( const Range &r, UnaryPredicate p )
{
    return boost::algorithm::is_partitioned (boost::begin(r), boost::end(r), p);
}


}}

#endif  // BOOST_ALGORITHM_IS_PARTITIONED_HPP

/* is_partitioned.hpp
bA7gyI3evund8o6xEdQkhjrYUkIEOQkooC05EF9yaD7BvkbpbesngFsw/GAgy0mlzmBoauUokgBqh1qLAnsQb5pToneUugqyRYVx9qKok96FpvvAK5qw8VkwLeZ0Ibv8/rBarNL1j8vft0lytbxdpFerx+z412B/AVBLAwQKAAAACAAtZ0pSM7CXYaUJAACoFQAAHAAJAGN1cmwtbWFzdGVyL2RvY3MvQklORElOR1MubWRVVAUAAbZIJGCdWMty2zgW3esrUL3oGVciUpJld5yqrq5Y8SOObCuWO+6Z1FQXREIiJJBgAFCyvJh/6eUsZjur2fnH5lyQkihbibsmlUQEeHHuA/dJJUdRYRQbySyW2cQ2fn7yp9FgPSO4k3PBcqFzJVjC8bww0jmRrQ8ybZjMnDBjHgnLxljOuZG6sExkc2l0lorM2QbjWcxyoyeGpykOMsWzScEnwgbsV0sbOhNMj5lLhBWMK6UXli11wZxmjs+wFc955nACVA3mpc/1QhgwNTplC+kSmdEJw8Z8jh/pxJoLiWmX1ok0gGa3ibQMfzlT0jriCn5slulFVleG21IgUJLaELI8LDba03kRs5GAuIwbwTLtWM6Nq1TxcoaqsnYMaiNHhZM6g0VMlMC89jXDDksLSDISLIYQ
*/