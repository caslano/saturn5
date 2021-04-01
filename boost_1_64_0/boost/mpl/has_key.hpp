
#ifndef BOOST_MPL_HAS_KEY_HPP_INCLUDED
#define BOOST_MPL_HAS_KEY_HPP_INCLUDED

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

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/has_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct has_key
    : has_key_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, has_key)

}}

#endif // BOOST_MPL_HAS_KEY_HPP_INCLUDED

/* has_key.hpp
4uHuFg/ufTGLz+eae78/9e6u905uufQWSdzCjR+jbhk1qSi6Isrk1mZ4q9EObmqVRriglxQ3kWV4nMwIoL62WlI/M1APpqU5uzgEkcKjZRmIEDciFYUHX9CkyoWhjPhFzP5vtkCoRDM6Z18kcU1ogX+cmCGCXr6LuQSM4wa52+KokafrGQy5qbt2tfklBBncQaQtSquiInvn2XAbtIzMhcMRqXBSxiQRV6v9Kbqp/K01FnopIqJTgdpppjKkv/KZbqG3j5Ji+lLRrASAuJT26CTGF3KF873Gtm1slzsGKiyw6bSHlxTUDYeBM13TMu2ueVUmRCvepfMkK1jelygCspHLEzCQeYK0TEJcAY1qVvQpmtuJRaB+QOMy/tZCtC87Zlw6v/JrYosKH82KcFXi0DkBZvvf2NjOZ7jLwz6dwYvoOx1NaI4RHrmr9xMj2CrwO5MQDHyY391KXrpisFmXouuvpp1YEJDMVG3yNjscVxTKdc5uVgbXNxqx+idBVoRuzZmzdSni/U1hTFLT+T7NRgIfOrPHb5/usRreQtL3/xApm3AQbFVVBZdSrA==
*/