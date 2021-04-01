
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl;

template< int N >
struct fold_chunk;

template<> struct fold_chunk<0>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef state0 state;
        typedef iter0 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<1>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        

        typedef state1 state;
        typedef iter1 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<2>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        

        typedef state2 state;
        typedef iter2 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<3>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        

        typedef state3 state;
        typedef iter3 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<> struct fold_chunk<4>
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef First iter0;
        typedef State state0;
        typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
        typedef typename mpl::next<iter0>::type iter1;
        typedef typename apply2< ForwardOp, state1, typename deref<iter1>::type >::type state2;
        typedef typename mpl::next<iter1>::type iter2;
        typedef typename apply2< ForwardOp, state2, typename deref<iter2>::type >::type state3;
        typedef typename mpl::next<iter2>::type iter3;
        typedef typename apply2< ForwardOp, state3, typename deref<iter3>::type >::type state4;
        typedef typename mpl::next<iter3>::type iter4;
        

        typedef state4 state;
        typedef iter4 iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template< int N >
struct fold_chunk
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef fold_impl<
              4
            , First
            , Last
            , State
            , ForwardOp
            > chunk_;

        typedef fold_impl<
              ( (N - 4) < 0 ? 0 : N - 4 )
            , typename chunk_::iterator
            , Last
            , typename chunk_::state
            , ForwardOp
            > res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step;

template<
      typename Last
    , typename State
    >
struct fold_null_step
{
    typedef Last iterator;
    typedef State state;
};

template<>
struct fold_chunk< -1 >
{
    template<
          typename First
        , typename Last
        , typename State
        , typename ForwardOp
        >
    struct result_
    {
        typedef typename if_<
              typename is_same< First,Last >::type
            , fold_null_step< Last,State >
            , fold_step< First,Last,State,ForwardOp >
            >::type res_;

        typedef typename res_::state state;
        typedef typename res_::iterator iterator;
    };

    /// ETI workaround
    template<> struct result_< int,int,int,int >
    {
        typedef int state;
        typedef int iterator;
    };

};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_step
{
    typedef fold_chunk< -1 >::template result_<
          typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        > chunk_;

    typedef typename chunk_::state state;
    typedef typename chunk_::iterator iterator;
};

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
    : fold_chunk<N>
        ::template result_< First,Last,State,ForwardOp >
{
};

}}}

/* fold_impl.hpp
Sqt2Ve11UIAhtOYqC1mYG/wrEpi8RMeC8Vy3VKU/GYECzfjve8F8sNpkLHDpkTRil0oAaMU6blL0oYvkf3Jz5tT9Z/4ldQvLBLGJDGV9bWuuD3Hiu8eqlQpRKDrxEeiPWNjoQxBx2Rafzqcv9sUDasvVIF1IP2vwNt7aQLb3ctzhssVdnyFJFq8B3SPDRLbcLz+h645kvk7AlzwcDZ8ou3J8ufwW5HSCy6P2CmYvEYdP6f1UW42QKdAohC6/c0pRT8lyihn4Rp0GLL+V3z9yNlqX1TvURTLBUNgyWF/lH734z8L9todwhTZzt/5Ce8pE2GPWhOai94iwmu5zqj8H70KIYegIe8C4jS0oPuLLggZhXnvHJjn7NTKko46oSPeG5q5HyzKAFrfNFOYWHQgqZdVGzs2/1Mxf3nWnHba5zlvtz6/99h0Ws8o7U+e/4Eu9fdubdFhl+oByM77UiG3bLdwQk/8hPnq1e5by33IKbWWUHSZRzljp5Fvx1pMFKBGpn4VAE7N2oFTaakV8Efmo6TTQvaOiXTg6eR7g70RBVW2lKYfDmhcNu+MIpw==
*/