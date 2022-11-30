
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