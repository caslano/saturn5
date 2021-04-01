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
ASTiJUXOs0N8j45nuqOekRRbXxNR40Z3mgQJFiEE2aQXvIjtluYVMSKjTC+yHDJfL0qyfyzjClaOkYqaTs7gUKNU5twHSKUUpNdwhMHMAUhtQlT1iMv3hPREyXKBCxH2T7Xnk2YuvPGBH6KraLYIP48V3X8S6/IP4zbA0a3Jo9sw9VLpF4u6Pi4KGuA95iKR2tJw/yIs5wRKas4JCG1bjtqFTuPCjEz+2FHbWDeW3JATkRAcEvX45+k3fIMBD2vAobF11FeUH3+YHx3Yw7v6M7sZAghCUnIhAPl2ldP2h7V2Q3i1M+7WoKv/GYLvWCmWps4QYVykRXmOtymzxLXe8GSOw5Lsy+L/6+KY0k13j5cHRbdgBmkzh23FzsD8pXK7nHTS7BEk6LauimlyoZqxO3aE/veNp1Xwsh01X0lQPUGHbEI8Ijd7B/3SiEO1dO2Jcm7ZHtbhJwjngrSoNyTDhfrFd56FwSnlZJ9zt2Z5FGraPsTe4mYdz7Gkm7WTE+UPcSlhyf/hD7CIJMoOZGxKrWKhCImNcmz43oFIILkavZnAXYT8nHsPYwGqLw==
*/