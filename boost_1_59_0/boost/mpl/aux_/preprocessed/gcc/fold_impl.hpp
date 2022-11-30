
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