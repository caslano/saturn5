
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
trWDc3zmOwOVbSG7D/U9g6yH2eN/jhp/P2p8R9T4yqjxZWH85/onP8S0yP6ZED8+Xz/d6ULqxMnImrciWwjxKSkTp3Tt2z1vH+VbJEhP65OnhWm7o/ojLx36IT6knGkT0jLH3ze+OtKHTELWMrsK6Bu6hsj3KxJpN9k8A3LfvXjevC9ZNnlC1rI7jN9m3fGJiZOz47XJtEpVzJM6IWN8SMNr4R0N20idEp/sz6ztLLT+2rYz
*/