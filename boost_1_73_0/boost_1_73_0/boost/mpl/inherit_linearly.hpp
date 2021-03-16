
#ifndef BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
#define BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Types_)
    , typename BOOST_MPL_AUX_NA_PARAM(Node_)
    , typename Root_ = empty_base
    >
struct inherit_linearly
    : fold<Types_,Root_,Node_>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,inherit_linearly,(Types_,Node_,Root_))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit_linearly)

}}

#endif // BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

/* inherit_linearly.hpp
jU0Vc6qztKt64s5cTQ1O1DY2VWJRzz7RqaemZidqG6CitQ3RtPn1GFLKKRxQwjt7zfSsCtH7YPaKTOQ2D/lFbVtQmCfTzyRuE2KCvmv3Fub2U8Zt4KfI1F01yeWnnNuUMtFHcPzzxGvcfiZzm4NM96WUu/xMIT9IV0X++n9uP1dyG9zQQPmZ4vIzldtUyLhGterXz+1nGrc5ybSfqS4/VzEzX7cdxF6FeD9Xs/h8XeXyU8Ft2srjE9/YHHL7mc4=
*/