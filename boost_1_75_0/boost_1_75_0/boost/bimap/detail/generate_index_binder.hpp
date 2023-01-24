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
SuS5nL6XCiP5yW0WfOgOEBZ5StJ9n5aivtoB2CiB6/nksDESMvhMXrCbKHIUsrzFqYWehazrxUrldDpi/BmJewb4AHPKHeLokgRLpPvmxJvR0ubPF3Wxejax7GWOhUYCaP1CAgj8zxVXcHiXooXHS/H4yYrgotHMQngv71TucGC1MyAukS89VyntzuYD17Q5djFAj0J8Nr/tBWQi+LMI+JDsyUXTPMcuVKWSV4SkPWggjE3Oj2eUMTYl84B1QWlhGviliYpLl4dkg3OtxesiWI5ZFvCHw5W4O/HAiW0/VPpPl2/NTpfnAIH5MoygDCx1GJHkIoUpTxrNNqQ/MmUqeok0nt/MjELSHqfq9GLt68lWcKe9ZGRLUuWNk3ytva9FGZTaFSZ0ZcUmXSkevSvTN5hwDHH8ElEfmOQHzhsOZnGglcN70BwlE5bq7ejYr/QStM2RMcD7jJKqaWhtyQYV3D3SCYpydq7f70j6xVX0eCljUpyaGM2Ucj99pnBV5+lYwkZiGWtrid/WEtqy+2YwlKSXoj47vYKNwxLUmbNyBT9j/ZlL6bJu70sNOuViO6SPzBJ+CeuDMC1rtlJ3hUEX9P1h3LHOKY0E47iX1kaq99oK0CTkpUJu3JKNRIUkPiaM9J7ZAT4XgQUvNAWx4PXwBkeEetXnPbOu7ShweJEddFXHmt8Sb/mOF9d1qv5mGxa7vCOl3OqoYN8L/zDS
*/