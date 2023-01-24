// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/mutant.hpp
/// \brief Mutate functions to extract views of mutant classes.

#ifndef BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP
#define BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace bimaps {
namespace relation {

/// \brief Relation details, mutant idiom and symmetrical metafunctions builders.

namespace detail {

//@{
/// \brief Converts a mutant class to a view with zero overhead.
/**

This function is a safe wrapper around reinterpret_cast. It checks at
compile time that the desired view is supported by the mutant class.
See also mutant, can_mutate_in.
\ingroup mutant_group
                                                                            **/


template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< mpl::not_< is_const< Type > >,

View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View>
    ));
    return *reinterpret_cast< View* >(boost::addressof(m));
}

template< class View, class Type >
BOOST_DEDUCED_TYPENAME enable_if< is_const< Type >,

const View&

>::type mutate( Type & m )
{
    BOOST_MPL_ASSERT((
        ::boost::mpl::contains<BOOST_DEDUCED_TYPENAME Type::mutant_views,View> 
    ));
    return *reinterpret_cast< const View* >(boost::addressof(m));
}

//@}

} // namespace detail
} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_MUTANT_HPP


/* mutant.hpp
gC/wwwUolYl4IURn+5UO0IrGPekBe3wC25Xn8AWYiQBu6foTvho+VR5NJ9iXHAGlEJX+7XI6/s1ST7RFu1ncaH99o4l0dRtO7wL2Dy8P1x2CA/1gITs0hFRroj7QG71xXDAu6NgADBQFPvkCDBS3sIHibk8HDPNsFv2D+9Jea+1xXAYomnPs3EW7IaXbZmItXcA+QPRJUKva99Qq7OepootYBltBvlbF4cugirDYuslUwca/zl2BHZZvKBdeg4XD664UBR+UBSOus63rYOr7mScC7DJFkcOiaAdYbRsXy8FiDhPP7G2X8cxmMaTEX2ZYIZCU25wl1xVsXFB7FmIJFsEOhsNk3o6my9ggUKxy2GXqHpFnLDnS0jIMb/cFk+sK/R27X149x5WesN8JzC79g555R+iZw8+sI2FabMDmzzXGfSgRbbrbV+sSwDPa5fvR6dsE1Mn3PGiNK2bARV+6QiZw2pZM5fDfEBLZBXbYXysHxEuKdykbmC+NfRPXtRCJFsQ4SvOyaYpYsziM9O0uUzYsPh2AoK9pXs2UAnBNGSMgsf1tbR3x4i+5wqHEEJJ4y0JxkuPTwAKZzlZ79bPgxo/3jW4AzS6kvTYA0gRPuNFqkmnPxFsEfQVQqW5DoCLInyPO52wI3e51r4YT2G3PmE14KREuFnFg8XggxwIZrwbduhIVbaHAt1iFpTv2x7EXTvAcZam2D1K7C7Rk
*/