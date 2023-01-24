
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
TIGchp0TiNNby6h6iVRxAVcXfU5MOdKgb+1GMFBEm4hbRzSe5NrtW8rDOu1uXDpR6G64qyoNf06SMblx/vF1A3Vnh0ycoolUHUtwS2scyql9DSrEEmdyl/M+VT91fYKV+hoJm5xMbPDlMnCF//bOvMhTmWAFqSu3F4PiBpn+amRpD21+fvEdMeVobho3SyRcUV92nfvUy+KZk97cGc5hpGrYPqtWlvmohaOgEFqaqLskH0kcde70lHuxOaSevuO90NBX0vPRE3BLntuGLFduUWcw+IeDKb2k7gtS2kcYppZWdQ3CH0hOd0achDzslVCGd9jnrlyPQiDpHDFsqNOPrDhG78H2tTq1pKSHjQ0ursVfzy/a/Z4oERAHYsE9WjatLVZsa9FXVTAiW7D4y1yAU7xQSpBG2XkGDf4BLek9ArDggYKmCK1uqJtHGYpN9lLYR+e3GHFvV9bjzPiRb80v2TYHOvQuf5oSWizwLeNsPOJP1V18hAbY+keT9+UR1U/PWgoYj5+fhQckpRdQAojubwIyGD2dmgjnFY1Udb164sPZrGla6AlD/fCDP4yc2CjR/npXWSwmauXcFduaz/cN80WpnjYTJ7pWXdBGJI+V/3N4oraW6TvjA48FwlBknAr5jJsmuy4yAb4am+cFzcbMcG5W6tjuqpyZyhkczJlAPqEuZja+U1cAtrNyoVc66kGdaxXDpSaAnGLDkZti
*/