
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