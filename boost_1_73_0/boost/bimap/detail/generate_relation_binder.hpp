// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/generate_relation_binder.hpp
/// \brief Define macros to help building the set type of definitions

#ifndef BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP
#define BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/apply.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_0CP(                             \
                                                                              \
        SET_TYPE_OF                                                           \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF<Relation> type;                                   \
                                                                              \
    };
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_1CP(                             \
                                                                              \
        SET_TYPE_OF,                                                          \
        CP1                                                                   \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF                                                   \
        <                                                                     \
            Relation,                                                         \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP1,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type         \
                                                                              \
        > type;                                                               \
                                                                              \
    };
/*===========================================================================*/



/*===========================================================================*/
#define BOOST_BIMAP_GENERATE_RELATION_BINDER_2CP(                             \
                                                                              \
        SET_TYPE_OF,                                                          \
        CP1,                                                                  \
        CP2                                                                   \
    )                                                                         \
                                                                              \
    template< class Relation >                                                \
    struct bind_to                                                            \
    {                                                                         \
        typedef SET_TYPE_OF                                                   \
        <                                                                     \
            Relation,                                                         \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP1,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type,        \
            BOOST_DEDUCED_TYPENAME mpl::apply<CP2,                            \
                BOOST_DEDUCED_TYPENAME Relation::storage_base >::type         \
                                                                              \
        > type;                                                               \
                                                                              \
    };
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_GENERATE_RELATION_BINDER_HPP

/* generate_relation_binder.hpp
22HSD5ijzYk4iwvN5bjAr5phdrUf3PnC/JocLtK60Kpq1YTdNATxVRC0o9XdutW683fsZQFMeImVZ+Vbq2B1BVYhKLWVLY9dJDp7rWLrgHWQJKkE7+CUdRrsioQxR9nR9q8VoGArtmE7tuY84bzkHId3XATfqAd6tYBV9HQfREcUwpxrek281uBXD+9eUpin0D5f0M9l/TMpZX3/Srq6NX19qz+Qnp5OLnjYD5WUDUfCoSrk
*/