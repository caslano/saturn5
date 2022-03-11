
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