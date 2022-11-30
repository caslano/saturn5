/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file one_of.hpp
/// \brief Test ranges to see if only one element matches a value or predicate.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_ONE_OF_HPP
#define BOOST_ALGORITHM_ONE_OF_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/algorithm/cxx11/none_of.hpp>


namespace boost { namespace algorithm {

/// \fn one_of ( InputIterator first, InputIterator last, Predicate p )
/// \return true if the predicate 'p' is true for exactly one item in [first, last).
/// 
/// \param first The start of the input sequence
/// \param last  One past the end of the input sequence
/// \param p     A predicate for testing the elements of the sequence
///
template<typename InputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool one_of ( InputIterator first, InputIterator last, Predicate p )
{
//  find_if
    for (; first != last; ++first)
        if (p(*first))
            break;

    if (first == last)
        return false;    // Didn't occur at all
    return boost::algorithm::none_of (++first, last, p);
}

/// \fn one_of ( const Range &r, Predicate p )
/// \return true if the predicate 'p' is true for exactly one item in the range.
/// 
/// \param r    The input range
/// \param p    A predicate for testing the elements of the range
///
template<typename Range, typename Predicate> 
BOOST_CXX14_CONSTEXPR bool one_of ( const Range &r, Predicate p )
{
    return boost::algorithm::one_of ( boost::begin (r), boost::end (r), p );
}


/// \fn one_of_equal ( InputIterator first, InputIterator last, const V &val )
/// \return true if the value 'val' exists only once in [first, last).
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param val      A value to compare against
///
template<typename InputIterator, typename V> 
BOOST_CXX14_CONSTEXPR bool one_of_equal ( InputIterator first, InputIterator last, const V &val )
{
//  find
    for (; first != last; ++first)
        if (*first == val)
            break;

    if (first == last)
        return false;                    // Didn't occur at all
    return boost::algorithm::none_of_equal (++first, last, val);
}

/// \fn one_of_equal ( const Range &r, const V &val )
/// \return true if the value 'val' exists only once in the range.
/// 
/// \param r    The input range
/// \param val  A value to compare against
///
template<typename Range, typename V> 
BOOST_CXX14_CONSTEXPR bool one_of_equal ( const Range &r, const V &val )
{
    return boost::algorithm::one_of_equal ( boost::begin (r), boost::end (r), val );
} 

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_ALL_HPP

/* one_of.hpp
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
*/