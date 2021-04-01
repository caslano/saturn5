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
BGIZShmWMuku7VH4vx62vEFBPRMqDeL1OtXOjfCZKA220VWgS0ZieHeh2RDIIuKcsNjC3a450BlxaE0kkyPAac+FdhXDGMbrHe0rT71j0SiLJf2rToVpzScbNB0roOJBqYawaMGmudzhJQs/3nKvPSAqHmvd5hdy5lcR1LQap/lnn+KGO0CD3BPN4KImEFcuior9334D4rXDV2OLcUU9Gq3qtgM2PsJKAnMsgfsn5J4uKdXB790Znl9CIo2aA+6Hk/VG8PVH8Mw/TXFx/wuIGFjHUPIuC1T5/06NLlPWBxqYAdiNBmM5R2OCBlONFpsJBgp8VVd9KKCS9LgIf0jPpsnosiYYi8seu675U3DkfIl5+Z83vatRObmYMdoUsOgPrYnH9uQuoIH7NXEy0qeMWIhFf/Q2LYETSHWARh2wksC87BBGnuQBP72LmskRhTDIPVP/j1aJRHiZ+zF8EK+ZxOabao+MMkWCPtGj5NDeT9yl+6hjyiZXJvcUkJJ7npccrM757yK7o/eg7eWRZi/LyNBwSlwAypdRp8COlrpt6P13LaBg4MHiGPoQFw==
*/