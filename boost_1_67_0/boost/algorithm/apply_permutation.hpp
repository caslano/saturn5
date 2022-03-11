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
#include <type_traits>

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