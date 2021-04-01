
#ifndef BOOST_MPL_FIND_IF_HPP_INCLUDED
#define BOOST_MPL_FIND_IF_HPP_INCLUDED

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

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(find_if)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct find_if
{
    typedef typename iter_fold_if<
          Sequence
        , void
        , mpl::arg<1> // ignore
        , protect< aux::find_if_pred<Predicate> >
        >::type result_;

    typedef typename second<result_>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2,find_if)

}}

#endif // BOOST_MPL_FIND_IF_HPP_INCLUDED

/* find_if.hpp
nmpe1mynnTESdcfW3uHNKc/8AF/rK0MRDZ9uvepowt7fldmdEwU6PNjOuEP8LmhGXl+HyO4T5RTkRF7YZWkcElqBIKdxurwqbspYFWrcrWjIMPsVbVmDCW+/96zPQWoEnEi9/1787V3ingZt+e1kUXNp7BUxxVSIKz1+IiYeUkoofdlfey5nSuMBI6KaPdQV9RE6qioUY+Z1ZsPuYCo6kduez6b5ZcdVWZxW+qS9fiP77ZMX9JMU2BYcyGMA1Lr5RIh4OfWOm9wcAe6CpbCIGEUAPdyQc2/sG3QSQtjsVe4lU1EArcUKcXAX8QwsXQlvoAe6raMrgWIRG2RDm4NIGdqTVTaqzMekQlYJWCjOIbxYl/oB5JsPH/cBnYUwRNZ3er1fAOyxiS0wmuQ3U294RCt16oP/DAvJEI/X/KCgE9T2DgHwz560qDb0v5f0YC7iURVTOVCwX2G8ixPsiT6waLpDwrk97JbbiDo9Qz7kcSUe4VjtbPDN6wKeTx3cuftCKbSVil2DitcLaj17rAG+2PLpdOYEoxVnlgs+EyFogiVWYxFXNNvEbp6GUw==
*/