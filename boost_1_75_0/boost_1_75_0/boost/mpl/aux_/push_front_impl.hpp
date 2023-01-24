
#ifndef BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

struct has_push_front_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_front' implementation below

template< typename Tag >
struct push_front_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_front_impl';
        // if you've got an assert here, you are requesting a 'push_front' 
        // specialization that doesn't exist.
        BOOST_MPL_ASSERT_MSG(
              ( boost::is_same< T, has_push_front_arg >::value )
            , REQUESTED_PUSH_FRONT_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_front_impl
{
    template< typename Seq > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_front< Seq, has_push_front_arg > >
    {
#else
    {
        typedef aux::has_type< push_front< Seq, has_push_front_arg > > type;
        BOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_front< Seq, has_push_front_arg > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_front_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_front_impl)

}}

#endif // BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

/* push_front_impl.hpp
zzbk36+HDY5YbXfO4BhSk0WQ614jOu6WtDq0L3A3okDRnCH+Pf6muIg20ObYuAdutigrzOVHTUpjyPiumIhnhu4O3d5DNEWyOQ4M4p/KYuBSIHjTCNaNMmAbncme1a/ibWcwFizgNRTde+fXsvE8vRra+/HneptrmEgfbNBSKOLcJ2qXN70iQ3CNirVNVPGO3IUKYNDwu/H3+L0py4+IxbpakqyCQNovui4aOWm70QemXtn9W9nOg/pooMeOfnNYJo7fI074pOW0Sxs+CGS8n/CxPYmCmVpYyMsMVRK7te7R79dfHVwJfffHN4koF+08kRn2yCaOHzdUWPF6ABjPP8FGf/X6OWfJIPr09tyS19GRxD3anzBc+YBFnm/qZIqeVdjNZS2OFTYSoP3x2oXbcy6082FzpWP3B0aaWPvotq/z4yidj2Y2gHV0jzbjznamwG0N78DQKWea1sAcanzCKqR6Q2R3bHnjQ++SULAj+kztoRuWy5MqauLXjN/qR22oxfLOSRz7ehiR5FBzQUANG7uJbjFxXA/8S6MrHNMYZeLpHmSUec9nZD+UBn5mGTTsd1SjAN74dfBRg0EVSwbf9rrdgrvcmJez2uyJ5oLAc1eZX5pOhCcIOw0QBnvJGMddb+9u8J9+nVG/HqA33hHL55s7Gfl+c00B3gj7LRgXiBTg1E0C6dKiWlRiY1/qzODtKFz4UH6Idm6JuFdw
*/