
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