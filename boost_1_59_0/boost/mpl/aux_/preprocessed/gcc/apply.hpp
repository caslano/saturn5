
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