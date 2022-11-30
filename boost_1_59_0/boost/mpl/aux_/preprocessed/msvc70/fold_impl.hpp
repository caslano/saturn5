
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