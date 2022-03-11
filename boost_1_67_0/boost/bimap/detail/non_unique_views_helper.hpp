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
+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
*/