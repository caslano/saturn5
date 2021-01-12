
#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/contains_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED

/* contains.hpp
j9VwGlbHmVgbV2IdXIv18QNsgB9iQzyOgXgSm+BVDMLfsDkq9a0tsAK2xkYYjE2wA7bHThiNXXA0dkX7cSrvBY10sV+fJJ4vDsMqOBzr4UhsiTrsg1EYjqPQVg+YL8tNdFEPOEae28ViNYyT5RqwH8bjEEzAkWjEKBwvy/cpZHu3g2uXHDfVCV5y3PxCvMp4FWvirxiAv0m6r2EnvI7d8CZG4L8xFu/geCxclOs1FsOTWALP
*/