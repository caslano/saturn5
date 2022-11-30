
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/iter_fold_impl.hpp" header
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