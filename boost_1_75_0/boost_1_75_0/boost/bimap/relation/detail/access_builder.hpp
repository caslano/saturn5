// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/member_with_tag.hpp>
#include <boost/bimap/relation/member_at.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>


/******************************************************************************
                   BIMAP SYMMETRIC ACCESS RESULT OF
*******************************************************************************

namespace result_of {

template< class Tag, class SymmetricType >
struct NAME
{
    typedef -unspecified- type;
};

} // namespace result_of

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER(                       \
                                                                              \
        NAME,                                                                 \
        METAFUNCTION_BASE                                                     \
    )                                                                         \
                                                                              \
    namespace result_of {                                                     \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME METAFUNCTION_BASE                      \
        <                                                                     \
            Tag,SymmetricType                                                 \
                                                                              \
        >::type value_type;                                                   \
                                                                              \
        typedef BOOST_DEDUCED_TYPENAME mpl::if_< is_const<SymmetricType>,     \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::const_reference,  \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::reference         \
                                                                              \
        >::type type;                                                         \
    };                                                                        \
                                                                              \
    }
/*===========================================================================*/



/******************************************************************************
                   BIMAP SYMMETRIC ACCESS IMPLEMENTATION
*******************************************************************************

namespace detail {

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( Tag , const Relation & );

} // namespace detail

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER(                  \
                                                                              \
        NAME,                                                                 \
        TP_SYMMETRIC,                                                         \
        PARAMETER_NAME,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    namespace detail {                                                        \
                                                                              \
                                                                              \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::left,TP_SYMMETRIC               \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::left,                         \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        LEFT_BODY;                                                            \
    }                                                                         \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::right,TP_SYMMETRIC              \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::right,                        \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        RIGHT_BODY;                                                           \
    }                                                                         \
                                                                              \
    }
/*===========================================================================*/


/******************************************************************************
                   BIMAP RELATION ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( const SymmetricType & );

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER(                       \
                                                                              \
        NAME                                                                  \
    )                                                                         \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    BOOST_DEDUCED_TYPENAME result_of::NAME<Tag,SymmetricType>::type           \
    NAME( SymmetricType & s )                                                 \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::   \
            member_with_tag                                                   \
            <                                                                 \
                Tag,SymmetricType                                             \
                                                                              \
            >::type member_at_tag;                                            \
                                                                              \
        return detail::NAME(member_at_tag(),s);                               \
    }
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP


/* access_builder.hpp
B1URz+n3hxinLpHTbwsxTF0yJwMVF01UU5FqAnH+diX1Bg3uhiM68rvLlbLSMwEh05SjphdKVLG0YpM9IlSUzrU8bdIU1FGq/R61KcmOHPClSdqAJU1HrIkF9nIB16DxJUD3IezVP4M1u/OL3yGShAZuM7bmSQH3DrqKMKUhDITSgH3XYCmSZkIS6W97nSBS8tpJejoaiFgM4eczJ+nZj99n8Ht3fn+U3yP5fRy/nzlBzxv5/Xd+T+H377ndy/j9c/5+Ib9v4ve2/P4Wv5v5fRm/H+V2/fz+I7/n8vsX/D6J37fw+1h+f4ff3fz+khw/vz/D7/34fQa/d+f3R/k9ksczroGet0E66pI5Uq8Q9ix3bFVN0pMxKv23CQEM8ae67L98ENkHGEMff0gGAutMHKEXLCbAIw66cvLjDaEdSkIcnYy8CttAfEl0kkP/UA6EuoPiNQJnid6esPLENK+18Dg4pBEdCNjfSGSTcz49mA/vVJfcmWgjnKgqdAyOd5JhOy56m7YjchVwZUyL51t2LIwtNd4+RtP06rEw9X6MVIigUbCQgi39PpEMieLw/eiGi0KCLTnq8k2aiFxlQmDQE61tM9+CUVU5Q7c7fUOjfKMqI/L/OWsrWEjGLGCQomyssVDgmpewT+P3ig46oyXb4rcfc4XjFR+Cub754w8Ck1EDGZiRrEFGkoIJ5tx/3HEwBO4KMIxyjQCkoaeS
*/