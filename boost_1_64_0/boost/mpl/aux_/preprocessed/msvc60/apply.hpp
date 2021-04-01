
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
H43BDl/s5+ySPxgzP3ApHXaJk96WZaGtg0C+essQQbFuU6FASsyR6ZTRzxMsPSQvlsylS7+sv9iOfID0SmDeI+tj4H0hqO+b4E75HEsCNu2GZv/dQ/YumqVwGpRwVf75fTushOJWcbTvmFCBXbfsxaN3mmpwjZRtvj2YvrBq3L9a5VuO5HtZ1Dg//XGWXZj+nxkRB/Zgoel/+E+6RKwuCj2inIRN7Z/ylBDjjXhk12pivvisSljDIzfIJLdOqW9yrKNLAgbB3VIEbqduvd3K590XOE0obcUbTH8EI9OrUxgZOgDkUz9oVxAOlppk08lPV5q4E3jP3MmCb2uMdvkdTRH9UQs8j+XX/hryLmmZiv6fFwY0b0JZSiWpQTbKf931fGYcx4uYnBePSO8MzC8Xy/I0gqV+5LIEISASgSvbMd6p2pk/ENZOeSNjfBMZxtDyNhSrw479fJ5pfJnHCgNYCFAsxAXVBITQ7vLILMGW5BOBWGBU1325lc062G4LAji06ZIM9i/iLbhqxshMqmjij7GLPq1n/ftAP/fzIn7G5sIlgpoAfjY2pz62ig==
*/