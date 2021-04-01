
#ifndef BOOST_MPL_DISTANCE_HPP_INCLUDED
#define BOOST_MPL_DISTANCE_HPP_INCLUDED

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

#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>


namespace boost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag > struct distance_impl
{
    template< typename First, typename Last > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::msvc_eti_base< typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type >
    {
#else
    {
        typedef typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type type;
        
        BOOST_STATIC_CONSTANT(long, value =
              (iter_fold<
                  iterator_range<First,Last>
                , mpl::long_<0>
                , next<>
                >::type::value)
            );
#endif
    };
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct distance
    : distance_impl< typename tag<First>::type >
        ::template apply<First, Last>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, distance, (First, Last))
};

BOOST_MPL_AUX_NA_SPEC(2, distance)

}}

#endif // BOOST_MPL_DISTANCE_HPP_INCLUDED

/* distance.hpp
/SMX85OHLswtqvUzL/2olYRpat6OU5440FcwU06QA3wdo7DpNydu3xfqqqAOukFG97P+hg/a5hLUPp/vBub8vHRFDC/mNWFLYGwVAFSXx2OKJqgMaFGGpUAoceePJ8/m4lr4sjincl7M8HY2o8AT5zXQZjTWbBnCkZpLqceMPiX3Np4pvPjICdzsvelddAsWf44mVn/AA+OykwFZ0g38pECWGt+xKrVLn2Y7y38IHeCJ/3L9f2kTVfXKG+j/5LXakO5bFaROsq/4Nb/FcrjFC4ETIVKm/J0SMYWqI6hjdByKf1z0F8zXDcQuDV48W4MKL5DHWG1vt80RUVSwCHQwly6g33vuig7bKY5HR5bFRFd2+40ZgUH3+MkD3RGZK1OmdH1vYvwuz6vni26l4HkWyKKdxnHBv4lZYqppJvlDIjkfNlQr29J/Du1cyi118uisE2z0Grz7Stui1r5Cs5XicguOVhjUu3oiYp0Rt4COdtdgI9s9pPUErTt5ArFB9yuxw6NcPF7Gloz1r6fAITNyUPFAu5YQWUEYA7tQAY2mUG1Ud86TUvfsb+JdVQ==
*/