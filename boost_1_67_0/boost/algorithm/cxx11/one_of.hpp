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