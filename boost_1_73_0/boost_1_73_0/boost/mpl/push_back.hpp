
#ifndef BOOST_MPL_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_PUSH_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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
#include <boost/mpl/aux_/push_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_back
    : push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_back,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_back
    : has_push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_back,(Sequence))
};


BOOST_MPL_AUX_NA_SPEC(2, push_back)
BOOST_MPL_AUX_NA_SPEC(1, has_push_back)

}}

#endif // BOOST_MPL_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
YXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTgxVVQFAAG2SCRgrVNRb5swEH4/if9wypSXatRkqrQFeWhVNy3VuiZqWPfswJGgEhsZJ5R/vzNeEm17nYXAd/7uu8+fjXTUuUJ1lIGsdWX480JDb2zZZbDI89X4wtVynY8zMbtOQIoLRopQBtJS2wycKJVT2RmM75IEl9+w67uiMR3BZ+UoxfxAbzGZ46M5MmKW4OwmvZmnjP36PYc12SPZFL24uBsDUakXAtg0KjzcUIROUvzuDG/wrqlJc0ldEshiDBgQGDLYOdcy/BSi1GpPQSp6qeMuUYqQRlmY/V7pMhSmQkwXDLhfpVNfsVo+5aIn0SvtxOzDDOPY64k3tVZ2wE+N2Qqvn5eu3avjZc8S7DsTy6puCH2/j5O/CiYZ/KTaloB+eFyY+eGMnx/axqgSKmN95EtrvQW3G4FhL6GWlDtYNkR4Fm/YyRl27JlsXQ3opaOqHFlkgpEMd6rDDZHGSbczbgLyOGKZoLXGmcI0Gfg2+IcNp4OPYGE6l+I/pkXwg08gvt2yhBSLg23E9PnL0/p++RjBbVFQy+krcRXBndHOH+cD6a3bpfh+fsnlQ8vXSLVtUxfK1UaL17jv+5jd2MfMSbowJZURRP/fxsv2pTh7Ii5/
*/