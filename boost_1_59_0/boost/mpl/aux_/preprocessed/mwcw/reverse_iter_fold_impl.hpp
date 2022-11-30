
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