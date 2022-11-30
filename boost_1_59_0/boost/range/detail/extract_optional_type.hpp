// Boost.Range library
//
//  Copyright Arno Schoedl & Neil Groves 2009.
//  Use, modification and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_EXTRACT_OPTIONAL_TYPE_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_EXTRACT_OPTIONAL_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/mpl/has_xxx.hpp>

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX)

// Defines extract_some_typedef<T> which exposes T::some_typedef as
// extract_some_typedef<T>::type if T::some_typedef exists. Otherwise
// extract_some_typedef<T> is empty.
#define BOOST_RANGE_EXTRACT_OPTIONAL_TYPE( a_typedef )                          \
    BOOST_MPL_HAS_XXX_TRAIT_DEF(a_typedef)                                      \
    template< typename  C, bool B = BOOST_PP_CAT(has_, a_typedef)<C>::value >   \
    struct BOOST_PP_CAT(extract_, a_typedef)                                    \
    {};                                                                         \
    template< typename C >                                                      \
    struct BOOST_PP_CAT(extract_, a_typedef)< C, true >                         \
    {                                                                           \
        typedef BOOST_DEDUCED_TYPENAME C::a_typedef type;                       \
    };

#else

#define BOOST_RANGE_EXTRACT_OPTIONAL_TYPE( a_typedef )                          \
    template< typename C >                                                      \
    struct BOOST_PP_CAT(extract_, a_typedef)                                    \
    {                                                                           \
        typedef BOOST_DEDUCED_TYPENAME C::a_typedef type;                       \
    };

#endif

#endif // include guard

/* extract_optional_type.hpp
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
*/