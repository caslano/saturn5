
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