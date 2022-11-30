
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