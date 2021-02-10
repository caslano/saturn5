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
uely52NeFEf4GMzJtYOZI2Z7cka2hMGwabtvnaw7htY3ZhhDM9cTF3G2/WQ8F4GNb3ild66pOKUZ3RDGSTfMvw/+i8wEi/4qa8RL+gxmfzyYS5hNbfubiU8aK+9cZE/tQWef9x3msnL/EEZMvBEzlIHwmLGxgvkn61vXlMvRDCFGz33gYaub6/AMndD6KDuwbQv7ht7ROjADLp3sM/xjzRF3OTMMME8+9Fvzm67WhIF/49UL3o8hL5ILp6EwYwcnms+c8SaqZabR1k+cOV7i5Lq/356maYjfPjwc/XSa99s6dA98Xv/nY5xdvKOPfmmdhYtHZxtxDVw3cbHTyUfThHruHPyxd9zHwY+Rv2Eoh3ucjgj7w2Lsg3Ot/KDPxADxCcAJM2wtb2/wD35j27NXEHxe2+zvt5XJK+dKt9E98P7DnbgLFk92+B3rp5WiglMx8MHhHT9dcjjlRemMNFO4sqC4DJdytEm48A1svn+CpyIXmgatjO8GW3MHeMV9sd1ACKv1+SJdN8wT3OzGyOEbRCQiDE8L+rHQrjLPc9u7UXbuD2JxDrB3cBAieZj3ra/NUx/OwNoR+McTGDY7SaCXo7rCVDQc7ZFXmWlCvIat1i5KKBbTjK61k2s0grE0+VdGFDaa4+DqSX1HpK4M
*/