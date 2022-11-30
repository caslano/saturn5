
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
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
*/