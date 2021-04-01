
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
gIEJVV7OEoMxzv+F2Hbg9EpoDAU0vrgzYWVAOcFcQE4TFyMoMSz2zzJbRNhaFF31Tk9ucfhZ5DsV6uBQRNyfhx35gI/+GXHujHJ4UVijbWFHt7+jIjD7Lf6Y8WlKZi2X31KoUdctrxaN5h1XbXnA+/mu/UI9HSxMFIZeuLHPOaRUuj9iBOvke4KBhMQSEaQgNQxrA/aVYOa2IYbw3RTFhAZpV3Ut3ohcrdstEOFwr44/A/++JB0mqgYrjvPqX57di4v0lIFZhbNOx0VHRS/QmGyKBkeEBuePQh3etOWs8SKfznISSBuy+kjgDJBgIdO3772DsNcBU5tnyKjLUUZIpEN96NwpSsGoyvR35sNci+H4dD+xXWVqckcLbDWHZWXc7iBZbVrkvlyqw3xTUoS/+OmPzaIs+ddAbHC60bYPhtUOGNhkPdJ0OIFHSWfAS2LKla31pWg+9gAhupc+dNE0XytqZAC+igZM8dTlAsQaBIYUtGDp+GOEf21U9kMa2djdiBUhbl2v+qdXMxdbzkfD9xSGL0+K7KqvC1qA0ojqpKgBn5ohL4TfxtOzhw==
*/