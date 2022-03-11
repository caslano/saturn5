/* 
    Copyright 2008 Adobe Systems Incorporated

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
   January 2008 mtc Version for Adobe Source Library
   January 2013 mtc Version for Boost.Algorithm

*/

/**************************************************************************************************/

/*!
\author Marshall Clow
\date    January 2008
*/

#ifndef BOOST_ALGORITHM_GATHER_HPP
#define BOOST_ALGORITHM_GATHER_HPP

#include <algorithm>                // for std::stable_partition
#include <functional>

#include <boost/config.hpp>
#include <boost/bind.hpp>           // for boost::bind
#include <boost/range/begin.hpp>    // for boost::begin(range)
#include <boost/range/end.hpp>      // for boost::end(range)


/**************************************************************************************************/
/*!
    \defgroup gather gather
    \ingroup mutating_algorithm

    \c gather() takes a collection of elements defined by a pair of iterators and moves
    the ones satisfying a predicate to them to a position (called the pivot) within
    the sequence. The algorithm is stable. The result is a pair of iterators that
    contains the items that satisfy the predicate.

    Given an sequence containing:
    <pre>
    0 1 2 3 4 5 6 7 8 9
    </pre>

    a call to gather ( arr, arr + 10, arr + 4, IsEven ()) will result in:

    <pre>
    1 3 0 2 4 6 8 5 7 9
        |---|-----|
      first |  second
          pivot
    </pre>


    The problem is broken down into two basic steps, namely, moving the items before the pivot
    and then moving the items from the pivot to the end. These "moves" are done with calls to
    stable_partition.

    \par Storage Requirements:

    The algorithm uses stable_partition, which will attempt to allocate temporary memory,
    but will work in-situ if there is none available.

    \par Time Complexity:

    If there is sufficient memory available, the run time is linear in <code>N</code>.
    If there is not any memory available, then the run time is <code>O(N log N)</code>.
*/

/**************************************************************************************************/

namespace boost { namespace algorithm {

/**************************************************************************************************/

/*!
    \ingroup gather
    \brief iterator-based gather implementation
*/

template <
    typename BidirectionalIterator,  // Iter models BidirectionalIterator
    typename Pred>                   // Pred models UnaryPredicate
std::pair<BidirectionalIterator, BidirectionalIterator> gather 
        ( BidirectionalIterator first, BidirectionalIterator last, BidirectionalIterator pivot, Pred pred )
{
//  The first call partitions everything up to (but not including) the pivot element,
//  while the second call partitions the rest of the sequence.
    return std::make_pair (
        std::stable_partition ( first, pivot, !boost::bind<bool> ( pred, _1 )),
        std::stable_partition ( pivot, last,   boost::bind<bool> ( pred, _1 )));
}

/**************************************************************************************************/

/*!
    \ingroup gather
    \brief range-based gather implementation
*/

template <
    typename BidirectionalRange,    //
    typename Pred>                  // Pred models UnaryPredicate
std::pair<
    typename boost::range_iterator<const BidirectionalRange>::type,
    typename boost::range_iterator<const BidirectionalRange>::type>
gather (
    const BidirectionalRange &range,
    typename boost::range_iterator<const BidirectionalRange>::type pivot,
    Pred pred )
{
    return boost::algorithm::gather ( boost::begin ( range ), boost::end ( range ), pivot, pred );
}

/**************************************************************************************************/

}}  // namespace

/**************************************************************************************************/

#endif


/* gather.hpp
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
*/