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
nmo95YLahwKBAFy5pBxtnBeOZSiuC0nYB8oJtwJz9eBbeFtgtCGqHM3VnL9ohgr+CjPRvQbjxTSYoNYfa5cuHb5at68Gw88XECogp15sRktea8i+K+G477rWqf6h5pS+5c57GmxFZHz1WjmirAPOLT+HpfmGiamMhqlMsaWKLfO58tgBnsSXcRLpwiTPYiqeQL41gqaRxYfL2HgsHuxg4tDKHX7FpPrITsjh+zQNrHTh9sVwncadq0YLeVJd59dFpfVtsHkngF0m+A3j24mXvhk8fWPxMkj6nyp+c/wZZjqH3fln5SrPm3z5cb6B5VVN6kAjgLqcBXQBq8aEMqjfvuKPcLrolPtPGAtuYi/VkEEz3BahhRcyUPrAcBMEw4U4ZXDDY2w13zAjv1GDBkovZOlyG/GmrPhT5Y47yvq66LYaeMsWuwoqhMQZgRDwqxMxI4BOhEISAsAvHybhq7FzqXw0Llc5UNJ7vEq5lYC9i6AV+eXh+Q2tH+uzvkV3gX1e3jKlh8sfeVQMfINowZRSFqLmPiawFgqObEQfsN9+RbhJbUMlaTXSsF12o1gqC1rx1LdVpS0kbSNeb962/cF6ApAjsNgC/x3CZ5WSfzTM1Ozdm+8+MtyYwrs39RRD2+VbiSZqLt+baH1G13E01LwoQY+ad/AN54Ct4CsUyY9nh3gvwOuXafA8mB2W5u0W6xZypEjoAUp+kTAWj0dy
*/