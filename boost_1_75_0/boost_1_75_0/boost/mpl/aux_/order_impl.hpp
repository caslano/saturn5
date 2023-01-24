
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
oYuIS7WoAPJkeP4ymWnPD5DyV+4JZtBZ1W8gcZye7S7K0li5Tidspb2TCNJ6pxItV7yfvt6JfbhVU1XMMkDvif/FS8/N25YHC0CfjBitdWxDEs+Pr9h/OBWI4OGJSACkYFqeRbeNNfesh33tE3K5jvYRWLnv3p3ulD+3rs0AcClnLxiy0zlSXHDqYhfP9WamZKmbq/MCvRerdYauTPVaDYcPURD/FqGMuocahhwX9jZp59Wv3EeLtsAwanergHKE24QSvRgm6rFBfc1lv9ubrYXjTkZD1gxa+SxS/YJVW2e18mC/0as23Kkg1UY1AHf/VVEZsbBQp9HIZ+dzXD43tMyOg8UTtdkRjvXFb4ZEbiaTWbboqDB4ydynymZnES3bNcF9m7v1rBQWcfhNkYBOiRaMAqaxLvgws0vD59X9UbubiQn6ZGpsXPXi2/yn9tsCvScbxBqfPcSZQEzZqO0gFZrYZRSd6tWKQqeK21YD2KM/jf/9SR1CFwx/chVprafTDTU7JkFLKr5ZoOE+dAMl6QR6cZvu2bhBQat6/TIsNS7fmOKFaGLooqg9InBySm5Y1fXbV5VDY2hNP2FTVEYk76YsYU1U/i4uZ+FRnQP8LSf5UTTyMXD0ms2DgIhKPV51ckRBsxio10GrnlE2OgdIsUwhXN1ES10t3o1U4E++dpHye2J1CJcGQvzpL/L/EEYS1ujJxu4yWp2ymsES
*/