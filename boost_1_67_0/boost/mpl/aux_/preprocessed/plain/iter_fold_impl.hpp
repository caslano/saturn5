
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