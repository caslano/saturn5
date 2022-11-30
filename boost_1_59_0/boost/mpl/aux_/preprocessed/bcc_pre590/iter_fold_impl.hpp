
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "iter_fold_impl.hpp" header
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
struct iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< 0,First,Last,State,ForwardOp >
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
struct iter_fold_impl< 1,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
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
struct iter_fold_impl< 2,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
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
struct iter_fold_impl< 3,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
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
struct iter_fold_impl< 4,First,Last,State,ForwardOp >
{
    typedef First iter0;
    typedef State state0;
    typedef typename apply2< ForwardOp,state0,iter0 >::type state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,state1,iter1 >::type state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,state2,iter2 >::type state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,state3,iter3 >::type state4;
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
struct iter_fold_impl
{
    typedef iter_fold_impl<
          4
        , First
        , Last
        , State
        , ForwardOp
        > chunk_;

    typedef iter_fold_impl<
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
struct iter_fold_impl< -1,First,Last,State,ForwardOp >
    : iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , ForwardOp
        >
{
};

template<
      typename Last
    , typename State
    , typename ForwardOp
    >
struct iter_fold_impl< -1,Last,Last,State,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* iter_fold_impl.hpp
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
*/