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
g/5BoU94f2KJBpQS984+PClxD3tKwsnWeCWfHeeJZT5Jw+SfhhT85MhHpBg7KNeO4mXCZr6AvfY+nBwdHYOFt5OjOnRIyGgAI0HDCU1mdXjlKYrtk7u7Q07/rAMVQIJDpWjsMw48mooFSSjgc8BcGnLqAeHgUe4mbIIvLAThU5iygEJ7cHHV67+pw8JnLsYWllEK3I/SwAOf3FJIqEvZrVYRk0RANEVp1O0xLlBfKlgUHuLSFARN5hxVyMVJwCMgt4QFZILLEAG+EDE/bTTcNAnQ8oYXubzh5q4f+mKeeXGFFszJEqJYgIgg5bQOkq8O88hjU3lHKJAYp5OAcb9emoILhV4jSoDTIEBVKMYo1yZTGGXI1CUXxGgtE/LGo5DLlRZ+NF9jRAhRyTRNQlwGIUAeL0KA65CGHk0Ur3I6XyFDU0G7JSSlrR5EIVoCZmsEvZEJE8IZr8OH3vjt4HIMH1rDYas/voLBGbT6V6jrXa/fwXgzXCkBehcnlOPKCbB5HDDqqQV/3WUYuMCU3TVtfbcNekddJyeuvNgGC90g9ajHkqZdPtuGG8fTgMwcGXOHCyKYG7BJ025fXJydt9447cvhuTMat8a99nnvtW0YKSczurdvfDdk0biYNq9edQdnxqWkn4LUY7lROGUz
*/