
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