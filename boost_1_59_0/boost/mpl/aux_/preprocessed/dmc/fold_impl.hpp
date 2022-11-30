
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