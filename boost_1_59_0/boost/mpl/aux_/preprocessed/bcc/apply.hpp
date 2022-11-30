
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
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
*/