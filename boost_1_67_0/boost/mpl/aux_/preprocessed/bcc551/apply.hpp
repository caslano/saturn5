
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