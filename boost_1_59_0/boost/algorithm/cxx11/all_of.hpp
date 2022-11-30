/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  all_of.hpp
/// \brief Test ranges to see if all elements match a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ALL_OF_HPP
#define BOOST_ALGORITHM_ALL_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn all_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if all elements in [first, last) satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool all_of ( InputIterator first, InputIterator last, Predicate p )
{
    for ( ; first != last; ++first )
        if ( !p(*first)) 
            return false;
    return true; 
} 

/// \fn all_of ( const Range &r, Predicate p )
/// \return true if all elements in the range satisfy the predicate 'p'
/// \note returns true on an empty range
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool all_of ( const Range &r, Predicate p )
{
    return boost::algorithm::all_of ( boost::begin (r), boost::end (r), p );
} 

/// \fn all_of_equal ( InputIterator first, InputIterator last, const T &val )
/// \return true if all elements in [first, last) are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param val   A value to compare against
///
template<typename InputIterator, typename T> 
BOOST_CXX14_CONSTEXPR bool all_of_equal ( InputIterator first, InputIterator last, const T &val )
{
    for ( ; first != last; ++first )
    if ( val != *first ) 
        return false;
    return true; 
} 

/// \fn all_of_equal ( const Range &r, const T &val )
/// \return true if all elements in the range are equal to 'val'
/// \note returns true on an empty range
/// 
/// \param r    The input range
/// \param val  A value to compare against
///
template<typename Range, typename T> 
BOOST_CXX14_CONSTEXPR bool all_of_equal ( const Range &r, const T &val ) 
{
    return boost::algorithm::all_of_equal ( boost::begin (r), boost::end (r), val );
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
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
*/