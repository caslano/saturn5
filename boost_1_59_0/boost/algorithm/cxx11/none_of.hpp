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
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
*/