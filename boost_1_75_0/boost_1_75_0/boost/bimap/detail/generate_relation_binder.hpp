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
5HSBXf+crxjIZw6M7bLH7i+u49NhP/jf6Dc+bpz7JuWaBSaDdWWFvWi+xQz3OyuU3142GexFc6LMSMCpNCKs8/CdD8oibOKlGFprIPyoCO/TZyAe/0Zx0lciSyMMaG4Go/ByZ1hmfC8dNRGGsmhST4ykw7Ri4SlyAY4dLGtgFKqawSCKWryLKGKDTk4hHi9VLU2ABn9+JxQNYsaSQPvRbX7bO+/orVIk2QdLLsgGX3VBZT8syTrjSwwGOOlB1U3Ad/eTU4KwMfAKhbhy9mq7kt7rgh8C/zkepACAN/Pn9fzZ90FSYm55gJ4bHqD3q/izNc9n4vkujOH3n/jzF/48MYbyHYK0sp+ndvLnYw+gbEbyy5v5/6X88tlzXH4RMS1157qJEGW3z20SI0omUJ5Nk39Nm1ubJv8kpeyweuGKht2/WZKPWFcmWVeWjd2gWPJLPR1Scy+2Ju8C7FdLLiTg/Q02KlLKJmv+RBTOD0gpmyd/lVQLbkq2uOQLLquDCUI72ZKlnMgyqmsjmKJZVxqsK1pRA1ZHpSO/1u3OPTvN04eBY/d/hbVPErWT7Rouo69DPVDJDrCmljdXHRaudAe9Q94TocCxMGyBw39Jbr/WblNuv5aeqNTka9zmpNqqe/CKzrbqP3PPXmbNH8ywxxp3z849O8OaD27mwDRG3vvZzYr9LoAbnLu4n8Vmvn+brn9CM09B2ymbp9xgXWkW
*/