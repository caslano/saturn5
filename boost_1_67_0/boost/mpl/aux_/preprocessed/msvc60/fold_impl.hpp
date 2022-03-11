
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