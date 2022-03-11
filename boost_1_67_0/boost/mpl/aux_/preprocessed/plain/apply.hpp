
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