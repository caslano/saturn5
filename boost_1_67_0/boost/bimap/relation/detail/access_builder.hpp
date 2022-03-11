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