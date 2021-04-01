
#ifndef BOOST_MPL_ERASE_KEY_HPP_INCLUDED
#define BOOST_MPL_ERASE_KEY_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct erase_key
    : erase_key_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Key >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,erase_key,(Sequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2,erase_key)

}}

#endif // BOOST_MPL_ERASE_KEY_HPP_INCLUDED

/* erase_key.hpp
+DvAqBo+B8IfoqeJumtu0BUNoyDvs7QHCSiomfDPPdNevg375V7JoWbm73r0132Rbp0+mH2YvGgdkKMBeQ5b/UiL9lABxd06ssXs8ENWn2VP7t1On7FMWM16r4qoP8mpJSFiIYebfQgUhN8LaicqjtxvUqUA8X1F6yJ5KoVsW1JX7OKFIASQtX/1soL9PZJzDSplJHjwM0xgheOrPv//yO1ME2pVnBOPRZ6ZvtKTgG/y3e5jMcW84LKISdCh8ZnUqHtZCf+RBrG6ZEEVI998ZtiWldTaHEETLe/3XjHhoFXP2pql3oZTMup3DIfyqqKMnysyE45O8cHlGFQCWJDyYFMDSeLKp23YglZk8I3BgI6hED24ePoUiEkUXmciOcbX5vnhFu/jBCuDBxdk7prKPPZGm0ABqk5TBYXZ01noWnoJyVRJghvRcTbCtcC/vpoPTZFofiGmjj5tqshstXazZtAOEGDfNZ8latktPojWWOCwLTrjJK3v9ap+1VsuJH+YU8ANbrQz5WFPSZmFzVgbGeg4x9H8p8fEIzoLKBnLaSe+79Or7uGxqkYBjg==
*/