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
m0t/rr4zPmr7rYUIYmbEViezJStyNv8+so+jOHJAVwBzTu8h828uS78+xEQEzWwObPn2BjkznO6BW5pu8F4wq7683VOY2QAEOyahyX8d5niLjvsqv3Z3kARha/04bABOR1pi+DWh5yLlnLBHlVMJ/HoUv1ih5RMgimH2yrOTAWHbXA8txhK40c0KfqyNGOYC4fwusE4l0M11oG23U5oDHwfjKTzrv//zqSDMzV+WX2daOkW9FkM6p2AtdP8XCvHjYwqN7kG1arw7QCS877uOkvrndLZP62WnIuBu1RF2SLZdPHphc7Da051l+cx+mI6NrxZETeVr/N/aDLUDd3dCI7DzEQuOTqV6kvINi2dm8OwMcp5MO3gDrL5cC2ycYQFaea7OulOcvLBG4d8aD5czMK/xlQ+cMvalLg6pepEQunLUZFa0ymrqOtsvPZSevKKJhrpOpATxCwSpdH4lYoQOKkVyplJ9VJZjj5NymC9nehEQZzMZtUjUpWFBZI5BoZCQ78u5+qf57D7vpeiNlIjhwfioKH0LmgYhfquwcGN6e25OQgKvTTS6gK/NJA==
*/