
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