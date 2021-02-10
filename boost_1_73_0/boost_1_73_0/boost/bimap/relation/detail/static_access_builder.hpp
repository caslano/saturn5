// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/// \file relation/detail/static_access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/is_tag_of_member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>



/******************************************************************************
              BIMAP SYMMETRIC STATIC ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SYMETRIC_TYPE >
struct NAME
{
    -UNDEFINED BODY-;
};

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_STATIC_ACCESS_BUILDER(                          \
                                                                              \
        NAME,                                                                 \
        SYMMETRIC_TYPE,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    template                                                                  \
    <                                                                         \
        class Tag,                                                            \
        class SYMMETRIC_TYPE,                                                 \
        class Enable = void                                                   \
    >                                                                         \
    struct NAME                                                               \
    {                                                                         \
        BOOST_BIMAP_STATIC_ERROR(                                             \
            BOOST_PP_CAT(NAME,_FAILURE),                                      \
            (SYMMETRIC_TYPE,Tag)                                              \
        );                                                                    \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_left      \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        LEFT_BODY;                                                            \
    };                                                                        \
                                                                              \
    template< class Tag, class SYMMETRIC_TYPE >                               \
    struct NAME                                                               \
    <                                                                         \
        Tag, SYMMETRIC_TYPE,                                                  \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_right     \
            <                                                                 \
                Tag,                                                          \
                SYMMETRIC_TYPE                                                \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        RIGHT_BODY;                                                           \
    };
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_DETAIL_STATIC_ACCES_BUILDER_HPP



/* static_access_builder.hpp
DTbhySfyfxE++PYcp0b/xWP339RR9BWKH+S6xPdTSlpwy/I1asDTLF+h7lmiUkub1lH0lKJLso3+tYjzMqIl7iAbcfZ0tjRiljqo9xqw/fbtG3gFO1s7WyEcMCW4hHPH1YSbWQjtxO/8kbKbm6bl+yFwB0w2S1HjVFiweuoWzHDAtRQxV5YnwCwk3MZGTPBDKHAph6mQHHqj04vj4bsQFqmIUxKy1DnYVOcygZRdczA85uK6kJEx40BPkR2FJ8I6FJg7oVUTdXNw3MwtySD1TFoN7JoJySaoiDlIncvsbqsV50ai9a1Ex7YVV+43UzdfeXKBRszZEnTmwGnILQ+BKEOY60RM6Y2A4GaWT6SwaXhrDapSSUsbsFxKkoV8gtvCbA7nJTwhkUGGFgtHL6uVJVWLVM/vECKOJGWaG4WKEAckSjTCHEKuEm48sfe8UlFi6gF+NDS39iagFRoDQfccjs8DmDArbAgfj8dHow9j+Ng9O+sOxxcwOoTu8IKEvT8eHmDoBSozwG8ywy0qNyDmmRQ8KXX+uKdVa21C+6B/3tsn9Ufj8Smc5NIJnw9TbeaZtg4WaFCRVXkmNUs8wm6BWZAkgrKESZ9BlgyEdqsS6MX3bxhazzFaCcKZYroUQiywQqZicw4vp1q/pAgw
*/