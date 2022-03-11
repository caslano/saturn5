
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