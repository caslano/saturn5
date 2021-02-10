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
mk6nOi6UsOH9GE9rrX6p7NCEzvpJsR+PjcANoN6j4JNPBVcntxsO9ciuGcqu+qxmqWlt9Q3YK5luUDOZIkMHsTTA0sjA+WwSrsN9YTh6BeMb3GoTAFRzg+nuRuGid8mlDYmkuYapr7xQq1qPohxrq3EjCF0q+l+uR6RUc8BtxNWLKb7TOqS82T3qHPp84cRM69L+Oi95nyKiWQn3mpW10fcbH5dK3q86tnrH4CuX02hR2ImF8hn57HWPpzVxdM7TQEfY89JU8WtDvcNlOXr1K6ms1ZlnvJwYMQPkn1RxHxWs2zpqd9vdMMGA4XQWfC3kzCs5neVl98ht+H+ounYOnahULJHtGw30hQpxdXd39/Zt71uZ3D6MuMLMEIKs2ex5Q+PeMajIjAYDWBFGbByjlUD99kIcP/5BJ5AzpeIz+yDRvsK66pA89Ts144Ev+EKG26RlQCcpj9llwP7uSeDYJ7dPZU6F41HOs/KaEIhXwpU0HmJgHkS6tIov2Ac7M1RXB+e1XjNPyqRU8rw2ciIzzCXLuhHRzhpFhj0vJpjiCEJbh0seftqdV3IMg1Yg0ib2q2oSwR5rlkkzUhJzow+3DQghos+sDSK2Ko85tjezSAzvo7GT06AVEt3WlIO+366CGAMWk86yHzI/6/5Q
*/