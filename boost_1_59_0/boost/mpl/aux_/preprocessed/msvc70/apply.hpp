
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

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
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

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
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

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
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

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
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

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
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

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
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
*/