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
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
*/