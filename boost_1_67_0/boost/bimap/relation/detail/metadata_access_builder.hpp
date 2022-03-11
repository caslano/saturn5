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