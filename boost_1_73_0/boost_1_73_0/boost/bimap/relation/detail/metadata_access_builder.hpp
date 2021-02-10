// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/metadata_access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/is_tag_of_member_at.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>



/******************************************************************************
              BIMAP SYMMETRIC METADATA ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SymmetricType >
struct NAME
{
    typedef -unspecified- type;
};

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER(                        \
                                                                              \
        NAME,                                                                 \
        METADATA_BY_LEFT,                                                     \
        METADATA_BY_RIGHT                                                     \
    )                                                                         \
                                                                              \
    template                                                                  \
    <                                                                         \
        class Tag,                                                            \
        class SymmetricType,                                                  \
        class Enable = void                                                   \
    >                                                                         \
    struct NAME                                                               \
    {                                                                         \
        BOOST_BIMAP_STATIC_ERROR(                                             \
            BOOST_PP_CAT(NAME,_FAILURE),                                      \
            (SymmetricType,Tag)                                               \
        );                                                                    \
    };                                                                        \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    <                                                                         \
        Tag, SymmetricType,                                                   \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_left      \
            <                                                                 \
                Tag,                                                          \
                SymmetricType                                                 \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME SymmetricType::METADATA_BY_LEFT type;  \
    };                                                                        \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    <                                                                         \
        Tag, SymmetricType,                                                   \
        BOOST_DEDUCED_TYPENAME enable_if                                      \
        <                                                                     \
            ::boost::bimaps::relation::support::is_tag_of_member_at_right     \
            <                                                                 \
                Tag,                                                          \
                SymmetricType                                                 \
            >                                                                 \
                                                                              \
        >::type                                                               \
    >                                                                         \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME SymmetricType::METADATA_BY_RIGHT type; \
    };
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_DETAIL_METADATA_ACCES_BUILDER_HPP



/* metadata_access_builder.hpp
rD84IiQhuK2YwrIKWp82cJJiieArHNgZdIcVsIS+Qtzwxa2dr64FVj0yb4yrtMTNBqIUaQdFXx86e03l4IdFfLXh8Ar2AoPM8s4OygbWT9gjuyBqW/JOesdEyixU6Hudd9pcaKBc1POiCXvHg6JujTWD6T2+PDsLbnjbAoCfh13z9WAYb7FDzojed5Npteq82Ob+55r6X4HpB43zGyuCfqPN2XSwXuk/htlShIi71m+e1kYCuaGN2IYYt+F2wRteXpxh4DHF+v4rFZlN8G8FLi1qfusWbVYhb6WbMAmlbTM9gPYJdvbsYO+FG9/48Ze2jyoq6a2dtHBxxZjZGC1ZWUJCYS7FkptGzSnN0PPJqkkBIInAOrTRc7p86u32fZy5cCWMjdoyqoSxHgWMBJobz0uRkDJmnOmOsTs+PZv8PjiLBxjdvt+ECu1eStTK7Wyyykw3WbXZoqjGFm8XQ+vMyfksxiGEdnNaLJfLHr0n2NpoT8h5ZNKoyU1FscegfY45NmbLPK95ag4laJL1Gbyri9Hs+ORyPJyNJmNsvE/LfQtySfEUNO22lvDSevJlE3WLTyH1Qhse/4PG0WA2CMG3l+CFBdg2WCwoWi3v8MDCU4i/1HjG35r0+6emSuMJVmD8zBGzIJiVpjGb+iXm
*/