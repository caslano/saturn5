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
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
*/