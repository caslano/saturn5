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
T4N4pAt7BpaN2OPMWersT71zH+JMLHws5NIZQ1VJGFIr8UTpJqMuFcKgPIGZQh9NoMaTngoF1TYLSofV9gfVjgKl6wHOkskmTNeUNpCZJh/SUAd338MhXh6hA3MFHW3dSU/HMFa1ZE1RROUWDKlvU8JXmc/DDHNPC90iuTxr03T361Tdmy5e5KjGXvVY1wVnpfim6wRL2/eZA+icrvhvtVHeDDor2WimN7sO/whWV1MitWSuDA4muRr4x0FGvK5+kMHg/EzC8FH8HTJR5yUK8GRrOiCEfE4Md/azpq/IdzczCTXSsKA+Iilf2lYeLnhpqzzR7/mT3uFHnIlvEeb2hOsZXMcKhASL1u3b/YmAEl+nwhRUlPp4M+KQYjJA1NVPiUPhEYc9yaLL92tuqEkUJeJu7zjdHXfxXc8wiS3fj3LJ9/vwZofkqvy96m+y8EFHoaRbz0jSx/CS57JG8ZukeN+hge5uhmNlgWNW6a6f3MtB9oM8uq3kxpHQGBTXax9MjeZhcfI2feIXxsijl2TixJ3Gt5ZMOyr0XNfONsz9X75lChS/wr+PzjSQISSSCb4tX7PQfNBEQnLpva55O45OUbGERCio21dHCGC7Sjad/4bEH9v3VsvavSfh/WQNCqr+3IqzvYQUDxtSCa5yzXsp9F5BHjqM7/Gl1zT9n8oFSb/ig6tJkL5Noj9cZGAM2lL+uUKrkB9ilhCa/ID0
*/