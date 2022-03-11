
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