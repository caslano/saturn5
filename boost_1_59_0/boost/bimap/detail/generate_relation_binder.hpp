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
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
*/