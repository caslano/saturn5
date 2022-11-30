
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