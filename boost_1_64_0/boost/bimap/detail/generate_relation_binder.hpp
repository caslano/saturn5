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
O0wJoCfjhSTSkB+frTHW67g1t0d1cywsn23741xJQ+Coquhma1dvwnQ87Nm5H8GqgVA1oExVD+mFVKOXo8s8DTZPe53/gNRU/pbYSffsfD5ZWuMmR+DGOABrqKaiDsLufz5U2MAYIZPK5B01eJ79ck/jBLNDd3lyluOFozSX+mQpQNJBLOUeBvnjV0fI1auZTuapCRLeAMXBCXtew67AD3wofqrgl/taAGY4hugdSDui22xwe3J5rAx1HTPw1dSySxDCKaMjfIK0IZtYSuHYHWRtlsLvTCjGu1RGeFXluSZbPCh6O6DpjGtqUe3wDVDtpnIiPaDZLF+z8a4RzjZ4YanEi3zmqO7Sq96PVPlYT4USXcSaUtJdDnoCHBWtUgBYq4yKmTOVqfOY6WlnHzXerKXdaRi+bJCMIENU4TF0L5Ld584afpP7UYYqLnA2yDL26+vbok5CwfNWNKdxEzKE4BhvRx10KxuVxHFmsQkTvW1y7laZxUQPQpFbm3mNaM9QIEr4IPJzLJ2nT4oKCQfrTadA4OV9pg9EkF3OqSZVDKpLJZCZvvttlPAzWA==
*/