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
I5mYOslqHAHItPHynfTmJBbyqqR98PuS9NOE2Rhpql7IB9ZV2OudMDq1mJIKKy0MyAu54zeCLz4orfsSYlmY70u+ZliO5XMP+sHSCK0VsPH3+bP+1SCsH7/oMThNF/nFoG/23zsQ7UPZqQ8umU7wKXYRqNRaT1fCelPfeevs4T/V1piUm3DFwh5z1Ckkcs4CWjjk2gCiVnNvjAOwkjbrIuDN6Dv0c/D285daTRKvTsmR78F9JEfw0PTfYRxFAxpf2pcCxRkUimOp9DIGnea5dc7nFmJK/QmpxneTY/fyMaRftXK4JGs36Fc4a5QuelgaVplBq+Bz3vDTFV0CfnvsDGeWnR9S/YculxlPtYUjssGifhJrkI8cmHEdX4cmnMQU2vYhKDMSOvNRlBM2Qk8jiSbU59s2TvH8JO5RL9IMzSAna3j+Jm6y2wuyVYsn0yTYqo3wvFBntGrR3p4GUShG9FyXY1qFxoDJR6qLfNAWDoSNmFH+s05fxDZhjlDdGM30gvS/DEgHmJGIzi4eDDdsR0qbVG9DwGZpDmXDU1xup3m5MgyPd+0hV+EL/w==
*/