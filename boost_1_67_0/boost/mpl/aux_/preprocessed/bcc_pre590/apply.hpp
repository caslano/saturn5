
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