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
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
*/