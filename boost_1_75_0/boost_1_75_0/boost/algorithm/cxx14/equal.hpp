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
0mAsUv8dU694ZipbcmSa/mb+LQn7TOcWodv33MUyhtwNOmWGN3DB3B32T/e+mnkyYD+Edrpc/KMPb8E0+N/4f80r3UCrFcI0FKtmPbYg5A5OI14q7yzvY+1HlULoj0suTrqOynylWHDpbLrki9rxTnhZffF2qQEEJSCkZqftVdbgx+/CIdhpeJjawVUx/Xw9xImLjO9V9XG1wfRqlxo7S29HbrVX26rmbmeexFwA4GzzVARSFLR25YAFVtGqFNkVukT+vDakg+d3+Jh5XCURufunDQe5IwSnMVl6IzBSSG4r/U3CZ+fz2GepCgzuP8wM/s37uFxwQpbh6bsHRF4gXQCyOmJv5K/S7hItJRWG/RH5wdWU2x94EB5q2RhKee0NsZOURYPIIeZ3csQ41Fe1zWYEmpFoImBT6YbeXM/nwIPKq8Nv2ErOBHilOVcnc3+UkJoBlRIKrx9ZEc4O1IccWEFxrxRy99+D+FSSZGxlkKGa2ybcajVVz7n5R9uuvZnqcq6HH7KXQy+AUAbc7RFoRA0zyg/ugLAf3X0yCWEmKApDAByZzesdHmpdbAbDkIGGjN3gPfRsYEZhUw8yvgrL5b2d29dMypanNhdlIkYXeWJPfyn/k1g4cR1jqSlKDhaTOPs8Ajc4MPUdvCsXy/DLodZJ1BjrVfbYkGuE8U7ZMq35hX/1FQ1Zdi/7LKEUuMWX1feR86fWuVbgUMLr
*/