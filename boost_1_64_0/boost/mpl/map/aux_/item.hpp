
#ifndef BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>


namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Key, typename T, typename Base >
struct m_item
    : Base
{
    typedef Key         key_;
    typedef pair<Key,T> item;
    typedef Base        base;
    typedef m_item      type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    BOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<T>, VALUE_BY_KEY, m_item, aux::type_wrapper<Key>* );
    BOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<item>, ITEM_BY_ORDER, m_item, order* );
    BOOST_MPL_AUX_MAP_OVERLOAD( order_tag_, ORDER_BY_KEY, m_item, aux::type_wrapper<Key>* );
};


template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;
    typedef m_mask  type;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    BOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<void_>, VALUE_BY_KEY, m_mask, aux::type_wrapper<Key>* );
    BOOST_MPL_AUX_MAP_OVERLOAD( aux::type_wrapper<void_>, ITEM_BY_ORDER, m_mask, key_order_* );
};

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES


#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n, typename Key, typename T, typename Base >
struct m_item;

#   else

template< long n >
struct m_item_impl
{
    template< typename Key, typename T, typename Base >
    struct result_;
};

template< long n, typename Key, typename T, typename Base >
struct m_item
    : m_item_impl<n>::result_<Key,T,Base>
{
};


#   endif


template< typename Key, typename T, typename Base >
struct m_item_
    : Base
{
    typedef Key     key_;
    typedef Base    base;
    typedef m_item_ type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    BOOST_MPL_AUX_MAP_OVERLOAD( order_tag_, ORDER_BY_KEY, m_item_, aux::type_wrapper<Key>* );
};

template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;
    typedef m_mask  type;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    BOOST_MPL_AUX_MAP_OVERLOAD( aux::no_tag, ORDER_BY_KEY, m_mask, aux::type_wrapper<Key>* );
    BOOST_MPL_AUX_MAP_OVERLOAD( aux::yes_tag, IS_MASKED, m_mask, key_order_* );
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED

/* item.hpp
vuiLvuiLvuiLvuiLvuiLvuiLvvzzlj3S/k8j8qwhSvP/7vX/P4y2unTa6opYm379o7OGWNrcbG3/sdLvv0X++7GZ2bKGY3//m1RjCBa76e8/SOknnWhpe7Nl4m/b5ZVJ9rbLIZLXVo1+/hlOefnTbtlQ4tJuadu3JDd9+5PZt3yn/Pxrs2zf9vK9XI/bYLZtkm3bD75/z0dcJcdNnVf3APfHbbFLXv49F7HCw7GbFuB67Iawf80uefr+PIR122HSZt5Hth1NSmXbGxJd+6T4sj/a/UtkPAozn6j6OTj3Ewhz6nOibvteJm3fd0ifjWtxWDrH311ZjfQMkfKmoNOi2V8j93DHvjNTD/et70xH9k36cFj700j/f+n7UVep9H/p0j4zW5W/86HPjPW7skL6Bhwsz/sHYZryG05yOP4zyiuH2PoGhHn6nXF84wc59wVwPZbd5Rh56pskx1d97NTjnco+2vvZK79tCmpZZ6ebPgE/y9wntZKpw7Ml+7o+czFC+R4Osj1zYbue+XIts15vjkr3/VkLa1nWuinL0WwnJtlWFtX1wfeypHegLCn7uT73kaF8P5Ktz3107LjwPdZ43sOe92o3eY8m7wZb3h07Dle5z1vvI9KFfUT+q89mXHiN5fyGGJ5qu6Vg84RD8/PueeDe07q+74i0aXMfqf1sRrj6mYtE7WczeqjWy5f1Qr1sz+Qh3xh1m7uHfA9Trddsy1d7eymkDbJeHzfPVlwmz0gswWhcKn+3oZvcT8h9RiLpCOU6K/fLh0ufiiTsh4MwCVNwKA7B0TgUczAVi3EYVuBRWI/DcTaOxLl4NC7BY/A2zMC7cAw+ipm4CbPwI8xGpZBjcW8cjwfisRiKuRiBx+MwzMcROAEn4kScjgVYiyfhIjwFl+BkvAqn4M1oxNVYhvdiOW7ESnwWp+M2rMZfsAa7cexqMQDrMQTNGIqzsB+ehaNxDmbiuZiP5+GJOBcnYyOegfPxfFyAl+LFeA024bW4yDqOcDe5L5H7Fc4j54p85DxeKX0zlmMYXoWReDXG4gpMwWvxCLwOx+D1cl5vwAK8EafgSizHm3EG3oJL8VZcjrdhM96Bt+BqfAzvxNfxLnwb1+AHeA9+hvfhn7gWA2X+9ANwHfbBhzAeH8aRuB5H4wacgI/jZHwCK3AjTsVNOB+fwUvxWbwcn8Mr8Xm8BV+S8/wKPomv4Uv4Or6Ob+K3+Bb+jm/j/hzrdzAI31U/GzTI/gyR9vWClKy9Xoz6+iPrRXrZXoPWerK9BlVflP0agwyJjUG7NcfW8o36PFv/5j4oYY/s+5/sh9LatGf6ouTy+6kmLSCtJG0ibScFXhBkiCNlkspJDaRm0voL9H4q+qIv+qIv+qIv+qIv+qIv/7dlT7X/d8b8f9b2/7XF0v6vbtyXtv2bVW376W7a9jOVNtw4a/u3vYHan7aR4+Nd2/ZXa7Ttb3DKq8rsPR9r+/Q7xU7t06r8At207Wexb1ud8qNx2mt+6jad9bLdGhnDazppLNtti3Ns721vmvY+lpf1mElbqce2249Cvbfd7lK1y6rbqTcF8C+Zu+xA3ITj0pWAp2u5U4yUpLbOUvbuXtpKwxNc26KV/Nu3IG1UTvsX7Gb/wtzsX4Rze6pqXsf6ejN/a287Vb5zFL+97VTaSZXdYTWH70VuoGvbZC7HYUOCvW1SvhtevxfWczfej3bJIdbzEejaNpinfI8SrG2D/pfj+Hi9XVBvF+ycdsGHLO2CeZszje+PO2/1L+lz8suHL+y259oFm+N8axfcEOdbu+DWOO/tgtNIbbJeDcl5DLMCaZ+ZhD3wBIzEE3EoFuGReAqeiJNxMk7BaWjE6Vgs+WU=
*/