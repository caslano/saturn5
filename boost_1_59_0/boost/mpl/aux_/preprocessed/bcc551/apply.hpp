
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
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