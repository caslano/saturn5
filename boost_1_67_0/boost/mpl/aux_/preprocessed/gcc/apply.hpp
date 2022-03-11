
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