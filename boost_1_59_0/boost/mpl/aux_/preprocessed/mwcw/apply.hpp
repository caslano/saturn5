
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
+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
*/