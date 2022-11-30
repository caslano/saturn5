/*
  Copyright (c) Alexander Zaitsev <zamazan4ik@gmail.com>, 2017

  Distributed under the Boost Software License, Version 1.0. (See
  accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt)

  See http://www.boost.org/ for latest version.


  Based on https://blogs.msdn.microsoft.com/oldnewthing/20170104-00/?p=95115
*/

/// \file  apply_permutation.hpp
/// \brief Apply permutation to a sequence.
/// \author Alexander Zaitsev

#ifndef BOOST_ALGORITHM_APPLY_PERMUTATION_HPP
#define BOOST_ALGORITHM_APPLY_PERMUTATION_HPP

#include <algorithm>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm
{

/// \fn apply_permutation ( RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end, RandomAccessIterator2 ind_begin )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_begin    The start of the item sequence
/// \param item_end		 One past the end of the item sequence
/// \param ind_begin     The start of the index sequence.
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename RandomAccessIterator1, typename RandomAccessIterator2>
void
apply_permutation(RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end,
                  RandomAccessIterator2 ind_begin, RandomAccessIterator2 ind_end)
{
    typedef typename std::iterator_traits<RandomAccessIterator1>::difference_type Diff;
    typedef typename std::iterator_traits<RandomAccessIterator2>::difference_type Index;
    using std::swap;
    Diff size = std::distance(item_begin, item_end);
    for (Diff i = 0; i < size; i++)
    {
        Diff current = i;
        while (i != ind_begin[current])
        {
            Index next = ind_begin[current];
            swap(item_begin[current], item_begin[next]);
            ind_begin[current] = current;
            current = next;
        }
        ind_begin[current] = current;
    }
}

/// \fn apply_reverse_permutation ( RandomAccessIterator1 item_begin, RandomAccessIterator1 item_end, RandomAccessIterator2 ind_begin )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_begin    The start of the item sequence
/// \param item_end		 One past the end of the item sequence
/// \param ind_begin     The start of the index sequence.
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename RandomAccessIterator1, typename RandomAccessIterator2>
void
apply_reverse_permutation(
        RandomAccessIterator1 item_begin,
        RandomAccessIterator1 item_end,
        RandomAccessIterator2 ind_begin,
        RandomAccessIterator2 ind_end)
{
    typedef typename std::iterator_traits<RandomAccessIterator2>::difference_type Diff;
    using std::swap;
    Diff length = std::distance(item_begin, item_end);
    for (Diff i = 0; i < length; i++)
    {
        while (i != ind_begin[i])
        {
            Diff next = ind_begin[i];
            swap(item_begin[i], item_begin[next]);
            swap(ind_begin[i], ind_begin[next]);
        }
    }
}

/// \fn apply_permutation ( Range1 item_range, Range2 ind_range )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_range    The item sequence
/// \param ind_range     The index sequence
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename Range1, typename Range2>
void
apply_permutation(Range1& item_range, Range2& ind_range)
{
    apply_permutation(boost::begin(item_range), boost::end(item_range),
                      boost::begin(ind_range), boost::end(ind_range));
}

/// \fn apply_reverse_permutation ( Range1 item_range, Range2 ind_range )
/// \brief Reorder item sequence with index sequence order
///
/// \param item_range    The item sequence
/// \param ind_range     The index sequence
///
/// \note Item sequence size should be equal to index size. Otherwise behavior is undefined.
///       Complexity: O(N).
template<typename Range1, typename Range2>
void
apply_reverse_permutation(Range1& item_range, Range2& ind_range)
{
    apply_reverse_permutation(boost::begin(item_range), boost::end(item_range),
                              boost::begin(ind_range), boost::end(ind_range));
}

}}
#endif //BOOST_ALGORITHM_APPLY_PERMUTATION_HPP

/* apply_permutation.hpp
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
*/