
#ifndef BOOST_MPL_ORDER_HPP_INCLUDED
#define BOOST_MPL_ORDER_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct order
    : order_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,order,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, order)

}}

#endif // BOOST_MPL_ORDER_HPP_INCLUDED

/* order.hpp
s/naEru5nFKuqLcr5yrFNln0mMwybljxcsNae6dI3H3NVENOepl6mVd6u0+PITS25vfQJp6qGpGbLLSGxZoITTJms1MKySOsdrmwto5qqq78syDtnHvEKKPHtKBRo/96LYDkdPsoS2L9QSPMf7vG/9Zx/cZxWxgm2u4vdvrUdSTnLpJauC1UnR9GKxR8PbsEdjt9SoL16H/wdg56z1315ODGpLFIhMoW5j5YunCUe27ejM1pkaAIt+tgqHxLUmsv1KhPOPtFMOH2TaKSsfNPtIQB7v4X7qoYXW3tSDZl4VRsQkIyaIoPgbNvsUZhu0bhnKFV/BaWaMJMzF9NZZXliKgPJWWW3C6DvHh7U/JHiVdHRzR0tnGXqmMjVxpN3rIu3FejLW7hS64iPeMpl7NWqn/m8wYMv3+7XFxkHvDuuXYbL83auPtcX7lUMyTyKlvCB3j0ELOyR2pJbVoG/YlzV7b9C6rhWy0XvjSB/aF1/Uh/vE7gy9PDYO3Lrc9a7+ZGU7nSWVws0741VV6VxxhtbwStgRQKG/OehIIcCBtFz00iO1eNexU6peTWoyvRly383DUR3BdfxWk8ANDWnHtT1/u8ov+w8qqdLtcK7A3zwrfXzrF5rm9c/wtfFVCF5cbYmrSi393f+H3bJqF58qwv9wyfSDZWU9v8z7lhd6vcsnuoZtt7wEut+Dras0GkVcvoRkCpOxTh1U03VuU9
*/