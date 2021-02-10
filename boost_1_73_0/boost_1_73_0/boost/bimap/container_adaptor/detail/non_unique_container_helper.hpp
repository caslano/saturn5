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
q5Haib2DTKHQdfV5xg4v2sUAfGQoVYbOKeiSvR4RXkUfo38AUEsDBAoAAAAIAC1nSlKqbLrN0gcAAA4TAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3AzLW11bHRpLmNVVAUAAbZIJGCtV2tv20YW/a5fceuiiehKlOQAu9vYCVa1nVSobRmSDSOLAMSIHEqzJTlcDmnZSPLf99wZUpRkp94FqjwoDe899/2YweFf9+nQIb34Cey/AB88Lcd1of8tw/J56iD4Su4PuD7j+ZKQAbUsXwOPXmb5Sl3LEtRSTvh7ELwk6DPrxv8NmPNzwF9xAjbmPNX5Y6GWq5K6px6NfvnlH9Sno+HRsEdnIlMyoXkps4Uslj06iezJP1fi4cE38n2PZEki8Wuom5UyZHRcrkUhCd8TFcrMyIiEoUiasFAL/FAZlStJsUoknU6vP02uPvZovVLhikEedUVmpaskopW4l1TIUKp7h5GLoiQdgx3gkTIlAKtS6cyHbEmlLFLDGCxeJEaTuBcqEQsIEiWtyjI3bweDsCoSaD+IdGgGYWO+vyrTjSWfoEQqHknnJZWaKiN7xJQ9SnWkYn7CITjMq0WizKrXagNRWTTQBRmZJIwFPiWNU1vSvHZPj8koh8aq5IfR
*/