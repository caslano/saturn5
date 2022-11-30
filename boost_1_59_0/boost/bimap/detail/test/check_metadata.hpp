// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP
#define BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/cat.hpp>


// Easier way to call BOOST_MPL_ASSERT_MSG in class scope
/*===========================================================================*/
#define BOOST_BIMAP_MPL_ASSERT_MSG_ACS(p1,p2,p3)                              \
                                                                              \
    struct p2 {};                                                             \
    BOOST_MPL_ASSERT_MSG(p1,p2,p3);                                           \
/*===========================================================================*/


// Build a descriptive name.
/*===========================================================================*/
#define BOOST_BIMAP_WRONG_METADATA_MESSAGE(                                   \
                                                                              \
        P_CLASS,                                                              \
        P_NAME,                                                               \
        P_CORRECT_TYPE                                                        \
                                                                              \
    )                                                                         \
                                                                              \
    BOOST_PP_CAT                                                              \
    (                                                                         \
        WRONG_METADATA__,                                                     \
        BOOST_PP_CAT                                                          \
        (                                                                     \
            P_CLASS,                                                          \
            BOOST_PP_CAT                                                      \
            (                                                                 \
                __AT__,                                                       \
                BOOST_PP_CAT                                                  \
                (                                                             \
                    P_NAME,                                                   \
                    BOOST_PP_CAT                                              \
                    (                                                         \
                        __IS_DIFERENT_TO__,                                   \
                        P_CORRECT_TYPE                                        \
                    )                                                         \
                )                                                             \
            )                                                                 \
        )                                                                     \
    )
/*===========================================================================*/


// Check if the metadata have the correct type, and if not inform
// it with a useful compile time message.
/*===========================================================================*/
#define BOOST_BIMAP_CHECK_METADATA(                                           \
                                                                              \
        P_CLASS,                                                              \
        P_NAME,                                                               \
        P_CORRECT_TYPE                                                        \
                                                                              \
    )                                                                         \
                                                                              \
    BOOST_BIMAP_MPL_ASSERT_MSG_ACS                                            \
    (                                                                         \
        (                                                                     \
            ::boost::is_same                                                  \
            <                                                                 \
                P_CLASS::P_NAME,                                              \
                P_CORRECT_TYPE                                                \
                                                                              \
            >::value                                                          \
        ),                                                                    \
        BOOST_BIMAP_WRONG_METADATA_MESSAGE                                    \
        (                                                                     \
            P_CLASS,                                                          \
            P_NAME,                                                           \
            P_CORRECT_TYPE                                                    \
        ),                                                                    \
        (P_CLASS::P_NAME,P_CORRECT_TYPE)                                      \
    )
/*===========================================================================*/


// Just for autodocumment the test code
/*===========================================================================*/
#define BOOST_BIMAP_TEST_STATIC_FUNCTION(NAME)                                \
    namespace NAME
/*===========================================================================*/


// Just for autodocument the test code
/*===========================================================================*/
#define BOOST_BIMAP_CALL_TEST_STATIC_FUNCTION(NAME)
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP


/* check_metadata.hpp
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
*/