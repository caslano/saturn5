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
t/6GNKhMufAd6IejzOUr96U3IFnq35/CMJcp0/qIj4FPnPmnbLktRGXVYa1NdevS/GI+6LBgr1IIzBgWu6GPhTZVvJLaB0KZL0XrXJcvNM23FcqgrS5ceNrt7PkFRv1DKRpd6gBvUBcJnIRlxIhwE0WaFkQ3K7kI1I2o7m33CTGp2yPxWLaI7qXDFaHNkSjACeIH6u7h4LFK0A28H7xGfNqWGptjBnNngemfF4sKtwxF54vofiHkeiYSmOKlsRjEWzQGnInbXxBbQsMs4ttek6nl6DSwPFbpfLS0LojUTquKxWyXgM5d8MX9AMC8nkrRtR4Kk/6ngeCIxHJVfwlXzzP2CuyagiQ9BWIIFlhIHmyJ4/uBrQxQ2WUrGNcaO6No18zG/WbQiSE97UxZUCcWifedsRKRSEqxi0Utbv/7sWSeFJpGESaZsKBHV3elzs4HxpHma6PepkfS/6TMh3rYg6I3xXoS84KYxFR/MoTJXoza7lyP3upjMe2ZvVNAS48z9uileKKwGs8so/DY3FLo5hMCrycxucgjWEZ3ovLmSZqfvjQVgjvyJEJQcYH8I7FPGE8d7ouDizEhYeOW+K0VXBkX/fHm5qGaHQeTx6u4Fd3/uvOUQ2VWeZBj8uY2eHPhpv+v12M3gI2bAu7H8MxpLXATdKxSr0T35Nue8k6ory/JQcDlBn4K59sbM/RlDl50Rt7boDK3chmn1JG3
*/