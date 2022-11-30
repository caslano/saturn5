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
#include <utility>                  // for std::make_pair

#include <boost/config.hpp>
#include <boost/bind/bind.hpp>      // for boost::bind
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
    typename BidirectionalIterator,  // models BidirectionalIterator
    typename Pred>                   // models UnaryPredicate
std::pair<BidirectionalIterator, BidirectionalIterator> gather 
        ( BidirectionalIterator first, BidirectionalIterator last, BidirectionalIterator pivot, Pred pred )
{
//  The first call partitions everything up to (but not including) the pivot element,
//  while the second call partitions the rest of the sequence.
    using namespace boost::placeholders;
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