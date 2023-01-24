/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  none_of.hpp
/// \brief Test ranges to see if no elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_NONE_OF_HPP
#define BOOST_ALGORITHM_NONE_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn none_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if none of the elements in [first, last) satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool none_of ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( p(*first)) 
            return false;
    return true;
} 

/// \fn none_of ( const Range &r, Predicate p )
/// \return true if none of the elements in the range satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param r     The input range
/// \param p     A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool none_of ( const Range &r, Predicate p )
{
    return boost::algorithm::none_of (boost::begin (r), boost::end (r), p );
} 

/// \fn none_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if none of the elements in [first, last) are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool none_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return false;
    return true; 
} 

/// \fn none_of_equal ( const Range &r, const V &val )
/// \return true if none of the elements in the range are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param r     The input range
/// \param val   A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool none_of_equal ( const Range &r, const V & val ) 
{
    return boost::algorithm::none_of_equal (boost::begin (r), boost::end (r), val);
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
IYR8yDx/V06HKNTM+O8vVlo5NTMji9+spE5yBLVC5vlDeDqMR3Toyji1HJeqtRi3+gzoMc+jYqIzJMRHzqIEOBCz7R622mnq3QYMvKy4kEalWo7qOlZXJoWEwGQts/yhjzoyGEkhnW7VZpRU0Lf+fMoeTwtCfjBgWsnaWd7BYQ8ed0PRlkoq2esSLOsq/+CQ9QJ8cMjz6gT6ldv+NASBJJEBDw69BF9EgNXr16agi5rdIdi6x9ArPzA1M/GUDuYAccqI8u4RfJnzFQKh5MRGrR7s9giCxoeQtn5R5ooxHO5SCYJyYnVfcyFOsPoN/6xYYPYreHJIEjgxJJ31ggJxohe+tGic6IIcQaS4SQMfakRoovadpA8WMaD+fi92FIVFIGc52pPpBSI52QMfO38+4UGRUP9skRJOy7GLxBIlOkrxz37kr6n7l0nDYqGkQnpU6G2jPT77tY4VpOOsiSEke3mNpO00KSFce0ZuZaxCTChDoz21ODqe3z8opfyModbxlP7QOiqKwJ92I0mAPNoT4ayi+kEKlBIiuL+lzV/KjIIbZb4N4j+iRPkndkqylkPig338T9z9vCpSVsakEMD+lhL/F90PGcM9q+900hhRpsZEf5FmMaPE7Bv5dbIqxP/k2/uHOGJFCRsRJePXTmFAx93f4uE/YkfR/7fAihUFzQsKAd7/JGEH5H3gchc6yr7CXjTNFMhZcX7b8Tpb
*/