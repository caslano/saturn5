
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