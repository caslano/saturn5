
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