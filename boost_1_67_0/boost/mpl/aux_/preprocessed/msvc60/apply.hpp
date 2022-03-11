
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

{
    typedef typename apply_wrap0<
          typename lambda<F>::type
       
        >::type type;

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

{
    typedef typename apply_wrap1<
          typename lambda<F>::type
        , T1
        >::type type;

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

{
    typedef typename apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >::type type;

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

{
    typedef typename apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >::type type;

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

{
    typedef typename apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >::type type;

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

{
    typedef typename apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >::type type;

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