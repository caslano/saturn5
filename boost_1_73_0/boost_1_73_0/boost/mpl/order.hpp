
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
Icxdk7HrI0wz2eC7u+n5F72U7uxbkR/gJuLIAYDVTByjpS+yGnwfu59s5DiYb35VZw/j/AKwRXo6ZUEmYddUp4sELA5S/zAVRjZMxoGVvexpa/bACZP1GOzsGoSmenP51WXrcadlrHPTvYfYk3vLuCN8FUSU43D0M+oTpost+xjsO9ZqkUtLpzGKdRM4euyc7ZO1mM6eAmJP+9KpJ05kR42UkJlfOfIDHJk2nuP4jNYM24SNkQWKTF+jJlgnkBY=
*/