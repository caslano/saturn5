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