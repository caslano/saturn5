
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