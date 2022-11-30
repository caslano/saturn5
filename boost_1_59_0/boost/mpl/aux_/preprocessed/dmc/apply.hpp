
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