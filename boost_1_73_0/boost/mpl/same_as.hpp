
#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : is_same<T1,T2>
    {
#else
    {
        typedef typename is_same<T1,T2>::type type;
#endif
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<T1,T2> >
    {
#else
    {
        typedef typename not_< is_same<T1,T2> >::type type;
#endif
    };
};

}}

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

/* same_as.hpp
u0+dGe6la5q5BkvzXWldeVJUWuMTvXr+y20tRqc1t03CAuss4rLuo6UzzJOap+25WmZMScpt27lWeeN50tShgm0kZd27vhfSK/8yx9u1Nx7yLm96p4b78q2hfclNwvuRfds+Kr2JSSlJ6Um/WXq/i0rf/uz0hX05K9IumLiOiKShQ742rkO6c9v9LtIhf9qHdig47ekh8o+FtK8Qdkb2dYeotKcmJ4z7Dff1L6V9pnT3s472
*/