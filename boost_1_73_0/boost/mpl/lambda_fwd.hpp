
#ifndef BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

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

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   include <boost/mpl/int.hpp>
#   include <boost/mpl/aux_/lambda_arity_param.hpp>
#   include <boost/mpl/aux_/template_arity_fwd.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = int_< aux::template_arity<T>::value >
        )
    >
struct lambda;

}}

#else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/bool.hpp>

namespace boost { namespace mpl {

template< 
      typename T = na
    , typename Tag = void_
    , typename Protect = true_
    > 
struct lambda;

}}

#endif

#endif // BOOST_MPL_LAMBDA_FWD_HPP_INCLUDED

/* lambda_fwd.hpp
OYZreBbfYAp3cgIj9/aTeSrTOJ0ZXMKzuYpT+BjP4WZewM94IUtV9LvIZryYLXkJz+BlnMKFvIWL+Bav43u8ngdXch/HFryJk7mE6byTt/P3vI/3cDVX8gU+wLf5B37Fh/k9H2ExF9arWY1r2Jxr2YZPcACf5FncwFl8io9zI9fzGT7DZ/kN/8hSVXTxyQp8kdW5mXX4EtvxFXbgFnbjNp7F13gZ/8RFfIO3cDvv5g52r6a8
*/