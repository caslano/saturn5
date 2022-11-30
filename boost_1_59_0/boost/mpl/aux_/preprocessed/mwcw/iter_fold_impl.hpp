
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