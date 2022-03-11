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