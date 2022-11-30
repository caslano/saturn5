
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 0,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp, state0, typename deref<iter0>::type >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef state1 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 2,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 3,First,Last,State,ForwardOp >
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< 4,First,Last,State,ForwardOp >
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

template<
      int N
    , typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl
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

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,First,Last,State,ForwardOp >
    : fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2<ForwardOp,State, typename deref<First>::type>::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* fold_impl.hpp
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
*/