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