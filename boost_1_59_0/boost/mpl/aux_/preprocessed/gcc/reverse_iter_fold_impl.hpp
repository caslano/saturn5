
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