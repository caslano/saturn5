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
eaSRObjcHEAmk2SwH3hwwjnM+k19o5pPerFE1vVufMEnY8Qjt8EI+J7vdqyZFmQ20RpHG+yXW2gR6c8X9srTj1yG1hKsBakAs5GLjg335w6TiL7VkD5nb8Yb8gPu8zU/XMKPMCaAZVEeJGsqYY/vQSX4sxS57gFRh1TRhw9+mN+7BkgBZTIQhegoUxsav+AqAOdx1MWf3gjkM7C3wBTpjCNWnrLNGqYZYs+dc6QU919N/LRSA/JnqjOzzBIsLolYDB7Fa7u35gUpmtnOQr22duF1e4zzlKElXCyJzfomRZICzWtm0gam3W21l2PGlwPjNrksMQTq2Xfb9hnctzv+BS6SAIEN1mxS7s8YxvlBMDsrYWsBmJsuhDEZ7tUUAQb58t5pUqSEBpZ7ewpCyw0Dm2jS2v0kIc/tdu6oYzztoyYdgVP2dncADr5v0m93//9kz/Te5L46fWtc+pS8WLrtJj5oaufNFtKaf5KFBDvsXAVhzVwhuU8Ac3aEtO7HggYXqn7C71qssH0izr7YZx8oKTCucx3/gv61SNewajQ+rlEx+VqqSd1/qSj09Q==
*/