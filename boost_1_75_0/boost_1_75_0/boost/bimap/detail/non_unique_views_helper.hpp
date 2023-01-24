// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/non_unique_views_helper.hpp
/// \brief Details for non unique views

#ifndef BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP
#define BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

/*===========================================================================*/
#define BOOST_BIMAP_NON_UNIQUE_VIEW_INSERT_FUNCTIONS                         \
                                                                             \
template <class InputIterator>                                               \
void insert(InputIterator iterBegin, InputIterator iterEnd)                  \
{                                                                            \
    for( ; iterBegin != iterEnd ; ++iterBegin )                              \
    {                                                                        \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(              \
                    BOOST_DEDUCED_TYPENAME base_::value_type(*iterBegin)) ); \
    }                                                                        \
}                                                                            \
                                                                             \
std::pair<BOOST_DEDUCED_TYPENAME base_::iterator, bool> insert(              \
    BOOST_DEDUCED_TYPENAME ::boost::call_traits<                             \
        BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)            \
{                                                                            \
    typedef BOOST_DEDUCED_TYPENAME base_::base_type::iterator base_iterator; \
                                                                             \
    std::pair< base_iterator, bool > r(                                      \
        this->base().insert(                                                 \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x) )          \
    );                                                                       \
                                                                             \
    return std::pair<typename base_::iterator, bool>(                        \
        this->template functor<                                              \
            BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(r.first),    \
            r.second                                                         \
    );                                                                       \
}                                                                            \
                                                                             \
BOOST_DEDUCED_TYPENAME base_::iterator insert(                               \
    BOOST_DEDUCED_TYPENAME base_::iterator pos,                              \
        BOOST_DEDUCED_TYPENAME ::boost::call_traits<                         \
            BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)        \
{                                                                            \
    return this->template functor<                                           \
        BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(                 \
            this->base().insert(                                             \
                this->template functor<                                      \
                    BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(pos),  \
            this->template functor<                                          \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x))           \
    );                                                                       \
}
/*===========================================================================*/

#endif // BOOST_BIMAP_DETAIL_NON_UNIQUE_VIEWS_HELPER_HPP

/* non_unique_views_helper.hpp
Me2ilIVSj1IqmlL9KRVDqUhKxVJq2WFMxVPqLkolUur8IUwlU+pdSqVSKpFSEqXCKJXB2/ue+oe3OrhfKm8ppYopVWGGMyrTr4/BGZVQXGg0sK4t0kDSd4IGjh1QaeDF/SoNnNun0kDFPpUGZuxTaWDP13oayP9aTwPDv9bTQM1ePQ2s3qungWf26mmg2149DSh79DTw6B49DcTt0dPAr7v1NLB0t54GHtitp4Gvd+lp4MVdehqw7NLTwHc79TTw0U49DQzeqaeBmJ16GjheqaeBZyr1NHBDpZ4GDuzQ08DTO/Q0ELVDTwOHt+tpYMk2PQ3ctU1PA39u1dPAz4+EpoE9FqSB9yoEDWSWqzTQskylgX9tVmkAGyzk06D/ZpUGTn+l0sDgTXoaqNuop4GNG/U08OBGPQ1ctVFPA4aNehp4boOeBu7ZoKeBw6V6GlhYqqeBB0r1NNC1VE8D+9braUBar6eBluv1NDB9nZ4Ghq/T00DsOj0NrP5STwPPfKmngZFf6mnA8KWeBj5Yq6cB11o9DdSu0dNA7ho9DYxYo6eBuFV6GjhcoqeBnBI9Dfz0sJ4GJHnrUF8HuL5vqEqEC1h0D3W8OHgUtsreqdFotiifdZuvLa16F63rRlkc125BdzgwOvZ1tA+BMISl7ph0tmthglIZhBNMkyvsG6q6gxe0I5g/G50lTbMY3GnsEW1w3yzJw2KqbwIzVTTg
*/