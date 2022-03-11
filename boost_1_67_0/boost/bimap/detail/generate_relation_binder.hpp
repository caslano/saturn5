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