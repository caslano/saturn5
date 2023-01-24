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
V02+10xm9VzzIXdrQ2MJ4ZRgFdb0La3IDye5wSQQRq8zixZFBn7yIRyo4wBdvk5wm+TQ3AaDjiReFxDNOzvIK3b6U7jEPzGN/I3qdR209TbtlFRdRy4uX8ccsoKBH88yLuGOzl11FVzmcieU5eGPpFL1HJ01/1kS6mMW6vUxd2/KXQUUZPDsDXJDf/eXZh4UqwV9cYBwNiuWCWcr0GKXCWArjTxOSQm/zCmp4lix07d+Im4q0KNJj3V4Up3vN+iUA+MoqDXD9Di/7dxaM3ffzpJ4IGQv6VvHnbjjRudeI4mCWQbuIzULdxfjeOCjIfxzqkFCryMUzE/EG18fhnuqnfaSD1pwBiL5Wg9fFmVQnt1qgriyIWIKfo+2SNOBQcE1uLrdJoO3zuw2eevCPBY1fqFqdROzlhNLFj+3Ma81C4ipk23YC7ZS0/xxBswfKaVuSpwkR50V8ydd3k4+NEWwrJyJkr+8eqMjwHX/R2v0F1b1YYSyA7hVWdXpC34/EdqPTwqp8jv1164nuf3nU9z+M4eeSo4aWz7A53zaYL0AdhSJ8DQnwr5IhD3L8voKIuRSz9XXaBEp0Mu9IL6DQeFzDq82B4XSY/sCIL1PDZz0cGtKs1FQXLpvHac4J6O4T9cAxbEpS8nt69Hg1CnPI9TPDmBddVNih3LUtyPWhXiPR7Tf7mRoLwuY7zesDsR6A3JGVZhf4HziEwLTY58g
*/