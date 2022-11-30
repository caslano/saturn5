// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/non_unique_container_helper.hpp
/// \brief Details for non unique containers

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

/*****************************************************************************/
#define BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS             \
                                                                              \
template <class InputIterator>                                                \
void insert(InputIterator iterBegin, InputIterator iterEnd)                   \
{                                                                             \
    for( ; iterBegin != iterEnd ; ++iterBegin )                               \
    {                                                                         \
        this->base().insert(                                                  \
            this->template functor<                                           \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(               \
                    BOOST_DEDUCED_TYPENAME base_::value_type(*iterBegin)) );  \
    }                                                                         \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME base_::iterator insert(                                \
    BOOST_DEDUCED_TYPENAME ::boost::call_traits<                              \
        BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x)             \
{                                                                             \
    return this->base().insert( this->template functor<                       \
                                   BOOST_DEDUCED_TYPENAME base_::             \
                                        value_to_base>()(x) );                \
}                                                                             \
                                                                              \
BOOST_DEDUCED_TYPENAME base_::iterator                                        \
    insert(BOOST_DEDUCED_TYPENAME base_::iterator pos,                        \
               BOOST_DEDUCED_TYPENAME ::boost::call_traits<                   \
                    BOOST_DEDUCED_TYPENAME base_::value_type >::param_type x) \
{                                                                             \
    return this->template functor<                                            \
        BOOST_DEDUCED_TYPENAME base_::iterator_from_base>()(                  \
            this->base().insert(this->template functor<                       \
                BOOST_DEDUCED_TYPENAME base_::iterator_to_base>()(pos),       \
            this->template functor<                                           \
                BOOST_DEDUCED_TYPENAME base_::value_to_base>()(x))            \
    );                                                                        \
}
/*****************************************************************************/

#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_NON_UNIQUE_CONTAINER_HELPER_HPP



/* non_unique_container_helper.hpp
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
*/