
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
0t7e0kDobimXIgVoIXu8LQS47peVcQyJCHE2Nu3RX3/jmJdeu5VOp6suqoxfxjPzPDN+VEdxqRiVvE6cKFkI/Fnx7YPIAlknHd8f5gO0b3wzaVAZMaAbFZp13+/2zHIR09WWONbxumMZj+9gzLN7nhVlFHDiZDyNt3VCnJNi8Yk/KBbxSkAVLZdKJrZVPi/DRakMfc6DnanIjjELxDiuQS9imZBioYqeN7Y+nZcKpCkSxRNV9Lcpr4HifyorVOv4N2AhzSRX15EUxWr101WxfDTu8mSpwhrYVwUym82KLkbB/YhRhU504J/tm8wyTuP19akmNJ+eFkiB+GEkAf8ozGkAKZVSk4OTJT9Bgg5wDRsHZEcy7H9KBry3f3lDQi7/Y0ISoQCv5EZ/o8M2dOTM2KXyc/AaboS5ZWseRBjsbWFXKq/BBj8e9fxp35+4btN188FzW/msvXRv3B+fJ+W+O6Nfmp777LvQQ35/clsO2svrp8RIFcXx6/QYTg782E/4QeYAvSRLbLeMwyJKOFIFMucGYpoEb0iUrTHcRgmN4+1HTN2AeQ2CvYfAQs5WddLCKTCRJJypSCRQwo6zqy+2yz/ftmvYG/bO+84jrvZC8w6acaSTNfrD8gU+rwWnapNxVCpdUDIed8nJeDz0
*/