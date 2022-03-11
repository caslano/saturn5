
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