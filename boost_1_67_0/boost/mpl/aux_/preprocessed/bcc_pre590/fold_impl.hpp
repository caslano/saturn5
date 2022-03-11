
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