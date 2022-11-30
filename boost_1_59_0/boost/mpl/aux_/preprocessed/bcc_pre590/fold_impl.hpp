
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