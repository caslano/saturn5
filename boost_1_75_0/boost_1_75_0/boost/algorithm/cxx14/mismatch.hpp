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
yYI7zf6BKDLh85QZATNEaM9jskXw8tDPxy8X/OAF6noVefDS9jhveFixqe64F7Gpdrn4fo9q2BOo0OAP3Q798sKFfNPHCaQWQn5cEMO+CDnyedkO030CALOw/oTBHKNP/qEM8p33wuRFwq76UO0lp/FEyTSUkbcTp92e4nIrPvTYfjCjdTK6EQ82lHRlR8zGXo8+oi99EQtmoWwlCiocprhPRCDeX5BRKhUi3x4GDDWHUv4j/EATDnNUcJm3J+7lwYI3USjd+t/0wV/27E7J+RH8OooG+5p+9Be76qmXXQskyX8/xwrdRwTRLRsf6DN+11Bp3x/9+C4V7VDO+w3bvvwvW0y6E64mW/+WeyZUAvPOjp2GhO6GdNCnmWkOm56FrR82EU+xpKsUHYiFiurza/3DD1xPS+ebj8gG3YVR2Z209uUTGfFv+kWfS5o6CkQGZdiUZJTf2exnIys6SbyOR2aIhy3/pRPT3Y4XcIKbGV+avJqldcPlzjqoHkV+NW4WReJp+/UfR3RhquZei+1D27nD48H8zg9oQCc4TXnlr06EVHk+/Mvf2LA1lAsOWRCgjXAlm9lTOQ3h/sLu4ZErr0t1tXh/XGC2i9uq7gmhuTKacwpsIqP3emwwFhBLuWqd7KMkJ01RnjNUGJ+NJsi+a9jgthBxP0VXH1y7ZVlpiGEzyvyOnfkjBxzDZeGi2N5X8Zfyea90Lvs0vz5j
*/