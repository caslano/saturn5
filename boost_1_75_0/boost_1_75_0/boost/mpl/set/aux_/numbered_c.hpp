
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

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

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_C_TAIL(set, i_, T, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)< \
          T BOOST_PP_ENUM_TRAILING_PARAMS(i_, C) \
        > \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)
    : s_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_SET_C_TAIL(set,BOOST_PP_DEC(i_), T, C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c) type;
};

#   undef AUX778076_SET_C_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
CTnJ1jGE7V92DMmekgjqKBJbUHLZlxnGletRT5I9tZh0GRc15BO7zKBSFQTf1ZjZBFAIlLBHaJkORUhxyUxOMnVYgD5+/vVpkADliwSjzOCkYMxfPzRHFDH4bOjNowr2vv54yDoV5hfMzeRpyCUlRDt8X/FKmpOYTVV/7RK4MOMSKFVQeZJqJFc5CYpyaqMVfCGYAA6X3eh7IyjAJEdPjT8Jd2oAldo+AVKVQ5iBS9gUSSGztF2pK1uhj/INc87Z+EATZiEUH79zAV9yLCEYyhJcY3hFEB3ZO/s8tzPWuUeXH6tbjfKGuLbVC8AMu+7EJkDUIfLD5Dpbq0a8RvyeodRLiP4oIPT0MhdY9IK3oqiEvP5LQIhP6Djb94MSQvzi9IieolLnd40JqZUwzy7UB3P7tpcAK50Afnfns3B18QPj/kh3iSmN5CnIy6l5bXZ2mIu14cYv1nsx3XDtU8uXpa/u6KvdC3Xk4p+E9aLx7wk0viUCe09KB05aEcqAGLunl+7lzSt8v/TnVMTx6L9HUivY4VZHnSOe3Z+gqV3Zs/mku1crqjgEUZIsszaGABFdQ23RqWoorv1w/qgU4s6wn1l5UtVMMgzNr2h7m2ipTIEvjk9hza/zzZMs4KAh3pHB7PSrU8Z72pLJsfPFAlCT2OP66K3SrcKz5TOBXzo0qFMM9h3wZFTTy7GmtGWN1CH6YiXsl9wptUkXUjmN
*/