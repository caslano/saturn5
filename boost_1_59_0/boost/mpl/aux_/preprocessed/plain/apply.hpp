
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