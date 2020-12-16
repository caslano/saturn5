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
gwopTDfVXffOUbw7LTnqOFPdTjeu12a6nWy697naQHyHX0CtG6nUkrqdKVQOfUR7g25nN8W3Cm5jnarGOlVcpzBnpG7nSIzBcjuacg26ncN077p7M9xu3U4X/F1Rt5PLMqNupxnLjLqdZJYZdTtJLDPqdmJZZtTthLHMqNuxssyo25mOd6+ibqdYl8k8F+gymec8lhl1Oz10mczzzbpM5jlDl8k8N4CsMt0Oyzx1O+Z6HciNeh3ZRrNux1tnM8+HzibOW2fD6ynN5yi2ozmNTy4qW2z5Pj7yuNa3ZFGL8U+brVM0X395J8XTpOT52A3nFs2e/Gpp0VPhuyde/1zNG7VP6j+znhLPj8cT9W/UANi+/CL9kedqbgTjwU1gM/AlcBO4BXwD3Ar+BXwZfBd8hc/1eRWkdOQ4EI15UToNYPHbSGYf/CWC74ItwSNgG/AouJzdz7J7A/g+uBk8BkYjjr+BNcDjYAfwc/BO8AtwBngStKqYjwoGgV+DCeAZsD54DuwOngcngBfBB8DvwBfAS+Bm8EdwG/gTWFNzuRNBpzsFvAJmgjZ8TC0BA8GlYBC4CgwG14FVwA1gKHgBDAevgJGgZkGbCt4O1gKHgXHgX8F48FMwCbwM1gMTUJ6NQFof69YDsq4yGkyCzeFyDjWsZ70JjAIXgHHgw2ADsBXvP/su2Agcg/tNBjXkrzH4ONgETEX6TcG9YAqYj3ykghfANPC3aAPSwbp21EHwT2Am2AvvWTPwI7A5OBMVLgv8GcwGLYGu/WcfBVuCTYKQf3AX2AocEozfPPAc2AZ8MATjYGBcFehCwG1gW7AHbrQdeAJsD04Lw3g0WBW/Ah3B58BbwGYRKDfwKNgZHIBy68v1Nsutz2CdSzSYAJvM5TmAy3MUGAFOAHeCxaCzbk8ET4CTwCkoxxIwEOVXCj4J3gk2QflNBsvAu8DeVqQFHgfvBiejHKeCDpTfPeAT4DQwDuU3HXwNnAFmofxmgq3AWfj/TfBecDDKcTb4FXgfOBPlOAcMR/nNBf8A3g9mohwfAPeC88CBKMf54N/BB8HpuNHfgKEoxwXgSvC3YD2U40JwN7gIbB2Btgvk9oX6i2bty+PcvjwFxoPLwSbgSm5ffg+WgX/g9mUVty/PgnUR31pOZ578hqc+DaXbBHYaP6cYZz7BumALMAFsDSaBT7D7WXbT/oDcvtQHP+H34jjYEDwNNgar85nksWBTsDaYAuaCqWApmA5OBzNAi+qq7yFgNlgXbAHWA1uCjcAcsBvYChwP3gzeB7YF14LtwfVgB3ATeAsYqbncsaDTnQJ24naoG7gQ7A4uAXuAy8FbwVVgL3Ad2Bv8EuwLngcHgJfAgWBP1MtBYB9wCPg2mA8eBkeAX4MjeV/qO0Dn7/SUf2G/sX9mr7HDmO9/Frbq4wEiBbYbbOHj/jUAfuM3fuM3fuM3fuM3fuM312t+hfn/BaNu4P5/nxnW/xdyF6CGHX05ZnfnfvefynlbSFsOd5mNd7H/HDl+NJbcg2xm4135dL3QxuNdCM/zpuW4Ds4MH15UWoK/I3gMqoj8jNa+ECNVHgPjcNk8ToURqs/ghgatpihQV6qjVLPxsyI9rGEcTKpY5VnuBeSnyObeu30Iuasb51FzPAqFOSbdT9p8ndGfh+tT6HpfGefgk3Djqnu8uZiu32UY0/JM46QhDbNxsKwKYc56h4FBGQt9XG7Pcef1xpjfG6m659A/RbKmaqgIpzKfANkciieA4o1D+GXkTqV4z9ehs/UL3WcMDK1w7n+Mew9ECpNo2wONW5CKs/a0garZ+f816JmqclzrLQp72NpbqBR3vD4uTuMwo+h6vu0RrbPqzGMOrh4=
*/