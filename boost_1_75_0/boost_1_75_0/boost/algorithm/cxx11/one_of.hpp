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
5PHN0NY0/Cx9350MTREDZbM0+LFV0Sc/5MDPjIveZPKC5G8OFit/IZAKr2iZTUnrI/opCmGyXx2d8jRUk6Cu4mDnTnvniGeIehpuNfAjM7Xbm7O6OizjWD5JPT5wMCboLv9yze4QjK4yk6T4IkxeQ9UVZfFUJpM0MLyioBB247tktzURLRU7eUviUUQA6zHkDWXsL9iBKjuAp0Kf7CzdNAAR4qmawJLn1pN3oNGeEjtclbPpY0iqR8idxfsxqjxe7E/nJaRUOYBTN/Bc9UlQwvRq1XNXTOUb32gth5W5B8yT8eXd8yXcRQYCfBuuXPpCJ7CPu9wF8rF4YwqjoaLoLo8WSMT6LTTH121qGnNRvXyeG03cRXtKpvP5Tla8JMPeHuxMsfg8+DiFLjer8ls17lcx0jTwMf3n9p1r/13Xtac+N8KiriUND0GXpFO1tFMJe9CTrbZ0dPRmPtyygY0ntPup8kasXnVUMKnzrxPYjkTbf0GZi3M5OVBA8/oExZ6jjp6IP/jtszCObX35GG/o3dkIi5XDiA+eirC9V59f3hI1JQfcjD5D8G95hu6nqyHJEQUva4KPXd6GwxD2gNf3L0s5mjqlmYoNOU5vNh2GOzdcTxCs/b2mCuoK7hf7DTbsGAYtC88MYmfiNCkBPzcPDVMtCnUs782qMc+Q7oBjnt5fUCRbL+MNrIxFX0p/rvY5qyK7tJu6v1JRXvru
*/