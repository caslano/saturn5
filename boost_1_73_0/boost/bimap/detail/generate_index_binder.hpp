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
jB2OH5Vy52U3imqoDk5JMzVJba0mB35JD1y1VBymfmq6mvGX6fEqEqACHLiNP/tje9Xi82i/ilqUFq3FaLFaHXYG4rVGeLqCpmgGjmUi+XyS1ppe76j9ueu+lFR8lbY2yHOKtLfReB+i8I6i7779Q//dwX9vQardQe+q9yTH60e6naFngn9ZaK59+lf6OJzR6bhDzxjPGevY5tlpvA/2fYnnUc6sYtY0LzevNnWzCXlLJxKP
*/