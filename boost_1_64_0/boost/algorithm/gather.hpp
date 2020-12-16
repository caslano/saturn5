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
SAJkg78g5nkOAoBLEtoIJR0ilESTIZCIt2C4rI7ElyKbDIavr0cDOtLrYF9b7UuP+irHv0+ysLD/FabRbQgwkb5rSLL872EC5E8f4IU/bccLf/rQV+n/yE9HGBtRK5S3Lpj3ITqoHpKqVaQfRWOvYhJGDaQp1fqRCSx7qxbZ2ysEBMQEf7D5KrFaKnjl+I941ASTtg3oplRmDFSNQYMyVdyO8mArGCsfBjPaBkNQ5zCySRHkSnSHGyI6h69yVGJlqVMyIqEJsvFBZFJ5QbISviTBtMMd/yXJo8WzAUhlsjn4/lMsC9u7PxSXPqoRXrPQbb97fFoPbI8rXNCsLoMHbTh3cSTQzX2i/6bVPKDs/dqXt1lbZbxjHXOU4nky6sdqDwJBbSUU67WvsOpqWo8FmhKZTwgUTyCqhBNgvLS3AesmJVzs0kpc5jtEZuMyzExVe6bfLb/iDBi3lp+olTTDe00Wwt7YCq3kCLwcAZvVrND+VM8dmeCcWpmLHExp1DYaNQtZlIbBjRfSii1c5tYir9DLQv4bqTMmDu/336XcXzAyDkbGgsPhsC4aTiTumJpo8MLwCBfxwlR+uBChMECSwhDJDJGBt5RUfrg5wou31FR+pHHEEXhLT+VHBkcQq81MpUegGzhF+NxeCpiOJz0aHtELGjOREdmiD+kn51b1fu2ibxVtdfTd1OiOlPR1YDSpnudXhd1+7VwXOijamKJAMI/PWKiHVUSNdWurEOtLXxl9L1XhWACPyFC0OkSnrxIMiM0ArNeAjQpsHcyxAHuECctwCI1tDn2TNOdMjRPjSyC0LNtIFG1KidVQUiV9A8y2qGxqLzL3D32T7LmjEBTAff/9d+er/oL18JEKVS0X2EyNeGh+gQjWWF9hAwMab/blrcLmyQiwuEtbB5LHxgF3ctM+RFtP9L5wpVA7iL3mwPPr5+9Z52fmfZOqto713CLq9ljPt3KPSrB7VlWq7knkI+Wmo2Gj5WUl8sdEixnbn00q+RhPen4SueNU3HKgGc58bFLPLisOttT/ltKFhpUDAxzcdwfC0LBRHFjoYuPEzM0I8V20tUkFeKUs9ZlIx36y/z5J7Ckb3wUiNNdppHeVpGswLQnd6qLXvbtIlWaSGDoeiUqxsT07dzju04uRGqlOunJRrIfoxX6RRRAXu5Wq+5FE/ysBYqLaRvZfgCZHdcdV4UWvfGl3bMhx/ZE/MtlZQ4FdiEegbCUFnpTAee+zTUJPwOlXP7EbFhqb8Ofm5/Dnwk/xZ+of8Oext/Fn+U78WfMx/twD5ZvwcT+iwmmod1dVhA/qJ/qwxv0X24xe2HgRGl6uISg/OzTsYpQggf1obz0KdkBJKsIONqfzkUrFfrxDj+jIiPqO/ivWcEJxrdv9MMsUF+wZMuhXwFlxClr2lmTuzpkI63k76FRcW+PxZ96GMLlFXwWyK95T6ygn2B+nMexVBBtrtGAvM2AfFthEhp2eyrBFBLshDjvYgJ0usF6G/YnAnkCwj1mwCAvsOQLrYtivnQz7+YWAvTUO+xHCfHWjwGYzbF/Bu5ZgR8Vhaw3YTxwM62bYRBfDPkqwJ8dh7zdglxHsgtjNBHqUoF1AoM26BTrPAL1f0BaXTwB15hHQi68Iuaaq4UF/RASp/TthzfMw3oHvqiTGN5BAHwc+JPtiInBVa1s9/uN6U3QvaIhgU7SgiAaMZ+lH7hlUkH9IW6QTxA3xgjiNgnQzgNMZuL909A5g1kfEgbdOFOB3EwQ4lYFfEeDlBNwzDvyCAfyMAZzGwDOl/EsIWP/IAr7XAP6pAdxtxkkAThPMtxLwi3HgGxi4/FICzGTAqHTIRQT48zjgeQI4SN1bm7A/gcY=
*/