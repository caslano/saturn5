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
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
*/