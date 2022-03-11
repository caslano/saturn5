
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