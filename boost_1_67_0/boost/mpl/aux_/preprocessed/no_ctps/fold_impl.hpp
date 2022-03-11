
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