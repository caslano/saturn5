
#ifndef BOOST_MPL_EVAL_IF_HPP_INCLUDED
#define BOOST_MPL_EVAL_IF_HPP_INCLUDED

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

#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(C)
    , typename BOOST_MPL_AUX_NA_PARAM(F1)
    , typename BOOST_MPL_AUX_NA_PARAM(F2)
    >
struct eval_if
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_<C,F1,F2>::type
{
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,eval_if,(C,F1,F2))
};

// (almost) copy & paste in order to save one more
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct eval_if_c
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_c<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_c<C,F1,F2>::type
{
#endif
};

BOOST_MPL_AUX_NA_SPEC(3, eval_if)

}}

#endif // BOOST_MPL_EVAL_IF_HPP_INCLUDED

/* eval_if.hpp
tNBoiFMe3QndTBhrkIEuFANw+Flph7BIkgi8BcoVQVcrWsXJy2u4fI6Bqx08qOb1VYmZkDtUVDlkCznRkVVvCUnWFjNR6O1oMnnkX20spFElHy5GAvxK0Xt9QuBaUKDZU+6ZbAkZdNbFgE2+o9O7uvVGOULTJ3CV8UAWUlseCyRtDZw15bYiSJ3yuTZ7IU+XnSyIzlmX2ozFhyx/F0pPGW/61WEYDdsHtjUXu3icTuFhLP5oTY/NFKkGHl7YTfS0/k9yfEfF80X4FvZBn+ZYYp/dxOG6T1Y815bjEV8PJYOuBc0Yfu7XN1BLAwQKAAAACAAtZ0pS7LsvEB4CAADOAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE1NlVUBQABtkgkYLVTYWvbMBD9LvB/ODICbcFRkq1b57mB0BVSGG1o3H5X5XMl6kieJCd1f/1OdpsM9nlgZMt+9969p3Me0AcpPC5Yrk1l6faC3d660i/YqijW/QLrh4KlqTCdaINiOT9icj6UsU+wQbdDl3pdIssdNnVHn0sRxMDEZ5MZzKdTuLWwJBrr9JsI2hq4x9+tdliC33tZW48JG7gyWDZCKqTSz5P5Nzj5Kdxem1NYr9b8y2Q2mSfsypqAJqRF12AGAV8D
*/