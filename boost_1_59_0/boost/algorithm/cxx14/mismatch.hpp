/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  mismatch.hpp
/// \brief Find the first mismatched element in a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_MISMATCH_HPP
#define BOOST_ALGORITHM_MISMATCH_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn mismatch ( InputIterator1 first1, InputIterator1 last1, 
///                InputIterator2 first2, InputIterator2 last2,
///                BinaryPredicate pred )
/// \return a pair of iterators pointing to the first elements in the sequence that do not match
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
/// \param pred      A predicate for comparing the elements of the ranges
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2> mismatch (
                    InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, InputIterator2 last2,
                    BinaryPredicate pred )
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if ( !pred ( *first1, *first2 ))
            break;
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

/// \fn mismatch ( InputIterator1 first1, InputIterator1 last1, 
///                InputIterator2 first2, InputIterator2 last2 )
/// \return a pair of iterators pointing to the first elements in the sequence that do not match
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
template <class InputIterator1, class InputIterator2>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2> mismatch (
                    InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, InputIterator2 last2 )
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if ( *first1 != *first2 )
            break;
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

//  There are already range-based versions of these.

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_MISMATCH_HPP

/* mismatch.hpp
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
*/