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
Z3+lIm7XQSMLy3pslCmREoPeuneVmAtxRMOC78bFb+ZpKepg6zjvSmdu1rHKNaEQ4n1qUBzBDgdDtXRzwz7BQZ0wZrHFi/cn+GiDEZih52zO2e9BdMieCRSHml+tGJHBb38Qo079mPI9VNu+QsjEqNaXJFjYUF/9buRhPJU2DfZH2dz/KGGolf4RCHpRmNUax7MdbkfFwHK9xSgcFgKRM7XmymFimhrLX6QpEVHCwFh/u13ThAYK/yWlbrKBnHj0+EAqjW/CUPgmV2S1Xi2vvh/lW5uLfXITHRNAbJD25iHpTGWUfmY/Zz9upkxICF0nXgkBdal7tpYrWuXNAL87B28aHBga3oU4oRyAZ4X0Xu9yFLIGoOIodyfjH0T2TxekLjUKxaYSimpfv45EfFHw1BMqIHE0BVZDYh2ghP7P8SU8NXF+GLkJVUI8Ty30BiRAwu26896hW9+NEAIQGS1NVYz2r0V7RqrWT9bfZC9UPkFLMVwqdsklsv2Vtgdiu6U6qnKoBa8gC7VfvvrGkI/yYgljhQCfv4kYNK6OwPdlxyw5XN8HejYCOAeKAw==
*/