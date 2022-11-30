
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
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
*/