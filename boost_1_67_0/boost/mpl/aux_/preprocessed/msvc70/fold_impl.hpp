
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