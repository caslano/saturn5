
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
tQ//si1R5tjSed4DQJLp7VaqvC8hOB/MFut0vhQDh71crFJOZkDwB/wcM7LOuRd27kVxHDsLfSJ2QaHfE/dO1Qe2VXEEJxhkYbEFW2LXMSilgU9EBb4ptSWQfZdLEE2rrc50PWE0YNDVP4+Mx2baWAH/sfTYLzIneNxQberArq354GO6Ws8X796pkQJu+a3H5sVlNoJ1pTJqznqn7py0Z6fQqbpoJHke80jVlVPCL0T59Zr8BVBLAwQKAAAACAAtZ0pST9Q9bNUBAABZCAAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI1VVQFAAG2SCRg7Vbfa9swEH4X+H+4deSl4GnpDwZGGEopSyEsIXH7rslnW8SWjKQ1zX+/s5UmDXveloeCsX3S3fd9OukOiYA+KOkxZ0KbytJng7utdaXP2awoluMLvj8UrLJta7etVTJoa1iadvI1dVhq55ngxyjBI9BnWKN7QZd6XSITDvt2R7OlDDJC8+mXKVx/nULRaA/0SNiidqWFgK8BOvRe1sgiSgaD0tSPBq/kBtl8LyWDAZOPBPzqlt1bE9CEdI6mDk0G11fDkEEVnVVrPTK2GpTTGATiaxC87BCeVnOQtdTmEy0jKh0FqwbV5hxUfyj4UHAeCmJ9
*/