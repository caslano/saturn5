
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
AAvnDGC3RWJo2f5AGndFlMK+rqTrH4rpxYlYai0eT1NXn+YiMWaUMLYBOpM30YgZE3nzhtU00fsyU3edBPegCYgKksGHvLVcPkBR0L4+XKEmkDx6u9Cogbtw0moxMzv6ii49KOcXxM3ojq0kRrurw2SqHRvQqy/0jJ+x/PYEDFAOY1VvzbD9/TnstNkD7eYmVv2+H+W992bmRRpwDjZja77lkoqoIvPflgpz50Fs49QX5PtiCl9GFaS2SJx8lTbS52HPEV3TF1tVm7FM/TFtef6a3Ro0GBsfLyUbo1xMvPeZyWftgnyUJOVNz4SoTwzrOnuP+uxVxjALJ5rr9YHpPVWge8r3yKllGI1XlaYNxTG0ukCWYsOFyE9Ynm1750gPDZOxeOMtfJ2mjETpSbT82k82wzWTJsxci+Jt10l0Vl9UNRoi3+Y5/yLtg8lZFjxX5AaCr0vAWb+QXmlcZ30WyEDsUCFXmvmaNBd4ImtYDDbEuqH/UA+cLqjk0X1LyPW7IXPX8Mb1h6t44aDrWPoqjxf6a6Dxx3BmNfMkNdMgemy+giyOByIx2gVNGy7Tye1mOBxrSutH5dDYaYNog2cQCTVnoatjN4WnyUK13p22lZRRjEkcGUhf5lFey2hklDnvu3sIwrXHsGlNPyGjJo6tpk8o5lE9XDpj8Z6XIiM/l2I7KjnJX0Sf9K/M96Y+xn3iZJvaBqHZ+nyzwSL6Jm7C694EUIvwLRKtS6Saikw2RGUkYoof8X4efUitTR8u/g5k2PYB6Td84aM/mckkfYXlZWk+on4UBh3YweKvpFLCY0PqWZKO/bsewWC4FU2J6GLlR2wxP/Mceba+h3/yUSDTBx9DmpBy5ihMn2TS3QQDWlTtByPhbkrVXoAt7XlIlwuhUqkvWBBiwj/5e9HQvBNs4pPBJDzUD+c8hHB78CEqVxwEyfnhfJHMQKyunc1e7PLDJKl3KNvwBMOXDCWJEbtxRqsYjqPqcfMSsRk991Hx4g6/eVabTM70xsPSc7jyTrCmLCpHio9tEB87DpJmfVlsqiOsFILQ9KUO3V4S+MKdqfc0S9avVZhMgiJ50c94WrCrCt/XL8ZI2cmcOZRTsrk5ehQMIZUzlQyNnBDUtI/GW47CPYMmWiiwMz5s6suNPoTi0rQ57Ji1Bw0eUc3iXh0ix+QiurX3Ag6FVbOBpUvJNXIMs9nyAkmu7uzSqyV4/siUzZm/ACHTnNijDj/aX1XFzzrn4ZQtsaBx9sjxW0a++VEUw+9xTbGvGF3mzEeVaAvWgrZzb81HVKVxl38xfwTvwUv48cGvoMeV2Yft7yg/Wps9NbbBuId3+bF5Y3GgTZtKDgfQLMUp/InnG2y7EUfRlX1QvnsHv2gfTcvLO9nnpH04HCZJl0NWIHr/UnrvYUzqIwJontUBOtk9HulRg9CgdoJPGNRAbXX9aH/SCFqyyJqVFogiWOgCs79XiF5d9jThy0KUPZWG9JmBgnOhjOlRlyQdGXocqgZHYWl4jEn90MboTEncLXhG3o0XWMc1A1xYXcZ3B5njnOgAHrd1FBaNqGUunimkE+PACg6J0rkP8Yz81mC22Bxurt6fforEMBx5Q/39V7Kpt0dg875ovjs9n8bKO6G4TIoKRIv4RiEPNDwOpHeXHOiT8SpaeMASZ7MesKhBajTovhuWBudRV/8R7LZPI9YnDORXCs/T+OYQWm+xmu77rYfPoFeIO3EONYPO0quznqQU5oeNyZ7stMNelIpN5h3xr6jAeSSch9TSmsHj2OPKbeB5ptRvzVf6+i0BMmZu9HL7Tjyoz8ItW1FWMs6KTi09jY9No+lVcjIdz/yBO93BaB++FbuyHKjXm+M=
*/