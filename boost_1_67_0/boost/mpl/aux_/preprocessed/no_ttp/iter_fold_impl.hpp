
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