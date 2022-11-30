
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