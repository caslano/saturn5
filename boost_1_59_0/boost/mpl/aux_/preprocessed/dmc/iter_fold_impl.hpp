
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