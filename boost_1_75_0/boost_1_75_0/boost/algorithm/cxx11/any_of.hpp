/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

/// \file
/// \brief Test ranges to see if any elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ANY_OF_HPP
#define BOOST_ALGORITHM_ANY_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn any_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if any of the elements in [first, last) satisfy the predicate
/// \note returns false on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool any_of ( InputIterator first, InputIterator last, Predicate p ) 
{
    for ( ; first != last; ++first )
        if ( p(*first)) 
            return true;
    return false; 
} 

/// \fn any_of ( const Range &r, Predicate p )
/// \return true if any elements in the range satisfy the predicate 'p'
/// \note returns false on an empty range
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool any_of ( const Range &r, Predicate p )
{
    return boost::algorithm::any_of (boost::begin (r), boost::end (r), p);
} 

/// \fn any_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if any of the elements in [first, last) are equal to 'val'
/// \note returns false on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool any_of_equal ( InputIterator first, InputIterator last, const V &val ) 
{
    for ( ; first != last; ++first )
        if ( val == *first )
            return true;
    return false; 
} 

/// \fn any_of_equal ( const Range &r, const V &val )
/// \return true if any of the elements in the range are equal to 'val'
/// \note returns false on an empty range
/// 
/// \param r     The input range
/// \param val   A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool any_of_equal ( const Range &r, const V &val ) 
{
    return boost::algorithm::any_of_equal (boost::begin (r), boost::end (r), val);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
7EstEU6OhidmzYOirt7mFdWr1WFwyccOI1k61C6QwGzPvx7PUVd32Pcv4KqTLtHNDMM9E+xx0NKQuzTHiz/nqtm5c/eSSvMLpaYn7s4jdlo+zamNClWAH+F83XOwCR42lCc0w0Bxak26IfukjbRMGo7xe2xg81X7xmpakmR1pE9J+GvGL/5i6h6qpvPWnTu3lJ7zE9/B14NiuJHDqDMSEGrPDHXjaal3BcWZccGw6H56NRnqJKyExKMc1dCsH1Qsdceq6v3HONtUz/hTaQmD7deRe74tykkXZY2O7RLTVB80fyD9Y35WNIBPXM4oG2pdZp7N/geyopiq/n7fyXyrFrtxm8MakyZxJPaYIortllhre4kxRzo8We4S94N8fi7YjbegO8XLOSzM5Roy9MZth/BE0fKItVwq5p/ovC/KcndBvikScVzcAy/Sy1IHOvAtNnq3ZBQLDVhPCYgrSvqlDhXN0g0Rdr58FYDSI+CsJOrYN3iIe4OUf8SY7yy+NBozZEJwakv5p3zA5DvmdTpCSzPjZg+is2rCODztH4pao1csTrOWvPmqnn8IuetvENsjvaN67uR7eVIwQlnokH8gg+g09p/sunUWzJFBmh/8RKcomRZah3S7rpyDT2Z4KagpUg4WiPMDHaEX0atScEXnjQ6d+tz5js6bl/HVHYFTXv/aev9Rau0qYXPJnnjBDUEJB9oOvjyQkPXLTT8X
*/