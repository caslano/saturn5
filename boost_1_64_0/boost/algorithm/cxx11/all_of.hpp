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
V11D1nZtgscr3I3Bn1C2n0xZdbF+7WxkpVuMCz68h505+5EdsgyBi10+1PXx4Rn0IE+sYUNwCNeua4tGwtGRlwSh6jvXoiOnBuOTRVgSYfYPpWmYqdwNJTFrARRSykZfFPnqlKVCFJ0E8Kgg6Yl/uzSMD2mHjGYUpS1+GwYl6iGLbTw5EWVwRNOLobDZbVY+IzHJ/WSikTKN4WkPdeWamRvb/vMixfHNsrdsWvvb/2ts+vFNnaYTKm7TqzljVYGhraWEWJXQYjXW5bWxAu0v1920JtQKJb0tCYOnO46jMqitkgsoUWdmdbikl3hh4RaeWbUk52dkIV0/Oyh51xEySYCH1r8Ydk3vmE3BDAlKGM9MeSqPUL45eHUXbDxw/I8vg4LE6igIU03W3eQyU+/ZSZqr5C0GdciEeoi79UWLdWhSgWLosxFOXdVTzu0TfxZ0HFDZ1rTtk72/OVRD9MTSisVMjZuu10Mqm9+MKwAW0pR+RAXqda1wOghfocR9zpnYQ6YMUZHkRDB6JEo5FwEU+6NvMUWvDfdLE4LB/eYyoOB0wWYONA6ByLKZ8Q==
*/