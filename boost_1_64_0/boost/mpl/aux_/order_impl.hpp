
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
sWc9ikdM+DLteTjQxOAiIjP7AW4Df56MjUelgvnZxTQ+Nmol+WXSg0GzROCqLgMq6wjGnRdC70pFDrUVskpZnroNhiwXMfMgJ+7XvIo8SlSKJIWSd3FS5iflLexp9hcrsgEwLD4rIGlCe4wKJ1cjnrpp7Oy2KKb4Fhhn8RDfSqX/7yZBcOn2SsyUODYo9WZC2XfoDXPONGjxE6HSQnILTGG76B4mKW7bQ34Z3keaC5b5NHf1ML1u/ikM8m87KhPDe3dwrxG/7iHCWKH8+zHE3YtUKi6DdZ1boHOk8dRRnb17i9hFUqL523bLqd9qJhVVuxaujtjd+jHhYKQHgjhmt2xm2dmaCJQhBFaMdYKWvkZSdx3C5eo9plUAQBTvIDlFM3xGKnNi1H0/6MTNUYYnApVbQZIkDccvo8zKNzUXA1t9mFxSkOC6YX4bMoboL/NfSp2klk/r3oOSPmGiqTKwVCFqqNX49b6VGpvnlqFJ6WJ+AnG4qlQHQKPk/YO2Hzcl+qTJ+3JAmM/KIycRrw0zh7qY4ye1s0l5ie9uUXTDAb7mBD++G4CPxYy1Aw==
*/