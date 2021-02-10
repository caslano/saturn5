
#ifndef BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED

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

#include <boost/mpl/order_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; requires 'Seq' to provide corresponding overloads 
// of BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY

template< typename Seq, typename Key > struct x_order_impl
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
{
    BOOST_STATIC_CONSTANT(long, value = 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(
              Seq
            , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*, 0)
            ) )
        );

    typedef long_<value> type;

#else // ISO98 C++
    : long_< 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(
              Seq
            , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*, 0)
            ) )
        >
{
#endif
};

template< typename Tag >
struct order_impl
{
    template< typename Seq, typename Key > struct apply
        : if_<
              typename has_key_impl<Tag>::template apply<Seq,Key>
            , x_order_impl<Seq,Key>
            , void_
            >::type
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,order_impl)

}}

#endif // BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED

/* order_impl.hpp
MzBVVAUAAbZIJGDlWVtT2zgUfvcM/0FNp7Ntl+B7bmuYMfd0IU2Jgfapo9jypThWKiuk6a/fIytxQiAUWujSNsM4lq1z+/Sdc4TicJJzH+dkS3GSLKTwdUEmY8qCfEs59LxucUEHe5682U0iEEB4xGP5oOMdHcuho84lHVUqe456hF0SVs2TgCgOI8N0sqUozrNqFbkpJyzDnCAeEwRyhMEd5qWNLJDaY4LhXY7wcEgwQ0mGGMmHNMtJjjhVSJaPGJGic00BJXn2F0cDzMHMBqpWp3YVBe19GaYYLCc0QyFlhVQwGqaJL7yxNA0MfB6BD3kLZqdJ3x+xtNQYEE58Lu1hFCWXJJu5PMR5LhBASY7GjGYRwikD7ycILIEVBYUJg3mWppcxoJc4lx5gjoVtoTF/tVHaHSdpCkHnHBQhH0QSiRRoy8h4rufTSIAGMC3EIjBMOMpJFsCLjIIUKx7KIKThYvXQkNF+SgZTT0EETAVXPH2mKAWKcvn2i0imQKEYDJdUWJ8GX8IhxBwRn65pklaqvqEXyjuEBDP4YClKHWuKZE4LHSc+ozkNebXd7qn2hram7NCMk4xXvcmQtBAnX7ga80H6D/JjzHLCN5OcVhsNu1nV55OPSBbxuIWM+ppyfn5edcEKPC+AahWG
*/