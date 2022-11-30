
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "fold_impl.hpp" header
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