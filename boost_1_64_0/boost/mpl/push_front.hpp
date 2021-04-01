
#ifndef BOOST_MPL_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/push_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_front
    : push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_front,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_front
    : has_push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(2, push_front)
BOOST_MPL_AUX_NA_SPEC(1, has_push_front)

}}

#endif // BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
ioSNUc9zUuQwPledeAtWovdMOv5yLeixJuiMrQiByAFYTN8SwdeLKsA0ZNWbwT0UyMfwzv5/N26XRL3E0bnFvqJDmInu5UPsuUcf+2TsvsvtaMzy2nufPJNZeFLLQQWVYrQT1PCLQXMZXEGlB971o0KFSIWiCPMzugYbcAbgiw0NTo5jL94qts+4Fm13o/OzvmbWuyOHkh8C1cIH6g6Kut0ztlnQZf9A8Pf1NDZI8pRsvBMTFzc8QHJy9nNfMJ0h7K5Hz2ijHrBcMB5TfInfLM+Ss41iXsNXNl5j7XQ9inOzgQe3uBmZil6AN9UQFnBg+XapGaGC8G7HjGpemjrNET8Lf9R3/LTOXS0se+AWcOZg82rHxLS4bdodM8Xv3JYMWXQgDgVnap3hmAvt4ysgQ6FGag5jJRUJzk4j4Zb8x8MH33qITFYdC7v4CY9cPzooZJEEwDuHq85/h/2Pr2WIXu7k4YRW6kjHwiJ6ggqcg7cMx19AemuUN4+Z4gVOR7v22k2t3Z0gFbuwMhlxtKOdyYQBydIstXl3deLB8aryI/IWfka8SFcX6JduyA==
*/