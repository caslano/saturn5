/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  equal.hpp
/// \brief Test ranges to if they are equal
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EQUAL_HPP
#define BOOST_ALGORITHM_EQUAL_HPP

#include <iterator>

#include <boost/config.hpp>

namespace boost { namespace algorithm {

namespace detail {

    template <class T1, class T2>
    struct eq {
        BOOST_CONSTEXPR bool operator () ( const T1& v1, const T2& v2 ) const { return v1 == v2 ;}
        };
    
    template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
                 RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
                 std::random_access_iterator_tag, std::random_access_iterator_tag )
    {
    //  Random-access iterators let is check the sizes in constant time
        if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
            return false;

    //  std::equal
        for (; first1 != last1; ++first1, ++first2)
            if (!pred(*first1, *first2))
                return false;
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( InputIterator1 first1, InputIterator1 last1, 
                 InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred,
                 std::input_iterator_tag, std::input_iterator_tag )
    {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2 )
        if ( !pred(*first1, *first2 ))
            return false;

    return first1 == last1 && first2 == last2;
    }
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2,
///             BinaryPredicate pred )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
/// \param pred      A predicate for comparing the elements of the ranges
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred )
{
    return boost::algorithm::detail::equal ( 
        first1, last1, first2, last2, pred,
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2 )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
template <class InputIterator1, class InputIterator2>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2 )
{
    return boost::algorithm::detail::equal (
        first1, last1, first2, last2,
        boost::algorithm::detail::eq<
            typename std::iterator_traits<InputIterator1>::value_type,
            typename std::iterator_traits<InputIterator2>::value_type> (),
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

//  There are already range-based versions of these.

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EQUAL_HPP

/* equal.hpp
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
*/