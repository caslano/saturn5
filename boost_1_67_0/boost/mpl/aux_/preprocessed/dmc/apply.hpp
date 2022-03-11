
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