
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