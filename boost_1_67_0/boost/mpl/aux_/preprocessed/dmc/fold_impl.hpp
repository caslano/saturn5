
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