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