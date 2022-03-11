
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