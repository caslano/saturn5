
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