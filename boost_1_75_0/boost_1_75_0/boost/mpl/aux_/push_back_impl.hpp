
#ifndef BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

struct has_push_back_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_back' implementation below
template< typename Tag >
struct push_back_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_back_impl';
        // if you've got an assert here, you are requesting a 'push_back' 
        // specialization that doesn't exist.
        BOOST_MPL_ASSERT_MSG(
              ( boost::is_same< T, has_push_back_arg >::value )
            , REQUESTED_PUSH_BACK_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_back_impl
{
    template< typename Seq > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_back< Seq, has_push_back_arg > >
    {
#else
    {
        typedef aux::has_type< push_back< Seq, has_push_back_arg > > type;
        BOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_back< Seq, has_push_back_arg > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_back_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_back_impl)

}}

#endif // BOOST_MPL_AUX_PUSH_BACK_IMPL_HPP_INCLUDED

/* push_back_impl.hpp
/2rHyMznZultE91o4rg5m6Vvq89NOzJvOc9wDNMnQPd0FH+71/JbLGPIwRmVX3g9aQ8mI0c8gbEPUfWsAf0D2S/nxuauRJ+2CLNUydpsiZYxv1i7lKE7cwxve5FZpeJMJraKuDNkxHjl1sneDWFn6I22BgLWFdWRCNVzfKO57vitTj/OO5BI5uNpESlH5iY1/o6L7lTvaF7a25QpXxoNk75J/S8OK1xeExxNbMoP3T2PG37bLQYpD86nOUfvOjqeysWvCjBJ7E7C7bPZDv0niLfN8ihi673LgtrUWuLgVV2+oKDd3ZudBqK927zYQVQR0m6JzjgqHRTNLB5Yke4NoIPL7q6k3jhd+GR2mRPQ8XDEzHuNY1YP6HweGdPltFJ4qOAN0DBix4L0sl3oE2QoNwUYiBDhLpKd7JFADrA6dprepo9FTzQvP+93nu5nSm2Qd07pnbuK6EOYtn6nOQnmdP6mYlY2Jj/yzN5tnR5kawAcOlK8oYZN//Jyo+hIuHPP3p0xSL6KQWlNO/p+Ej3idFR8FS6RfJpsYSv+40dBgAKuuiJMVVvTNd/8UB+MpG3hvt9s0qBmLjwS2mnQc2cuML8BvnMfjN+dzAdQGHc09dy+goxbqn97gVdHz1nOP6ZJTT3jHRjfs9+8cxVNG+K3mLhcxgG+5QF0y9yg5K6lOrmifD0Ae6kkZsATDrkHnwETITltAZzVnhtSzcMT
*/