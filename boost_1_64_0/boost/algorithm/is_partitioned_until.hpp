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
PiHSjzg1yL70gAuZO8wGgjoGVJ5Ouj5pNqkc0k/boDse9qwXkdZm63uimAoKuOz5fgDStyV9B6ao0jyCi40GT3EFhrlyB4PdHxYUwn8wGkPS7WXIZr1wSg4s4313WGN9AigCunLxjHl7conJvR0fzrE1f9ml4GH937a6lBMDi+g/wTNKdHbnK/4xjh8Ik7TvqvjrLEcXhuMFENL6grnVxr7EGHnlicoHn0/tkDF+hjg4pUQW+LdQwHgKBmljXeOlkTVi34iBMAg1yc2HeTbs0+VL9bgGWBLgqs5MpU4HxvLzNzc9FM1LEHz0VTSGv2RMQStswgz4US40lOZk+MSJH1D5HhnymB7h2mfGrGmwHtgHk65/H2brAbrYVRlI7cBMUiQPaJHpZZtWK7ar+pBlw01+zjOvxVpsJPguldUjuyXQbr5XXT163pzXwz/h+ICk3cLPTXgq7wI1SZS41niBtyTCwmJCu+EKjMSBXuCiWjJ4tqgjpW0N2S+SegS4lmjc4EreW0F/4aMeTU/j9IgEJIJo6k+z6oN+lKlqzTMS2N1FyYCTeoy7yV0BZw==
*/