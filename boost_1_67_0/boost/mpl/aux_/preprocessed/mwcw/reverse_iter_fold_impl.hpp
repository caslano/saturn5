
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/reverse_iter_fold_impl.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

/// forward declaration

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl;

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 0,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef fwd_state0 bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter0 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    

    typedef fwd_state1 bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    typedef bkwd_state0 state;
    typedef iter1 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 2,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    

    typedef fwd_state2 bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter2 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 3,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    

    typedef fwd_state3 bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter3 iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< 4,First,Last,State,BackwardOp,ForwardOp >
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef fwd_state4 bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef iter4 iterator;
};

template<
      long N
    , typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl
{
    typedef First iter0;
    typedef State fwd_state0;
    typedef typename apply2< ForwardOp,fwd_state0,iter0 >::type fwd_state1;
    typedef typename mpl::next<iter0>::type iter1;
    typedef typename apply2< ForwardOp,fwd_state1,iter1 >::type fwd_state2;
    typedef typename mpl::next<iter1>::type iter2;
    typedef typename apply2< ForwardOp,fwd_state2,iter2 >::type fwd_state3;
    typedef typename mpl::next<iter2>::type iter3;
    typedef typename apply2< ForwardOp,fwd_state3,iter3 >::type fwd_state4;
    typedef typename mpl::next<iter3>::type iter4;
    

    typedef reverse_iter_fold_impl<
          ( (N - 4) < 0 ? 0 : N - 4 )
        , iter4
        , Last
        , fwd_state4
        , BackwardOp
        , ForwardOp
        > nested_chunk;

    typedef typename nested_chunk::state bkwd_state4;
    typedef typename apply2< BackwardOp,bkwd_state4,iter3 >::type bkwd_state3;
    typedef typename apply2< BackwardOp,bkwd_state3,iter2 >::type bkwd_state2;
    typedef typename apply2< BackwardOp,bkwd_state2,iter1 >::type bkwd_state1;
    typedef typename apply2< BackwardOp,bkwd_state1,iter0 >::type bkwd_state0;
    

    typedef bkwd_state0 state;
    typedef typename nested_chunk::iterator iterator;
};

template<
      typename First
    , typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,First,Last,State,BackwardOp,ForwardOp >
{
    typedef reverse_iter_fold_impl<
          -1
        , typename mpl::next<First>::type
        , Last
        , typename apply2< ForwardOp,State,First >::type
        , BackwardOp
        , ForwardOp
        > nested_step;

    typedef typename apply2<
          BackwardOp
        , typename nested_step::state
        , First
        >::type state;

    typedef typename nested_step::iterator iterator;
};

template<
      typename Last
    , typename State
    , typename BackwardOp
    , typename ForwardOp
    >
struct reverse_iter_fold_impl< -1,Last,Last,State,BackwardOp,ForwardOp >
{
    typedef State state;
    typedef Last iterator;
};

}}}

/* reverse_iter_fold_impl.hpp
+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
*/