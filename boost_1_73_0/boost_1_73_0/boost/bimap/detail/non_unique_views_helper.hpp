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
fzwcWrKSHwzNjNkpnVIetOYIY7jF0+QAfMcYzpfxKpouZqP3Ux86BNNxNGej5qMougsX6MGO4YnmluLalNqN+lAb644D4m7Rp06A5yW1uEXkSlUvsVngMGjkHySqPGWi4t1JXY6WeMrLkgR4HsV4FS3D94vpH6tptEQygjiFniiQyvWFTOkSTWc1kybDMrALEmfKLKMqm16K+1hhA+HPpJ+Fv4STtQ8vbk845w0Z4SUoHvYh8htHGRvUg1uO2E16B1McgcY5T/4EfANca6VNG472IYRvjobreYdfqKzS6NmsiwcRQ1CPLzl6kGEr5+kb+M7cy47vff4bd1Kw1Y6WuHonWY2KHdsbSArOZF19KVTzoi0G4BOFormw8UIX0+sh4JX3yfsbUEsDBAoAAAAIAC1nSlLFT3wGAQYAAN4NAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3AzLXRscy5jVVQFAAG2SCRgrVddb9s2FH33r7jLMNQOFDlpH7a2aTE3ddegWWxY7ooAAQxaoixuMqmRVBxj7X/fuZQUO+iKZECVxLIo3nO/z2WGh9/v6tEhPXgtwt8CF+5BYmrNnzL1/717sfhMzQ+krnF/SMmQdiKfFwN6WOQz9YPIotVyyt8Xi4cU
*/