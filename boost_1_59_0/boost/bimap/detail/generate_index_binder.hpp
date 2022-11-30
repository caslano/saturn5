// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_index_binder.hpp
/// \brief Define macros to help building the set type of definitions


#ifndef BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/multi_index/tag.hpp>


/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP(                                \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor                                                          \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_1CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER                                                      \
                                                                              \
    > type;                                                                   \
};
/*===========================================================================*/




/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_2CP(                                \
                                                                              \
    MULTI_INDEX_TYPE,                                                         \
    CONFIG_PARAMETER_1,                                                       \
    CONFIG_PARAMETER_2                                                        \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE                                                  \
    <                                                                         \
        multi_index::tag< Tag >,                                              \
        KeyExtractor,                                                         \
        CONFIG_PARAMETER_1,                                                   \
        CONFIG_PARAMETER_2                                                    \
                                                                              \
    > type;                                                                   \
                                                                              \
};
/*===========================================================================*/


// This is a special registration to allow sequenced and random access indices
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_0CP_NO_EXTRACTOR(                   \
                                                                              \
    MULTI_INDEX_TYPE                                                          \
                                                                              \
)                                                                             \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef MULTI_INDEX_TYPE< multi_index::tag< Tag > > type;                 \
};
/*===========================================================================*/


// This is yet another special registration to allow unconstrained sets
// to play along smoothly with the other index types.

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_INDEX_BINDER_FAKE                                \
                                                                              \
template< class KeyExtractor, class Tag >                                     \
struct index_bind                                                             \
{                                                                             \
    typedef void type;                                                        \
};                                                                            \
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_GENERATE_INDEX_BINDER_HPP

/* generate_index_binder.hpp
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
*/