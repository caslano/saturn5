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
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
*/