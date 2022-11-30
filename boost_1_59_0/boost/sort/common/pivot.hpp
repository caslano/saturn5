//----------------------------------------------------------------------------
/// @file pivot.hpp
/// @brief This file contains the description of several low level algorithms
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_PIVOT_HPP
#define __BOOST_SORT_COMMON_PIVOT_HPP

#include <cstdint>

namespace boost
{
namespace sort
{
namespace common
{
//
//##########################################################################
//                                                                        ##
//                    G L O B A L     V A R I B L E S                     ##
//                                                                        ##
//##########################################################################
//
//-----------------------------------------------------------------------------
//  function : mid3
/// @brief : return the iterator to the mid value of the three values passsed
///          as parameters
//
/// @param iter_1 : iterator to the first value
/// @param iter_2 : iterator to the second value
/// @param iter_3 : iterator to the third value
/// @param comp : object for to compare two values
/// @return iterator to mid value
//-----------------------------------------------------------------------------
template < typename Iter_t, typename Compare >
inline Iter_t mid3 (Iter_t iter_1, Iter_t iter_2, Iter_t iter_3, Compare comp)
{
	if (comp (*iter_2, *iter_1)) std::swap ( *iter_2, *iter_1);
	if (comp (*iter_3, *iter_2))
	{	std::swap ( *iter_3, *iter_2);
		if (comp (*iter_2, *iter_1)) std::swap ( *iter_2, *iter_1);
	};
	return iter_2;
};
//
//-----------------------------------------------------------------------------
//  function : pivot3
/// @brief : receive a range between first and last, calcule the mid iterator
///          with the first, the previous to the last, and the central
///          position. With this mid iterator swap with the first position
//
/// @param first : iterator to the first element
/// @param last : iterator to the last element
/// @param comp : object for to compare two elements
//-----------------------------------------------------------------------------
template < class Iter_t, class Compare >
inline void pivot3 (Iter_t first, Iter_t last, Compare comp)
{
    auto N2 = (last - first) >> 1;
    Iter_t it_val = mid3 (first + 1, first + N2, last - 1, comp);
    std::swap (*first, *it_val);
};

//
//-----------------------------------------------------------------------------
//  function : mid9
/// @brief : return the iterator to the mid value of the nine values passsed
///          as parameters
//
/// @param iter_1 : iterator to the first value
/// @param iter_2 : iterator to the second value
/// @param iter_3 : iterator to the third value
/// @param iter_4 : iterator to the fourth value
/// @param iter_5 : iterator to the fifth value
/// @param iter_6 : iterator to the sixth value
/// @param iter_7 : iterator to the seventh value
/// @param iter_8 : iterator to the eighth value
/// @param iter_9 : iterator to the ninth value
/// @return iterator to the mid value
//-----------------------------------------------------------------------------
template < class Iter_t, class Compare >
inline Iter_t mid9 (Iter_t iter_1, Iter_t iter_2, Iter_t iter_3, Iter_t iter_4,
                    Iter_t iter_5, Iter_t iter_6, Iter_t iter_7, Iter_t iter_8,
                    Iter_t iter_9, Compare comp)
{
    return mid3 (mid3 (iter_1, iter_2, iter_3, comp),
                 mid3 (iter_4, iter_5, iter_6, comp),
                 mid3 (iter_7, iter_8, iter_9, comp), comp);
};
//
//-----------------------------------------------------------------------------
//  function : pivot9
/// @brief : receive a range between first and last, obtain 9 values between
///          the elements  including the first and the previous to the last.
///          Obtain the iterator to the mid value and swap with the first
///          position
//
/// @param first : iterator to the first element
/// @param last : iterator to the last element
/// @param comp : object for to compare two elements
//-----------------------------------------------------------------------------
template < class Iter_t, class Compare >
inline void pivot9 (Iter_t first, Iter_t last, Compare comp)
{
    size_t cupo = (last - first) >> 3;
    Iter_t itaux = mid9 (first + 1, first + cupo, first + 2 * cupo,
                         first + 3 * cupo, first + 4 * cupo, first + 5 * cupo,
                         first + 6 * cupo, first + 7 * cupo, last - 1, comp);
    std::swap (*first, *itaux);
};
//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
#endif

/* pivot.hpp
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
*/