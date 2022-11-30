
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